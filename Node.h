#pragma once
#include <vector>
#include <string>
using namespace std;

class Node
{
public:
    Node(){}
    Node(string Eqtype,double ab,double S_ab):Eq_type(Eqtype),Ability(ab),S_Ability(S_ab) {}
    ~Node() {}



    string Eq_type;
    double Ability;
    double S_Ability;
};

class Data
{
public:
    Data(){}
    Data(const Data& d){
        this->data=d.data;
    } 
    ~Data(){}

    vector<Node>& getNlist()
    {
        return this->data;
    }
    
    void addnode(Node n,int num){
        for(int i = 0 ; i < num ; ++i)
        {
            data.push_back(n);
        }
    }
private:
    vector<Node>data;
};
