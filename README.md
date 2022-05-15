# cmove

Move const values in C++

Performance and const-correctness are now friends! :tada: :rocket:

## Description

This header only library allows you to move `const` values.

### Why?

This allows making your programs const-correct without being worried about extra copies.

`const` in C++ is scoped, and it is not equivalent to `immutable`. The standard does not provide any language feature that allows the developers to mark a function as `immutable`. So, the library writers usually only provide `f(T && arg)` and `f(T const & arg)` overloads, and they do not provide `f(T const && arg)`. This results in extra copies while the function is not necessarily `mutating`.

Using `cmove` allows following core guidelines without being worried about performance.
https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#con1-by-default-make-objects-immutable

## Example

Run it online: https://cpp.godbolt.org/z/daGKT3P3G

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
  // s is const for you here
  // ...
  // error:
  // my_struct_1.value = "changed value";

  // you don't need s anymore, so you can move it to my_struct_2 without copying
  const auto my_struct_2 = MyStruct(cmove::cmove(my_struct_1));

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
FetchContent_Declare(_cmove URL https://github.com/aminya/cmove/archive/refs/heads/master.zip)
FetchContent_MakeAvailable(_cmove)
```

Then link it to your targets:
```
find_package(cmove CONFIG REQUIRED)
target_link_libraries(main PRIVATE  cmove::cmove)
```