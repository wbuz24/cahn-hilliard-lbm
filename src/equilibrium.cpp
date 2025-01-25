#include "equilibrium.hpp"
#include <cmath>

void equilibriumG(Domain &domain) {
    double fEq;
    double gammaU, gamma0;
    long duE = 0;
    long eU = 0;

    Node* node;
    for (long i; i < domain.nX; i++) {
        for (long j; j < domain.nY; j++) {
            node = domain.nodes[i][j];

            if (node->id != 20) {
                for (long k; k < 9; k++) {
                    eU = e[k][0] * node->uX + e[k][1] * node->uY;
                    duE = node->eDvdx[k] * e[k][1] + node->eDudy[k] * e[k][0];

                    gammaU = w[k] * (1 + 3*eU + 4.5*pow(eU, 2) - 1.5*node->uSqr  + 3*(node->tau * duE));

                    fEq = node->rho * gammaU;
                    
                    node->gBarEq[k] = fEq / 3 + (node->p - node->rho / 3) * gamma0;
                }
            }
        }
    }
    return;
}

void equilibriumH(Domain &domain) {
    Node* node;
    double feq;

    for (long i = 0; i < domain.nX; i++) {
        for (long j = 0; j < domain.nY; j++) {
            node = domain.nodes[i][j];

            if (node->id != 20) {
                for (long k = 0; k < 9; k++) {
                    double eU = e[k][0] * node->uX + e[k][1] * node->uY;
                    double duE = node->eDvdx[k] * e[k][1] + node->eDudy[k] * e[k][0];
                    
                    feq = node->rho * w[k] * (1 + 3 * eU + 4.5 * pow(eU, 2) - 1.5 * node->uSqr + 3 * node->tau * duE);

                    node->hEq[k] = feq * node->phi;
                    node->hEq[k] += 0.5 * w[k] * (node->mbl * node->d2mu) * 0.0;
                }
            }
        }
    }
}

void sourceG(Domain &domain) {
    (void)domain;
    // nu = (nu1*(rho - rho2) + nu2*(rho1 - rho))/(rho1-rho2)

    // Force = zeros((2,nx,ny), dtype=float) 

    // grad_phi = grad(phi, mix=1.0)
    // grad_p_star = grad(p_star, mix=1.0)
    

    // # Force[0,:,:] = g[0]*rho[:,:] + nu*(dvdx + dudx)*(rho1-rho2)*grad_phi[0,:,:] - (1/3)*p_star[:,:]*(rho1-rho2)*grad_phi[0,:,:] - (0.0/3)*rho[:,:]*grad_p_star[0,:,:] + MU*grad_phi[0,:,:]

    // # Force[1,:,:] = g[1]*rho[:,:] + nu*(dudy + dvdy)*(rho1-rho2)*grad_phi[1,:,:] - (1/3)*p_star[:,:]*(rho1-rho2)*grad_phi[1,:,:] - (0.0/3)*rho[:,:]*grad_p_star[1,:,:] + MU*grad_phi[1,:,:]

    
    // Force[0,:,:] = g[0]*rho[:,:] + DphiDx(rho*nu*(dudx + dvdy + dvdx + dudy), Mix=1) - (1/3)*p_star[:,:]*(rho1-rho2)*grad_phi[0,:,:] - (0.0/3)*rho[:,:]*grad_p_star[0,:,:] + MU*grad_phi[0,:,:]

    // Force[1,:,:] = g[1]*rho[:,:] + DphiDy(rho*nu*(dudx + dvdy + dvdx + dudy), Mix=1) - (1/3)*p_star[:,:]*(rho1-rho2)*grad_phi[1,:,:] - (0.0/3)*rho[:,:]*grad_p_star[1,:,:] + MU*grad_phi[1,:,:]


    // source_g1 = zeros((9,nx,ny))

    // for ix in prange(nx):
    //     for iy in prange(ny):
    //         if domain[ix,iy] != 20: 
    //             for i in prange(9):
    //                 eu = (e[i,0]*u[0,ix,iy] + e[i,1]*u[1,ix,iy])

    //                 source_g1[i,ix,iy] = 0.5 * w[i]* ( (3*(e[i,0] - u[0,ix,iy])*Force[0,ix,iy] + 3*(e[i,1] - u[1,ix,iy])*Force[1,ix,iy]) + (9*(eu)*(e[i,0]*Force[0,ix,iy] + e[i,1]*Force[1,ix,iy])) )
                    
    // return source_g1
    return;
}

void sourceH(Domain &domain) {
    (void)domain;
    // grad_phi = grad(phi, mix=1.0)
    
    // Force = zeros((2,nx,ny), dtype=float)

    // L2_norm_egrad_phi = sqrt(grad_phi[0,:,:]**2 + grad_phi[1,:,:]**2)

    // source_h1 = zeros((9,nx,ny), dtype=float)

    // for ix in prange(nx):
    //     for iy in prange(ny):
    //         if domain[ix,iy] != 20: 
    //             interface_normal = array((0.0 , 0.0), dtype=float)

    //             if L2_norm_egrad_phi[ix,iy] >= L2_norm_thrshld:
    //                 interface_normal[0] = grad_phi[0,ix,iy]/L2_norm_egrad_phi[ix,iy]
    //                 interface_normal[1] = grad_phi[1,ix,iy]/L2_norm_egrad_phi[ix,iy]

    //             Force[0,ix,iy] = -4*(phi[ix,iy]- phi1)*(phi[ix,iy] - phi2)* (0.25*sqrt(2*beta/k))* interface_normal[0]/(phi1 - phi2)
    //             Force[1,ix,iy] = -4*(phi[ix,iy]- phi1)*(phi[ix,iy] - phi2)* (0.25*sqrt(2*beta/k))* interface_normal[1]/(phi1 - phi2)
                
    //             for i in prange(9):
    //                 eu = (e[i,0]*u[0,ix,iy] + e[i,1]*u[1,ix,iy])

    //                 source_h1[i,ix,iy] = 0.5 * w[i]* Mlb[ix,iy] * ( (3*(e[i,0] - u[0,ix,iy])*Force[0,ix,iy] + 3*(e[i,1] - u[1,ix,iy])*Force[1,ix,iy]) + (9*(eu)*(e[i,0]*Force[0,ix,iy] + e[i,1]*Force[1,ix,iy])) )
                    
    // return source_h1
    return;
}