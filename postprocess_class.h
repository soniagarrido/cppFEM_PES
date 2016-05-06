#ifndef POSTPROCESS_CLASS_H
#define POSTPROCESS_CLASS_H

#include <iostream>
#include <fstream>
#include<ClassNodes.h>
#include<classelem_2d_tri_linear.h>
using namespace Eigen;
using namespace std;


class postprocess_class
{
public:
    postprocess_class();


    void export_vtk(vector<ClassElem_2D_tri_linear>& ,vector<ClassNodes>&);


};

#endif // POSTPROCESS_CLASS_H
