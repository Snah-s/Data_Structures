#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, vector<vector<int>>& graph, vector<int>& state) {
  state[node] = 1;

  for (int neighbor : graph[node]) {
    if (state[neighbor] == 1) {
      return true;
    }
    if (state[neighbor] == 0 && dfs(neighbor, graph, state)) {
      return true;
    }
  }

  state[node] = 2;
  return false;
}

bool detectCycleDFS(int nodes, vector<vector<int>>& graph) {
  vector<int> state(nodes, 0);

  for (int i = 0; i < nodes; ++i) {
    if (state[i] == 0) {
      if (dfs(i, graph, state)) {
        return true;
      }
    }
  }
  return false;
}

/*

// MATRIZ DE ADYACENCIA

bool dfs(int node, vector<vector<int>>& matrix, vector<int>& state) {
  state[node] = 1;

  for (int neighbor = 0; neighbor < matrix.size(); ++neighbor) {
    if (matrix[node][neighbor] == 1) {
      if (state[neighbor] == 1) {
        return true;
      }
      if (state[neighbor] == 0 && dfs(neighbor, matrix, state)) {
        return true;
      }
    }
  }

  state[node] = 2;
  return false;
}

bool detectCycleDFS(int nodes, vector<vector<int>>& matrix) {
  vector<int> state(nodes, 0); 

  for (int i = 0; i < nodes; ++i) {
    if (state[i] == 0) {
      if (dfs(i, matrix, state)) {
        return true;
      }
    }
  }
  return false;
}

*/

int main() {
  int nodes = 4;
  vector<vector<int>> graph = {{1}, {2}, {3}, {1}};

  if (detectCycleDFS(nodes, graph)) {
    cout << "Ciclo detectado" << endl;
  } else {
    cout << "No se detectó ciclo" << endl;
  }

  return 0;
}