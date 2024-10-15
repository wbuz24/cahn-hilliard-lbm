#include <cmath>
#include "domain.hpp"
#include "mathOperations.hpp"

using namespace std;

void uSqr(Domain &domain) {
    for (auto node : domain.nodes) {
        node->usqr = pow(node->u[0], 2) + pow(node->u[1], 2);
    }
    return;
}

void DphiDx(Domain &domain) {
    return;
}

void DphiDy(Domain &domain) {
    return;
}

void grad(Domain &domain) {
    return;
}

void div(Domain &domain) {
    return;
}

void biasedDphiDx(Domain &domain) {
    return;
}

void biasedDphiDy(Domain &domain) {
    return;
}

void biasedGrad(Domain &domain) {
    return;
}

void biasedDiv(Domain &domain) {
    return;
}

void D2phiDx2(Domain &domain) {
    return;
}

void laplace(Domain &domain) {
    return;
}

void eDphiDx(Domain &domain) {
    return;
}

void eGrad(Domain &domain) {
    return;
}