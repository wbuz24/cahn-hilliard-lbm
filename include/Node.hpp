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
        5 = Edge node
        20 = Solid node
        21-29 = Fluid node next to solid
          21 = ne
          22 = e
          23 = se
          24 = n
          26 = s
          27 = nw
          28 = w
          29 = sw
    */

    // Physical properties
    double uX;       // Velocity in x direction
    double uY;       // Velocity in y direction
    double phi;      // Order parameter
    double rho;      // Density
    double tau;      // Relaxation time
    double p;        // Pressure
    double pStar;    //
    double thermoP;  // Thermodynamic pressure
    double mbl;      // Mobility
    double nu;       // Kinematic viscosity
    double mu;       // Dynamic viscosity
    double mu0;
    double muOld;
    double forceX;   // Source gravity in x direction
    double forceY;   // Source gravity in y direction
    double tmp;      // Temporary variable to store intermediate values

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

    // Particle distribution functions (size 9 for D2Q9 model)
    std::vector<double> gIn;
    std::vector<double> gEq;
    std::vector<double> gBarIn;
    std::vector<double> gBarOut;
    std::vector<double> gBarEq;
    std::vector<double> sourceGBar;

    std::vector<double> hIn;
    std::vector<double> hEq;
    std::vector<double> hBarIn;
    std::vector<double> hBarOut;
    std::vector<double> hBarEq;
    std::vector<double> sourceHBar;

    std::vector<int> neighbors;  // Neighbor look-up table

    Node(int posX, int posY);
};

#endif // NODE_HPP