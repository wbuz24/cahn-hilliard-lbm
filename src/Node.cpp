#include "node.hpp"

Node::Node(int x_coord, int y_coord) : x(x_coord), y(y_coord), id(0) {
	uX = 0;
	uY = 0;
	
	phi = 0;
	rho = 0;
	tau = 0;
	p = 0;
	pStar = 0;
	thermoP = 0;
	mbl = 0;
	nu = 0;
	mu = 0;
	mu0 = 0;
	muOld = 0;

	d2mu = 0;
	dudx = 0;
	dudy = 0;
	dvdx = 0;
	dvdy = 0;
	dpdx = 0;
	dpdy = 0;
	dphidx = 0;
	dphidy = 0;
	d2phidx2 = 0;
	biasedDudx = 0;
	biasedDudy = 0;
	biasedDvdx = 0;
	biasedDvdy = 0;
	uSqr = 0;

	eDudy.resize(9, 0);
	eDvdx.resize(9, 0);

	gIn.resize(9, 0);
	gEq.resize(9, 0);
	gBarIn.resize(9, 0);
	gBarOut.resize(9, 0);
	gBarEq.resize(9, 0);
	sourceGBar.resize(9, 0);

	hIn.resize(9, 0);
	hEq.resize(9, 0);
	hBarIn.resize(9, 0);
	hBarOut.resize(9, 0);
	hBarEq.resize(9, 0);
	sourceHBar.resize(9, 0);

	neighborLookup.resize(12, false);
}
