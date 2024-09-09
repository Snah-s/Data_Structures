// Clase Base

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

};
