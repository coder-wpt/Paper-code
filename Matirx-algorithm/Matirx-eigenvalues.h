#ifndef MATIRX_EIGENVALUES_H
#define MATIRX_EIGENVALUES_H

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

template<int N>
class Matirx_algorithm
{
private:
    vector<double>w;
    vector<double>w0;
    double maxEV;
    double CI;
    double CR;
    double RI;
    vector<double>EV;
    vector<vector<double>>array;
    vector<double> Matirx_mul();
    
public:
    Matirx_algorithm(double a[N][N],double ri):RI(ri)
    {
        
        for(int i = 0; i < N ; ++i)
        {
            vector<double>temp;
            for(int j = 0 ; j < N ; ++j)
            {
                temp.push_back(a[i][j]);
            }
            array.push_back(temp);
        }
    }

    void Calculation_CR();
    void Calculation_w();
    void Calculation_EV();
    void run(){
        Calculation_w();
        Calculation_EV();
        Calculation_CR();
         
        cout<<endl;
        cout<<"w:"<<endl;
        for(int i=0;i<N;i++)
        {
            cout<<w[i]<<" ";
        }
        cout<<endl;
        cout<<"w0:"<<endl;
        for(int i=0;i<N;i++)
        {
            cout<<w0[i]<<" ";
        }
        cout<<endl;
        cout<<"maxEV:"<<maxEV<<endl;
        cout<<"C.I.="<<CI;
        cout<<"C.R.="<<CR; 
        cout<<endl;
    }
};

template<int N>
vector<double> Matirx_algorithm<N>::Matirx_mul()
{
    if((array.empty()||w.empty())&&array.size()!=w.size())return vector<double>();

    vector<double>ret;
    for(int i=0 ; i < N ; ++i)
    {
        double temp = 0;
        for(int j = 0; j < N ;++j)
        {
            temp += array[i][j]*w[j];
        }  
        ret.push_back(temp);
    }
    return ret; 
}

template<int N>
void Matirx_algorithm<N>::Calculation_CR()
{
    if(maxEV==0)return;

    CI = (maxEV-N)/(N-1);

    CR = CI/RI;
}
template<int N>
void Matirx_algorithm<N>::Calculation_w()
{
    if(array.empty())return;
    
    for(auto i:array)
    {
        double temp=1;
        for(auto j:i)
        {
            temp*=j;
        }
        w.push_back(pow(temp,double(1.0/N)));
    }

    double sum=0;
    for(auto it:w)
    {
        sum+=it;
    }
    for(auto it:w)
    {
        w0.push_back(it/sum);
    }

    return;
}


template<int N>
void Matirx_algorithm<N>::Calculation_EV()
{
    if(w.empty())return;
    
    vector<double>w_temp=Matirx_mul();

    double ret=0;
    for( int i = 0;i < N ; ++i )
    {
        ret+=w_temp[i]/w[i];
    }
    maxEV=ret/4;
}
#endif
