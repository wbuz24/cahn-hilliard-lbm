 	/******************************** setup.cpp *********************************/

  /* UTK PEM Electrolyzer two-phase flow model 
	*  Implemented in cpp by Will Buziak
	*  Model developed by Frida Ronning and Anirban Roy 
  *  Advisors: 
  *   Dr. Matthew Mench
  *   Dr. Dougles Aaron
	*/

#include "cahn-hilliard.hpp"
#include <cstdio>
#include <fstream>
using namespace std;

/* Domain constructor */
void Domain::Setup() {
	Node *n;
	int i;

  /* Create an empty domain with fresh nodes */
	for (i = 0; i < Nx * Ny; i++) {
		n = new Node;

		n->Phi = 0;
		n->Rho = 0;
		n->P = 0;

		/* Create vectors with zeros */
		n->U.resize(2, 0);
		n->H.resize(2, 0);
		n->H_bar_in.resize(9, 0);
		n->H_bar_out.resize(9, 0);
		n->G.resize(9, 0);
		n->G_bar_in.resize(9, 0);
		n->G_bar_out.resize(9, 0);

		Domain.push_back(n);
	}

	printf("Sanity check: nx * ny: %d domain size: %ld\n", Nx * Ny, Domain.size());
}

/* Optionally read in csv file, must be inserted on command line */
void Domain::Read_CSV(vector <int> &temp_domain) {
  int curr; 
  char temp; 
	ifstream fin;

  /* read each line and parse for each number */
	fin.open(Inputfile);
  do { 
    scanf("%d%c", &curr, &temp); 

  } while(temp != '\n'); 
	
	fin.close();
}

void Domain::Domain_initialize(double ref_len, double deltax) {
	vector <int> temp_domain;
	double pitch_length, sphere_radius;
	int i, j;

	if (Read_flag) {
		/* Optionally read in a domain from a file */
		Read_CSV(temp_domain);
	}
	else {
		pitch_length = (ref_len / deltax) / 5;
		sphere_radius = pitch_length / 6;

		/* create a temporary domain */
		temp_domain.resize(Nx * Ny, 0);

		/* row-col justification: vec[i][j] = vec[i * rows + j] */
		for (i = 0; i < Nx; i++) {
			for (j = 0; j < Ny; j++) {
				/* comment for solid walls on edges */
				if (!j) temp_domain[i * Nx + j] = 20;
				if (j == Ny - 1) temp_domain[i * Nx + j] = 20;
				if (!i) temp_domain[i * Nx + j] = 20;
				if (i == Nx - 1) temp_domain[i * Nx + j] = 20;
			}
		}
	}

	/* set the domain node values */

	// Hey, Price this is where I am at right now 

}

void Node::Initial_config(Domain *domain, int maxIter, double ref_len, double deltax) {
	bool restart_flag = 0;
	long restart_iter; // Set when calling restart

	restart_iter = 30000;

	/* This all mimics the python code */
	domain->Domain_initialize(ref_len, deltax);

	(void) restart_flag;
	(void) maxIter;
}

