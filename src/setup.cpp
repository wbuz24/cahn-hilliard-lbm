
 	/******************************** setup.cpp *********************************/

  /* UTK PEM Electrolyzer two-phase flow model 
	*  Implemented in cpp by Will Buziak
	*  Model developed by Frida Ronning and Anirban Roy 
  *  Advisors: 
  *   Dr. Matthew Mench
  *   Dr. Dougles Aaron
	*/

#include "Cahn-Hilliard.hpp"
using namespace std;

vector <Node *> Setup(int nx, int ny) {
	vector <Node *> domain;
	Node *n;
	int i;

	for (i = 0; i < nx * ny; i++) {
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

		domain.push_back(n);
	}

	return domain;
}

void Node::initial_config(int maxIter) {
	(void) maxIter;
}

