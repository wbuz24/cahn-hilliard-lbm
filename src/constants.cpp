#ifndef CONSTANTS_CPP
#define CONSTANTS_CPP

#include "constants.hpp"

// Constructor implementation
Constants::Constants(const nlohmann::json& config) {
    // Lattice Definition
    e[0][0] = 1; e[0][1] = 1;
    e[1][0] = 1; e[1][1] = 0;
    e[2][0] = 1; e[2][1] = -1;
    e[3][0] = 0; e[3][1] = 1;
    e[4][0] = 0; e[4][1] = 0;
    e[5][0] = 0; e[5][1] = -1;
    e[6][0] = -1; e[6][1] = 1;
    e[7][0] = -1; e[7][1] = 0;
    e[8][0] = -1; e[8][1] = -1;

    weight[0] = 1.0 / 36.0; 
    weight[1] = 1.0 / 9.0; 
    weight[2] = 1.0 / 36.0; 
    weight[3] = 1.0 / 9.0;
    weight[4] = 4.0 / 9.0; 
    weight[5] = 1.0 / 9.0; 
    weight[6] = 1.0 / 36.0; 
    weight[7] = 1.0 / 9.0; 
    weight[8] = 1.0 / 36.0;

    for (int i = 0; i < 9; ++i)  h[i] = 0.0;

    // Define domain properties
    lx = config["domain"]["lx"];
    ly = config["domain"]["ly"];
    nLB = config["domain"]["nLB"];

    ref_len = ly;               
    deltaX = ly / (nLB - 1);
    deltaY = deltaX; // Uniform grid

    nx = lx / deltaX;
    ny = ly / deltaY;

    // Define fluid properties
    nuP = config["fluid"]["nuP"];
    rhoP = config["fluid"]["rhoP"];
    rho0 = config["fluid"]["rho0"];
    Re = config["fluid"]["Re"];
    
    phi1 = config["order"]["phi1"];
    phi2 = config["order"]["phi2"];

    sigmaP = config["fluid"]["sigmaP"];
    sigma = config["fluid"]["sigma"]; // Lattice units (must be less than 1e-3)

    deltaM = (rhoP / rho0) * pow(deltaX, 3);
    deltaT = sqrt((sigma / sigmaP) * deltaM);

    uP = (nuP * Re) / ref_len;
    nulb = nuP / (pow(deltaX, 2) / deltaT);

    uLB = (uP != 0) ? uP / (deltaX / deltaT) : deltaT / deltaX; // Velocity in lattice units (should be much smaller than the speed of sound, 1/3)

    densityRatio = config["ratios"]["density"];
    viscosityRatio = config["ratios"]["viscosity"];

    // Species 1 (water), Species 2 (air)
    rho1 = rho0;
    rho2 = densityRatio * rho0;
    nu1 = nulb;
    nu2 = viscosityRatio * nulb;

    mu1 = rho1 * nu1; // Dynamic viscosity
    mu2 = rho2 * nu2;

    // Cahn-Hilliard parameters define surface tension
    diff = 0.1 * (ly / deltaX);
    k = (3.0 / 2.0) * sigma * diff / sqrt(phi1 - phi2);
    beta = (12.0 / pow((phi1 - phi2), 4)) * (sigma / diff);

    D_2 = 2.42e-7;
    D_1 = 2.42e-9;

    We = pow(uLB, 2) * (ref_len / deltaX) * (rho1 - rho2) / sigma;
    Pe = (uP != 0) ? (uP * diff * deltaX / D_1) : ((uLB * deltaX / deltaT) * (diff * deltaX / D_1));

    // Calculate mobility using Peclet number
    mlb = (1.0 / Pe) / beta;
    contactAngle = M_PI / 4.0;
}

#endif // CONSTANTS_CPP
