#include <iostream>
#include <cmath>

template <typename T>
struct Node {
  T value;
  Node<T> *next;

  Node(): value(0), next(nullptr) {}
  Node(T data): value(data), next(nullptr) {}
  Node(T data, Node<T> *_next): value(data), next(_next) {}
};

int MCD(int a, int b);

int pow(int a, int b);

template <typename T>
class List {
private:
  Node<T> *head;

  Node<T>* split(Node<T>* head){
    Node<T>* slow = head;
    Node<T>* fast = head->next;

    while(fast && fast->next){
      slow = slow->next;
      fast = fast->next->next;
    }

    Node<T>* mid = slow->next;
    slow->next = nullptr;
    return mid;
  }

  Node<T>* merge(Node<T> *left, Node<T> *right){
    if(!left) return right;
    if(!right) return left;

    if(left->value < right->value) {
      left->next = merge(left->next, right);
      return left;
    } else {
      right->next = merge(left, right->next);
      return right;
    }
  }

  Node<T>* mergeSort(Node<T> *head){
    if(!head || !head->next){
      return head;
    }

    Node<T> *mid = split(head);

    Node<T> *left = mergeSort(head);
    Node<T> *right = mergeSort(mid);

    return merge(left, right);
  }

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

  void sort(){
    head = mergeSort(head);
  }

  void insertionSort(){
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

  int getBits(){
    int count{};
    int result{};
    Node<T> *curr = head;
    do{
      result += curr->value*std::pow(2,count);
      count++;
      curr = curr->next;
    }while(curr);

    return result;
  }

  List<T> getMid(){
    List<T> list;
    int mid = this->size()/2;

    Node<T> *curr = head;

    for (int i = 0; i < mid; i++){
      curr = curr->next;
    }

    while(curr){
      list.push_front(curr->value);
      curr = curr->next;
    }
    list.reverse();
    return list;
  }

  bool isCycle(){
    Node<T>* slow = head;
    Node<T>* fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if(fast == slow){
        return true;
      }
    }
    return false;
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

  void removeNfromTheEnd(int index){
    this->reverse();
    this->remove(index - 1);
    this->reverse();
  }

  void reverseFromNtoM(int left, int right){
    if (left >= right || !head) {
      return;
    }

    Node<T>* prev = nullptr;
    Node<T>* curr = head;
    Node<T>* next = nullptr;

    for (int i = 0; i < left - 1 && curr; i++) {
      prev = curr;
      curr = curr->next;
    }

    Node<T>* start = prev;
    Node<T>* end = curr;

    for (int i = 0; i < right - left + 1 && curr; i++) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }

    if (start) {
      start->next = prev;
    } else {
      head = prev;
    }
    end->next = curr;
  }

  void removeElements(T target){
    if(!head){
      return;
    }
    while(head->value == target){
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }
    Node<T>* curr = head;
    do{
      if(curr->next && curr->next->value == target){
        Node<T>* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
      }else{
        curr = curr->next;
      }
    } while(curr->next && curr);
  }

  void insertMCD(){
    Node<T> *curr = head;
    while(curr->next){
      Node<T> *temp = new Node(MCD(curr->value, curr->next->value), curr->next);
      curr->next = temp;
      curr = temp->next;
    }
  }

  void swap(int index1, int index2){
    if(index1 > this->size() && index2 > this->size()){
      return;
    }

    Node<T>* curr1 = head;
    Node<T>* curr2 = head;

    for(int i = 0; i < index1; i++){
      curr1 = curr1->next;
    }

    for(int i = 0; i < index2; i++){
      curr2 = curr2->next;
    }

    T temp = curr1->value;
    curr1->value = curr2->value;
    curr2->value = temp;
    
  }

  void swapPairs(){
    int count{};
    Node<T>* curr = head;
    while(curr){
      if(count%2 == 0 && curr->next){
        T temp = curr->value;
        curr->value = curr->next->value;
        curr->next->value = temp;
      }
      curr = curr->next;
      count++;
    }
  }

  void connectToFinal(){
    Node<T>* curr = head;
    while(curr->next){
      curr = curr->next;
    }
    curr->next = head;
  }

  void display(){
    Node<T>* curr = head;
    while (curr){
      if(!curr->next){
        std::cout<<curr->value; 
      }else{
        std::cout<<curr->value<<" -> ";
      }
      curr = curr->next;
    }
    std::cout<<std::endl;
  }
};

int MCD(int a, int b){
  if(b == 0){
    return a;
  }
  return MCD(b, a%b);
}


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