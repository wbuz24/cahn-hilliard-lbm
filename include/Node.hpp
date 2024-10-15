#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>

class Domain; // Forward declaration

class Node {
public:
    int x;
    int y;
    int z;
    int id;
    /* 
    Node ID key:
        0 = General fluid node
        3 = Inlet
        4 = Outlet
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
    double phi;    // Order parameter
    double rho;    // Density
    double mu;     // Dynamic viscosity
    double tau;    // Relaxation time
    double p;      // Pressure
    double u[3];   // Velocity components: u[0]=u_x, u[1]=u_y, u[2]=u_z

    // Simulation values
    double muOld;
    double d2mu;
    double dudy;
    double dvdy;
    double dudx;
    double dvdx;
    double biased_dudy;
    double biased_dvdx;
    double biased_dudx;
    double biased_dvdy;
    double e_dudy;
    double e_dvdx;
    double usqr;

    // Distribution functions (size 9 for D2Q9 model)
    std::vector<double> h;          // Equilibrium distribution function
    std::vector<double> hBarIn;     // Incoming distribution function
    std::vector<double> hBarOut;    // Outgoing distribution function
    std::vector<double> G;          // For Cahn-Hilliard equation
    std::vector<double> GBarIn;
    std::vector<double> GBarOut;

    std::vector<Node*> neighbors;

    Node(int posX, int posY, int posZ);
};

#endif // NODE_HPP