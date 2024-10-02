// Clase Base

template <typename T>
struct DNode {
  T val;
  DNode *prev;
  DNode *next;
  
  DNode(): val(0), prev(nullptr), next(nullptr) {}
  DNode(T value): val(value), prev(nullptr), next(nullptr) {}
  DNode(DNode<T> *_prev, T value): val(value), prev(_prev), next(nullptr) {}
  DNode(T value, DNode<T> *_next): val(value), prev(nullptr), next(_next) {}
  DNode(DNode<T> *_prev, T value, DNode<T> *_next): val(value), prev(_prev), next(_next) {}
};

template <typename T>
class DList {
private:
  DNode<T> *head;
  DNode<T> *tail;

public:
  DList(): head(nullptr), tail(nullptr) {}

  T front() const {
    if (head) return head->val;
    return T();
  }

  T back() const {
    if (tail) return tail->val;
    return T();
  }

  DNode<T>* getHead() const {
    return this->head;
  }

  void push_front(T value) {
    DNode<T> *newDNode = new DNode<T>(value, head);
    if (head) {
      head->prev = newDNode;
    } else {
      tail = newDNode;
    }
    head = newDNode;
  }

  void push_back(T value) {
    DNode<T> *newDNode = new DNode<T>(tail, value);
    if (tail) {
      tail->next = newDNode;
    } else {
      head = newDNode;
    }
    tail = newDNode;
  }

  void pop_front() {
    if (head) {
      DNode<T> *temp = head;
      head = head->next;
      if (head) {
        head->prev = nullptr;
      } else {
        tail = nullptr;
      }
      delete temp;
    }
  }

  void pop_back() {
    if (tail) {
      DNode<T> *temp = tail;
      tail = tail->prev;
      if (tail) {
        tail->next = nullptr;
      } else {
        head = nullptr;
      }
      delete temp;
    }
  }

  void insert(T value, int index) {
    if (index < 0 || index > size()) return;  // Índice fuera de rango
    if (index == 0) {
      push_front(value);
    } else if (index == size()) {
      push_back(value);
    } else {
      DNode<T> *newDNode = new DNode<T>(value);
      DNode<T> *curr = head;
      for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
      }
      newDNode->prev = curr;
      newDNode->next = curr->next;
      if (curr->next) {
        curr->next->prev = newDNode;
      }
      curr->next = newDNode;
    }
  }

  void remove(int index) {
    if (index < 0 || index >= size()) return;  // Índice fuera de rango
    if (index == 0) {
      pop_front();
    } else if (index == size() - 1) {
      pop_back();
    } else {
      DNode<T> *curr = head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      DNode<T> *temp = curr;
      curr->prev->next = curr->next;
      if (curr->next) {
        curr->next->prev = curr->prev;
      }
      delete temp;
    }
  }

  bool empty() const {
    return head == nullptr;
  }

  int size() const {
    DNode<T> *curr = head;
    int size = 0;

    while (curr) {
      curr = curr->next;
      size++;
    }

    return size;
  }

  void clear() {
    while (head) {
      pop_front();
    }
  }

  ~DList() {
    clear();
  }
};

// FIFO -> First In First Out
template <typename T>
class Queue{
private:
  DList<T> list;
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
};