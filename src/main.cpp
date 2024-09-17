#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include "Domain.hpp"
using namespace std;

int main(int argc, char** argv) {
    if (argc > 3 || argc < 2) {
        printf("Usage: ./bin/cahn-hilliard <Number of lattice units> <Input file>\n");
        return 1;
    }

    // Lattice Definition
    int e[9][2] = {
        {1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, 0},
        {0, -1}, {-1, 1}, {-1, 0}, {-1, -1} };

    double weight[9] = {
        {1/36}, {1/9}, {1/36}, {1/9}, {4/9}, {1/9}, {1/36}, {1/9}, {1/36} };

    double h[9] = {
        {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };

    long nLB = atoi(argv[1]); // Number of lattice units
    long maxIter = 10001;

    // Physical domain size [meters]
    double lx = 1e-3, ly = 1e-3;
    double ref_len = ly;      // Reference length in physical units

    // Lattice spacing in the x and y directions
    double deltaX = ly / (nLB - 1);
    double deltaY = deltaX;   // Uniform grid

    // Number of lattice points in the x and y directions
    long nx = lx / deltaX;
    long ny = ly / deltaY;

    // Viscosity and density of the fluid (water) in physical units
    double nuP = 3.64e-7;     // Viscosity of water at 80°C [m^2/s]
    double rhoP = 972.0;      // Density of water at 80°C [kg/m^3]
    double rho0 = 1.0;        // Density of water in lattice units
    
    // Limits of the order parameter
    double phi1 = 1.0, phi2 = 0.0;

    // Surface tension of the air-water interface
    double sigmaP = 6.28e-2;  // Surface tension in physical units [kg/s^2]
    double sigma = 1e-3;      // Lattice units (must be less than 1e-3)

    // Reynolds number
    double Re = 0.0;          // Assume Re = 0 for now

    // Velocity in physical units
    double uP = (nuP * Re) / ref_len;

    // Derived quantities
    double deltaM = (rhoP / rho0) * pow(deltaX, 3);  // Mass per lattice volume
    double deltaT = sqrt((sigma / sigmaP) * deltaM); // Lattice time step

    // Kinematic viscosity in lattice units
    double nulb = nuP / (pow(deltaX, 2) / deltaT);

    // Velocity in lattice units (should be much smaller than the speed of sound, 1/3)
    double uLB = (uP != 0) ? uP / (deltaX / deltaT) : deltaT / deltaX;

    // Density and viscosity ratios for water (species 1) and air (species 2)
    double densityRatio = 1e-3;   // Ratio rho2/rho1
    double viscosityRatio = 10.0; // Ratio nu2/nu1

    // Species 1 (water), Species 2 (air)
    double rho1 = rho0, rho2 = densityRatio * rho0;
    double nu1 = nulb, nu2 = viscosityRatio * nulb;

    // Dynamic viscosity
    double mu1 = rho1 * nu1;
    double mu2 = rho2 * nu2;

    // Cahn-Hilliard parameters define surface tension
    double diff = 0.1 * (ly / deltaX);  // Diffusive interface thickness
    double k = (3.0 / 2.0) * sigma * diff / sqrt(phi1 - phi2);  // Surface tension coefficient
    double beta = (12.0 / pow((phi1 - phi2), 4)) * (sigma / diff);  // Energy parameter

    // Diffusion coefficients
    double D_2 = 2.42e-7;  // Diffusion coefficient of O2 in water [m^2/s]
    double D_1 = 2.42e-9;  // Diffusion coefficient of water in water [m^2/s]

    // Weber number
    double We = pow(uLB, 2) * (ref_len / deltaX) * (rho1 - rho2) / sigma;

    // Pecelet number definition
    double Pe = (uP != 0) ? (uP * diff * deltaX / D_1) : ((uLB * deltaX / deltaT) * (diff * deltaX / D_1));

    // Calculate mobility using Peclet number
    double mlb = (1.0 / Pe) / beta;
    double contactAngle = M_PI / 4.0;

    /*****************************************************************/
    /*********************** Start of Main ***************************/
    /*****************************************************************/

    Domain *domain = new Domain(nx, ny);

    if (argc == 3) {
        domain->inputFile = argv[2];
        domain->readFlag = true;
    }

    /* Initial_config function comes from setup.cpp & is translated from setup.py */
    //test->Initial_config(domain, maxIter, ref_len, deltaX);

    /* Initialize Mu and Tau */

    delete domain;
    return 0;
}