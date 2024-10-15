#ifndef BOUNDARY_CONDITIONS_HPP
#define BOUNDARY_CONDITIONS_HPP

#include "domain.hpp"

void neumannBC();
void neumann2BC();
void macroscopicInflow();
void macroscopicPressureInflow();
void macroscopicOutflow();
void macroscopicWallBC();
void zouHeBC();
void boundryConfig(Domain &domain);

#endif // BOUNDARY_CONDITIONS_HPP