#include "./move_const.h"
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
    const auto s2 = MyStruct(move_const(s));

    // use s2 somewhere
    return int(s2.value.size());
}
