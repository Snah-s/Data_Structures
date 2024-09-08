// cirular double linked list
#include <iostream>

template <typename T>
struct Node {
  T val;
  Node *prev;
  Node *next;
  Node(): val(-1), prev(nullptr), next(nullptr){}
  Node(T value): val(value), prev(nullptr), next(nullptr){}
  Node(Node<T> *_prev, T value): val(value), prev(_prev), next(nullptr){}
  Node(T value, Node<T> *_next): val(value), prev(nullptr), next(_next){}
  Node(Node<T> *_prev, T value, Node<T> *_next): val(value), prev(_prev), next(_next){}
};

template <typename T>
class cList{
private:
  Node<T> *sentinel;

public:
  cList() {
    sentinel = new Node<T>();
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
  }

  T front(){
    return sentinel->next->val;
  }

  T back(){
    return sentinel->prev->val;
  }

  void push_front(T value){
    Node<T> *newNode = new Node(sentinel, value, sentinel->next);
    sentinel->next->prev = newNode;
    sentinel->next = newNode;
  }

  void push_back(T value){
    Node<T> *newNode = new Node(sentinel->prev, value, sentinel);
    sentinel->prev->next = newNode;
    sentinel->prev = newNode;
  }

  void pop_front(){
    if (sentinel->next != sentinel) {
      Node<T> *temp = sentinel->next;
      sentinel->next = sentinel->next->next;
      sentinel->next->prev = sentinel;
      delete temp;
    }
  }

  void pop_back(){
    if (sentinel->prev != sentinel) {
      Node<T> *temp = sentinel->prev;
      sentinel->prev = sentinel->prev->prev;
      sentinel->prev->next = sentinel;
      delete temp;
    }
  }

  void insert(T value, int index){
    Node<T> *curr = sentinel;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    Node<T> *newNode = new Node(curr, value, curr->next);
    curr->next->prev = newNode;
    curr->next = newNode;
  }

  void remove(int index){
    Node<T> *curr = sentinel;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    if (curr == sentinel) {
      std::cout << "Sentinel" << std::endl;
      return;
    }else{
      Node<T> *temp = curr->next;
      curr->next = curr->next->next;
      curr->next->prev = curr;
      delete temp;
    }
  }

  T operator[](int index){
    Node<T> *curr = sentinel->next;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    if (curr == sentinel) {
      return -1;
    }
    return curr->val;
  }

  bool empty(){
    return sentinel->next == sentinel;
  }

  int size(){
    int count{};
    Node<T> *curr = sentinel->next;
    while (curr != sentinel) {
      count++;
      curr = curr->next;
    }
    return count;
  }

  void clear(){
    while (!empty()) {
      pop_front();
    }
  }

  void reverse(){
    Node<T> *curr = sentinel;
    Node<T> *temp = nullptr;
    do {
      temp = curr->prev;
      curr->prev = curr->next;
      curr->next = temp;
      curr = curr->prev;
    } while (curr != sentinel);
  }

  void display(){
    Node<T> *curr = sentinel->next;
    std::cout <<"Sentinel -> ";
    while (curr != sentinel) {
      std::cout << curr->val << " -> ";
      curr = curr->next;
    }
    std::cout<<"Sentinel" << std::endl;
  }
};