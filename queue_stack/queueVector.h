#include <vector>
using namespace std;

template <typename T>
class Queue{
private:
  vector<T> list;
public:
  Queue(){}

  ~Queue(){
    list.clear();
  }

  void enqueue(T value){
    list.push_back(value);
  }

  void dequeue(){
    list.erase(list.begin());
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