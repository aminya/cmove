# cmove

Move const values in C++

Performance and const-correctness are now friends! :tada: :rocket:

### Description

This header only library allows you to move `const` values.

**Note**: you should move a const value only if you are sure that the target does not modify the object

### Why?

This allows making your programs const-correct without being worried about extra copies.

`const` in C++ is scoped, and it is not equivalent to `immutable`. The standard does not provide any language feature that allows the developers to mark a function as `immutable`. So, the library writers usually only provide `f(T && arg)` and `f(T const & arg)` overloads, and they do not provide `f(T const && arg)`. This results in extra copies while the function is not necessarily `mutating`.

Using `cmove` allows following core guidelines without being worried about performance.
https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#con1-by-default-make-objects-immutable

### Example

Run it online: https://cpp.godbolt.org/z/daGKT3P3G

```cpp
#include "./cmove.h"
#include <string>

struct MyStruct
{
    std::string value;
};

int main() {
    const auto s = MyStruct{ "Hello World im long string string string" };

    // ...
    // s is const for you here
    // ...
    // error:
    // s.value = "changed value";

    // you don't need s anymore, so you can move it to s2 without copying
    const auto s2 = MyStruct(cmove(s));

    // use s2 somewhere
    return int(s2.value.size());
}
```
