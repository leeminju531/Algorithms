#include <iostream>
#include <vector>

using namespace std;

typedef pair<vector<int>,vector<int>> dist_and_prev;

#define POSITIVE_INF INT16_MAX  
#define NEGATIVE_INF INT16_MIN

#define CANNOT_CALC -100

struct Edge{
  int from;
  int to;
  int weight;
};

dist_and_prev bellmanFord(const int V, const int start, const vector<Edge>& edges){
  vector<int> dist(V,POSITIVE_INF);
  dist[start] = 0;
  
  vector<int> prev(V,CANNOT_CALC); // Add prev if you wanna get a path.

  // Relaxation
  for(int i=0;i<V-1;i++){
    for(auto& edge : edges){
      int from = edge.from;
      int to = edge.to;
      int cost = edge.weight;
      if(dist[from] + cost < dist[to]){
        dist[to] = dist[from] + cost;
        prev[to] = from;
      }
    }
  }

  // Set the nodes within any negative cycles to 'negative inf'.
  for(int i=0;i<V-1;i++){
    for(auto& edge : edges){
      int from = edge.from;
      int to = edge.to;
      int cost = edge.weight;
      if(dist[from] + cost < dist[to]){
        dist[to] = NEGATIVE_INF;
        prev[to] = CANNOT_CALC;
      }
    }
  }

  dist_and_prev res;
  res.first = dist;
  res.second = prev;
  return res;
}

int main(){

  int V = 8; // the number of vertexes
  // refer to the graph on README  
  vector<Edge> edges = {
        {0, 1, 2},
        {1, 2, -1},
        {0, 2, 8},
        {2, 5, -10},
        {5, 4, 8},
        {2, 4, 1},
        {0, 3, 3},
        {2, 3, 1},
        {4, 6, -7},
        {6, 5, -2},
        {6, 7, 100}
    };

  // bellman-ford
  auto answer = bellmanFord(V,0,edges);
  vector<int> distances = answer.first;
  vector<int> prev = answer.second;

  // shortest distances from start node (0)
  for(int i=0;i<V;i++){
    cout <<"i : "<<i <<", dist : "<<distances[i] << endl;
  }
  cout << endl << endl;

  // prev
  for(int i=0;i<V;i++){
    cout <<"i : "<<i <<", prev : "<<prev[i] << endl;
  }
  cout << endl << endl;

  // getting path example using prev.
  // shortest path from start(0) to goal(3)
  int goal = 3;
  cout << "shortest path from start(0) to goal(3) : " ;
  if(distances[goal] == NEGATIVE_INF){
    cout << "The goal is in negative cycle. can't get path" << endl;
  }
  else{
    vector<int> rpath;
    int node = goal;
    while(node != CANNOT_CALC){
      rpath.emplace_back(node);
      node = prev[node];
    }

    for(int i=rpath.size()-1;i>=0;i--){
      cout << rpath[i] << " ";
    }
    cout << endl << endl;
  }
  
  return 0;
}