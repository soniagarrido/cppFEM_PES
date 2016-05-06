#ifndef READ_FILES_H
#define READ_FILES_H

#include "Eigen/Dense"
#include <string>
#include <iostream>
#include <fstream>

using namespace Eigen;
using namespace std;

class read_files
{
public:


    int getn () const;
        //getn -  returns the number of gauss points
    int getncoord() const;
        //getcoord - returns ncoord
    int getnodes() const;
        //getnodes - returns nodes

    VectorXd integrationpoints();

    VectorXd weightpoints ();

    MatrixXd shapefunctions();

    MatrixXd deriv_shapefunctions();


};

#endif // READ_FILES_H
