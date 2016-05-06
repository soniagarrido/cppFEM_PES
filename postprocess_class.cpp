#include "postprocess_class.h"
#include <iostream>
#include <fstream>


using namespace Eigen;

using namespace std;

//Constructor

postprocess_class::postprocess_class()
{

}

void postprocess_class::export_vtk(vector<ClassElem_2D_tri_linear>& elem_input ,vector<ClassNodes>& node_input)

{

int num_nodes=node_input.size();
int nelements=elem_input.size();
int node_per_element=elem_input[0].get_local_conectivity().size();
ofstream myfile;
myfile.open ("MyParaviewFile_2D_tri_linear.vtk"); //for 2D triangular linear elements
myfile << "# vtk DataFile Version 1.0\n";
myfile << "ECM-CELL DIFFUSION-MECHANICS\n";
myfile << "ASCII\n";
myfile << "\n";
myfile << "DATASET UNSTRUCTURED_GRID\n";
myfile << "POINTS "<<num_nodes<<" float\n";

// WRITING COORDINATES OF NODES

for (int i=0; i<num_nodes; i++){
    myfile << node_input[i].getcoordinates().transpose()<<" 0.0000" <<"\n" ;

}


// WRITING CONNECTIVITY OF NODES
myfile << "\nCELLS "<< nelements<<" "<<(1+node_per_element)*nelements<<"\n";

for (int i=0; i<nelements; i++){
myfile << node_per_element<<" "<<elem_input[i].get_local_conectivity().transpose()<<"\n";
}

myfile << "CELL_TYPES "<<nelements<<"\n";
for (int i=0; i<nelements; i++){
    myfile<<"5 ";
    //myfile<<elem_input[i].get_paraview_type().
}


//WRITING VARIABLES

myfile << "\nPOINT_DATA "<<num_nodes<<"\n" ;
myfile << "SCALARS Ux float\n";
myfile << "LOOKUP_TABLE default\n";

for (int i=0; i<num_nodes; i++){
    myfile << node_input[i].getSol()<<"\n" ;

}



myfile.close();

}
