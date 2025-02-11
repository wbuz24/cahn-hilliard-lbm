#include "collideAndStream.hpp"

using namespace std;

void collide(Domain &domain) {
    for (long x = 0; x < domain.nX; x++) {
        for (long y = 0; y < domain.nY; y++) {
            Node* node = domain.nodes[x][y];

            if (node->id != 20) {
                for (int i = 0; i < 9; i++) {
                    node->gOut[i] = node->gIn[i] - (node->gIn[i] - node->gEq[i])/(node->tau + 0.5) + node->sourceG[i];
                    node->hOut[i] = node->hIn[i] - (node->hIn[i] - node->hEq[i])/(node->tau + 0.5) + node->sourceH[i];
                }
            }

        }
    }
    return;
}

void stream(Domain &domain) {
    long nx = domain.nX;
    long ny = domain.nY;
    long nextX, nextY;

    for (long x = 0; x < nx; x++) {
        for (long y = 0; y < ny; y++) {
            Node* node = domain.nodes[x][y];

            if (node->id == 20) continue;

            for (int i = 0; i < 9; i++) {
                nextX = x + e[i][0];
                nextY = y + e[i][1];

                // Handle x-boundary conditions
                if (domain.periodicity[0] == 1) {
                    // Periodic boundary
                    if (nextX < 0) {
                        nextX = nx - 1;
                    } else if (nextX >= nx) {
                        nextX = 0;
                    }
                } else {
                    // Stream to infinity boundary
                    if (nextX < 0 || nextX >= nx) {
                        continue;
                    }
                }

                // Handle y-boundary conditions
                if (domain.periodicity[1] == 1) {
                    // Periodic boundary
                    if (nextY < 0) {
                        nextY = ny - 1;
                    } else if (nextY >= ny) {
                        nextY = 0;
                    }
                } else {
                    // Stream to infinity boundary
                    if (nextY < 0 || nextY >= ny) {
                        continue;
                    }
                }

                // Skip if the target node is an obstacle (id == 20)
                if (domain.nodes[nextX][nextY]->id == 20) {
                    continue;
                }

                domain.nodes[nextX][nextY]->gIn[i] = node->gOut[i];
                domain.nodes[nextX][nextY]->hIn[i] = node->hOut[i];
            }
        }
    }
    return;
}