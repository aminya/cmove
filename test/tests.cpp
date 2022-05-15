#include <catch2/catch.hpp>
#include <cmove/lib.hpp>

struct MyStruct {
  std::string value;
};

TEST_CASE("cmove::cmove") {
  const auto s = MyStruct{"Hello World im long string string string"};

  // ...
  // s is const for you here
  // ...
  // error:
  // s.value = "changed value";

  // you don't need s anymore, so you can move it to s2 without copying
  const auto s2 = MyStruct(cmove::cmove(s));

  // use s2 somewhere
  return int(s2.value.size());
}
