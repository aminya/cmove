#pragma once

#include <type_traits>

namespace cmove {

/**
  A function to move `const` values.
  ```cpp

  const auto my_struct_1 = MyStruct{"Hello World im long string string string"};
  cmove::cmove(my_struct_1)


  ```
*/
template <typename T>
constexpr typename std::remove_const<typename std::remove_reference<T>::type>::type &&
cmove(T &&arg) noexcept {
  return const_cast<typename std::remove_const<typename std::remove_reference<T>::type>::type &&>( // NOLINT
      static_cast<typename std::remove_reference<T>::type &&>(arg));
}

} // namespace cmove