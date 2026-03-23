#include <iostream>
#include <cstdlib>
#include "GC_Data.hh"
#include "GC_Greedy.hh"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <input_file>" << endl;
    exit(1);
  } 
  
  Graph in(argv[1]);
  Coloring out(in);
  GreedyGCSolver(in, out);
  cout << out << endl;  
  return 0;
}

