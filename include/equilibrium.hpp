#ifndef EQUILIBRIUM_HPP
#define EQUILIBRIUM_HPP

#include "domain.hpp"

void equilibriumG(Domain &domain);
void equilibriumH(Domain &domain);
void sourceG(Domain &domain, Constants &constants);
void sourceH(Domain &domain, Constants &constants);

#endif // EQUILIBRIUM_HPP