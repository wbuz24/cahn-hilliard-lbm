#include <vector>

class Node {
public:
  int X;
  int Y;
  double Phi;
  double Tau; // initialize to .5

  Node *Neighbors[9];
};
