#include "../queue_stack/queueVector.h"

void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& component) {
  Queue<int> q;
  q.enqueue(start);
  visited[start] = true;
  component.push_back(start);
  
  while (!q.empty()) {
    int node = q.front();
    q.dequeue();
    for (int neighbor : adj[node]) {
      if (!visited[neighbor]) {
        visited[neighbor] = true;
        q.enqueue(neighbor);
        component.push_back(neighbor);
      }
    }
  }
}

vector<vector<int>> adjacentComponents(int n, vector<vector<int>>& adj) {
  vector<bool> visited(n, false);
  vector<vector<int>> components;
  
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      vector<int> component;
      bfs(i, adj, visited, component);
      components.push_back(component);
    }
  }
  
  return components;
}