#include <fstream>
#include "GC_Data.hh"

Graph::Graph(string file_name)
{
  char ch;
  string buffer;
  unsigned i, j, val;

  ifstream is(file_name);

  if (!is)
  {
    cerr << "Could not open file " << file_name << endl;
    exit(1);
  }

  is >> buffer >> ch >> nodes >> ch; // read nodes = <num_nodes>;
  is >> buffer >> ch >> colors >> ch; // read colors = <num_colors>;

  adjacency_matrix.resize(nodes,vector<bool>(nodes,false));
  adjacency_list.resize(nodes);

  is >> buffer >> ch >> ch >> ch;  // read adjacency_matrix = [|


  for (i = 0; i < nodes; i++)
  {
    for (j = 0; j < nodes; j++)
	  {
	    is >> val >> ch;
	    if (val == 1 && i < j)
	    {
	      adjacency_matrix[i][j] = true;
	      adjacency_matrix[j][i] = true;
	      adjacency_list[i].push_back(j);
	      adjacency_list[j].push_back(i);
	    }
	  }
  }
}

ostream& operator<<(ostream& os, const Graph& g)
{
  unsigned i, j;

  os << "nodes = " << g.nodes << ";" << endl;
  os << "colors = " << g.colors << ";" << endl << endl;
  os << "adjacency_matrix = [";
  
  for (i = 0; i < g.nodes; i++)
    {
      os << '|';
      for (j = 0; j < g.nodes; j++)
	    {
	      os << g.adjacency_matrix[i][j];
	      if (j < g.nodes - 1)
	        os << ",";
	    }
      if (i == g.nodes - 1)
	      os << "|];";
      os << endl;
    }
  for (i = 0; i < g.nodes; i++)
  {
	 for (j = 0; j < g.adjacency_list[i].size(); j++)
       os << g.adjacency_list[i][j] << " ";
     os << endl;
  }	 
  return os;
}

void Coloring::Reset()
{
	unsigned i;
	for (i = 0; i < in.Nodes(); i++)
	  coloring[i] = -1;
}

ostream& operator<<(ostream& os, const Coloring& col)
{
  unsigned i;
  os << "[";
  for (i = 0; i < col.in.Nodes() - 1; i++)
    os << col[i] << ",";
  os << col[i] << "]";
  return os;
}


