#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "constants.hpp"
#include "domain.hpp"
#include "mathOperations.hpp"
#include "macroscopic.hpp"
#include "boundaryConditions.hpp"

using json = nlohmann::json;
using namespace std;

int main(int argc, char** argv) {
    // Create a JSON object and read from config file
    json config;
    ifstream inFile("config.json");

    if (!inFile.is_open()) {
        cerr << "Failed to open config.json for reading." << endl;
        return 1;
    }
    inFile >> config;
    inFile.close();

    // Initialize simulation constants from config
    Constants constants(config);

    // Create domain
    Domain domain(constants.nx, constants.ny, config);

    // Set node neighbors in all 9 directions
    for (auto& node : domain.nodes) {
        for (int i = 0; i < 9; i++) {
            int x = node->x + constants.e[i][0];
            int y = node->y + constants.e[i][1];

            if (x >= 0 && x < constants.nx && y >= 0 && y < constants.ny) {
                node->neighbors.push_back(domain.nodes[x * constants.ny + y]);
            } else {
                node->neighbors.push_back(nullptr);
            }
        }
    }

    // Initial phi, rho, p, u, mu, tau
    domain.initialize(config, constants);

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