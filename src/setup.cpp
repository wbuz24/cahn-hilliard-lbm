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

void Domain::Setup() {
	Node *n;
	int i;

	for (i = 0; i < Nx * Ny; i++) {
		n = new Node;

		n->Phi = 0;
		n->Rho = 0;
		n->P = 0;

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

void Domain::Domain_initialize() {
	vector <int> temp_domain;

	if (Read_Flag) {
		/* Optionally read in a domain from a file */
		Read_CSV(temp_domain);
	}
	else {
  	
	}

}

void Node::Initial_config(Domain *domain, int maxIter) {
	bool restart_flag = 0;
	long restart_iter; // Set when calling restart

	restart_iter = 30000;

	domain->Domain_initialize();

	(void) restart_flag;
	(void) maxIter;
}

