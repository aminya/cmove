# cmove

Move const values in C++

Performance and const-correctness are now friends! :tada: :rocket:

[![ci](https://github.com/aminya/cmove/actions/workflows/ci.yml/badge.svg)](https://github.com/aminya/cmove/actions/workflows/ci.yml)

## Description

This header only library allows you to move `const` values.

### Why?

`cmove::cmove` allows for making your programs const-correct without being worried about extra copies.

As seen in [this link](https://cpp.godbolt.org/z/cnvvxbKcn), `cmove::cmove` generates a much smaller and faster code.

This also allows cleaning up the code, as you can remove your exessive constructor duplication. The following code will be efficient and clean with the help of `cmove::cmove`:
```cpp
struct MyStruct
{
    std::string value;
    MyStruct(std::string value_in): value(std::move(value_in)) {}
};
```
```cpp
const auto my_struct_1 = MyStruct{"Hello World im long string"};
MyStruct(cmove::cmove(my_struct_1))
```

Using `cmove` allows [the core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#con1-by-default-make-objects-immutable
) while increasing performance. This `cmove::cmove` behavior is similar to the Rust's move behavior.

## Example

Run it online: https://cpp.godbolt.org/z/Ynq5eTroE

```cpp
#include <cmove/lib.hpp>

#include <string>
#include <fmt/core.h>

struct MyStruct
{
    std::string value;
};

int main() {
  const auto my_struct_1 = MyStruct{"Hello World im long string string string"};

  // ...
  // my_struct_1 is const for you here
  // ...
  // error:
  // my_struct_1.value = "changed value";

  // you don't need my_struct_1 anymore, so you can move it to my_struct_2 without copying
  const auto my_struct_2 = MyStruct{cmove::cmove(my_struct_1)};

  // error:
  // my_struct_2.value = "changed value";

  // use my_struct_2 somewhere
  fmt::print("{}", my_struct_2.value);
}
```

## Usage in your project

cmove is a header-only library, so you can download and use the [header file](https://github.com/aminya/move_const/blob/c3f45d3445fde61dc0de3158af64252abd7a8c79/cmove/include/cmove/lib.hpp).

To automatically integrate it to your CMake project, add the following code to your CMake file:

```cmake
# https://github.com/aminya/cmove
include(FetchContent)
FetchContent_Declare(_cmove URL https://github.com/aminya/cmove/releases/download/v1.0.1/cmove-1.0.1.zip)
FetchContent_MakeAvailable(_cmove)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${_cmove_SOURCE_DIR})
```

Then link it to your targets:
```
find_package(cmove CONFIG REQUIRED)
target_link_libraries(main PRIVATE  cmove::cmove)
```