#pragma once

#include <type_traits>

namespace cmove {

/**
  A function to move `const` values.
*/
template <typename T>
constexpr typename std::remove_const<typename std::remove_reference<T>::type>::type &&cmove(T &&arg) {
  return const_cast<typename std::remove_const<typename std::remove_reference<T>::type>::type &&>( // NOLINT
      static_cast<typename std::remove_reference<T>::type &&>(arg));
}

} // namespace cmove