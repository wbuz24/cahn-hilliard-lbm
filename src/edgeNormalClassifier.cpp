#include "edgeNormalClassifier.hpp"
#include <cmath>

using namespace std;

vector<Node*> identifyNeighbors(Domain &domain, Node* node) {
    long x = node->x;
    long y = node->y;
    long nx = domain.nX;
    long ny = domain.nY;

    vector<Node*> neighbors;
    neighbors.resize(8, nullptr);

    /* 
    # D2Q9 Lattice structure
    #   6         3         0
    #      .      ^     .
    #         .   |   .
    #           . | . 
    #   7 <------ 4 ------> 1
    #           . |  .
    #        .    |     .
    #     .       v       .
    #   8         5         2
    */

    // Add periodic BC
    if ((0 < x && x < nx - 1) && (0 < y && y < ny - 1)) {
        // Internal node
        neighbors[0] = domain.nodes[x+1][y+1]; // NE
        neighbors[1] = domain.nodes[x+1][y];   // Right
        neighbors[2] = domain.nodes[x+1][y-1]; // SE
        neighbors[3] = domain.nodes[x][y+1];   // Up
        neighbors[4] = domain.nodes[x][y-1];   // Down
        neighbors[5] = domain.nodes[x-1][y+1]; // NW
        neighbors[6] = domain.nodes[x-1][y];   // Left
        neighbors[7] = domain.nodes[x-1][y-1]; // SW
    } else if ((x == 0) && (y == 0)) {
        // Bottom left corner of boundary
        neighbors[0] = domain.nodes[x+1][y+1]; // NE
        neighbors[1] = domain.nodes[x+1][y];   // Right
        neighbors[2] = domain.nodes[x+1][y+1]; // SE
        neighbors[3] = domain.nodes[x][y+1];   // Up
        neighbors[4] = domain.nodes[x][y+1];   // Down
        neighbors[5] = domain.nodes[x+1][y+1]; // NW
        neighbors[6] = domain.nodes[x+1][y];   // Left
        neighbors[7] = domain.nodes[x+1][y+1]; // SW
    } else if ((x == 0) && (y == ny - 1)) {
        // Top left corner
        neighbors[0] = domain.nodes[x+1][y-1]; // Flipped NE
        neighbors[1] = domain.nodes[x+1][y];   // Right
        neighbors[2] = domain.nodes[x+1][y-1]; // SE
        neighbors[3] = domain.nodes[x][y-1];   // Flipped up
        neighbors[4] = domain.nodes[x][y-1];   // Down
        neighbors[5] = domain.nodes[x+1][y-1]; // Flipped NW
        neighbors[6] = domain.nodes[x+1][y];   // Flipped left
        neighbors[7] = domain.nodes[x+1][y-1]; // Flipped SW
    } else if ((x == nx - 1) && (y == 0)) {
        // Bottom right corner
        neighbors[0] = domain.nodes[x-1][y+1]; // Flipped NE
        neighbors[1] = domain.nodes[x-1][y];   // Flipped Right
        neighbors[2] = domain.nodes[x-1][y+1]; // Flipped SE
        neighbors[3] = domain.nodes[x][y+1];   // Up
        neighbors[4] = domain.nodes[x][y+1];   // Flipped down
        neighbors[5] = domain.nodes[x-1][y+1]; // NW
        neighbors[6] = domain.nodes[x-1][y];   // Left
        neighbors[7] = domain.nodes[x-1][y+1]; // Flipped SW
    } else if ((x == nx - 1) && (y == ny - 1)) {
        // Top right corner
        neighbors[0] = domain.nodes[x-1][y-1]; // Flipped NE
        neighbors[1] = domain.nodes[x-1][y];   // Flipped right
        neighbors[2] = domain.nodes[x-1][y-1]; // Flipped SE
        neighbors[3] = domain.nodes[x][y-1];   // Flipped up
        neighbors[4] = domain.nodes[x][y-1];   // Down
        neighbors[5] = domain.nodes[x-1][y-1]; // Flipped NW
        neighbors[6] = domain.nodes[x-1][y];   // Left
        neighbors[7] = domain.nodes[x-1][y-1]; // SW
    } else if ((x == 0) && (0 < y && y < ny - 1)) {
        // Left edge
        neighbors[0] = domain.nodes[x+1][y+1]; // NE
        neighbors[1] = domain.nodes[x+1][y];   // Right
        neighbors[2] = domain.nodes[x+1][y-1]; // SE
        neighbors[3] = domain.nodes[x][y+1];   // Up
        neighbors[4] = domain.nodes[x][y-1];   // Down
        neighbors[5] = domain.nodes[x+1][y+1]; // Flipped NW
        neighbors[6] = domain.nodes[x+1][y];   // Flipped left
        neighbors[7] = domain.nodes[x+1][y-1]; // Flipped SW
    } else if ((x == nx - 1) && (0 < y && y < ny - 1)) {
        // Right edge
        neighbors[0] = domain.nodes[x-1][y+1]; // Flipped NE
        neighbors[1] = domain.nodes[x-1][y];   // Flipped right
        neighbors[2] = domain.nodes[x-1][y-1]; // Flipped SE
        neighbors[3] = domain.nodes[x][y+1];   // Up
        neighbors[4] = domain.nodes[x][y-1];   // Down
        neighbors[5] = domain.nodes[x-1][y+1]; // NW
        neighbors[6] = domain.nodes[x-1][y];   // Left
        neighbors[7] = domain.nodes[x-1][y-1]; // SW
    } else if ((0 < x && x < nx - 1) && (y == 0)) {
        // Bottom edge
        neighbors[0] = domain.nodes[x+1][y+1]; // NE
        neighbors[1] = domain.nodes[x+1][y];   // Right
        neighbors[2] = domain.nodes[x+1][y+1]; // Flipped SE
        neighbors[3] = domain.nodes[x][y+1];   // Up
        neighbors[4] = domain.nodes[x][y+1];   // Flipped down
        neighbors[5] = domain.nodes[x-1][y+1]; // NW
        neighbors[6] = domain.nodes[x-1][y];   // Left
        neighbors[7] = domain.nodes[x-1][y+1]; // Flipped SW
    } else if ((0 < x && x < nx - 1) && (y == ny - 1)) {
        // Top edge
        neighbors[0] = domain.nodes[x+1][y-1]; // Flipped NE
        neighbors[1] = domain.nodes[x+1][y];   // Right
        neighbors[2] = domain.nodes[x+1][y-1]; // SE
        neighbors[3] = domain.nodes[x][y-1];   // Flipped up
        neighbors[4] = domain.nodes[x][y-1];   // Down
        neighbors[5] = domain.nodes[x-1][y-1]; // Flipped NW
        neighbors[6] = domain.nodes[x-1][y];   // Left
        neighbors[7] = domain.nodes[x-1][y-1]; // SW
    }
    return neighbors;
}

void identifyEdges(Domain &domain) {
    int ne, right, se, above, below, nw, left, sw;
    int numNeighbors;

    Node* node;
    for (int i=0; i < domain.nX; i++) {
        for (int j=0; j < domain.nY; j++) {
            node = domain.nodes[i][j];

            if (node->id == 0) {
                vector<Node*> neighbors = identifyNeighbors(domain, node);

                ne    = neighbors[0]->id;
                right = neighbors[1]->id;
                se    = neighbors[2]->id;
                above = neighbors[3]->id;
                below = neighbors[4]->id;
                nw    = neighbors[5]->id;
                left  = neighbors[6]->id;
                sw    = neighbors[7]->id;

                numNeighbors = right + left + above + below + nw + ne + se + sw;

                if (numNeighbors > 0) {
                    // Electrolyte to the right
                    if (right && !(above && left && below && nw && ne && se && sw)) {
                        node->isEdge = true;
                    }
                    
                    // Electrolyte below
                    if (above && !(left && right && below && nw && ne && se && sw)) {
                        node->isEdge = true;
                    }
                    
                    // Electrolyte to the left
                    if (left && !(right && above && below && nw && ne && se && sw)) {
                        node->isEdge = true;
                    }
                    
                    // Electrolyte above
                    if (below && !(right && above && left && nw && ne && se && sw)) {
                        node->isEdge = true;
                    }
                    
                    // Electrolyte above right
                    if (nw && !(right && above && left && below && ne && se && sw)) {
                        node->isEdge = true;
                    }
                    
                    // Electrolyte above left
                    if (ne && !(right && above && left && below && nw && se && sw)) {
                        node->isEdge = true;
                    }
                    
                    // Electrolyte below left
                    if (se && !(right && above && left && below && nw && ne && sw)) {
                        node->isEdge = true;
                    }
                    
                    // Electrolyte below right
                    if (sw && !(right && above && left && below && nw && ne && se)) {
                        node->isEdge = true;
                    }
                }
            }
        }
    }
}

double euclideanDistance(Node* node1, Node* node2) {
    double x1 = node1->x;
    double y1 = node1->y;
    double x2 = node2->x;
    double y2 = node2->y;

    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

vector<Node*> kClosestNeighbors(Node* node, vector<Node*> edgeNeighbors, int k) {
    if (edgeNeighbors.size() < k) {
        return edgeNeighbors;  // If fewer than k neighbors, return all available
    }

    // Sort neighbors based on Euclidean distance
    sort(edgeNeighbors.begin(), edgeNeighbors.end(), [&](Node* a, Node* b) {
        return euclideanDistance(node, a) < euclideanDistance(node, b);
    });

    // Return the first k closest neighbors
    return vector<Node*>(edgeNeighbors.begin(), edgeNeighbors.begin() + k);
}

void classifyBC(Domain &domain) {
    Node* node;
    for (int i=0; i < domain.nX; i++) {
        for (int j=0; j < domain.nY; j++) {
            node = domain.nodes[i][j];

            if (node->isEdge) {
                vector<Node*> neighbors = identifyNeighbors(domain, node);
                vector<Node*> edgeNeighbors;

                for (int k=0; k < 8; k++) {
                    if (neighbors[k]->isEdge) {
                        edgeNeighbors.push_back(neighbors[k]);
                    }
                }
                // Need to check how to handle edgeNeighbors of size < 2
                edgeNeighbors = kClosestNeighbors(node, edgeNeighbors, 2);

                // Calculate slope
                double dx = edgeNeighbors[0]->x - edgeNeighbors[1]->x;
                double dy = edgeNeighbors[0]->y - edgeNeighbors[1]->y;
                double normal;

                if (dx == 0) {
                    normal = 0;
                } else if (dy == 0) {
                    normal = numeric_limits<double>::infinity();
                } else {
                    normal = -(dx/dy);
                }
                normal = 0;

                if (normal == 0) {
                    if (domain.nodes[i+1][j]->id == 0 || domain.nodes[i+1][j]->isEdge) {
                        // node2lookup[(i,j)] = [(i+1,j), -1]
                    } else {
                        // node2lookup[(i,j)] = [(i-1,j), -2]
                    }

                } else if (isinf(normal)) {
                    if (domain.nodes[i][j+1]->id == 0 || domain.nodes[i][j+1]->isEdge) {
                        if (domain.nodes[i][j+1]->id == 0) {
                            // node2lookup[(i,j)] = [(i,j+1), -3]
                        } else if (domain.nodes[i][j-1]->id != 1) {
                            // node2lookup[(i,j)] = [(i,j-1), -4]
                        } else {
                            // node2lookup[(i,j)] = [(i,j+1), -3]
                        }
                    } else {
                        // node2lookup[(i,j)] = [(i,j-1), -4]
                    }

                } else if (normal == 1) {
                    if (domain.nodes[i+1][j+1]->id == 0 || domain.nodes[i+1][j+1]->isEdge) {
                        // node2lookup[(i,j)] = [(i+1,j+1), -5]
                    } else {
                        // node2lookup[(i,j)] = [(i-1,j-1), -6]
                    }
                
                } else if (normal == -1) {
                    if (domain.nodes[i+1][j-1]->id == 0 || domain.nodes[i+1][j-1]->isEdge) {
                        // node2lookup[(i,j)] = [(i+1,j-1), -7]
                    } else {
                        // node2lookup[(i,j)] = [(i-1,j+1), -8]
                    }
                }
            }
        }
    }
}
