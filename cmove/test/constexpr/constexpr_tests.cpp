#include <catch2/catch.hpp>
#include <string>
#include <fmt/core.h>
#include <cmove/lib.hpp>

struct MyStruct {
  double value;
};

TEST_CASE("cmove::cmove constexpr") {
  constexpr auto my_struct_1 = MyStruct{1000.0};

  // ...
  // s is const for you here
  // ...
  // error:
  // my_struct_1.value = "changed value";

  // you don't need s anymore, so you can move it to s2 without copying
  constexpr auto my_struct_2 = MyStruct(cmove::cmove(my_struct_1));

  // error:
  // my_struct_2.value = "changed value";

  // use my_struct_2 somewhere
  fmt::print("{}", my_struct_2.value);
}
