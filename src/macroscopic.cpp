#include "macroscopic.hpp"
#include "mathOperations.hpp"
#include <cmath>

using namespace std;

void macroscopic(Domain &domain, Constants &constants) {
    // Definition of constants
    double phi1 = constants.phi1;
    double phi2 = constants.phi2;
    double rho1 = constants.rho1;
    double rho2 = constants.rho2;
    double beta = constants.beta;
    double nu1 = constants.nu1;
    double nu2 = constants.nu2;
    double gX = constants.gX;
    double gY = constants.gY;
    double k = constants.k;

    // Calculate gradient of phi
    derivativeX(domain, &Node::phi, &Node::dphidx);
    derivativeY(domain, &Node::phi, &Node::dphidy);

    // Gradient calculations
    derivativeX(domain, &Node::uX, &Node::dudx);
    derivativeY(domain, &Node::uX, &Node::dudy);
    derivativeX(domain, &Node::uY, &Node::dvdx);
    derivativeY(domain, &Node::uY, &Node::dvdy);

    Node* node;
    for (long i; i < domain.nX; i++) {
        for (long j; j < domain.nY; j++) {
            node = domain.nodes[i][j];

            node->pStar = 0;
            node->phi = 0;
            node->uX = 0;
            node->uY = 0;

            for (long k; k < 9; k++) {
                // Calculates composition from CH equilibrium functions
                node->phi += node->hIn[k];

                // Calculates velocity from NS equilibrium functions
                node->uX += e[k][0] * node->gIn[k];
                node->uY += e[k][1] * node->gIn[k];

                // Calculates pressure from NS equilibrium functions
                node->pStar += node->gIn[k];
            }

            // Set limits for composition to remain between 0 and 1
            if (node->phi <= min(phi1, phi2)) {
                node->phi = min(phi1, phi2);
            } else if (node->phi >= max(phi1, phi2)) {
                node->phi = max(phi1, phi2);
            }

            // Calculate density from composition
            node->rho = (rho1 * (node->phi - phi2) + rho2 * (phi1 - node->phi)) / (phi1 - phi2);
            node->p = node->pStar * node->rho / 3;

            node->nu = (nu1 * (node->rho - rho2) + nu2 * (rho1 - node->rho)) / (rho1 - rho2);

            // Calculate mu0
            node->mu0 = 4 * beta * (node->phi - phi2) * (node->phi - phi1) * (node->phi - 0.5 * (phi2 + phi1));
        }
    }

    laplace(domain, &Node::phi, &Node::d2phidx2);

    // Force[0,:,:] = g[0]*rho[:,:] + DphiDx(rho*nu*(dudx + dvdy + dvdx + dudy), Mix=1) - (1/3)*p_star[:,:]*(rho1-rho2)*grad_phi[0,:,:] + MU*grad_phi[0,:,:]
    // Force[1,:,:] = g[1]*rho[:,:] + DphiDy(rho*nu*(dudx + dvdy + dvdx + dudy), Mix=1) - (1/3)*p_star[:,:]*(rho1-rho2)*grad_phi[1,:,:] + MU*grad_phi[1,:,:]

    // node->forceX = gX * node->rho + node->TEMP - (1/3) * node->pStar * (rho1 - rho2) * node->dphidx + node->mu * node->dphidx;
    // node->forceY = gY * node->rho + node->TEMP - (1/3) * node->pStar * (rho1 - rho2) * node->dphidy + node->mu * node->dphidy;

    for (long i; i < domain.nX; i++) {
        for (long j; j < domain.nY; j++) {
            node = domain.nodes[i][j];

            // Update mu value
            node->mu = node->mu0 - k * node->d2phidx2;
            node->mu = 2.2 * node->mu;

            // Adjusting pressure and velocities based on Lee paper suggestions (macroscopic equations)
            // node->uX = node->uX + (0.5 * forceX) / node->rho;
            // node->uY = node->uY + (0.5 * forceY) / node->rho;

            // Thermodynamic pressure calculation
            node->thermoP = node->p + (node->phi * node->mu0 - beta * pow((pow(node->phi, 2) - node->phi), 2)) - k * node->phi * node->d2phidx2 + 0.5 * k * (pow(node->dphidx, 2) + pow(node->dphidy, 2));
        }
    }
    return;
}