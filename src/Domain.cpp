#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include "json.hpp"
#include "domain.hpp"
#include "node.hpp"

using namespace std;

Domain::Domain(long nx, long ny, const nlohmann::json& config) : nX(nx), nY(ny) {
    nodes.reserve(nX * nY);

    for (long i = 0; i < nX; ++i) {
        for (long j = 0; j < nY; ++j) {
            nodes.push_back(new Node(i, j)); // Initialize each Node
        }
    }

    // Read periodicity from config
    periodicity[0] = config["domain"]["periodicity"]["x"] ? 1 : 0; // Periodicity in the X direction
    periodicity[1] = config["domain"]["periodicity"]["y"] ? 1 : 0; // Periodicity in the Y direction

    string inputFile = config["domain"]["input_file"];
    ifstream fin(inputFile);

    if (!fin.is_open()) {
        cerr << "Error opening file: " << inputFile << endl;
        return;
    }

    // Read domain from CSV file
    string line;
    long idx = 0;
    while (getline(fin, line)) {
        stringstream ss(line);
        int value;
        while (ss >> value) {
            nodes[idx]->id = value;
            idx++;
            if (ss.peek() == ',') ss.ignore();
        }
    }
    fin.close();
}

void Domain::initialize(const nlohmann::json& config, Constants &constants) {
    double p0 = 0.0;
    double p1 = 0.0;
    double p2 = 0.0;
    double s = 0.5;  // Saturation of domain with respect to phi1

    double rho1 = constants.rho1;
    double rho2 = constants.rho2;
    double beta = constants.beta;
    double phi1 = constants.phi1;
    double phi2 = constants.phi2;

    // Set properties for each node
    for (auto& node : nodes) {
        if (config["simulation"]["bubble"]["shape"] == "random") { // Handle random bubble shape
            // Set initial velocity
            node->u[0] = 0.0;
            node->u[1] = 0.0;

            // Set initial pressure
            node->p = 0.0;

            if (node->id == 20) { // Solid wall
                node->phi = 0.0;
            } else {
                node->phi = 0.55; // Need to change this to random distribution (CH_setup.py, line ~360)
            }

        } else {
            // Handle other shapes here
            
        }

        node->rho = (rho1 * (node->phi - phi2) + rho2 * (phi1 - node->phi)) / (phi1 - phi2);
        node->mu = 2 * beta * (node->phi - phi2) * (node->phi - phi1) * (2 * node->phi - (phi2 + phi1));
        node->tau = config["simulation"]["tau"];
    }
}
