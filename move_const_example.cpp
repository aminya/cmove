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