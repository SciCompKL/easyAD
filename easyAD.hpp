#ifndef EASYAD_HPP
#define EASYAD_HPP

#ifdef __cplusplus

#include <cmath>
#include <ostream>
#include <istream>
#include <type_traits>

struct Forward {
  double val;
  double dot;
  constexpr Forward(double val, double dot): val(val), dot(dot) {}
  constexpr Forward(double val): val(val), dot(0.0) {}
  constexpr Forward(Forward const& forw): val(forw.val), dot(forw.dot) {}
  Forward() = default; // If a non-trivial default constructor were used, Forward could not be used in unions

  template<typename T>
  explicit constexpr operator T() const {
    return val;
  }
};
using Gorward = Forward;

#include "traits.hpp"

// basic arithmetic with two operands
constexpr inline Forward operator +(Forward a, Forward b){
  return {a.val+b.val, a.dot+b.dot};
} 
constexpr inline Forward operator -(Forward a, Forward b){
  return {a.val-b.val, a.dot-b.dot};
} 
constexpr inline Forward operator *(Forward a, Forward b){
  return {a.val*b.val, a.dot*b.val+a.val*b.dot};
} 
constexpr inline Forward operator /(Forward a, Forward b){
  return {a.val/b.val, a.dot/b.val-a.val*b.dot/(b.val*b.val)};
} 

// overloads with one non-active operand
template<typename T, typename std::enable_if<std::is_arithmetic<T>::value,bool>::type = true>
constexpr Forward operator +(Forward a, T b){
  return a + Forward(b);
}
template<typename T, typename std::enable_if<std::is_arithmetic<T>::value,bool>::type = true>
constexpr Forward operator +(T a, Forward b){
  return Forward(a) + b;
}
template<typename T, typename std::enable_if<std::is_arithmetic<T>::value,bool>::type = true>
constexpr Forward operator -(Forward a, T b){
  return a - Forward(b);
}
template<typename T, typename std::enable_if<std::is_arithmetic<T>::value,bool>::type = true>
constexpr Forward operator -(T a, Forward b){
  return Forward(a) - b;
}
template<typename T, typename std::enable_if<std::is_arithmetic<T>::value,bool>::type = true>
constexpr Forward operator *(Forward a, T b){
  return a * Forward(b);
}
template<typename T, typename std::enable_if<std::is_arithmetic<T>::value,bool>::type = true>
constexpr Forward operator *(T a, Forward b){
  return Forward(a) * b;
}
template<typename T, typename std::enable_if<std::is_arithmetic<T>::value,bool>::type = true>
constexpr Forward operator /(Forward a, T b){
  return a / Forward(b);
}
template<typename T, typename std::enable_if<std::is_arithmetic<T>::value,bool>::type = true>
constexpr Forward operator /(T a, Forward b){
  return Forward(a) / b;
}

// increment/decrement operators
inline Forward& operator++(Forward& a){
  ++a.val;
  return a;
}
inline Forward& operator--(Forward& a){
  ++a.val;
  return a;
}
inline Forward operator++(Forward& a, int){
  return a.val++;
}
inline Forward operator--(Forward& a, int){
  return a.val++;
}

// arithmetic assignment operators
template<typename T>
Forward& operator +=(Forward& a, T const& b){
  a = a + b;
  return a;
} 
template<typename T>
Forward& operator -=(Forward& a, T const& b){
  a = a - b;
  return a;
} 
template<typename T>
Forward& operator *=(Forward& a, T const& b){
  a = a * b;
  return a;
} 
template<typename T>
Forward& operator /=(Forward& a, T const& b){
  a = a / b;
  return a;
} 

// basic arithmetic with one operand
constexpr inline Forward operator -(Forward a){
  return {-a.val,-a.dot};
}
constexpr inline Forward operator +(Forward a){
  return a;
}

// comparisons
constexpr inline bool operator==(Forward const& a, Forward const& b){
  return a.val==b.val;
}
constexpr inline bool operator!=(Forward const& a, Forward const& b){
  return a.val!=b.val;
}
constexpr inline bool operator>(Forward const& a, Forward const& b){
  return a.val>b.val;
}
constexpr inline bool operator<(Forward const& a, Forward const& b){
  return a.val<b.val;
}
constexpr inline bool operator>=(Forward const& a, Forward const& b){
  return a.val>=b.val;
}
constexpr inline bool operator<=(Forward const& a, Forward const& b){
  return a.val<=b.val;
}


// stream I/O
inline std::ostream& operator<<(std::ostream& out, Forward a){
  return out << a.val;
}
inline std::istream& operator>>(std::istream& in, Forward& a){
  a.dot = 0.0;
  return in >> a.val;
}

// math.h functions

namespace std {

inline Forward max(Forward a, Forward b){
  if(a>b){
    return a;
  } else {
    return b;
  }
}
inline Forward min(Forward a, Forward b){
  if(a<b){
    return a;
  } else {
    return b;
  }
}

constexpr inline Forward abs(Forward a){
  return {abs(a.val), a.val >= 0. ? a.dot : -a.dot};
}
constexpr inline Forward acos(Forward a){
  return {acos(a.val), -1./sqrt(1-a.val*a.val) * a.dot};
}
constexpr inline Forward acosh(Forward a){
  return {acosh(a.val), 1./sqrt(a.val*a.val-1) * a.dot};
}
constexpr inline Forward asin(Forward a){
  return {asin(a.val), 1./sqrt(1-a.val*a.val) * a.dot};
}
constexpr inline Forward asinh(Forward a){
  return {asinh(a.val), 1./sqrt(a.val*a.val+1) * a.dot};
}
constexpr inline Forward atan(Forward a){
  return {atan(a.val), 1./(1+a.val*a.val) * a.dot};
}
constexpr inline Forward cos(Forward a){
  return {cos(a.val), -sin(a.val) * a.dot};
}
constexpr inline Forward cosh(Forward a){
  return {cosh(a.val), sinh(a.val) * a.dot};
}
constexpr inline Forward copysign(Forward a, Forward b){
  return {copysign(a.val,b.val), copysign(1.0, a.val*b.val) * a.dot};
}
constexpr inline Forward erf(Forward a){
  return {erf(a.val), 2.0/sqrt(M_PI) * exp(-a.val*a.val) * a.dot};
}
constexpr inline Forward erfc(Forward a){
  return {erfc(a.val), -2.0/sqrt(M_PI) * exp(-a.val*a.val) * a.dot};
}
constexpr inline Forward exp(Forward a){
  return {exp(a.val), exp(a.val) * a.dot};
}
constexpr inline Forward exp2(Forward a){
  return {exp2(a.val), exp2(a.val)*log(2.0) * a.dot};
}
constexpr inline Forward expm1(Forward a){
  return {expm1(a.val), exp(a.val) * a.dot};
}
constexpr inline Forward fabs(Forward a){
  return {fabs(a.val), (a.val>0?1.:-1.) * a.dot};
}
constexpr inline Forward floor(Forward a){
  return {floor(a.val), 0.0};
}
constexpr inline Forward ceil(Forward a){
  return {ceil(a.val), 0.0};
}
constexpr inline Forward trunc(Forward a){
  return {trunc(a.val), 0.0};
}
constexpr inline Forward round(Forward a){
  return {round(a.val), 0.0};
}
constexpr inline Forward nearbyint(Forward a){
  return {nearbyint(a.val), 0.0};
}
constexpr inline Forward rint(Forward a){
  return {rint(a.val), 0.0};
}
constexpr inline long lrint(Forward a){
  return lrint(a.val);
}
constexpr inline long long llrint(Forward a){
  return llrint(a.val);
}
constexpr inline Forward fmod(Forward a, Forward b){
  return {fmod(a.val, b.val), 1.0 * a.dot - trunc(a.val/b.val) * b.dot};
}
inline Forward modf(Forward a, Forward* b){
  b->dot = 0.;
  return {modf(a.val, &b->val), a.dot};
}
constexpr inline Forward log(Forward a){
  return {log(a.val), 1/a.val * a.dot};
}
constexpr inline Forward log2(Forward a){
  return {log2(a.val), 1/(a.val*log(2.0)) * a.dot};
}
constexpr inline Forward log10(Forward a){
  return {log10(a.val), 1/(a.val*log(10.0)) * a.dot};
}
constexpr inline Forward log1p(Forward a){
  return {log1p(a.val), 1/(a.val+1.0) * a.dot};
}
constexpr inline Forward sin(Forward a){
  return {sin(a.val), cos(a.val) * a.dot};
}
constexpr inline Forward sinh(Forward a){
  return {sinh(a.val), cosh(a.val) * a.dot};
}
constexpr inline Forward sqrt(Forward a){
  return {sqrt(a.val), 0.5/sqrt(a.val) * a.dot};
}
constexpr inline Forward cbrt(Forward a){
  return {cbrt(a.val), cbrt(a.val)/(3.0*a.val) * a.dot};
}
constexpr inline Forward hypot(Forward a, Forward b){
  return {hypot(a.val,b.val), a.val/hypot(a.val,b.val) * a.dot + b.val/hypot(a.val,b.val) * b.dot};
}
constexpr inline Forward tan(Forward a){
  return {tan(a.val), 1/(cos(a.val)*cos(a.val)) * a.dot};
}
constexpr inline Forward tanh(Forward a){
  return {tanh(a.val), (1-tanh(a.val)*tanh(a.val)) * a.dot};
}
constexpr inline Forward atan2(Forward a, Forward b){
  return {atan2(a.val,b.val), -b.val/(a.val*a.val + b.val*b.val) * a.dot + a.val/(a.val*a.val + b.val*b.val) * b.dot};
}
inline Forward pow(Forward a, Forward b){
  double da = 0., db = 0.;
  if(b.val!=0.0 && b.val!=-0.0){
    da = b.val*pow(a.val,b.val-1.0);
  }
  if(a.val<=0.){
    db = pow(a.val,b.val)*log(a.val);
  }
  return {pow(a.val,b.val), da * a.dot + db * b.dot};
}
inline Forward pow(Forward a, double b){
  return pow(a, Forward(b));
}
inline Forward pow(double a, Forward b){
  return pow(Forward(a), b);
}
inline Forward tgamma(Forward a){
  double derivative = (tgamma(a.val*1.01)-tgamma(a.val*0.99))/(a.val*0.02); // TODO
  return {tgamma(a.val), derivative * a.dot};
}
inline Forward lgamma(Forward a){
  double derivative = (lgamma(a.val*1.01)-lgamma(a.val*0.99))/(a.val*0.02); // TODO
  return {lgamma(a.val), derivative * a.dot};
}
inline bool isfinite(Forward a){
  return isfinite(a.val);
}
inline bool isinf(Forward a){
  return isinf(a.val);
}
inline bool isnan(Forward a){
  return isnan(a.val);
}

}
using std::abs;
using std::acos;
using std::acosh;
using std::asin;
using std::asinh;
using std::atan;
using std::cos;
using std::cosh;
using std::copysign;
using std::erf;
using std::erfc;
using std::exp;
using std::exp2;
using std::expm1;
using std::fabs;
using std::floor;
using std::ceil;
using std::trunc;
using std::round;
using std::nearbyint;
using std::rint;
using std::lrint;
using std::llrint;
using std::fmod;
using std::modf;
using std::log;
using std::log2;
using std::log10;
using std::log1p;
using std::sin;
using std::sinh;
using std::sqrt;
using std::cbrt;
using std::hypot;
using std::tan;
using std::tanh;
using std::atan2;
using std::pow;
using std::lgamma;
using std::tgamma;
using std::isfinite;
using std::isinf;
using std::isnan;

#include <string>
namespace std {
  inline std::string to_string(Forward a){
    return to_string(a.val);
  }
}

#else
  #define ForwardIfPossible(x) (x)
#endif // __cplusplus

#endif // EASYAD_HPP
