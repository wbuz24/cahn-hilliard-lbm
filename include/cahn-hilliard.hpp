#include <vector>
#include <string>

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

	void Initial_config(class Domain *domain, int maxIter, double ref_len, double deltax);
};

class Domain {
public:
	int Nx;
	int Ny;
	std::vector <Node *> Domain;
	std::string Inputfile;
	bool Read_flag;

	void Setup();
	void Read_CSV(std::vector <int> &temp_domain);
	void Domain_initialize(double ref_len, double deltax);
};

