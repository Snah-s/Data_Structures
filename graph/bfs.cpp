#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool detectCycleBFS(int nodes, vector<vector<int>>& graph) {
  vector<int> inDegree(nodes, 0);

  for (int i = 0; i < nodes; ++i) {
    for (int neighbor : graph[i]) {
      inDegree[neighbor]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < nodes; ++i) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }

  int count = 0;

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    count++;

    for (int neighbor : graph[node]) {
      inDegree[neighbor]--;
      if (inDegree[neighbor] == 0) {
        q.push(neighbor);
      }
    }
  }

  return count != nodes;
}

/*

// MATRIZ DE ADYACENCIA
bool detectCycleBFS(int nodes, vector<vector<int>>& matrix) {
  vector<int> inDegree(nodes, 0);

  for (int i = 0; i < nodes; ++i) {
    for (int j = 0; j < nodes; ++j) {
      if (matrix[i][j] == 1) {
        inDegree[j]++;
      }
    }
  }

  queue<int> q;
  for (int i = 0; i < nodes; ++i) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }

  int count = 0;

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    count++;

    for (int neighbor = 0; neighbor < nodes; ++neighbor) {
      if (matrix[node][neighbor] == 1) {
        inDegree[neighbor]--;
        if (inDegree[neighbor] == 0) {
          q.push(neighbor);
        }
      }
    }
  }

  return count != nodes;
}

*/

int main() {
  int nodes = 4;
  vector<vector<int>> graph = {{1}, {2}, {3}, {1}};

  if (detectCycleBFS(nodes, graph)) {
    cout << "Ciclo detectado" << endl;
  } else {
    cout << "No se detectó ciclo" << endl;
  }

  return 0;
}