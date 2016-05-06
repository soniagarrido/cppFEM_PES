#ifndef SOLVER_H
#define SOLVER_H
#include "Eigen/Dense"
#include <string>
#include <vector>
#include<classelem_2d_tri_linear.h>

class Solver
{
public:
    Solver();
    void initialize_global_K_and_f(const int&);
    void assembly_global_K_and_f(vector<ClassElem_2D_tri_linear> &, const int&);
    void apply_bc(const MatrixXd&, const int&);
    void solve_linear_system();
    MatrixXd get_solution();


private:
MatrixXd global_K;
MatrixXd global_f;
MatrixXd results;
};

#endif // SOLVER_H
