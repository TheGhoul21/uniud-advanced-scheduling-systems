#ifndef _BDS_INPUT_HH_
#define _BDS_INPUT_HH_

#include <iostream>
#include <vector>

using namespace std;

class BDS_Input 
{
  friend ostream& operator<<(ostream& os, const BDS_Input& bs);
public:
  BDS_Input(string file_name);
  unsigned Tasks() const { return tasks; }
  unsigned Shifts() const { return shifts; }
  unsigned OptimalValue() const { return optimal_value; }
  unsigned ShiftMembers(unsigned s) const { return shift_members[s].size(); }
  unsigned ShiftMember(unsigned s, unsigned i) const { return shift_members[s][i]; }
  unsigned TaskCoverage(unsigned t) const { return task_coverage[t].size(); }
  unsigned TaskCovering(unsigned t, unsigned i) const { return task_coverage[t][i]; }
  bool Covers(unsigned s, unsigned t) const { return covers[s][t]; }
  unsigned ShiftCost(unsigned s) const { return shift_cost[s]; }
  
protected:
  unsigned tasks, shifts;
  unsigned optimal_value;

  vector<unsigned> shift_cost;
  
  vector<vector<bool>> covers; 
  vector<vector<unsigned>> shift_members; 
  vector<vector<unsigned>> task_coverage; 
};

class BDS_Output 
{
  friend ostream& operator<<(ostream& os, const BDS_Output& out);
  friend istream& operator>>(istream& is, BDS_Output& out);
public:
  BDS_Output(const BDS_Input& i);
  BDS_Output& operator=(const BDS_Output& out);
  bool operator[](unsigned s) const { return selected_shifts[s]; }
  unsigned Members() const { return members; }
  unsigned Shifts() const { return in.Shifts(); }
  unsigned Tasks() const { return in.Tasks(); }
  unsigned Coverage(unsigned t) const { return coverage[t]; }
  unsigned Uncovered() const { return uncovered; }
  unsigned TotalCost() const { return total_cost; }

  // Setters
  void InsertShift(unsigned s);
  void RemoveShift(unsigned s);
  void RemoveAll();

 private:
  const BDS_Input& in;
  vector<bool> selected_shifts;
  vector<unsigned> coverage;
  unsigned members;
  unsigned uncovered;
  unsigned total_cost;
};
#endif



