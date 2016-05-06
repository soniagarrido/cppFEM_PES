#ifndef BC_CLASS_H
#define BC_CLASS_H
#include"Eigen/Dense"
#include <string>

using namespace Eigen;
using namespace std;

class BC_Class
{
public:
    BC_Class();
    void setid(const int&);
    void setnodes(const double&, const double&);
    void setcoordinates(const MatrixXd&);
    void setvalue(const double&);
    void compute_contribution();
    MatrixXd getnodes();
    MatrixXd get_nodal_contribution(const int&);


private:
    int id;
    MatrixXd nodes;
    MatrixXd coordinate1;
    MatrixXd coordinate2;
    double value;
    double contribution1,contribution2;
};

#endif // BC_CLASS_H
