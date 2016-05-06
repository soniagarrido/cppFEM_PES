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
void ClassElem_2D_tri_linear :: compute_local_K_and_f()
{
MatrixXd Ke;
MatrixXd fe;
VectorXd Nxi_igaus, Neta_igaus;
MatrixXd Nx,Ny;
MatrixXd Jacob;
MatrixXd res;
double dvol;

Ke.resize(nelnodes,nelnodes);
fe.resize(nelnodes,1);
Jacob.resize(2,2);
Ke=Ke*0;
fe=fe*0;

for (int i=0 ; i<ngaus ; i++)
{
Nxi_igaus=dN.row(2*i);
Neta_igaus=dN.row(2*i+1);

Jacob(0,0)=Nxi_igaus.dot(local_coordinates.col(0).transpose());
Jacob(0,1)=Nxi_igaus.dot(local_coordinates.col(1).transpose());
Jacob(1,0)=Neta_igaus.dot(local_coordinates.col(0).transpose());
Jacob(1,1)=Neta_igaus.dot(local_coordinates.col(1).transpose());

dvol=Jacob.determinant()*w(i);

res=Jacob.inverse()*dN;

Nx=res.row(0);
Ny=res.row(1);



Ke=Ke+(diff*((Nx.transpose()*Nx)+(Ny.transpose()*Ny))*dvol);

fe=fe+N.transpose()*source*dvol;

}

local_K=Ke;
local_f=fe;

}
};

#endif // CLASSELEM_2D_TRI_LINEAR_H
