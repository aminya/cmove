# move_const

 Move const values in C++

Performance and const-correctness are now friends! :tada: :rocket:

### Description

This header only library allows you to move `const` values.

**Note**: you should move a const value only if you are sure that the target function does not modify the object (it is non-mutating).

### Why?
This allows making your programs const-correct without being worried about extra copies.

`const` in C++ is scoped, and it is not equivalent to `immutable`. The standard does not provide any language feature that allows the developers to mark a function as `immutable`. So, the library writers usually only provide `f(T && arg)` and `f(T const & arg)` overloads, and they do not provide `f(T const && arg)`. This results in extra copies while the function is not necessarily `mutating`.

Using `move_const` allows following core guidelines without being worried about performance.
https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#con1-by-default-make-objects-immutable

### Example

Run it online: https://cpp.godbolt.org/z/h4Kn1a

```cpp
#include <string>
#include "move_const.h"

struct S
{
    std::string value;

    S() = default;
    ~S() = default;

    S(S const&) = default;
    S(S&&) = default;
    S& operator=(S const&) = default;
    S& operator=(S&&) = default;

};

int main()
{
    const auto s = S{"Hello World im long string string string"};

    // ...
    // s is const for you here
    // ...

    // you don't need s anymore, so you can move it to s2 without copying
    const auto s2 = S(move_const(s));
}
```
