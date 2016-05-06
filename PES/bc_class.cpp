#include "bc_class.h"


//Constructor
BC_Class::BC_Class()
{

}


void BC_Class::setid(const int& input)
{
id=input;
}

void BC_Class::setnodes(const double& n1, const double& n2)
{
nodes.resize(1,2);
nodes<<n1 , n2 ;
}

void BC_Class::setvalue(const double& input)
{
value=input;

}

MatrixXd BC_Class::getnodes()
{
return nodes;
}
