#include "maxHeapArr.h"

int main() {
  MaxHeap<int> h;

  h.insert(3);
  h.insert(2);
  h.insert(15);
  h.insert(5);
  h.insert(4);
  h.insert(45);

  cout << "Heap: ";
  h.display();

  cout << h.extractMax() << endl;

  h.display();

  cout << h.getMax() << endl;

  return 0;
}