#ifndef SJF_HPP_
#define SJF_HPP_

#include <vector>
#include <queue> 
#include "data.hpp"

Metrics SJF( const std::vector<Process> & );

class CompareDurations  
{
public:
  bool operator()(const Process &i, const Process &j)  
  {  
      return i.duration_ > j.duration_;  
  }  
};

using min_priority_queue = std::priority_queue<Process, std::vector<Process>, CompareDurations>;

void InsertProcessInQueue( const std::vector<Process> &vecProcess, min_priority_queue &priority_queue, int &time );

#endif // SJF_HPP_ 