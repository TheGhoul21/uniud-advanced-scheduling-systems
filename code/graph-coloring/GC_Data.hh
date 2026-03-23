#ifndef _GRAPH_HH_
#define _GRAPH_HH_

#include <iostream>
#include <vector>

using namespace std;

class Graph
{
  friend ostream& operator<<(ostream& os, const Graph& g);
 public: 
  Graph(string file_name);
  unsigned Nodes() const { return nodes; }
  unsigned Colors() const { return colors; }
  bool Arc(unsigned i, unsigned j) const { return adjacency_matrix[i][j]; }
  unsigned Degree(unsigned i) const { return adjacency_list[i].size(); }
  unsigned ArcListMember(unsigned i, unsigned j) const { return adjacency_list[i][j]; }
 protected:
  unsigned nodes, colors;
  vector<vector<bool>> adjacency_matrix;
  vector<vector<unsigned>> adjacency_list;
};

class Coloring
{
  friend ostream& operator<<(ostream& os, const Coloring& col);
public:
  Coloring(const Graph& my_in) : in(my_in), coloring(in.Nodes(), -1) {}
  void Reset();
  int operator[](unsigned i) const { return coloring[i]; }
  int& operator[](unsigned i) { return coloring[i]; }
protected:
  const Graph& in;
  vector<int> coloring;
};
#endif
