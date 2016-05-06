#include <iostream>
#include <vector>
#include <string>
#include"Eigen/Dense"
#include <ClassNodes.h>
#include <Classelem_2d_tri_linear.h>
#include<BC_Class.h>
#include<solver.h>
#include<class_aux.h>
#include<postprocess_class.h>


using namespace Eigen;
using namespace std;

int main()
{
MatrixXd data_coordinates, data_BC, data_conectivity,material, aux_nodes, aux_coords, aux_sol;
int num_nodes, nelements,nBC, element_type, node_per_element, dimension;
string file_path_coordinates,file_path_conectivity, file_path_bc,file_path_material;
double data_source=0; //No source term is considered in this problem


file_path_conectivity = "elem_2D_tri_linear.txt";
file_path_coordinates = "nodes_2D_tri_linear.txt";
file_path_bc = "BC.txt";
file_path_material = "material.txt";//In this case we consider the diffusivity term equal to 1


data_coordinates=read_files (file_path_coordinates);
data_conectivity= read_files(file_path_conectivity);
material=read_files(file_path_material);
data_BC=read_files(file_path_bc);

cout<<" Select element type \n";
 cout<<"1: 2D triangular linea\n";
 cout<<"2: 2D triangular quadratic \n";
 cout<<"3: 2D quadratic linear \n";
 cout<<"4: 2D quadratic quadratic \n";
 cout<<"5: 3D triangular linea\n";
 cout<<"6: 3D triangular quadratic \n";
 cout<<"7: 3D quadratic linear \n";
 cout<<"8: 3D quadratic quadratic \n";
 cout<<"Element type:  ";
 cin>>element_type;
 if (element_type != 1 && element_type != 2 && element_type != 3 && element_type != 4 && element_type != 5 && element_type != 6 && element_type != 7 && element_type != 8){
     cout<<" \n ERROR: This element type does not exist";
        return 0;
 }


if (element_type==1)
{
 dimension=2; //3D or 2D
 node_per_element=3; // nodes per element
 nelements=404; //for 2D triangular linear elements
 num_nodes=243; //for 2D triangular linear elements
 nBC=17;//for 2D triangular linear elements where inlet has u=1 and outlet u=0
}
else
{
cout<<"**************************************************"<<endl;
cout<<"Element formulation not implemented."<<endl;
cout<<"**************************************************"<<endl;
return 0;
}

    return 0;




//VECTOR OF NODE OBJECTS
vector<ClassNodes>  nod(num_nodes,ClassNodes());

for (int i=0; i<num_nodes; i++)
{
    nod[i].setid(i);
    nod[i].setcoordinates(data_coordinates.row(i));
}

//VECTOR OF ELEMENT OBJECTS

vector<ClassElem_2D_tri_linear> elements(nelements,ClassElem_2D_tri_linear());
for (int i = 0; i<nelements; i++)
{
elements[i].setid(i);
elements[i].setdiff(material(i,0));
elements[i].setsource(data_source);
elements[i].set_local_conectivity(data_conectivity.row(i));
aux_nodes=elements[i].get_local_conectivity().transpose();
aux_coords.resize(node_per_element,dimension);
for (int j=0; j<node_per_element; j++)
{
aux_coords.row(j)=nod[aux_nodes(0,j)].getcoordinates().transpose();
}
elements[i].set_local_coordinates(aux_coords);
elements[i].setformulation();
elements[i].compute_local_K_and_f();
}


//VECTOR OF BC OBJECTS

vector<BC_Class> BC(nBC, BC_Class());
for (int i=0 ; i<nBC ; i++)
{
    BC[i].setid(i);
    BC[i].setnodes(data_BC(i,0),data_BC(i,1));
    BC[i].setvalue(data_BC(i,2));
    aux_coords.resize(2,2);

}


//ASSEMBLY AND SOLVE

Solver sol;
sol.assembly_global_K_and_f(elements,num_nodes);
sol.apply_bc(data_BC,num_nodes);
sol.solve_linear_system();

//Solution node object
aux_sol=sol.get_solution();
for (int i = 0; i<num_nodes; i++ )
{
    nod[i].save_Sol(aux_sol(i));
}
}

<<<<<<< HEAD
//Postprocess

postprocess_class export_object;
export_object.export_vtk(elements, nodes);
=======
//Export the solution to vtk (paraview)
postprocess_class export_object;
export_object.postprocess(elements, nodes);
>>>>>>> origin/master

cout<<elements[1];
return 0;
}






