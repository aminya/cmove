#include <string>
#include "move_const.h"

struct S
{
    S() = default;
    ~S() = default;

    S(S const&) = default;
    S(S&&) = default;
    S& operator=(S const&) = default;
    S& operator=(S&&) = default;

    std::string s = "Hello World im long string string string";
};

int main()
{
    const S s;
    S s2(move_const(s));
}
