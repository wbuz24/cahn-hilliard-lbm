#include <vector>

class Node {
public:
  int X;
  int Y;
  double Phi;
  double Rho;
  double Mu;
  double Tau; // initialize to .5
  std::vector <double> U; /* Size is 2 */
	double P;
  std::vector <double> H;
  std::vector <double> H_bar_in;
  std::vector <double> H_bar_out;
  std::vector <double> G;
  std::vector <double> G_bar_in;
  std::vector <double> G_bar_out;

  std::vector <Node *> Neighbors; /* Array of node pointers, size will be 9 */

	void initial_config(int maxIter);
};

std::vector <Node *> Setup(int nx, int ny);
