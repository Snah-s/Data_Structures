template <typename T>
struct ListNode {
  T val;
  ListNode<T> *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(T x) : val(x), next(nullptr) {}
  ListNode(T x, ListNode<T> *next) : val(x), next(next) {}
};

template <typename T>
class List {
private:
  ListNode<T> *head;
  int count;

public:
  List() : head(nullptr), count(0) {}

  bool empty() {
    return head == nullptr;
  }

  ListNode<T> *getHead() const {
    return head;
  }

  T front() {
    if (!head)
      return T();
    return head->val;
  }

  void push_front(T val) {
    head = new ListNode<T>(val, head);
    count++;
  }

  void pop_front() {
    if (head) {
      ListNode<T> *temp = head;
      head = head->next;
      delete temp;
      count--;
    }
  }

  void clear() {
    while (head) {
      pop_front();
    }
  }

  void reverse() {
    ListNode<T> *prev = nullptr;
    ListNode<T> *curr = head;
    ListNode<T> *next = nullptr;

    while (curr) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    head = prev;
  }

  int size() const {
    return count;
  }

  ~List() {
    clear();
  }
};