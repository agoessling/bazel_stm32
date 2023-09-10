load("//third_party:stm32cubef7.bzl", "hal_library")

cc_binary(
    name = "main.elf",
    srcs = [
        "interrupts.cc",
        "main.cc",
        "startup.c",
        ":hal_source",
    ],
    linkopts = [
        "-T $(execpath :stm32f746nghx.ld)",
        # Disable linker warning about load segment being RWX.  This occurs because .init_array and
        # .fini_array input sections are emitted as RWX but are stored in flash (RX).
        "-Wl,--no-warn-rwx-segments",
        "-lstdc++",  # remove when toolchain is updated.
    ],
    target_compatible_with = [
        "@bazel_arm_toolchains//platforms/cpu:cortex-m7+nofp.dp",
        "@platforms//os:none",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":hal_include",
        ":stm32f746nghx.ld",
    ],
)

cc_library(
    name = "hal_conf",
    hdrs = ["stm32f7xx_hal_conf.h"],
    includes = ["."],
    visibility = ["//visibility:private"],
)

hal_library(
    name = "hal",
    device = "STM32F746xx",
    hal_config_lib = ":hal_conf",
    hse_value = 25000000,
    msp_file = "stm32f7xx_hal_msp.c",
    visibility = ["//visibility:private"],
)
