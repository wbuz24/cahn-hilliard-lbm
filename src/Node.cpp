#include "Node.hpp"
#include "Domain.hpp"  // Include the Domain class

Node::Node(int x_coord, int y_coord) : x(x_coord), y(y_coord), phi(0.0), rho(0.0), p(0.0) {
	u.resize(2, 0);
	h.resize(2, 0);
	hBarIn.resize(9, 0);
	hBarOut.resize(9, 0);
	G.resize(9, 0);
	GBarIn.resize(9, 0);
	GBarOut.resize(9, 0);
}

void Node::initialConfig(Domain* domain, int maxIter, double refLen, double deltaX) {
    bool restartFlag = 0;
	long restartIter = 30000; // Set when calling restart

	/* This all mimics the python code */
	domain->initialize(refLen, deltaX);
	(void) restartFlag;
	(void) maxIter;
}
