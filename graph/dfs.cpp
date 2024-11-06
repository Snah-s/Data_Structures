#include "../queue_stack/stack.h"
#include "../queue_stack/queueVector.h"

// 1. **DFS Iterativo con Pila**

void dfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
  Stack<int> stack;
  stack.push(start);
  while (!stack.empty()) {
    int node = stack.top();
    stack.pop();
    if (!visited[node]) {
      visited[node] = true;
      for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
          stack.push(neighbor);
        }
      }
    }
  }
}


// 2. **DFS con Registro de Tiempos de Entrada y Salida**
int time = 0;
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& in, vector<int>& out) {
  visited[node] = true;
  in[node] = time++;
  for (int neighbor : adj[node]) {
    if (!visited[neighbor]) {
      dfs(neighbor, adj, visited, in, out);
    }
  }
  out[node] = time++;
}


// 3. **DFS para Búsqueda de Ciclos**

enum Color { WHITE, GRAY, BLACK };
bool dfs(int node, vector<vector<int>>& adj, vector<Color>& color) {
  color[node] = GRAY;
  for (int neighbor : adj[node]) {
    if (color[neighbor] == GRAY) return true; // ciclo detectado
    if (color[neighbor] == WHITE && dfs(neighbor, adj, color)) return true;
  }
  color[node] = BLACK;
  return false;
}


// 4. **DFS para Encontrar Componentes Fuertemente Conexas (Kosaraju's Algorithm)**
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, Stack<int>& stack) {
  visited[node] = true;
  for (int neighbor : adj[node])
    if (!visited[neighbor])
      dfs(neighbor, adj, visited, stack);
  stack.push(node);
}

void dfs(int node, vector<vector<int>>& transpose, vector<bool>& visited) {
  visited[node] = true;
  for (int neighbor : transpose[node])
    if (!visited[neighbor])
      dfs(neighbor, transpose, visited);
}


// 5. **DFS para Árbol de Baja Profundidad (Low-Link Values)**

vector<int> disc, low;
vector<bool> visited;
int time = 0;

void dfs(int node, int parent, vector<vector<int>>& adj) {
  visited[node] = true;
  disc[node] = low[node] = ++time;
  int children = 0;
  for (int neighbor : adj[node]) {
    if (!visited[neighbor]) {
      children++;
      dfs(neighbor, node, adj);
      low[node] = min(low[node], low[neighbor]);
      if (low[neighbor] > disc[node]) {
      }
    } else if (neighbor != parent) {
      low[node] = min(low[node], disc[neighbor]);
    }
  }
}


// 6. **DFS para Contar Componentes Conexas**

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
  visited[node] = true;
  for (int neighbor : adj[node]) {
    if (!visited[neighbor]) {
      dfs(neighbor, adj, visited);
    }
  }
}

int countComponents(int n, vector<vector<int>>& adj) {
  vector<bool> visited(n, false);
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(i, adj, visited);
      count++;
    }
  }
  return count;
}


// 7. **DFS con Camino de Restauración**
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& path) {
  visited[node] = true;
  path.push_back(node);
  for (int neighbor : adj[node]) {
    if (!visited[neighbor]) {
      dfs(neighbor, adj, visited, path);
    }
  }
  path.pop_back();
}
