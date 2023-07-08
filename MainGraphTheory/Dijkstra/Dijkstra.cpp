#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<vector<int>,vector<int>> dist_and_prev;
typedef pair<int,int> node_and_cost;

#define INF INT32_MAX
#define CANT_CALC -1 


struct Edge{
  int from;
  int to;
  int weight;
};

dist_and_prev dijkstra(int V, int start, const vector<Edge>& edges){
  // edges to adjacency-list.
  vector<vector<Edge>> graph(V,vector<Edge>(0));
  for(const auto& edge : edges){
    graph[edge.from].emplace_back(edge);
  }

  vector<int> dist(V,INF);
  dist[start] = 0;

  vector<int> prev(V,CANT_CALC);
  class comp_for_pq{
  public:
    bool operator()(const node_and_cost& lhs,const node_and_cost& rhs){
      return lhs.second > rhs.second;
    }
  };
  priority_queue<node_and_cost,vector<node_and_cost>,comp_for_pq> pq;
  pq.push(node_and_cost (start,0));

  while(!pq.empty()){
    auto node_cost = pq.top();
    pq.pop();
    int cur_node = node_cost.first;
    int cur_cost = node_cost.second;

    if(dist[cur_node] < cur_cost) continue; // neat optimization

    for(const auto& adj : graph[cur_node]){
      int from = adj.from;
      int to = adj.to;
      int cost = cur_cost + adj.weight;
      if(dist[from] + cost < dist[to]){
        dist[to] = dist[from] + cost;
        prev[to] = from;
        pq.push({to,cost});
      }
    }
  }
  
  dist_and_prev res;
  res.first = dist;
  res.second = prev;
  return res;
}

int main(){
  int V = 6; // the number of vertexies.
  // refer to the graph on README  
  vector<Edge> edges = {
    {0,1,8},
    {1,3,7},
    {1,2,5},
    {2,4,5},
    {3,4,4},
    {4,5,7}
  };

  auto dist_and_prev = dijkstra(V,0,edges);
  auto dist = dist_and_prev.first;
  auto prev = dist_and_prev.second;


  // shortest distances from start node (0)
  for(int i=0;i<V;i++){
    cout <<"i : "<<i <<", dist : "<<dist[i] << endl;
  }
  cout << endl << endl;

  // prev
  for(int i=0;i<V;i++){
    cout <<"i : "<<i <<", prev : "<<prev[i] << endl;
  }
  cout << endl << endl;
  
  // getting path example using prev.
  // shortest path from start(0) to goal(3)
  int goal = 5;
  cout << "shortest path from start(0) to goal(5) : " ;
  if(dist[goal] == INF){
    cout << "The goal is un-rechable. can't get path" << endl;
  }
  else{
    vector<int> rpath;
    int node = goal;
    while(node != CANT_CALC){
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