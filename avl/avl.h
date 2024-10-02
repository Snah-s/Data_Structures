#include <iostream>

template <typename T>
struct Node {
  T val;
  Node<T> *left;
  Node<T> *right;
  int height;

  Node(T data): val(data), left(nullptr), right(nullptr), height(0) {}
};

template <typename T>
T maxVar(T a, T b){
  if (a > b){
    return a;
  }
  return b;
}

template <typename T>
class AVLTree {
private:
  Node *root;

  int getHeight(Node<T> *node){
    if (!node) return 0;
    return node->height;
  }

  int getBalance(Node<T> *node){
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
  }

  Node<T>* rightRotate(Node<T> *y){
    Node<T> *x = y->left;
    Node<T> *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxVar(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = maxVar(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
  }

  Node<T>* leftRotate(Node<T> *x){
    Node<T> *y = x->right;
    Node<T> *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxVar(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maxVar(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
  }

  Node<T>* insert(Node<T> *node, T data){
    if (!node) return new Node(data);

    if (data < node->val) {
      node->left = insert(node->left, data);
    } else if (data > node->val) {
      node->right = insert(node->right, data);
    } else {
      return node;
    }

    node->height = 1 + maxVar(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->val) return rightRotate(node);

    if (balance < -1 && data > node->right->val) return leftRotate(node);

    if (balance > 1 && data > node->left->val){
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }

    if (balance < -1 && data < node->right->val){
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }

    return node;
  }

  Node<T>* minvalNode(Node<T> *node){
    Node<T> *curr = node;
    while(curr->left){
      curr = curr->left;
    }
    return curr;
  }

  Node<T>* deleteNode(Node<T> *root, T data) {
    if (!root) return root;

    if (data < root->val){
      root->left = deleteNode(root->left, data);
    } else if (data > root->val){
      root->right = deleteNode(root->right, data);
    } else {
      if (!root->left || !root->right){
        Node<T> *temp = root->left ? root->left : root->right;
        if (!temp){
          temp = root;
          root = nullptr;
        } else {
          *root = *temp;
        }
        delete temp;
      } else {
        Node<T> *temp = minvalNode(root->right);
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val);
      }
    }

    if (!root) return root;

    root->height = 1 + maxVar(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0){
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0){
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }

    return root;
  }

  bool search(Node<T> *node, T data){
    if (!node) return false;
    if (node->val == data) return true;
    if (data < node->val) return search(node->left, data);
    return search(node->right, data);
  }

  void inorder(Node<T> *node){
    if (!node) return;
    inorder(node->left);
    std::cout<<node->val<<" ";
    inorder(node->right);
  }

  void preorder(Node<T> *node){
    if (!node) return;
    std::cout<<node->val<<" ";
    preorder(node->left);
    preorder(node->right);
  }

  void postorder(Node<T> *node){
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    std::cout<<node->val<<" ";
  }

  void dfs(Node<T> *node){
    if (!node) return;
    std::cout<<node->val<<" ";
    dfs(node->left);
    dfs(node->right);
  }

public:

  AVLTree() : root(nullptr) {}

  ~AVLTree(){
    while (root) {
      root = deleteNode(root, root->val);
    }
  }

  void insert(T data){
    root = insert(root, data);
  }

  void remove(T data){
    root = deleteNode(root, data);
  }

  bool search(T data){
    return search(root, data);
  }

  void display(){
    int choice;
    std::cout << std::endl << "1. Inorder"<<std::endl<<"2. Preorder"<<std::endl<<"3. Postorder"<<std::endl<<"4. DFS"<<std::endl<<std::endl;
    std::cin >> choice;
    switch (choice) {
      case 1:
        inorder(root);
        break;
      case 2:
        preorder(root);
        break;
      case 3:
        postorder(root);
        break;
      case 4:
        dfs(root);
        break;
      default:
        std::cout << "Invalid choice"<<std::endl;
    }
    std::cout << std::endl;
  }

};