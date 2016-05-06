#ifndef CLASSELEM_2D_TRI_LINEAR_H
#define CLASSELEM_2D_TRI_LINEAR_H
#include "Eigen/Dense"
#include <string>
#include<class_aux.h>

using namespace Eigen;
using namespace std;

class ClassElem_2D_tri_linear
{
public:
    ClassElem_2D_tri_linear();
    void setid(const int&);
    void setdiff(const double&);
    void setsource(const double&);
    void setformulation();
    void set_local_conectivity(const VectorXd&);
    void set_local_coordinates(const MatrixXd&);

    void compute_local_K_and_f();

    VectorXd get_local_conectivity();
    MatrixXd get_local_K();
    MatrixXd get_local_f();
protected:
int id;
double diff; //diffusivity of the material

VectorXd local_conectivity;
MatrixXd local_coordinates;
double source;
int nelnodes;
int ngaus;
VectorXd w;
MatrixXd N;
MatrixXd dN;
MatrixXd local_K;
MatrixXd local_f;

};

#endif // CLASSELEM_2D_TRI_LINEAR_H
