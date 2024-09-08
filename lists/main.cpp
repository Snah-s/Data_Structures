// testing lists
#include "circular.h"


int main(){
  cList<int> lista;
  lista.push_back(1);
  lista.push_back(2);
  lista.push_back(3);
  lista.push_back(4);
  lista.push_back(5);
  lista.display();
  std::cout<<lista[5]<<std::endl;
}