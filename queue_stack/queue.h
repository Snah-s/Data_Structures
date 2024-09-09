// FIFO -> First In First Out

#include <iostream>
#include "doubleList.h"

template <typename T>
class Queue{
private:
  List<T> list;
public:
  Queue(){}

  ~Queue(){
    list.clear();
  }

  void enqueue(T value){
    list.push_back(value);
  }

  void dequeue(){
    list.pop_front();
  }

  T front(){
    return list.front();
  }

  T back(){
    return list.back();
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
      std::cout << curr->value << " -> ";
      curr = curr->next;
    }
    std::cout << curr->val << std::endl;
  }
};