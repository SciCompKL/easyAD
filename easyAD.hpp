#ifndef EASYAD_HPP
#define EASYAD_HPP

#include <math.h>
#include <ostream>
#include <istream>

struct Forward {
  double val;
  double dot;
  constexpr Forward(double val, double dot): val(val), dot(dot) {}
  constexpr Forward(double val): val(val), dot(0.0) {}
  constexpr Forward(): val(0.0), dot(0.0) {}

  operator double(){
    return val;
  }
};

// basic arithmetic with two operands
Forward operator +(Forward a, Forward b){
  return {a.val+b.val, a.dot+b.dot};
} 
Forward operator -(Forward a, Forward b){
  return {a.val-b.val, a.dot-b.dot};
} 
Forward operator *(Forward a, Forward b){
  return {a.val*b.val, a.dot*b.val+a.val*b.dot};
} 
Forward operator /(Forward a, Forward b){
  return {a.val/b.val, a.dot/b.val-a.val*b.dot/(b.val*b.val)};
} 

// overloads with one non-active operand
Forward operator +(Forward a, double b){
  return a + Forward(b);
}
Forward operator +(double a, Forward b){
  return Forward(a) + b;
}
Forward operator -(Forward a, double b){
  return a - Forward(b);
}
Forward operator -(double a, Forward b){
  return Forward(a) - b;
}
Forward operator *(Forward a, double b){
  return a * Forward(b);
}
Forward operator *(double a, Forward b){
  return Forward(a) * b;
}
Forward operator /(Forward a, double b){
  return a / Forward(b);
}
Forward operator /(double a, Forward b){
  return Forward(a) / b;
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
Forward operator -(Forward a){
  return {-a.val,-a.dot};
}
Forward operator +(Forward a){
  return a;
}

// stream I/O
std::ostream& operator<<(std::ostream& out, Forward a){
  return out << a.val;
}
std::istream& operator>>(std::istream& in, Forward& a){
  a.dot = 0.0;
  return in >> a.val;
}

// math.h functions

namespace std {

Forward abs(Forward a){
  return {abs(a.val), a.val >= 0. ? a.dot : -a.dot};
}

Forward acos(Forward a){
  return {acos(a.val), -1./sqrt(1-a.val*a.val) * a.dot};
}
Forward asin(Forward a){
  return {asin(a.val), 1./sqrt(1-a.val*a.val) * a.dot};
}
Forward atan(Forward a){
  return {atan(a.val), 1./(1+a.val*a.val) * a.dot};
}
Forward cos(Forward a){
  return {cos(a.val), -sin(a.val) * a.dot};
}
Forward cosh(Forward a){
  return {cosh(a.val), sinh(a.val) * a.dot};
}
Forward exp(Forward a){
  return {exp(a.val), exp(a.val) * a.dot};
}
Forward exp2(Forward a){
  return {exp2(a.val), exp2(a.val)*log(2.0) * a.dot};
}
Forward expm1(Forward a){
  return {expm1(a.val), exp(a.val) * a.dot};
}
Forward fabs(Forward a){
  return {fabs(a.val), (a.val>0?1.:-1.) * a.dot};
}
Forward floor(Forward a){
  return {floor(a.val), 0.0};
}
Forward trunc(Forward a){
  return {trunc(a.val), 0.0};
}
Forward round(Forward a){
  return {round(a.val), 0.0};
}
Forward nearbyint(Forward a){
  return {nearbyint(a.val), 0.0};
}
Forward rint(Forward a){
  return {rint(a.val), 0.0};
}
Forward log(Forward a){
  return {log(a.val), 1/a.val * a.dot};
}
Forward log2(Forward a){
  return {log2(a.val), 1/(a.val*log(2.0)) * a.dot};
}
Forward log10(Forward a){
  return {log10(a.val), 1/(a.val*log(10.0)) * a.dot};
}
Forward log1p(Forward a){
  return {log1p(a.val), 1/(a.val+1.0) * a.dot};
}
Forward sin(Forward a){
  return {sin(a.val), cos(a.val) * a.dot};
}
Forward sinh(Forward a){
  return {sinh(a.val), cosh(a.val) * a.dot};
}
Forward sqrt(Forward a){
  return {sqrt(a.val), 0.5/sqrt(a.val) * a.dot};
}
Forward cbrt(Forward a){
  return {cbrt(a.val), cbrt(a.val)/(3.0*a.val) * a.dot};
}
Forward hypot(Forward a, Forward b){
  return {hypot(a.val,b.val), a.val/hypot(a.val,b.val) * a.dot + b.val/hypot(a.val,b.val) * b.dot};
}
Forward tan(Forward a){
  return {tan(a.val), 1/(cos(a.val)*cos(a.val)) * a.dot};
}
Forward tanh(Forward a){
  return {tanh(a.val), (1-tanh(a.val)*tanh(a.val)) * a.dot};
}
Forward atan2(Forward a, Forward b){
  double norm = a.val*a.val + b.val*b.val;
  return {atan2(a.val,b.val), -b.val/norm * a.dot + a.val/norm * b.dot};
}
Forward pow(Forward a, Forward b){
  double da = 0., db = 0.;
  if(b.val!=0.0 && b.val!=-0.0){
    da = b.val*pow(a.val,b.val-1.0);
  }
  if(a.val<=0.){
    db = pow(a.val,b.val)*log(a.val);
  }
  return {pow(a.val,b.val), da * a.dot + db * b.dot};
}
Forward pow(Forward a, double b){
  return pow(a, Forward(b));
}
Forward pow(double a, Forward b){
  return pow(Forward(a), b);
}

}



#endif // EASYAD_HPP
