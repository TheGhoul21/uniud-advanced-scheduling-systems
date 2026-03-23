#ifndef _GC_GREEDY_HH_
#define _GC_GREEDY_HH_
#include "GC_Data.hh"

void Update(unsigned n, unsigned c, vector<vector<unsigned>>& v, const Graph& in);
unsigned SelectNode(const vector<vector<unsigned>>& v, const Graph& in, const Coloring& out);
void GreedyGCSolver(const Graph& in, Coloring& out);

#endif
