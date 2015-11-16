#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

class AdjacencyList { // TODO: Refactor code
  public:
    using Vertices = unordered_map<int, list<int>>;
    
    AdjacencyList():edgeSize(0) {};

    int verSize() {
      return vertices.size();
    }

    template <class Function>
    void DFS(const int v, int *visited, Function fn, int where = 0) {
      visited[v] = 1;
      if( where == 2 )
        fn(v, -2);
      auto bg = vertices[v].begin();
      while( bg != vertices[v].end() ) {
        if( !visited[*bg] ) { 
          if(where == 0)
            fn(v, *bg);
          DFS(*bg, visited, fn, where);
        }
        ++bg;
      }
      if(where == 1)
        fn(v, -1);
    }
    
    vector<int> SCC() {
      AdjacencyList rev = reverse();

      int order[rev.verSize()];
      int index = 0;
      int visited[rev.verSize()];

      int sum;
      vector<int> res;

      for(int i = 0; i < rev.verSize(); i++) visited[i] = 0;

      for( int i = 0; i < rev.verSize(); i++ ) {
        if( !visited[i] ){ 
          rev.DFS(i, visited, [&index, &order](const int v, const int w){ order[index++] = v; }, 1);
        }
      }

      for(int i = 0; i < verSize(); i++) visited[i] = 0;

      for( int i = 0; i < verSize(); i++) {
        if( !visited[order[verSize()-i-1]] ) {
          sum = 0;
          DFS(order[verSize()-i-1], visited, [&sum](const int v, const int w){ sum++; }, 2);
          res.push_back(sum);
        }
      }
      return res;
    }

    AdjacencyList reverse() {
      AdjacencyList rev;

      for( int i = 0; i < verSize(); i++ )
        rev.vertices[i] = {};

      /* for( auto & ver : vertices ) { */
        // for( auto i : ver.second )
          // rev.insert(i, ver.first);
      // }

      for( int i = 0; i < verSize(); i++ ) {
        for( auto n : vertices[i])
          rev.insert(n, i);
      }
      return rev;
    }

    void DFS(const int v) {
      int * visited = new int[verSize()];
      for( int i = 0; i < verSize(); i++ ) 
        visited[i] = 0;
      DFS(v, visited, [](int from, int to){cout<<'<'<<from<<','<<to<<'>'<<endl;}, 0);
      delete [] visited;
    }

    void inspect() {
      cout<<"Count of vertices: "<<verSize()<<endl;
      cout<<"Count of edges: "<<edgeSize<<endl;
      cout<<"--"<<endl;
      for( auto &ver : vertices ) {
        cout<<ver.first<<":\t";
        for( auto i : ver.second )
          cout<<i<<", ";
        cout<<endl;
      }
    }

    void insert(int ver, const list<int> & edges) {
      vertices[ver] = edges;
      cout<<"edges: "<<edges.size()<<endl;
      edgeSize += edges.size();
    }

    void insert(int from, int to) {
      vertices[from].push_back(to);
      edgeSize++;
    }

    void inspect_list( const list<int> & edges ) {
      for( auto e : edges ) cout<<e<<' ';
      cout<<endl;
    }

    // Members
    int edgeSize;
    Vertices vertices;
};

void inspect(const vector<int> & vec) {
  for( auto n : vec ) cout<<n<<' ';
  cout<<endl;
}

void smallCase1() {
  AdjacencyList graph;

  graph.insert(0, {3});
  graph.insert(1, {7});
  graph.insert(2, {5});
  graph.insert(3, {6});
  graph.insert(4, {1});
  graph.insert(5, {8});
  graph.insert(6, {0});
  graph.insert(7, {4, 5});
  graph.insert(8, {2, 6});

  // graph.insert(0, list<int>() ); // Attn: which version this calls !!!
  
  graph.inspect();
  cout<<"--"<<endl;
  // graph.DFS(0);
  cout<<"--"<<endl;
  inspect(graph.SCC());
  // cout<<"--"<<endl;
}

void bigCase() {
  AdjacencyList g;
  for( int i = 0; i < 875714; i++ ) g.vertices[i] = {};
  int from, to;
  while( cin>>from>>to ) 
    g.insert( from-1, to-1 );
  auto res = g.SCC();
  sort(res.begin(), res.end());
  for(int i = 0; i < 5; i++) cout<<res[res.size() - i - 1]<<endl;
}

int main() {
  // smallCase1();
  bigCase();
  return 0;
}
