#pragma once
#include <type_traits>
#include <utility>

struct Forward;

#if 0
template<typename T>
T&& ForwardIfPossible(T&& t){
  return std::forward<T>(t);
}
#endif
#if 1
template<typename T>
typename std::conditional<std::is_floating_point<T>::value, Forward&&, T&&>::type ForwardIfPossible(T&& t){
  return std::forward<T>(t);
}
#endif


inline Forward operator "" _easyAD(long double literal){
  return literal;
}
