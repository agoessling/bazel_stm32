def hal_library(name, device, hal_config_lib, msp_file, hse_value = 25000000, **kwargs):
    """ Creates HAL library specific to project.

    This exports two targets {name}_include and {name}_source.  The include target should be added
    to the binary's deps.  The souce target should be added to the binary's srcs.

    Args:
      name: Name used as prefix for include and source targets.
      device: Stm32 device string used for selecting the correct HAL headers.
      hal_config_lib: Library which exposes "stm32f7xx_hal_conf.h" and can be imported without
          prefix (e.g. #include "stm32f7xx_hal_conf.h") from external libraries.
      msp_file: File containing overriding MSP functions. (e.g. HAL_MspInit())
      hse_value: Value of board HSE clock frequency.

    The reason this isn't a single cc_library is because of the HAL's use of weak references to
    incorporate the MSP's callbacks (e.g. HAL_MspInit()).  Weak references don't work when objects
    are bundled into static libraries (as is the case with cc_library).  Therefore, the final binary
    must link each individual object file.  Hence the need to include the HAL sources in the
    binary's srcs.
    """
    native.cc_library(
        name = name + "_include",
        deps = [
            hal_config_lib,
            "@stm32cubef7//:hal_header_lib",
            "@stm32cubef7//:cmsis_device",
            "@stm32cubef7//:cmsis_core",
        ],
        defines = [
            device,
            "HSE_VALUE={}".format(hse_value),
        ],
        **kwargs
    )

    native.filegroup(
        name = name + "_source",
        srcs = [
            msp_file,
            "//third_party:system_core_clock.c",
            "@stm32cubef7//:hal_source",
        ],
        **kwargs
    )
