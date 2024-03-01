#pragma once
#include <type_traits>

struct Forward;

template<typename T>
typename std::conditional<std::is_arithmetic<T>::value, Forward, T>::type ForwardIfPossible(T t){
  return t;
}


inline Forward operator "" _easyAD(long double literal){
  return literal;
}
