// testing lists
#include "list.h"


int main(){
  List<int> lista;
  lista.push_back(1);
  lista.push_back(2);
  lista.push_back(3);
  lista.push_back(4);
  lista.push_back(5);
  lista.display();

  lista.reverseFromNtoM(2,4);

  lista.display();
}