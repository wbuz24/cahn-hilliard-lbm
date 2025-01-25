#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "constants.hpp"
#include "domain.hpp"
#include "mathOperations.hpp"
#include "macroscopic.hpp"
#include "boundaryConditions.hpp"
#include "equilibrium.hpp"
#include "collideAndStream.hpp"

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

    long nX = constants.nx;
    long nY = constants.ny;

    // Create domain and initialize node variables (u, p, phi, rho, mu0, tau)
    Domain domain(nX, nY);
    domain.initialize(config, constants);

    // Initial calculation of mu
    laplace(domain, &Node::phi, &Node::muOld);

    for (int i = 0; i < nX; i++) {
        for (int j = 0; j < nY; j++) {
            Node* node = domain.nodes[i][j];
            node->muOld = node->mu0 - (constants.k * node->muOld);
        }
    }

    // Gradient calculations
    laplace(domain, &Node::muOld, &Node::d2mu);
    
    derivativeY(domain, &Node::uX, &Node::dudy);
    derivativeX(domain, &Node::uY, &Node::dvdx);
    derivativeX(domain, &Node::uX, &Node::dudx);
    derivativeY(domain, &Node::uY, &Node::dvdy);

    eGrad(domain, &Node::uX, &Node::eDudy);
    eGrad(domain, &Node::uY, &Node::eDvdx);
    uSqr(domain);

    // Initial equilibrium distribution based on the macroscopic values
    equilibriumG(domain);
    equilibriumH(domain);

    // Initialize residual values
    /* WHAT ARE THE VALUES HERE??? in python code */

    double time = 0;
    double iter = config["simulation"]["max_iter"];
    try {
        for (time = 0; time < iter; time++) {
            // Update macroscopic values
            macroscopic(domain, constants);

            // Update boundary conditions
            boundryConfig(domain);

            // Update muOld
            for (int i = 0; i < nX; i++) {
                for (int j = 0; j < nY; j++) {
                    domain.nodes[i][j]->muOld = domain.nodes[i][j]->mu;
                }
            }

            // Gradient calculations
            laplace(domain, &Node::mu, &Node::d2mu);
            
            derivativeY(domain, &Node::uX, &Node::dudy);
            derivativeX(domain, &Node::uY, &Node::dvdx);
            derivativeX(domain, &Node::uX, &Node::dudx);
            derivativeY(domain, &Node::uY, &Node::dvdy);

            eGrad(domain, &Node::uX, &Node::eDudy);
            eGrad(domain, &Node::uY, &Node::eDvdx);
            uSqr(domain);

            // Update equilibrium values and sources
            equilibriumG(domain);
            // sourceG(domain);

            equilibriumH(domain);
            // sourceH(domain);
            
            // Zou He BC
            // Wall
            // Inlet
            // Outlet

            // Collide and stream steps
            collide(domain);
            stream(domain);

            /* NEED TO CHECK WHAT THIS IS??? */
            // Calculate residual values

            // Output
            cout << "Iteration: " << time << " / " << iter << endl;
        }
    } catch (runtime_error &e) {
        cout << "Simulation stopped. Error." << endl;
        return 1;
    }
    cout << "Simulation complete." << endl;
    return 0;
}