#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <utility>

int minKey(int key[], bool mstSet[], int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void print(std::vector<std::pair<int,int>> v, int num){
  for (int x = 0; x < num; x++){
    std::cout << v[x].first << " " << v[x].second << std::endl;
  }
}

int main(int argc, char* argv[]) {
  // parse the expected input
  // first, the number of nodes for the complete graph part
  int num_nodes;
  std::cin >> num_nodes;

  // second, read in the complete graph
  std::vector< std::vector<int> > graph;
  for(int i=0; i<num_nodes; ++i) {
    std::vector<int> row;
    for (int j=0; j<num_nodes; ++j) {
      int cost;
      std::cin >> cost;
      row.push_back(cost);
    }
    graph.push_back(row);
  }

  //start of the mess

  int parent[num_nodes];
  int key[num_nodes];
  bool mstSet[num_nodes];

  for (int i = 0; i < num_nodes; i ++){
    key[i] = INT_MAX;
    mstSet[i] = false;
  }

  key[0] = 0;
  parent[0] = -1;


  int half = (num_nodes)/2 - 1;
  std::vector<std::pair<int,int>> vp;
  for(int j = 0; j <= half; j++){
    int u = minKey(key, mstSet, num_nodes);
    mstSet[u] = true;
    std::pair <int,int> p;
    if(j != 0){
      p.first = parent[u];
      p.second = u;
      vp.push_back(p);
    }
    for (int k = 0; k < num_nodes; k++){
      if(graph[u][k] && mstSet[k] == false && graph[u][k] < key[k]){
        parent[k] = u;
        key[k] = graph[u][k];
      }
    }
  }

  // last bit until newline from last cin followed by a blank line
  std::string skip;
  std::getline(std::cin, skip);
  std::getline(std::cin, skip);
  
  // read in the new edges
  // parse input lines until I find newline
  for(std::string line; std::getline(std::cin, line) && line.compare(""); ) {
    std::stringstream ss(line);
    int from;
    int to;
    int cost;
    ss >> from;
    ss >> to;
    ss >> cost;

    graph[to][from] = graph[from][to] = cost;
  }

  //update key value after second read
  for(int e = 0; e < num_nodes; e++){
    key[e] = INT_MAX;
  }
  for(int q = 0; q < num_nodes; q++){
    if(mstSet[q]){
      for(int w = 0; w < num_nodes; w++){
        if(graph[q][w] && mstSet[w] == false && graph[q][w] < key[w]){
          parent[w] = q;
          key[w] = graph[q][w];
        }
      }
    }
  }

  for(int j = half+1; j < num_nodes; j++){
    int u = minKey(key, mstSet, num_nodes);
    mstSet[u] = true;
    std::pair <int,int> p;
    if(j != 0){
      p.first = parent[u];
      p.second = u;
      vp.push_back(p);
    }
    for (int k = 0; k < num_nodes; k++){
      if(graph[u][k] && mstSet[k] == false && graph[u][k] < key[k]){
        parent[k] = u;
        key[k] = graph[u][k];
      }
    }
  }

    print(vp, half);
    std::cout << std::endl;
    print(vp, vp.size());

  return 0;
}
