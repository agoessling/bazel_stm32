load("@//third_party:freertos.bzl", "freertos_port")

cc_library(
    name = "common_include",
    hdrs = glob(["FreeRTOS/Source/include/*.h"], allow_empty = False),
    includes = ["FreeRTOS/Source/include"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "common_source",
    srcs = glob(["FreeRTOS/Source/*.c"], allow_empty = False),
    visibility = ["//visibility:public"],
)

[filegroup(
    name = "heap_{}".format(i),
    srcs = ["FreeRTOS/Source/portable/MemMang/heap_{}.c".format(i)],
    visibility = ["//visibility:public"],
) for i in range(1, 6)]

freertos_port(
    name = "gcc_cortex_m7",
    portable_path = "GCC/ARM_CM7/r0p1",
    visibility = ["//visibility:public"],
    target_compatible_with = select({
        "@bazel_arm_toolchains//platforms/cpu:cortex-m7+nofp.dp": [],
        "//conditions:default": ["@platforms//:incompatible"],
    }),
)
