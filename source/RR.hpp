#ifndef RR_HPP_
#define RR_HPP_

#include <vector>
#include <queue>
#include "data.hpp"

Metrics RR( const std::vector<Process> &p, int );

using const_iterator = std::vector<Process>::const_iterator;

inline void InsertProcessInQueue( std::queue<Process> &queue, const_iterator &it, const const_iterator end_it, int time, bool push_front );

#endif // RR_HPP_ 