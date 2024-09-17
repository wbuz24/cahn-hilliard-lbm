#include <cstdio>
#include <fstream>
#include "Domain.hpp"
#include "Node.hpp"
#include <iostream>
using namespace std;

Domain::Domain(long nx, long ny) : nX(nx), nY(ny), readFlag(false) {
    nodes.reserve(nX * nY); // Reserve space for the vector

    for (long i = 0; i < nX; ++i) {
        for (long j = 0; j < nY; ++j) {
            nodes.push_back(new Node(i, j)); // Initialize each Node
        }
    }
}

Domain::~Domain() {
    for (auto node : nodes) delete node;
}

void Domain::readCSV(vector <int> &temp_domain) {
    // Optionally read in csv file (command line argument)
	int curr; 
	char temp; 
	ifstream fin;

	// Read each line and parse for each number
	fin.open(inputFile);
	do { 
		scanf("%d%c", &curr, &temp); 
	} while(temp != '\n'); 
	fin.close();
}

void Domain::initialize(double refLen, double deltaX) {
	vector <int> tempDomain;

	if (readFlag) {
		readCSV(tempDomain);
	}
	else {
		double pitchLength = (refLen / deltaX) / 5;
		double sphereRadius = pitchLength / 6;

		tempDomain.resize(nX * nY, 0);

		/* row-col justification: vec[i][j] = vec[i * rows + j] */
		for (int i = 0; i < nX; i++) {
			for (int j = 0; j < nY; j++) {
				/* comment for solid walls on edges */
				if (!j) tempDomain[i * nX + j] = 20;
				if (j == nY - 1) tempDomain[i * nX + j] = 20;
				if (!i) tempDomain[i * nX + j] = 20;
				if (i == nX - 1) tempDomain[i * nX + j] = 20;
			}
		}
	}

	/* set the domain node values */

	// Hey, Price this is where I am at right now 

}