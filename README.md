# bazel_stm32

Example / template STM32 HAL projects built with [Bazel](https://bazel.build/) (using
[bazel_arm_toolchains](https://github.com/agoessling/bazel_arm_toolchains)).

In another life I've reimplemented the HAL, but couldn't bring myself to do it again (even if
open-source).  **But**, I still wanted to use Bazel with a sensible and documented startup
configuration. Hopefully these examples provide that.

`C` and `C++` projects are supported.

In particular, you might be interested in how the F7 HAL is incorporated into Bazel from ST's 
[STM32CubeF7 repo](https://github.com/STMicroelectronics/STM32CubeF7).  Some interesting aspects:

* `third_party/stm32cubef7.BUILD` -- BUILD file for external repo
* `third_party/stm32cubef7.bzl` -- `hal_library` macro for creating project specific HAL library
* `bare_metal/BUILD` -- Contains `//bare_metal:main.elf` showing how complete embedded target is
    built.

To build the `bare_metal` project:

```Shell
bazel build --config=m7 //bare_metal:main.elf
```
