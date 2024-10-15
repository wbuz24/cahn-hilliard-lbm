#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "json.hpp"
#include "domain.hpp"
#include "mathOperations.hpp"
#include "macroscopic.hpp"
#include "boundaryConditions.hpp"

using json = nlohmann::json;
using namespace std;

int main(int argc, char** argv) {

    /*****************************************************************/
    /********************** Base Definitions *************************/
    /*****************************************************************/

    // Create a JSON object and read from config file
    json config;
    ifstream inFile("config.json");

    if (!inFile.is_open()) {
        cerr << "Failed to open config.json for reading." << endl;
        return 1;
    }
    inFile >> config;
    inFile.close();

    // Lattice Definition
    int e[9][2] = { {1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, 0}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1} };

    double weight[9] = { {1/36}, {1/9}, {1/36}, {1/9}, {4/9}, {1/9}, {1/36}, {1/9}, {1/36} };

    double h[9] = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };

    // Define domain properties
    double lx = config["domain"]["lx"];     // Physical domain size [meters] in x and y directions
    double ly = config["domain"]["ly"];
    double lz = config["domain"]["lz"];
    long nLB = config["domain"]["nLB"];     // Number of lattice units (characteristic length scale)

    double ref_len = ly;                    // Reference length in physical units
    double deltaX = ly / (nLB - 1);         // Lattice spacing in the x and y directions
    double deltaY = deltaX;                 // Uniform grid
    double deltaZ = deltaX;

    long nx = lx / deltaX;                  // Number of lattice points in the x and y directions
    long ny = ly / deltaY;
    long nz = lz / deltaZ;

    // Define fluid properties
    double nuP = config["fluid"]["nuP"];    // Viscosity of water at 80°C [m^2/s]
    double rhoP = config["fluid"]["rhoP"];  // Density of water at 80°C [kg/m^3]
    double rho0 = config["fluid"]["rho0"];  // Density of water in lattice units
    double Re = config["fluid"]["Re"];      // Reynolds number
    
    double phi1 = config["order"]["phi1"];  // Limits of the order parameter
    double phi2 = config["order"]["phi2"];

    double sigmaP = config["fluid"]["sigmaP"]; // Surface tension of the air-water interface in physical units [kg/s^2]
    double sigma = config["fluid"]["sigma"];   // Lattice units (must be less than 1e-3)

    double deltaM = (rhoP / rho0) * pow(deltaX, 3);      // Mass per lattice volume
    double deltaT = sqrt((sigma / sigmaP) * deltaM);     // Lattice time step

    double uP = (nuP * Re) / ref_len;                    // Velocity in physical units
    double nulb = nuP / (pow(deltaX, 2) / deltaT);       // Kinematic viscosity in lattice units

    double uLB = (uP != 0) ? uP / (deltaX / deltaT) : deltaT / deltaX; // Velocity in lattice units (should be much smaller than the speed of sound, 1/3)

    double densityRatio = config["ratios"]["density"];
    double viscosityRatio = config["ratios"]["viscosity"];

    // Species 1 (water), Species 2 (air)
    double rho1 = rho0, rho2 = densityRatio * rho0;
    double nu1 = nulb, nu2 = viscosityRatio * nulb;

    double mu1 = rho1 * nu1; // Dynamic viscosity
    double mu2 = rho2 * nu2;

    // Cahn-Hilliard parameters define surface tension
    double diff = 0.1 * (ly / deltaX);                              // Diffusive interface thickness
    double k = (3.0 / 2.0) * sigma * diff / sqrt(phi1 - phi2);      // Surface tension coefficient
    double beta = (12.0 / pow((phi1 - phi2), 4)) * (sigma / diff);  // Energy parameter

    double D_2 = config["coefficients"]["D_2"];  // Diffusion coefficient of O2 in water [m^2/s]
    double D_1 = config["coefficients"]["D_1"];  // Diffusion coefficient of water in water [m^2/s]

    double We = pow(uLB, 2) * (ref_len / deltaX) * (rho1 - rho2) / sigma;  // Weber number
    double Pe = (uP != 0) ? (uP * diff * deltaX / D_1) : ((uLB * deltaX / deltaT) * (diff * deltaX / D_1)); // Pecelet number definition

    // Calculate mobility using Peclet number
    double mlb = (1.0 / Pe) / beta;
    double contactAngle = M_PI / 4.0;

    /*****************************************************************/
    /*********************** Start of Main ***************************/
    /*****************************************************************/

    Domain domain(nx, ny, nz, config);

    domain.initialize(ref_len, deltaX);

    domain.initializeMacros(uP, deltaT, deltaX);

    // Initialize rho, mu and tau
    for (auto& node : domain.nodes) {
        node->rho = (rho1 * (node->phi - phi2) + rho2 * (phi1 - node->phi)) / (phi1 - phi2);
        node->mu = 2 * beta * (node->phi - phi2) * (node->phi - phi1) * (2 * node->phi - (phi2 + phi1));
        node->tau = config["simulation"]["tau"];
    }

    // Gradient calculations

    // Initial equilibrium distribution based on the macroscopic values

    // Hin equilibrium

    // Initializing residuals and other variables

    // Simulation parameters
    double initialIter = 0;
    if (config["simulation"]["restart"]) {
        initialIter = config["simulation"]["restart_iter"];
    }
    double maxIter = config["simulation"]["max_iter"];

    double res_phi = 1.0;
    double time = 0.0;
    double epsilon_p = tan(M_PI / 2); // Set epsilon_p to tan(pi/2) (5e-1 would be another possible value as mentioned)
    double res_u = 1.0;

    // Compute loop goes here:
    try {
        for (double time = initialIter; time < maxIter; time++) {
            // Update macroscopic values
            macroscopic(domain);

            // Update boundary conditions
            boundryConfig(domain);

            // Update other values

            // Compute equilibrium distribution

            // Collision step

            // Streaming step

            // Boundary conditions

            // Compute residuals

            // Check for convergence

            // Output info as needed
    
        }
    } catch (runtime_error &e) {
        cout << "Simulation stopped. Error." << endl;
        return 1;
    }
    cout << "Simulation complete." << endl;
    return 0;
}