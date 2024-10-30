#include <iostream>
#include <cmath>

template <typename TK>
struct Node {
  TK* keys;
  Node** children;
  int count;
  bool leaf;

  Node(): keys(nullptr), children(nullptr), count(0), leaf(true){}

  Node(int M, bool isLeaf): count(0), leaf(isLeaf){
    keys = new TK[M];
    children = new Node<TK>*[M + 1];
    for (int i{}; i < M + 1; i++) children[i] = nullptr;
  }

  ~Node(){
    delete[] keys;
    delete[] children;
  }
};

template <typename TF, typename TS>
struct Pair {
  TF first;
  TS second;

  Pair(): first(TF()), second(TS()){}
  Pair(TF f, TS s): first(f), second(s){}

  bool operator==(const Pair<TF, TS>& other) const {
    return first == other.first && second == other.second;
  }

  bool operator!=(const Pair<TF, TS>& other) const {
    return first != other.first || second != other.second;
  }

  bool operator<(const Pair<TF, TS>& other) const {
    return first < other.first || (first == other.first && second < other.second);
  }

  bool operator>(const Pair<TF, TS>& other) const {
    return first > other.first || (first == other.first && second > other.second);
  }

  Pair<TF, TS>& operator=(const Pair<TF, TS>& other){
    first = other.first;
    second = other.second;
    return *this;
  }
};

template <typename TK>
class BTree {
private:
  Node<TK>* root;
  int M;

  std::string toString(Node<TK>* node, std::string sep){
    if (!node) return "";
    std::string result = "";
    for (int i{}; i < node->count; i++){
      if (!node->leaf) result += toString(node->children[i], sep);
      result += std::to_string(node->keys[i]);
    }

    if (!node->leaf) result += toString(node->children[node->count], sep);

    return result + "";
  }

  TK minKey(Node<TK>* node){
    Node<TK>* curr = node;
    while (!curr->leaf) curr = curr->children[0];
    return curr->keys[0];

  }

  bool search(Node<TK>* node, TK key){
    int index{};
    while (index < node->count && key > node->keys[index]) index++;
    if (node->keys[index] == key){
      return true;
    } else if (node->leaf){
      return false;
    } else {
      return search(node->children[index], key);
    }
  }

  void relocate(Node<TK> *&node, TK key){
    int index = node->count - 1;
    while (index >= 0 && key < node->keys[index]){
      node->keys[index + 1] = node->keys[index];
      index--;
    }
    index++;
    node->keys[index] = key;
    node->count++;
  }

  void relocate_right(Node<TK> *&node, TK key, Node<TK>* rightTree){
    int index = node->count - 1;

    while(index >= 0 && key < node->keys[index]){
      node->keys[index + 1] = node->keys[index];
      node->children[index + 2] = node->children[index + 1];
      index--;
    }
    index++;
    node->keys[index] = key;
    node->children[index + 1] = rightTree;
    node->count++;
  }

  Node<TK>* generate_right_node(Node<TK>* node, int indexFrom){
    Node<TK>* rightNode = new Node<TK>(M, node->leaf);
    int index = indexFrom, indexTemp{};

    while(index < M - 1){
      rightNode->keys[indexTemp] = node->keys[index];
      rightNode->children[indexTemp] = node->children[index];
      index++;
      indexTemp++;
    }
    rightNode->children[indexTemp] = node->children[index];
    rightNode->count = indexTemp;
    return rightNode;
  }

  Pair<TK, Node<TK>*> split_par(Node<TK> *&node, TK key, Node<TK> *right_tree = nullptr){
    int m = (M - 1) / 2;
    TK mid = node->keys[m];
    Node<TK>* rightNode = generate_right_node(node, m + 1);
    node->count = m;

    if (key < mid){
      relocate(node, key);
    } else {
      relocate_right(rightNode, key, right_tree);
    }
    return Pair<TK, Node<TK>*>(mid, rightNode);
  }

  Pair<TK, Node<TK>*> split_impar(Node<TK> *&node, TK key, Node<TK> *right_tree = nullptr){
    Node<TK>* rightNode;
    TK mid;

    int m = (M - 1) / 2;

    if (key > node->keys[m]){
      rightNode = generate_right_node(node, m + 1);
      mid = node->keys[m];
      node->count = m;
      relocate_right(rightNode, key, right_tree);
    } else{
      m = m -1;
      rightNode = generate_right_node(node, m + 1);
      if (key < node->keys[m]){
        mid = node->keys[m];
        node->count = m;
        relocate_right(node, key, right_tree);
      } else {
        mid = key;
        node->count = m + 1;
        rightNode->children[0] = right_tree;
      }
    }
    return Pair<TK, Node<TK>*>(mid, rightNode);
  }

  Pair<TK, Node<TK>*> insert(Node<TK> *&node, TK key){
    int index = 0;
    while (index < node->count && key > node->keys[index]) index++;

    if (index < node->count && node->keys[index] == key) return Pair<TK, Node<TK>*>(TK(), nullptr);

    if (node->leaf){
      if (node->count < M - 1){
        relocate(node, key);
        return Pair<TK, Node<TK>*>(TK(), nullptr);
      } else {
        if (M % 2 == 0){
          return split_par(node, key);
        } else {
          return split_impar(node, key);
        }
      }
    } else {
      Pair<TK, Node<TK>*> split_result = insert(node->children[index], key);
      if (split_result.second) { 
        if (node->count < M - 1){
          relocate_right(node, split_result.first, split_result.second);
          return Pair<TK, Node<TK>*>(TK(), nullptr);
        } else {
          if (M % 2 == 0){
            return split_par(node, split_result.first, split_result.second);
          } else {
            return split_impar(node, split_result.first, split_result.second);
          }
        }
      } else {
        return Pair<TK, Node<TK>*>(TK(), nullptr);
      }
    }
  }


  Pair<TK, Node<TK>*> extractLast(Node<TK>*&node){
    return Pair<TK, Node<TK>*>(node->keys[node->count - 1], node->children[node->count--]);
  }

  Pair<TK, Node<TK>*> extractFirst(Node<TK>*&node){
    Pair<TK, Node<TK>*> result = Pair<TK, Node<TK>*>(node->keys[0], node->children[0]);
    for (int i{}; i < node->count - 1; i++){
      node->keys[i] = node->keys[i + 1];
      node->children[i] = node->children[i + 1];
    }
    node->children[node->count - 1] = node->children[node->count];
    node->count--;
    return result;
  }

  void pop(Node<TK> *&node, int pos){
    for (int i = pos; i < node->count - 1; i++){
      node->keys[i] = node->keys[i + 1];
      node->children[i + 1] = node->children[i + 2];
    }
    node->count--;
  }

  void join(Node<TK> *&leftNode, TK mid, Node<TK> *&rightNode){
    relocate_right(leftNode, mid, rightNode->children[0]);
    for (int i{}; i < rightNode->count; i++){
      relocate_right(leftNode, rightNode->keys[i], rightNode->children[i + 1]);
    }
  }

  void remove(Node<TK> *&node, TK key) {
    int index = 0;
    while (index < node->count && key > node->keys[index]) index++;

    if (node->leaf) {
      if (index < node->count && node->keys[index] == key) popElement(node, index);
    } else {
      if (index < node->count && node->keys[index] == key) {
        key = minKey(node->children[index + 1]);
        node->keys[index] = key;
        index = index + 1;
      }
      remove(node->children[index], key);

      if (node->children[index]->count < (M - 1) / 2) {
        if (index > 0 && node->children[index - 1]->count > (M - 1) / 2) {
          auto lastKey = extractLast(node->children[index - 1]);
          relocate_left(node->children[index], node->keys[index - 1], lastKey.second);
          node->keys[index - 1] = lastKey.first;
        } else if (index < node->count && node->children[index + 1]->count > (M - 1) / 2) {
          auto firstKey = extractFirst(node->children[index + 1]);
          relocate_right(node->children[index], node->keys[index], firstKey.second);
          node->keys[index] = firstKey.first;
        } else if (index > 0) {
          join(node->children[index - 1], node->keys[index - 1], node->children[index]);
          delete node->children[index];
          popElement(node, index - 1);
        } else {
          join(node->children[index], node->keys[index], node->children[index + 1]);
          delete node->children[index + 1];
          popElement(node, index);
        }
      }
    }
  }

  void display_tree(Node<TK> *node, string indent = " ", bool last = true) {
    cout << indent;
    if (last) {
      cout << char(192);
      indent += "  ";
    } else {
      cout << char(195);
      indent += "| ";
    }
    int j;
    cout << "[";
    for (j = 0; j < node->count - 1; j++)
      cout << node->keys[j] << ",";
    cout << node->keys[j];
    cout << "]" << endl;
    if (!node->leaf) {
      for (j = 0; j <= node->count; j++) display_tree(node->children[node->count - j], indent, j == node->count);
    }
  }
  
public:

  BTree(int M): M(M), root(nullptr){}

  bool search(TK key){
    return search(root, key);
  }

  void insert(TK key){
    if(!root){
      root = new Node<TK>(M, true);
      root->keys[0] = key;
      root->count = 1;
    } else {
      Pair<TK, Node<TK>*> splitResult = insert(root, key);
      if (splitResult.second){
        Node<TK> *parent = new Node<TK>(M, false);
        parent->keys[0] = splitResult.first;
        parent->children[0] = root;
        parent->children[1] = splitResult.second;
        parent->count = 1;
        root = parent;
      }
    }
  }

  void remove(TK key){
    remove(root, key);

    if (root->count == 0){
      Node<TK>* temp = root;
      root = root->children[0];
      delete temp;
    }
  }

  int height(){
    if (!this->root) return -1;

    Node<TK>* curr = this->root;
    int h{};
    while (!curr->leaf){
      curr = curr->children[0];
      h++;
    }
    return h;
  }

  void display(){
    display_tree(root);
  }

  std::string toString(std::string sep){
    return toString(root, sep);
  }

  ~BTree(){
    if (root) delete root;
  }
};
