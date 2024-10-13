#include "avl1.h"
#include "list.h"
#include "queue.h"

template <typename T>
void bfs(Node<T> *node){
  if (!node) return;
  Queue<Node<T>*> q;
  q.enqueue(node);
  while (!q.empty()){
    Node<T> *curr = q.front();
    q.dequeue();
    std::cout<<curr->val<<" ";
    if (curr->left) q.enqueue(curr->left);
    if (curr->right) q.enqueue(curr->right);
  }
}

template <typename T>
void inOrder(Node<T> *node, List<T> &list){
  if (!node) return;
  inOrder(node->left, list);
  list.push_back(node->val);
  inOrder(node->right, list);
}

template <typename T>
void solution(List<T> &list){
  Node<T> *root = nullptr;
  ListNode<T> *curr = list.getHead();
  while (curr){
    root = insert(root, curr->val);
    curr = curr->next;
  }
  bfs(root);
}

template <typename T>
void solution(T arr[], int size){
  Node<T> *root = nullptr;
  for (int i = 0; i < size; i++){
    root = insert(root, arr[i]);
  }
  bfs(root);
}

// array = [2, 4, 1, 3, 5, 6, 7]

int main() {
  int array[7] = {2, 4, 1, 3, 5, 6, 7};
  solution(array, 7);
  std::cout<<std::endl;
  return 0;
}
