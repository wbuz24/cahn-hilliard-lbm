#include <cmath>
#include "domain.hpp"
#include "mathOperations.hpp"

using namespace std;

void uSqr(Domain &domain) {
    for (long ix = 0; ix < domain.nX; ix++) {
        for (long iy = 0; iy < domain.nY; iy++) {
            Node* node = domain.nodes[ix][iy];
            node->uSqr = pow(node->uX, 2) + pow(node->uY, 2);
        }
    }
    return;
}