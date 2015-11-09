#include <iostream>
#include <unordered_map>
#include <list>
#include <ctime>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

class AdjacencyList {
  public:
    using Vertices = unordered_map<int, list<int>>;
    
    AdjacencyList():edgeSize(0) {};
    int kargarMinCut() {
      srand(time(nullptr));

      while(verSize() > 2) {
        auto pair = randSelectEdge();
        mergeVer(pair.first, pair.second);
      }

      int sum = 0;
      for( auto &pair : vertices )
        sum += pair.second.size();
      return sum;
    }

    pair<int, int> randSelectEdge() {
      unsigned r = rand() % edgeSize + 1;
      for( auto & ver : vertices ) {
        if( r <= ver.second.size() ) {
          list<int>::const_iterator it = ver.second.begin();
          for(unsigned i = 1; i < r; ++i, ++it);
          return { ver.first, *it };
        } else {
          r -= ver.second.size();
        }
      }
      exit(100); // should never arrive here.
    }

    int verSize() {
      return vertices.size();
    }

    void mergeVer(int fst, int snd) {
      auto &fstList = vertices[fst];
      auto &sndList = vertices[snd];

      unsigned size = fstList.size();
      fstList.remove_if( [snd](const int & val) { return val == snd; } );
      size -= fstList.size();

      size += sndList.size();
      sndList.remove_if( [fst](const int & val) { return val == fst; } );
      size -= sndList.size();

      fstList.splice( fstList.end(), sndList );

      vertices.erase(snd);

      edgeSize -= size;

      for( auto & ver : vertices ) {
        if( ver.first != fst ) 
          replace_if(ver.second.begin(), ver.second.end(), [snd](const int & val) { return val == snd;}, fst);
      }
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
      edgeSize += edges.size();
    }

    void inspect_list( const list<int> & edges ) {
      for( auto e : edges ) cout<<e<<' ';
      cout<<endl;
    }

    // Members
    int edgeSize;
    Vertices vertices;
};

void smallCase1() {
  AdjacencyList graph;
  graph.inspect();

  graph.insert(1, {2, 3});
  graph.insert(2, {1, 3, 4});
  graph.insert(3, {1, 2, 4});
  graph.insert(4, {2, 3});

  graph.inspect();

  cout<<graph.kargarMinCut()<<endl;

  graph.inspect();
}

void smallCase2() {
  AdjacencyList graph;
  graph.inspect();

  graph.insert(1, {2, 3});
  graph.insert(2, {4});
  graph.insert(3, {2, 4});
  graph.insert(4, {});

  graph.inspect();

  cout<<graph.kargarMinCut()<<endl;

  graph.inspect();
}

void bigCase() {
  AdjacencyList graph;
  string str;
  while(getline(cin, str)) {
    istringstream iss(str);
    int ver; iss >> ver;
    list<int> edges;

    int tmp;
    while( iss >> tmp )
      edges.push_back(tmp);
    graph.insert(ver, edges);
  }

  cout<<graph.kargarMinCut();
  // graph.inspect();
}

int main() {
  bigCase();
  return 0;
} 
