// Clase Base

template <typename T>
struct Node {
  T val;
  Node *prev;
  Node *next;
  Node *child;
  Node(): val(0), prev(nullptr), next(nullptr){}
  Node(T value): val(value), prev(nullptr), next(nullptr){}
  Node(Node<T> *_prev, T value): val(value), prev(_prev), next(nullptr){}
  Node(T value, Node<T> *_next): val(value), prev(nullptr), next(_next){}
  Node(Node<T> *_prev, T value, Node<T> *_next): val(value), prev(_prev), next(_next){}
};

template <typename T>
class List{
private:
  Node<T> *head;
  Node<T> *tail;

public:
  List(): head(nullptr), tail(nullptr){}
  T front(){
    return head->val;
  }

  T back(){
    return tail->val;
  }

  Node<T>* getHead() const {
    return this->head;
  }

  void push_front(T value){
    Node<T> *newNode = new Node(value, head);
    if (head) {
      head->prev = newNode;
    } else {
      tail = newNode;
    }
    head = newNode;
  }

  void push_back(T value){
    Node<T> *newNode = new Node(tail, value);
    if (tail){
      tail->next = newNode;
    } else {
      head = newNode;
    }
    tail = newNode;
  }

  void pop_front(){
    if (head) {
      Node<T> *temp = head;
      head = head->next;
      if (head) {
        head->prev = nullptr;
      } else {
        tail = nullptr;
      }
      delete temp;
    }
  }

  void pop_back(){
    if(tail){
      Node<T> *temp = tail;
      tail = tail->prev;
      if (tail){
        tail->prev = nullptr;
      } else {
        head = nullptr;
      }
      delete temp;
    }
  }

  void insert(T value, int index){
    if (index > size(head)){
      return;
    }
    if (index == 0) {
      push_front(head, tail, value);
    } else if (index == size(head)) {
      push_back(head, tail, value);
    } else {
      Node<T> *newNode = new Node(value);
      Node<T> *curr = head;
      for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
      }
      newNode->prev = curr;
      newNode->next = curr->next;
      curr->next->prev = newNode;
      curr->next = newNode;
    }
  }

  void remove(int index){
    if (index > size(head)){
      return;
    }
    if (index == 0){
      pop_front(head, tail);
    }else if (index == size(head)){
      pop_back(head, tail);
    } else {
      Node<T> *curr = head;
      for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
      }
      Node<T> *temp = curr->next;
      curr->next = curr->next->next;
      if (curr->next) {
        curr->next->prev = curr;
      } else {
        tail = curr;
      }
      delete temp;
    }
  }

  bool empty(){
    return head == nullptr && tail == nullptr;
  }

  int size(){
    Node<T> *curr = head;
    int size{};

    while (curr){
      curr = curr->next;
      size++;
    }

    return size;
  }

  void clear(){
    while (head) {
      pop_front(head, tail);
    }
  }

  ~List(){
    this->clear();
  }
};