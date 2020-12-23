#include <iostream>
#include "Matirx-eigenvalues.h"

int main()
{

    double A[4][4]={
        1,0.2,0.5,1,
        5,1,2,4,
        2,0.5,1,3,
        1,0.25,1.0/3,1
    };
    
    double B[4][4]={
        1,1.0/6,1.0/3,1,
        6,1,2,4,
        3,0.5,1,2,
        1,0.25,0.5,1
    };
    double C[4][4]={
        1,0.25,1.0/3,1,
        4,1,1,3,
        3,1,1,2,
        1,1.0/3,0.5,1
    };
    
    cout<<"A:"<<endl;
    Matirx_algorithm<4>a(A,0.89);
    a.run();
    
    cout<<"B:"<<endl;
    Matirx_algorithm<4>b(B,0.89);
    b.run();

    cout<<"C:"<<endl;
    Matirx_algorithm<4>c(C,0.89);
    c.run();

    return 0;

}

