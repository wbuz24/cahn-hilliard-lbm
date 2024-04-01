 /******************************** main.cpp *********************************/

/* UTK PEM Electrolyzer two-phase flow model 
 * Implemented in cpp by Will Buziak
 * Model developed by Frida Ronning and Anirban Roy 
 * Advisors: 
 *  Dr. Matthew Mench
 *  Dr. Dougles Aaron
*/


#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "cahn-hilliard.hpp"
using namespace std;

int main(int argc, char** argv) {
	
  /*****************************************************************/
	/************** CH_Base.py definitions are here ******************/

  /* Constant Definitions */
  long nLB, maxIter, nx, ny;
  double lx, ly, deltax, deltay, ref_len, we, mlb, cont_angle;

  /* 2D vectors */
  vector < vector <int> > periodicity;
//  vector < <Node> > domain; 
  Node *n;

  /* Flow Definitions*/
  double nuP, rhoP, rho0, rho1, rho2, phi1, phi2, deltaM, sigmaP, sigma, deltaT, Re, uP, uLB, nulb, density_ratio, viscosity_ratio, mu1, mu2, nu1, nu2, k, diff, beta, d_1, d_2, Pe; 

	
	/* Class definition */
	Domain *domain;
	Node *test;

  /* Lattice Definition */
  int e[9][2] = {
    {1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, 0},
    {0, -1}, {-1, 1}, {-1, 0}, {-1, -1} };

  double weight[9] = {
    {1/36}, {1/9}, {1/36}, {1/9}, {4/9}, {1/9}, {1/36}, {1/9}, {1/36} };

  double h[9] = {
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };

  if (argc != 2) {
    printf("./bin/cahn-hilliard Number-Of-Lattice-Units\n");
    return 0;
  }

  /* Initialize a domain, likely will become input args */
  nLB = atoi(argv[1]); // number of lattice units
  maxIter = 10001;
  lx = .001;
  ly = .001;
  ref_len = ly;


  /* Grid domain bounds */
  deltax = ly / (nLB - 1);
  deltay = deltax;
  nx = lx/deltax;
  ny = ly/deltay;
  
  nuP = .000000364; // viscosity of water in physical units
  rhoP = 972; // density of water in physical units
  rho0 = 1; // density of water in lattice units
  phi1 = 1;
  phi2 = 0; // limits of the order parameter
  sigmaP = .0628; // surface tension of air-water interface
  sigma = .0001; // has to be less than 1e-3
  Re = 0; /* Reynolds number */

  uP = (nuP * Re) / (ref_len + deltax); // velocity in physical units
  deltaM = (rhoP / rho0) * (deltax * deltax * deltax);
  deltaT = sqrt((sigma / sigmaP) * deltaM);
  nulb = nuP / ((deltax*deltax) / deltaT); // kinematic viscosity

  periodicity.resize(2); /* Periodic boundary conditions */

  /* Velocity in lattice units */
  if (uP != 0) uLB = uP/(deltax/deltaT);
  else uLB = deltaT / deltax;

  density_ratio = .001;
  viscosity_ratio = 10;

  rho1 = rho0;
  rho2 = density_ratio * rho0;
  nu1 = nulb;
  nu2 = viscosity_ratio * nulb;

  mu1 = rho1*nu1;
  mu2 = rho2*nu2;

  /* Cahn Hilliard parameters define surface tension */
  diff = .1 * (ly/deltax); // diffusive interface thickness
  k = (3/2) * sigma * diff / (sqrt(phi1 - phi2));
  beta = (12 / ((phi1 - phi2) * (phi1 - phi2) * (phi1 - phi2) * (phi1 - phi2))) * (sigma/diff);

  /* Diffusion coefficient in water */
  d_1 = .00000000242; // for O2
  d_1 = .000000242;   // for water
  
  /* Pecelet number */
  if (uP != 0) Pe = (uP * diff * deltax) / d_1;
  else Pe = ((uLB * deltax) / deltaT) * ((diff * deltax) / d_1);

  /* Weber Number definition */
  we = (uLB * uLB) * ((ref_len / 2) / deltax) * ((rho1-rho2)/sigma);
  mlb = (1 / Pe) / beta;
  cont_angle = M_PI / 4;

	/* "plt" variables are for plotting in python and are currently not included*/

  /*****************************************************************/
  /************************Start of Main****************************/

	test = new Node;
	domain = new Domain;

	domain->Nx = nx;
	domain->Ny = ny;

	/* Initialize a 2D vector of nodes */
	// Unique for cpp, must initialize all vectors
	// traverse the domain, creating new nodes and initializing their values

  domain->Setup();
	test->Initial_config(domain, maxIter);

  /* Initialize Mu and Tau */
}
