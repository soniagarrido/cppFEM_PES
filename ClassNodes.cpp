#include<ClassNodes.h>
#include "Eigen/Dense"
#include <string>
#include <iostream>

using namespace std;
using namespace Eigen;

//Constructor
ClassNodes::ClassNodes(){

}

//definition of set and get

void ClassNodes::setid(const int& input){
    id=input;
}
void ClassNodes::setcoordinates(const VectorXd& input){
    coordinates=input;
}

double ClassNodes::save_Sol(const double&input){
    Sol=input;
}

int ClassNodes::getid(){
    return id;
  }
VectorXd ClassNodes::getcoordinates(){
    return coordinates;
}

double ClassNodes::getSol(){
    return Sol;
    }
