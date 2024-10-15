#ifndef MATH_OPERATIONS_HPP
#define MATH_OPERATIONS_HPP

#include "domain.hpp"

void uSqr(Domain &domain);
void DphiDx(Domain &domain);
void DphiDy(Domain &domain);
void grad(Domain &domain);
void div(Domain &domain);
void biasedDphiDx(Domain &domain);
void biasedDphiDy(Domain &domain);
void biasedGrad(Domain &domain);
void biasedDiv(Domain &domain);
void D2phiDx2(Domain &domain);
void laplace(Domain &domain);
void eDphiDx(Domain &domain);
void eGrad(Domain &domain);

#endif // MATH_OPERATIONS_HPP
