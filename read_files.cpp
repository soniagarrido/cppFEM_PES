#include "Eigen/Dense"
#include <iostream>
#include <fstream>
#include <string>


#define MAXBUFSIZE  ((int) 1e6)
using namespace std;
using namespace Eigen;
MatrixXd read_data(const string& file_path)
{

    int x, y;
    int nrows = 0;
    int ncolumns = 0;
    string line;
    MatrixXd temp;

    ifstream in(file_path);

    //Count number of columns and rows
    while (getline(in, line)){
        stringstream is(line);
        ncolumns = 0;

        while (is)
        {
            std::string sub;
            is >> sub;
          ++ncolumns;
        }

        ++nrows;

    }
        --ncolumns;

    //Go to the beggining of the file again
    in.clear();
    in.seekg(0, ios::beg);

    //Error output for not opening file
    if (!in) {
      cout << "Cannot open file.\n";
      //return;
    }
    //Matrix population
    temp.resize(nrows, ncolumns);
    for (x = 0; x < nrows; x++) {
    for (y = 0; y < ncolumns; y++) {
        in >> temp(x,y);
      }
    }

    in.close();
    return temp;
};

