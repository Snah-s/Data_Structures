#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

template <typename T>
T maxVar(T a, T b){
  if (a > b){
    return a;
  }
  return b;
}

int height(TreeNode* node) {
  if (node == nullptr) return 0;
  return 1 + std::max(height(node->left), height(node->right));
}

int getBalance(TreeNode* node) {
  if (node == nullptr) return 0;
  return height(node->left) - height(node->right);
}

TreeNode* rightRotate(TreeNode* y) {
  TreeNode* x = y->left;
  TreeNode* T2 = x->right;
  x->right = y;
  y->left = T2;
  return x;
}

TreeNode* leftRotate(TreeNode* x) {
  TreeNode* y = x->right;
  TreeNode* T2 = y->left;
  y->left = x;
  x->right = T2;
  return y;
}

TreeNode* insert(TreeNode* node, int key) {
  if (node == nullptr) {
    return new TreeNode(key);
  }

  if (key < node->val) {
    node->left = insert(node->left, key);
  } else if (key > node->val) {
    node->right = insert(node->right, key);
  } else {
    return node;
  }

  int balance = getBalance(node);

  if (balance > 1 && key < node->left->val) {
    return rightRotate(node);
  }
  if (balance < -1 && key > node->right->val) {
    return leftRotate(node);
  }
  if (balance > 1 && key > node->left->val) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && key < node->right->val) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

TreeNode* minValueNode(TreeNode* node) {
  TreeNode* current = node;
  while (current->left != nullptr)
    current = current->left;
  return current;
}

TreeNode* deleteNode(TreeNode* root, int key) {
  if (root == nullptr) return root;

  if (key < root->val) {
    root->left = deleteNode(root->left, key);
  } else if (key > root->val) {
    root->right = deleteNode(root->right, key);
  } else {
    if ((root->left == nullptr) || (root->right == nullptr)) {
      TreeNode* temp = root->left ? root->left : root->right;

      if (temp == nullptr) {
        temp = root;
        root = nullptr;
      } else {
        *root = *temp;
      }
      delete temp;
    } else {
      TreeNode* temp = minValueNode(root->right);
      root->val = temp->val;
      root->right = deleteNode(root->right, temp->val);
    }
  }

  if (root == nullptr) return root;

  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}