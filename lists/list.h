#include <iostream>

template <typename T>
struct Node {
  T value;
  Node<T> *next;

  Node(): value(0), next(nullptr) {}
  Node(T data): value(data), next(nullptr) {}
  Node(T data, Node<T> *_next): value(data), next(_next) {}
};

template <typename T>
class List {
private:
  Node<T> *head;

public:
  List(): head(nullptr) {}
  ~List() {
    this->clear();
  }

  T front(){
    return head->value;
  }

  T back(){
    Node<T> *curr = head;
    while(curr->next){
      curr = curr->next;
    }
    return curr->value;
  }

  Node<T>* getHead() const {
    return this->head;
  }

  void push_front(T val){
    head = new Node(val, head);
  }

  void pop_front(){
    if(!head){
      return;
    }
    Node<T>* temp = head;
    head = head->next;
    delete temp;
  }

  void push_back(T val){
    if(!head){
      head = new Node(val);
      return;
    }
    Node<T>* curr = head;
    while(curr->next){
      curr = curr->next;
    }
    curr->next = new Node(val);
  }

  void pop_back(){
    if(!head){
      return;
    }
    Node<T>* curr = head;
    while(curr->next->next){
      curr = curr->next;
    }
    curr->next = nullptr;
    delete curr->next;
  }

  T operator[](int index){
    if (index > this->size() - 1){
      return -1;
    }
    Node<T> *curr = head;
    for(int i = 0; i< index; i++){
      curr = curr->next;
    }
    return curr->value;
  }

  bool empty(){
    return head == nullptr;
  }

  int size(){
    int count{};
    Node<T>* curr = head;
    while(curr){
      curr = curr->next;
      count++;
    }
    return count;
  }

  void clear(){
    Node<T> *curr = head;
    while (curr) {
      Node<T> *temp = curr;
      curr = curr->next;
      delete temp;
    }
  }

  void sort(){ // Insertion Sort
    if (!head || !head->next){
      return;
    }

    Node<T> *sorted = nullptr;
    Node<T> *curr = head;

    while (curr){
      Node<T> *next = curr->next;
      if (!sorted || sorted->value >= curr->value) {
        curr->next = sorted;
        sorted = curr;
      } else {
        Node<T> *sortedCurr = sorted;
        while(sortedCurr->next && sortedCurr->next->value < curr->value){
          sortedCurr = sortedCurr->next;
        }
        curr->next = sortedCurr->next;
        sortedCurr->next = curr;
      }
      curr = next;
    }
    head = sorted;
  }

  void insert(int index, T data){
    if (index > this->size() - 1){
      return;
    }
    Node<T>* curr = head;
    for(int i = 0; i< index - 1; i++){
      curr = curr->next;
    }
    curr->next = new Node(data, curr->next);
  }

  void remove(int index){
    if (index > this->size() - 1){
      return;
    }
    Node<T>* curr = head;
    for(int i = 0; i< index - 1; i++){
      curr = curr->next;
    }
    Node<T>* temp = curr->next;
    curr->next = curr->next->next;

    delete temp;
  }

  void reverse(){
    Node<T> *prev = nullptr;
    Node<T> *curr = head;
    Node<T> *next = nullptr;

    while(curr){
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr  = next;
    }
    head = prev;
  }

  void display(){
    Node<T>* curr = head;
    while(curr->next){
      std::cout<<curr->value<<" -> ";
      curr = curr->next;
    }
    std::cout<<curr->value<<std::endl;
  }
};

template<typename T> 
List<T> mergeOrderedList(List<T> &list1, List<T> &list2){
  List<T> result;
  list1.reverse();
  list2.reverse();
  Node<T>* curr1 = list1.getHead();
  Node<T>* curr2 = list2.getHead();
  
  while(curr1 && curr2){
    if (curr1->value > curr2->value){
      result.push_front(curr1->value);
      curr1 = curr1->next;
    } else {
      result.push_front(curr2->value);
      curr2 = curr2->next;
    }
  }

  while (curr1) {
    result.push_front(curr1->value);
    curr1 = curr1->next;
  }

  while (curr2){
    result.push_front(curr2->value);
    curr2 = curr2->next;
  }

  return result;
}

template <typename T>
List<T> intersectOrderedLists(List<T>& list1, List<T>& list2){
  List<T> result;

  Node<T> *curr1 = list1.getHead();
  Node<T> *curr2 = list2.getHead();

  while(curr1 && curr2){
    if(curr1->value == curr2->value){
      result.push_front(curr1->value);
      curr1 = curr1->next;
      curr2 = curr2->next;
    } else if (curr1->value < curr2->value) {
      curr1 = curr1->next;
    } else {
      curr2 = curr2->next;
    }
  }

  result.reverse();

  return result;
}