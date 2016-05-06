#ifndef NODES_H
#define NODES_H
#include "Eigen/Dense"
#include <iostream>
#include <string>


class ClassNodes{
public:
    ClassNodes();
    void setid(const int&);
    void setcoordinates(const VectorXd&);
    double save_Sol(const double&);

    int getid();
    VectorXd getcoordinates();
    double getSol();


private:
    int id;
    VectorXd coordinates;
    double Sol;

};

#endif // NODES_H
