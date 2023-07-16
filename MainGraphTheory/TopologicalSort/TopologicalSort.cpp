#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
  int from;
  int to;
  // int weight; Used for shortest path in a Directed Asyclic Graph (DAG).
};

vector<int> TopologicalSort(const vector<Edge>& edges, const int V){
  vector<int> res; // return topological order.

  // construct adjacency-list
  vector<vector<Edge>> graph(V,vector<Edge>());
  for(auto edge : edges){
    graph[edge.from].emplace_back(edge);
  }

  // Initialize in_degree.
  vector<int> in_degree(V,0);
  for(int i=0;i<V;i++){
    auto edges = graph[i];
    for(auto edge: edges){
      in_degree[edge.to]++;
    }
  }
  
  vector<bool> visited(V,false);
  queue<int> q; // list, stack으로 대체해도 상관 없음.

  // push nodes on condition that in_degree is 0.
  for(int n=0;n<V;n++){
    if(in_degree[n] == 0){
      visited[n] = true;
      q.push(n);
    }
  }

  while (!q.empty()){
    int cur_node = q.front();
    res.push_back(cur_node);
    q.pop();
    
    for(auto edge : graph[cur_node]){
      if(--in_degree[edge.to] == 0 && !visited[edge.to]){
        visited[edge.to] = true;
        q.push(edge.to);
      }
    }
  }

  return res;
}



int main(){
  
  int V = 6; // The number of vertexes.
  vector<Edge> edges = {
    {0,3},
    {0,1},
    {0,2},
    {1,2},
    {2,4},
    {4,5}
  };

  auto sorted_nodes = TopologicalSort(edges,V);

  // Just print the result.
  cout <<" Topological Ordering : ";
  for(int node : sorted_nodes){
    cout << node << " ";
  }
  cout << endl;

  return 0;
}
