#include <fstream>
#include <cmath>
#include "BDS_Data.hh"

BDS_Input::BDS_Input(string file_name)
{  
  unsigned i, s, n_tasks, t;
  ifstream is(file_name);
  
  if (!is) 
  {
    cerr << "Cannot open file " <<  file_name << endl;
	  exit(1);
  }

  is >> tasks >> shifts >> optimal_value;
  shift_members.resize(shifts);
  task_coverage.resize(tasks);
  covers.resize(shifts, vector<bool>(tasks,false));
  shift_cost.resize(shifts);
  
  for (s = 0; s < shifts; s++)
  {
    is >> shift_cost[s] >> n_tasks;
    for (i = 0; i < n_tasks; i++)
    {
      is >> t;
      shift_members[s].push_back(t);
      task_coverage[t].push_back(s);
      covers[s][t] = true;
    }
  }
}

ostream& operator<<(ostream& os, const BDS_Input& bds)
{
  unsigned s, t, i;
  os << bds.tasks << " " << bds.shifts << " " << bds.optimal_value << endl;
  for (s = 0; s < bds.shifts; s++)
    {
      os << bds.shift_cost[s] << " " << bds.shift_members[s].size() << " ";
      for (i = 0; i < bds.shift_members[s].size(); i++)
         os <<  bds.shift_members[s][i] << " ";
      os << endl;
    }
  os << endl;
  for (t = 0; t < bds.tasks; t++)
    {
      os << bds.task_coverage[t].size() << " ";
      for (i = 0; i < bds.task_coverage[t].size(); i++)
         os <<  bds.task_coverage[t][i] << " ";
      os << endl;
    }
  os << endl;
  for (s = 0; s < bds.shifts; s++)
     {
       for (t = 0; t < bds.tasks; t++)
          if (bds.covers[s][t])
            os << '*';
          else
            os << '-';
       os << endl;
     }
  os << endl;
  return os;
}

BDS_Output::BDS_Output(const BDS_Input& my_in)
  : in(my_in), selected_shifts(Shifts(), false), coverage(Tasks(), 0)
{
  members = 0;
  uncovered = Tasks();
  total_cost = 0;
}

BDS_Output& BDS_Output::operator=(const BDS_Output& out)
{
  selected_shifts = out.selected_shifts;
  members = out.members;
  coverage = out.coverage;
  uncovered = out.uncovered;
  total_cost = out.total_cost;
  return *this;
}

void BDS_Output::InsertShift(unsigned s) 
{ 
  unsigned i, t;
  selected_shifts[s] = true; 
  members++;
  total_cost += in.ShiftCost(s);
  for (i = 0; i < in.ShiftMembers(s); i++)
  {
    t = in.ShiftMember(s,i);
    coverage[t]++;
    if (coverage[t] == 1)
      uncovered--;
  }
}

void BDS_Output::RemoveShift(unsigned s) 
{ 
  unsigned i, t;
  selected_shifts[s] = false;
  members--;
  total_cost -= in.ShiftCost(s);
  for (i = 0; i < in.ShiftMembers(s); i++)
  {
    t = in.ShiftMember(s,i);
    coverage[t]--;
    if (coverage[t] == 0)
      uncovered++;
  }
}

void BDS_Output::RemoveAll()
{
  unsigned s, t;
  for (s = 0; s < in.Shifts(); s++)
    selected_shifts[s] = false;
  members = 0;  
  for (t = 0; t < in.Tasks(); t++)
    coverage[t] = 0;
  uncovered = in.Tasks();
  total_cost = 0;
}

ostream& operator<<(ostream& os, const BDS_Output& out)
{
  unsigned s, t, m = 0;
  os << "Shifts = (";
  for (s = 0; s < out.Shifts(); s++)
    {
      if (out.selected_shifts[s])
        {
          os << s;
          m++;
          if (m < out.members)
            os << ", ";
        }
    }
  os << ") [" << out.members << "/" << out.total_cost << "], Coverage = {";
  for (t = 0; t < out.Tasks(); t++)
    {
      os << out.coverage[t];
      if (t < out.Tasks() - 1)
        os << ", ";
    }
  os << "} (uncovered = " << out.uncovered << ")"; 
  return os;
}

