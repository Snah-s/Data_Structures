#include <iostream>
#include "queue.h"

template <typename T>
struct BTNode {
  T val;
  BTNode *left;
  BTNode *right;
  BTNode() : val(0), left(nullptr), right(nullptr) {}
  BTNode(T x) : val(x), left(nullptr), right(nullptr) {}
  BTNode(T x, BTNode *left, BTNode *right) : val(x), left(left), right(right) {}
};

template <typename T>
T max(T a, T b) {
  if (a < b) {
    return b;
  }else{
    return a;
  }
}

template <typename T>
BTNode<T> *insert(BTNode<T> *node, T val){
  if (!node) return new BTNode<T>(val);
  if (val < node->val){
    node->left = insert(node->left, val);
  } else if (val > node->val){
    node->right = insert(node->right, val);
  }
  return node;
}

template <typename T>
bool find(BTNode<T> *node, T val){
  if (node == nullptr) return false;
  if (node->val == val) return true;
  if (val < node->val){
    return find(node->left, val);
  }
  return find(node->right, val);
}

template <typename T>
BTNode<T> *remove(BTNode<T> *node, T val){
  if (!node) return node;
  if (val < node->val){
    node->left = remove(node->left, val);
  } else if (val > node->val){
    node->right = remove(node->right, val);
  } else {
    if (!node->left){
      BTNode<T> *temp = node->right;
      delete node;
      size--;
      return temp;
    } else if (!node->right){
      BTNode<T> *temp = node->left;
      delete node;
      size--;
      return temp;
    } else {
      BTNode<T> *temp = node->right;
      while (temp->left){
        temp = temp->left;
      }
      node->val = temp->val;
      node->right = remove(node->right, temp->val);
    }
  }
  return node;
}

template <typename T>
void inOrder(BTNode<T> *node){
  if (!node) return;
  inOrder(node->left);
  std::cout << node->val << " ";
  inOrder(node->right);
}

template <typename T>
void preOrder(BTNode<T> *node){
  if (!node) return;
  std::cout << node->val << " ";
  preOrder(node->left);
  preOrder(node->right);
}

template <typename T>
void postOrder(BTNode<T> *node){
  if (!node) return;
  postOrder(node->left);
  postOrder(node->right);
  std::cout << node->val << " ";
}

template <typename T>
int height(BTNode<T> *node){
  if (!node) return 0;
  return 1 + max(height(node->left), height(node->right));
}

template <typename T>
bool isBalanced(BTNode<T> *node){
  if (!node) return true;
  int leftHeight = height(node->left);
  int rightHeight = height(node->right);
  return abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

template <typename T>
bool isBST(BTNode<T> *node, T min, T max){
  if (!node) return true;
  if (node->val < min || node->val > max) return false;
  return isBST(node->left, min, node->val) && isBST(node->right, node->val, max);
}

template <typename T>
bool isLeaf(BTNode<T> *node){
  return !node->left && !node->right;
}

template <typename T>
void bfs(BTNode<T> *node){
  if (!node) return;
  Queue<BTNode<T>*> q;
  q.push(node);
  while (!q.empty()){
    BTNode<T> *curr = q.front();
    q.pop();
    std::cout << curr->val << " ";
    if (curr->left) q.push(curr->left);
    if (curr->right) q.push(curr->right);
  }
}