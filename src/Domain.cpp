#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include "json.hpp"
#include "domain.hpp"
#include "node.hpp"

using namespace std;

Domain::Domain(long nx, long ny) : nX(nx), nY(ny) {
    nodes.reserve(nX * nY);

    for (long i = 0; i < nX; ++i) {
        for (long j = 0; j < nY; ++j) {
            nodes[i].push_back(new Node(i, j));
        }
    }
}

// Lambda function to read in CSV input files
void readInputFile(long nX, long nY, const std::string& filename, std::function<void(long, long, int)> populateFunc) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    long i = 0;
    while (getline(fin, line)) {
        std::stringstream ss(line);
        int value;
        long j = 0;

        while (ss >> value) {
            if (i < nX && j < nY) {
                populateFunc(i, j, value);
                j++;
                if (ss.peek() == ',') ss.ignore();
            }
        }
        i++;
        if (i >= nX) break;
    }
    fin.close();
}

void Domain::initialize(const nlohmann::json& config, Constants &constants) {
    // Read periodicity from config
    periodicity[0] = config["domain"]["periodicity"]["x"] ? 1 : 0; // Periodicity in the X direction
    periodicity[1] = config["domain"]["periodicity"]["y"] ? 1 : 0; // Periodicity in the Y direction

    // Read in domain file
    std::string inputFile = config["domain"]["domain_file"];
    readInputFile(nX, nY, inputFile, [this](long i, long j, int value) {
        nodes[i][j]->id = value;
    });

    // Read in pressure file
    inputFile = config["domain"]["p_file"];
    readInputFile(nX, nY, inputFile, [this](long i, long j, int value) {
        nodes[i][j]->p = value;
    });

    // Read in order parameter file
    inputFile = config["domain"]["phi_file"];
    readInputFile(nX, nY, inputFile, [this](long i, long j, int value) {
        nodes[i][j]->phi = value;
    });

    // Read in velocity (x-direction) file
    inputFile = config["domain"]["uX_file"];
    readInputFile(nX, nY, inputFile, [this](long i, long j, int value) {
        nodes[i][j]->uX = value;
    });

    // Read in velocity (y-direction) file
    inputFile = config["domain"]["uY_file"];
    readInputFile(nX, nY, inputFile, [this](long i, long j, int value) {
        nodes[i][j]->uY = value;
    });

    double rho1 = constants.rho1;
    double rho2 = constants.rho2;
    double beta = constants.beta;
    double phi1 = constants.phi1;
    double phi2 = constants.phi2;

    // Set properties for each node
    for (int i = 0; i < nX; i++) {
        for (int j = 0; j < nY; j++) {
            Node* node = nodes[i][j];

            // Calculate density from composition and mu0
            node->rho = (rho1 * (node->phi - phi2) + rho2 * (phi1 - node->phi)) / (phi1 - phi2);
            node->mu0 = 2 * beta * (node->phi - phi2) * (node->phi - phi1) * (2 * node->phi - (phi2 + phi1));
            node->tau = config["simulation"]["tau"];
        }
    }

    // Create neighbor look up tables
    /*
    Set nodes as inlet/outlet and pick normal direction to node from legend below:
      0 = General fluid node
      3 = Inlet
      4 = Outlet
      20 = Solid node
      21-29 = Fluid node next to solid
        21 = ne = -5
        22 = e  = -1
        23 = se = -7
        24 = n  = -3
        26 = s  = -4
        27 = nw = -8
        28 = w  = -2
        29 = sw = -6
    */
}
