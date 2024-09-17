#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>

class Domain; // Forward declaration

class Node {
  public:
    // Position in the lattice
    int x;
    int y;

    // Physical properties
    double phi;    // Order parameter
    double rho;    // Density
    double mu;     // Dynamic viscosity
    double tau;    // Relaxation time
    double p;      // Pressure

    // Velocity components
    std::vector<double> u; // Size 2: u[0]=u_x, u[1]=u_y

    // Distribution functions (size 9 for D2Q9 model)
    std::vector<double> h;          // Equilibrium distribution function
    std::vector<double> hBarIn;     // Incoming distribution function
    std::vector<double> hBarOut;    // Outgoing distribution function
    std::vector<double> G;          // For Cahn-Hilliard equation
    std::vector<double> GBarIn;
    std::vector<double> GBarOut;

    std::vector<Node*> neighbors;

    Node(int posX, int posY);
    void initialConfig(Domain* domain, int maxIter, double refLen, double deltaX);
};

#endif // NODE_HPP