#include "GC_Greedy.hh"
#include "Random.hh"
#include <algorithm>
#include <numeric>

using namespace std;

void GreedyGCSolver(const Graph& in, Coloring& out)
{ 
  unsigned i, k, c;
  int n;
  vector<vector<unsigned>> colors(in.Nodes(), vector<unsigned>(in.Colors()));

  // iota generates vectors with values <0,1,2,3,...,c>
  for(i = 0; i < in.Nodes(); i++)
    iota(colors[i].begin(), colors[i].end(), 0);

  out.Reset();  
  for(i = 0; i < in.Nodes(); i++)
  {
    n = SelectNode(colors, in, out);
    if (colors[n].size() == 0)
      return; // coloring unsuccessful
    k = Random(0, colors[n].size()-1);
    c = colors[n][k];
    cerr << i << ". Assign color " << c << " to node " << n << endl;
    Update(n, c, colors, in);
    out[n] = c;    
  }
}

unsigned SelectNode(const vector<vector<unsigned>>& v, const Graph& in, const Coloring& out)
{
  unsigned i;
  int best = -1;

  for (i = 0; i < v.size(); i++)
  {
    if (out[i] == -1 && 
        (best == -1 || v[i].size() < v[best].size()
         || (v[i].size() == v[best].size() && in.Degree(i) > in.Degree(best))))
      best = i;
  }
  return best;
}

void Update(unsigned n, unsigned c, vector<vector<unsigned>>& v, const Graph& in)
{
  unsigned i, j, k;
  for (i = 0; i < in.Degree(n); i++)
  {
    k = in.ArcListMember(n,i);
    for (j = 0; j < v[k].size(); j++)
      if (v[k][j] == c)
      {
        v[k].erase(v[k].begin() + j);
        break;
      }
  }
}

