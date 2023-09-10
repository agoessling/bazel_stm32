workspace(name = "bazel_stm32")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# bazel_lint
http_archive(
    name = "bazel_lint",
    sha256 = "85b8cab2998fc7ce32294d6473276ba70eea06b0eef4bce47de5e45499e7096f",
    strip_prefix = "bazel_lint-0.1.1",
    url = "https://github.com/agoessling/bazel_lint/archive/v0.1.1.zip",
)

load("@bazel_lint//bazel_lint:bazel_lint_first_level_deps.bzl", "bazel_lint_first_level_deps")

bazel_lint_first_level_deps()

load("@bazel_lint//bazel_lint:bazel_lint_second_level_deps.bzl", "bazel_lint_second_level_deps")

bazel_lint_second_level_deps()

# stm32cubef7
http_archive(
    name = "stm32cubef7",
    build_file = "//third_party:stm32cubef7.BUILD",
    sha256 = "c8ede3e61aa2d47696e42edead53bcf3d8f3f2ae7e7a180ce001d19bbc397878",
    strip_prefix = "STM32CubeF7-1.17.1",
    url = "https://github.com/STMicroelectronics/STM32CubeF7/archive/refs/tags/v1.17.1.zip",
)

# bazel_arm_toolchains
http_archive(
    name = "bazel_arm_toolchains",
    strip_prefix = "bazel_arm_toolchains-0.1.1",
    sha256 = "9b097099d1818a4a6a629918a7f6fd672a45ef8c32109cfe3375e97ee5087d86",
    url = "https://github.com/agoessling/bazel_arm_toolchains/archive/v0.1.1.zip",
)

load("@bazel_arm_toolchains//toolchains:toolchains.bzl", "all_toolchain_deps")

all_toolchain_deps()

# freertos
http_archive(
    name = "freertos",
    build_file = "//third_party:freertos.BUILD",
    sha256 = "376037b763ae88543974c7c48f0febefa18bcd868e9a4e6aebaf7c9d3df31021",
    strip_prefix = "FreeRTOSv202212.01",
    url = "https://github.com/FreeRTOS/FreeRTOS/releases/download/202212.01/FreeRTOSv202212.01.zip",
)
