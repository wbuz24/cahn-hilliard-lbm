#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include "json.hpp"
#include "domain.hpp"
#include "node.hpp"

using namespace std;

Domain::Domain(long nx, long ny, long nz, const nlohmann::json& config) : nX(nx), nY(ny), nZ(nz), readFlag(false) {
    nodes.reserve(nX * nY);

    for (long i = 0; i < nX; ++i) {
        for (long j = 0; j < nY; ++j) {
            nodes.push_back(new Node(i, j, 0)); // Initialize each Node
        }
    }

    // Read periodicity from config
    periodicity[0] = config["domain"]["periodicity"]["x"] ? 1 : 0; // Periodicity in the X direction
    periodicity[1] = config["domain"]["periodicity"]["y"] ? 1 : 0; // Periodicity in the Y direction
    periodicity[2] = config["domain"]["periodicity"]["z"] ? 1 : 0; // Periodicity in the Z direction

    if (config["domain"]["read_flag"]) {
        readFlag = true;
        inputFile = config["domain"]["input_file"];
    }

    if (config["domain"]["write_flag"]) {
        writeFlag = true;
        outputFile = config["domain"]["output_file"];
    }
}

void Domain::readCSV() {
    ifstream fin(inputFile);
    string line;
    long idx = 0;

    if (!fin.is_open()) {
        cerr << "Error opening file: " << inputFile << endl;
        return;
    }

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

void Domain::writeCSV() {
    ofstream fout(outputFile);

    if (!fout.is_open()) {
        cerr << "Error opening file: " << outputFile << endl;
        return;
    }

    for (long i = 0; i < nX; i++) {
        for (long j = 0; j < nY; j++) {
            fout << nodes[i * nY + j]->id;
            if (j < nY - 1) fout << ",";
        }
        fout << endl;
    }
    fout.close();
}

void Domain::initialize(double refLen, double deltaX) {
    if (readFlag) {
        readCSV();
    } else {
        double pitchLength = (refLen / deltaX) / 5.0;
        double sphereRadius = pitchLength / 6.0;

        // Directly initialize node values
        for (long i = 0; i < nX; i++) {
            for (long j = 0; j < nY; j++) {
                Node* node = nodes[i * nY + j];

                // Create domain using spheres example (Save this for later)

                // create_boolean_domain_with_hcp_spheres(sphere_radius, pitch_length)
                // temp_domain[:,0] = 20  #bottom wall (full domain)
                // temp_domain[:,ny-1] = 20 #top wall (full domain)
                // temp_domain[0,:] = 20  #left wall (full domain)
                // temp_domain[nx-1,:] = 20  #right wall (full domain)
            }
        }

        // Save domain to file
        if (writeFlag) {
            writeCSV();
        }   
    }
}

void Domain::initializeMacros(double uP, double deltaT, double deltaX) {
    double p0 = 0.0;
    double p1 = 0.0;
    double p2 = 0.0;

    // Set properties for each node
    for (auto& node : nodes) {
        node->rho = 1.0; // Set initial density

        // Set initial velocity
        if (node->id == 20) { // Solid wall
            node->u[0] = 0.0;
            node->u[1] = 0.0;
            node->p = 0.0;
            node->phi = 0.0;
        } else {
            node->u[0] = uP * deltaT / deltaX;
            node->u[1] = 0.0;
        }
    }
}