#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm> 
#include "FCFS.hpp"
#include "SJF.hpp"
#include "RR.hpp"

void PrintMetrics( std::string str, const Metrics &m )
{
    std::cout << str << " " << std::fixed << std::setprecision(1) << m.return_time_ << " " << m.response_time_ << " " << m.waiting_time_ << std::endl; 
}

bool CompareProcesses( const Process &i, const Process &j )
{
    return i.arrive_time_ < j.arrive_time_;
}