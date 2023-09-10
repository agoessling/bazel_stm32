def freertos_port(name, portable_path, **kwargs):
    full_path = "FreeRTOS/Source/portable/{}/".format(portable_path)

    native.cc_library(
        name = name + "_include",
        hdrs = native.glob([full_path + "*.h"], allow_empty = False),
        includes = [full_path],
        **kwargs
    )

    native.filegroup(
        name = name + "_source",
        srcs = (
            native.glob([full_path + "*.c"], allow_empty = False) +
            native.glob([full_path + "*.S"], allow_empty = True)
        ),
        **kwargs
    )

def freertos_library(name, port, freertos_config_lib, heap = None, **kwargs):
    """ Creates FreeRTOS library specific to project.

    This exports two targets {name}_include and {name}_source.  The include target should be added
    to the binary's deps.  The souce target should be added to the binary's srcs.

    Args:
      name: Name used as prefix for include and source targets.
      port: Name of port (see freertos.BUILD).
      freertos_config_lib: Library which exposes "FreeRTOSConfig.h" and can be imported without
          prefix (e.g. #include "FreeRTOSConfig.h") from external libraries.
      heap: Name of FreeRTOS heap manager to use (e.g. "heap_4") or None.

    The reason this isn't a single cc_library is because of the use of weak references to
    incorporate the port's ISRs.  Weak references don't work when objects are bundled into static
    libraries (as is the case with cc_library).  Therefore, the final binary must link each
    individual object file.  Hence the need to include the HAL sources in the binary's srcs.
    """
    if heap == None:
        heap_srcs = []
    else:
        heap_srcs = ["@freertos//:{}".format(heap)]

    native.cc_library(
        name = name + "_include",
        deps = [
            freertos_config_lib,
            "@freertos//:common_include",
            "@freertos//:{}_include".format(port),
        ],
        **kwargs
    )

    native.filegroup(
        name = name + "_source",
        srcs = [
            "@freertos//:common_source",
            "@freertos//:{}_source".format(port),
        ] + heap_srcs,
        **kwargs
    )
