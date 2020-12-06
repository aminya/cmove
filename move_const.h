#include <type_traits>

template <typename T>
typename std::remove_const<typename std::remove_reference<T>::type>::type&& move_const(T&& arg)
{
    return const_cast<typename std::remove_const<typename std::remove_reference<T>::type>::type&&>(
        static_cast<typename std::remove_reference<T>::type&&>(arg)
    );
}
