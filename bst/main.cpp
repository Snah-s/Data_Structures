#include "bst.h"
#include <iostream>

using namespace std;

int main(){
  BinarySearchTree<int> bst;
  bst.insert(5);
  bst.insert(3);
  bst.insert(7);
  bst.insert(2);
  bst.insert(4);
  bst.insert(6);
  bst.insert(8);
  bst.display(); //inorder
  cout << endl;
  bst.display(); //preorder
  cout << endl;
  bst.display(); //postorder
  cout << endl;
  cout << bst.isBalanced() << endl;
  cout << bst.height() << endl;
  bst.remove(5);
  bst.display(); //inorder
  cout << endl;
  cout << bst.isBalanced() << endl;
  cout << bst.height() << endl;
  return 0;
}