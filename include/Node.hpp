#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

class Node {
public:
    long x;
    long y;
    int id;
    /* 
    Node ID key:
        0 = General fluid node
        3 = Inlet node
        4 = Outlet node
        20 = Solid node
        21-29 = Fluid node next to solid
          21 = ne
          22 = e
          23 = se
          24 = n
          25 = middle
          26 = s
          27 = nw
          28 = w
          29 = sw
    */
    bool isEdge;

    // Physical properties
    double uX;       // Velocity in x direction
    double uY;       // Velocity in y direction
    double phi;      // Order parameter
    double rho;      // Density
    double tau;      // Relaxation time
    double p;        // Pressure
    double pStar;    // Corrected pressure value from paper
    double pThermo;  // Thermodynamic pressure
    double mbl;      // Mobility
    double nu;       // Kinematic viscosity
    double mu;       // Dynamic viscosity
    double forceX;   // Summation of forces term: gravity, surface, pressure, and viscous forces
    double forceY;   // Used in NS eqn
    double tmp;      // Temporary variable to store intermediate values

    // Residual values
    double resUX;
    double resUY;
    double resPhi;
    double resP;
    double oldUX;
    double oldUY;
    double oldPhi;
    double oldP;
    double oldMu;
    double mu0;

    // Gradient values
    double d2mu;
    double dudx;
    double dudy;
    double dvdx;
    double dvdy;
    double dpdx;
    double dpdy;
    double dpStardx;
    double dpStardy;
    double dphidx;
    double dphidy;
    double d2phidx2;
    double uSqr;
    std::vector<double> eDvdx;
    std::vector<double> eDudy;

    // Particle distribution functions
    std::vector<double> gIn;
    std::vector<double> gOut;
    std::vector<double> gEq;
    std::vector<double> sourceG;

    std::vector<double> hIn;
    std::vector<double> hOut;
    std::vector<double> hEq;
    std::vector<double> sourceH;

    // std::vector<int> nodeLookup;         // Node look-up table
    // std::vector<int> inletNeighbors;     // Inlet neighbor look-up table
    // std::vector<int> outletNeighbors;    // Outlet neighbor look-up table

    Node(int posX, int posY);
};

#endif // NODE_HPP