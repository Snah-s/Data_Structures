// Clase Base

template <typename T>
struct Node {
  T val;
  Node *prev;
  Node *next;
  
  Node(): val(0), prev(nullptr), next(nullptr) {}
  Node(T value): val(value), prev(nullptr), next(nullptr) {}
  Node(Node<T> *_prev, T value): val(value), prev(_prev), next(nullptr) {}
  Node(T value, Node<T> *_next): val(value), prev(nullptr), next(_next) {}
  Node(Node<T> *_prev, T value, Node<T> *_next): val(value), prev(_prev), next(_next) {}
};

template <typename T>
class List {
private:
  Node<T> *head;
  Node<T> *tail;

public:
  List(): head(nullptr), tail(nullptr) {}

  T front() const {
    if (head) return head->val;
    return T();
  }

  T back() const {
    if (tail) return tail->val;
    return T();
  }

  Node<T>* getHead() const {
    return this->head;
  }

  void push_front(T value) {
    Node<T> *newNode = new Node<T>(value, head);
    if (head) {
      head->prev = newNode;
    } else {
      tail = newNode;
    }
    head = newNode;
  }

  void push_back(T value) {
    Node<T> *newNode = new Node<T>(tail, value);
    if (tail) {
      tail->next = newNode;
    } else {
      head = newNode;
    }
    tail = newNode;
  }

  void pop_front() {
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

  void pop_back() {
    if (tail) {
      Node<T> *temp = tail;
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
      Node<T> *newNode = new Node<T>(value);
      Node<T> *curr = head;
      for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
      }
      newNode->prev = curr;
      newNode->next = curr->next;
      if (curr->next) {
        curr->next->prev = newNode;
      }
      curr->next = newNode;
    }
  }

  void remove(int index) {
    if (index < 0 || index >= size()) return;  // Índice fuera de rango
    if (index == 0) {
      pop_front();
    } else if (index == size() - 1) {
      pop_back();
    } else {
      Node<T> *curr = head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      Node<T> *temp = curr;
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
    Node<T> *curr = head;
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

  ~List() {
    clear();
  }
};