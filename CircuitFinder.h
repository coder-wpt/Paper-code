//===----------------------------------------------------------------------===//
//
// Written by Xing Mingjie (mingjie.xing@gmail.com).
//
// An implementation of the Johnson's circuit finding algorithm [1].
//
// [1] Donald B. Johnson, Finding all the elementary circuits of a directed
//     graph, SIAM Journal on Computing, 1975.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCUIT_FINDER_H
#define CIRCUIT_FINDER_H

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include "Node.h"

typedef std::list<int> NodeList;

template<int N>
class CircuitFinder
{
  std::vector<Node> data;
  std::vector<NodeList> AK;
  std::vector<int> Stack;
  std::vector<bool> Blocked;
  std::vector<NodeList> B;
  std::vector<NodeList> CC;
  std::vector<NodeList> GC;
  std::vector<NodeList> UC;
  int S;
  int t_sum,n_sum,g_sum;
  int judge1,judge2;

  void unblock(int U);
  bool circuit(int V);
  void output();

  int c_num=0,g_num=0,u_num=0;
public:
  CircuitFinder(int Array[N][8],int s,int n,int g,vector<Node>Data)
    : AK(N), Blocked(N), B(N),t_sum(s),n_sum(n),g_sum(g),data(Data)
  {
    //<=judge1 //judge1< <=judge2 //judge2<
    judge1=t_sum;
    judge2=t_sum+n_sum;
    for (int I = 0; I < N; ++I) {
      for (int J = 0; J < 8; ++J) {
        if (Array[I][J]) {
          AK[I].push_back(Array[I][J]); 
        }
      }
    }
  }

  void run();
};

template<int N>
void CircuitFinder<N>::unblock(int U)
{
  Blocked[U - 1] = false;

  while (!B[U - 1].empty()) {
    int W = B[U - 1].front();
    B[U - 1].pop_front();

    if (Blocked[W - 1]) {
      unblock(W);
    }
  }
}

template<int N>
bool CircuitFinder<N>::circuit(int V)
{
  bool F = false;
  Stack.push_back(V);
  Blocked[V - 1] = true;

  for (int W : AK[V - 1]) {
    if (W == S) {
      output();
      F = true;
    } else if (W > S && !Blocked[W - 1]) {
        if(circuit(W)) F = true;
    }
  }

  if (F) {
    unblock(V);
  } else {
    for (int W : AK[V - 1]) {
      auto IT = std::find(B[W - 1].begin(), B[W - 1].end(), V);
      if (IT == B[W - 1].end()) {
        B[W - 1].push_back(V);
      }
    }
  }

  Stack.pop_back();
  return F;
}

template<int N>
void CircuitFinder<N>::output()
{
  int t_n=0,n_n=0,g_n=0;
  for (auto I = Stack.begin(), E = Stack.end(); I != E; ++I)
  {
    if (*I <= judge1) t_n++;
    if (*I >judge1 && * I <= judge2) n_n++;
    if (*I > judge2) g_n++;
  }
  if(t_n == 1 && n_n > 0 && g_n == 0) 
  {

    c_num++;
    NodeList temp; 
    std::cout << "Combat circuit: ";
    for (auto I = Stack.begin(), E = Stack.end(); I != E; ++I) {
        std::cout << *I << " -> ";
        temp.push_back(*I);
    }
    CC.push_back(temp);
    std::cout << *Stack.begin() << std::endl;
  }else if(t_n == 0 && n_n == 1 && g_n != 0)
  {
    g_num++;
    NodeList temp;
    std::cout << "Guarantee circuit: ";
    for (auto I = Stack.begin(), E = Stack.end(); I != E; ++I) {
        std::cout << *I << " -> ";
        temp.push_back(*I);
    }
    GC.push_back(temp);
    std::cout << *Stack.begin() << std::endl;
  }else{
    u_num++;
    NodeList temp;
   // std::cout << "Useless circuit: ";
    for (auto I = Stack.begin(), E = Stack.end(); I != E; ++I) {
        //std::cout << *I << " -> ";
        temp.push_back(*I);        
    }
   // std::cout << *Stack.begin() << std::endl;
    UC.push_back(temp);
  }

}

template<int N>
void CircuitFinder<N>::run()
{
  Stack.clear();
  S = 1;

  while (S < N) {
    for (int I = S; I <= N; ++I) {
      Blocked[I - 1] = false;
      B[I - 1].clear();
    }
    circuit(S);
    ++S;
  }
  
  std::cout << "Combat circuit's sum=" << c_num << std::endl;
  std::cout << "Guarantee circuit's sum=" << g_num << std::endl;
  std::cout << "Useless circuit's sum=" << u_num << std::endl;
}

#endif // CIRCUIT_FINDER_H

