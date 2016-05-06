#include "solver.h"
#include<classelem_2d_tri_linear.h>
#include<bc_class.h>

//Constructor
Solver::Solver()
{

}

//Assembly

void Solver::assembly_global_K_and_f(vector<ClassElem_2D_tri_linear>& input , const int& neq )
{

global_K.resize(neq,neq);
global_f.resize(neq,1);

for (int k=0; k<input.size() ; k++)
{
VectorXd Te = input[k].get_local_conectivity();
MatrixXd K_aux = input[k].get_local_K();
MatrixXd f_aux = input[k].get_local_f();

for (int i=0 ; i<Te.size() ; i++)
{
    for (int j=0; j<Te.size() ; j++)
    {
global_K(Te(i),Te(j))=global_K(Te(i),Te(j))+K_aux(i,j);
    }
global_f(Te(i),0)=global_f(Te(i),0)+f_aux(i,0);
}
}
}

//BC

void Solver:: apply_bc(const MatrixXd& data_bc, const int& neq)
{
int ndir;
MatrixXd A,b,c;
ndir=data_bc.col(0).size();

A.resize(ndir,neq);
A=A*0;

for (int i=0; i<ndir ; i++)
{
A(i,data_bc(i,0))=1;
}

b=data_bc.col(1);
c.resize(ndir,ndir);
c=c*0;

global_K.conservativeResize(neq+ndir,neq+ndir);

global_f.conservativeResize(neq+ndir,1);


global_K.block(0,neq,neq,ndir)=A.transpose();
global_K.block(neq,0,ndir,neq)=A;
global_K.block(neq,neq,ndir,ndir)=c;


global_f.block(neq,0,ndir,1)=b;

}

//Solve

void Solver::solve_linear_system()
{
results=global_K.partialPivLu().solve(global_f);
}


//Get

MatrixXd Solver::get_solution()
{
return results;
}




