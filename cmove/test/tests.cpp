#include <catch2/catch.hpp>
#include <string>
#include <fmt/core.h>
#include <cmove/lib.hpp>

struct MyStruct {
  std::string value;
};

TEST_CASE("cmove::cmove") {
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
