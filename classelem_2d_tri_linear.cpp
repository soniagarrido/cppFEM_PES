#include "classelem_2d_tri_linear.h"
//Constructor
ClassElem_2D_tri_linear::ClassElem_2D_tri_linear()
{

}


//deffinition of the formulation --> weight, integration ponits, Shape functions and its derivatives

void ClassElem_2D_tri_linear::setformulation(){
    VectorXd Ne(3);
    MatrixXd xi(2,1) , dNe(3,2);

    nelnodes=3;  //number of nodes per element

    ngaus=1;    //number of gauss points

    w.resize(1);
    w(0)=0.5;   //weight vectors

    xi(0,0)=1./3.;  //position of gp in chi
    xi(1,0)=1./3.;  //position of gp in eta

    N.resize(1,3);
    dN.resize(2,3);


    for (int i=0 ; i<ngaus ; i++)
    {
        //Shape functions formulas
        Ne(0)=xi(0,i);
        Ne(1)=xi(1,i);
        Ne(2)=1.-xi(0,i)-xi(1,i);
        //Shape function storage
        N.row(i)=Ne;
        //Shape functions derivatives formulas
        dNe=dNe*0;
        dNe(0,0)=1.;
        dNe(1,1)=1.;
        dNe(2,0)=-1.;
        dNe(2,1)=-1.;
        //Shape function derivatives storage
        for (int j=0 ; j<nelnodes ; j++)
        {
            dN(i*2,j)=dNe(j,0);
            dN(i*2+1,j)=dNe(j,1);
        }
    }

}

void ClassElem_2D_tri_linear::setid(const int& input)
{
id=input;
}
void ClassElem_2D_tri_linear::setdiff(const double& input)
{
diff=input;
}
void ClassElem_2D_tri_linear::setsource(const double& input)
{
source=input;
}
void ClassElem_2D_tri_linear::set_local_conectivity(const VectorXd& input)
{
local_conectivity=input;
}
void ClassElem_2D_tri_linear::set_local_coordinates(const MatrixXd& input)
{
local_coordinates=input;
}

VectorXd ClassElem_2D_tri_linear::get_local_conectivity()
{
return local_conectivity;
}
MatrixXd ClassElem_2D_tri_linear::get_local_K()
{
return local_K;
}
MatrixXd ClassElem_2D_tri_linear::get_local_f()
{
return local_f;
}
void ClassElem_2D_tri_linear:: compute_local_K_and_f()
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


//Ke=Ke+(diff*dvol*((res.row(0).transpose()*res.row(0))+(res.row(1).transpose()*res.row(1))));
Ke=Ke+(diff*((Nx.transpose()*Nx)+(Ny.transpose()*Ny))*dvol);

fe=fe+N.transpose()*source*dvol;

}

local_K=Ke;
local_f=fe;

}
