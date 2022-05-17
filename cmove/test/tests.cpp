#include <catch2/catch.hpp>
#include <string>
#include <fmt/core.h>
#include <utility>
#include <cmove/lib.hpp>

TEST_CASE("cmove const to a constuctor-less struct") {
  struct Str {
    std::string value;
  };
  const auto my_struct_1 = Str{"Hello World im long string string string"};
  const auto my_struct_2 = Str{cmove::cmove(my_struct_1)};
  fmt::print("{}", my_struct_2.value);
}

TEST_CASE("cmove const to a const& constructor") {
  struct Str {
    std::string value;
    explicit Str(const std::string &value_in) : value{value_in} { // NOLINT
    }
  };
  const auto my_struct_1 = Str{"Hello World im long string string string"};
  const auto my_struct_2 = Str(cmove::cmove(my_struct_1));
  fmt::print("{}", my_struct_2.value);
}

TEST_CASE("cmove const to a value/move constructor") {
  struct Str {
    std::string value;
    explicit Str(std::string value_in) : value{std::move(value_in)} { // NOLINT
    }
  };
  const auto my_struct_1 = Str{"Hello World im long string string string"};
  const auto my_struct_2 = Str(cmove::cmove(my_struct_1));
  fmt::print("{}", my_struct_2.value);
}

TEST_CASE("cmove const to a value/cmove constructor") {
  struct Str {
    std::string value;
    explicit Str(std::string value_in) : value{cmove::cmove(value_in)} { // NOLINT
    }
  };
  const auto my_struct_1 = Str{"Hello World im long string string string"};
  const auto my_struct_2 = Str(cmove::cmove(my_struct_1));
  fmt::print("{}", my_struct_2.value);
}

TEST_CASE("cmove const to a && constructor") {
  struct Str {
    std::string value;
    explicit Str(const std::string &value_in) : value{value_in} {
    }
    explicit Str(std::string &&value_in) : value{std::move(value_in)} {
    }
  };
  const auto my_struct_1 = Str{"Hello World im long string string string"};
  const auto my_struct_2 = Str(cmove::cmove(my_struct_1));
  fmt::print("{}", my_struct_2.value);
}