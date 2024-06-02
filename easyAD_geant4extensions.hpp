#ifndef EASYAD_GEANT4EXTENSIONS_HPP
#define EASYAD_GEANT4EXTENSIONS_HPP

#ifdef __cplusplus

#include "easyAD.hpp"
#include <complex>
using CF = std::complex<Forward>;
inline CF operator+(double a, CF b){ return Forward(a)+b; }
inline CF operator-(double a, CF b){ return Forward(a)-b; }
inline CF operator*(double a, CF b){ return Forward(a)*b; }
inline CF operator/(double a, CF b){ return Forward(a)/b; }
inline CF operator+(CF a, double b){ return a+Forward(b); }
inline CF operator-(CF a, double b){ return a-Forward(b); }
inline CF operator*(CF a, double b){ return a*Forward(b); }
inline CF operator/(CF a, double b){ return a/Forward(b); }

struct ForwardFloat : public Forward {
  template<typename...Args>
  ForwardFloat(Args&&...args): Forward(std::forward<Args>(args)...) {}
  ForwardFloat() = default;
};

// math functions to make mat4f etc. happy
inline ForwardFloat cosf(ForwardFloat a){
  return {cos(a.val), -sin(a.val) * a.dot};
}
inline ForwardFloat sinf(ForwardFloat a){
  return {sin(a.val), cos(a.val) * a.dot};
}
inline ForwardFloat sqrtf(ForwardFloat a){
  return {sqrt(a.val), 0.5/sqrt(a.val) * a.dot};
}
inline ForwardFloat atan2f(ForwardFloat a, ForwardFloat b){
  return {atan2(a.val,b.val), -b.val/(a.val*a.val + b.val*b.val) * a.dot + a.val/(a.val*a.val + b.val*b.val) * b.dot};
}
inline ForwardFloat fabsf(ForwardFloat a){
  return {fabs(a.val), (a.val>0?1.:-1.) * a.dot};
}
inline ForwardFloat acosf(ForwardFloat a){
  return {acos(a.val), -1./sqrt(1-a.val*a.val) * a.dot};
}
inline ForwardFloat floorf(ForwardFloat a){
  return {floor(a.val), 0.0};
}
inline ForwardFloat ceilf(ForwardFloat a){
  return {ceil(a.val), 0.0};
}
#endif // __cplusplus
#endif // EASYAD_GEANT4EXTENSIONS
