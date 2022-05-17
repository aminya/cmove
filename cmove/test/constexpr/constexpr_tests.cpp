#include <catch2/catch.hpp>
#include <string>
#include <fmt/core.h>
#include <utility>
#include <cmove/lib.hpp>

TEST_CASE("cmove const to a constuctor-less struct") {
  struct Str {
    double value;
  };
  constexpr auto my_struct_1 = Str{1000.0};
  constexpr auto my_struct_2 = Str{cmove::cmove(my_struct_1)};
  fmt::print("{}", my_struct_2.value);
}

TEST_CASE("cmove const to a const& constructor") {
  struct Str {
    double value;
    constexpr explicit Str(const double &value_in) : value{value_in} { // NOLINT
    }
  };
  constexpr auto my_struct_1 = Str{1000.0};
  constexpr auto my_struct_2 = Str(cmove::cmove(my_struct_1));
  fmt::print("{}", my_struct_2.value);
}

TEST_CASE("cmove const to a value/move constructor") {
  struct Str {
    double value;
    constexpr explicit Str(double value_in) : value{std::move(value_in)} { // NOLINT
    }
  };
  constexpr auto my_struct_1 = Str{1000.0};
  constexpr auto my_struct_2 = Str(cmove::cmove(my_struct_1));
  fmt::print("{}", my_struct_2.value);
}

TEST_CASE("cmove const to a value/cmove constructor") {
  struct Str {
    double value;
    constexpr explicit Str(double value_in) : value{cmove::cmove(value_in)} { // NOLINT
    }
  };
  constexpr auto my_struct_1 = Str{1000.0};
  constexpr auto my_struct_2 = Str(cmove::cmove(my_struct_1));
  fmt::print("{}", my_struct_2.value);
}

TEST_CASE("cmove const to a && constructor") {
  struct Str {
    double value;
    constexpr explicit Str(const double &value_in) : value{value_in} {
    }
    constexpr explicit Str(double &&value_in) : value{std::move(value_in)} { // NOLINT
    }
  };
  constexpr auto my_struct_1 = Str{1000.0};
  constexpr auto my_struct_2 = Str(cmove::cmove(my_struct_1));
  fmt::print("{}", my_struct_2.value);
}