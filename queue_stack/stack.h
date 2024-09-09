// LIFO -> Last In First Out

#include <iostream>
#include "singleList.h"

template <typename T>
class Stack{
private:
  List<T> list;

public:
  Stack(){}

  ~Stack(){
    list.clear();
  }

  void push(T value){
    list.push_front(value);
  }

  void pop(){
    list.pop_front();
  }

  T top(){
    return list.front();
  }

  bool empty(){
    return list.empty();
  }

  int size(){
    return list.size();
  }

  void display(){
    Node<T> *curr = list.getHead();
    while(curr->next){
      std::cout << curr->value << std::endl;
      curr = curr->next;
    }
    std::cout << curr->value << std::endl;
    std::cout << std::endl;
  }
};