#include "SJF.hpp"
#include <iostream>

void InsertProcessInQueue( min_priority_queue &priority_queue, const_iterator &it, const const_iterator end_it, int &time, const int size )
{
    static std::vector<bool> inserted( size, false );
    int num_inserted = 0;

    while ( it != end_it )
    {
        if ( priority_queue.empty() && (*it).arrive_time_ > time)
        {
            time = (*it).arrive_time_;
        }

        if ( ( (*it).arrive_time_ <= time ) && !inserted[(*it).id_] )
        {
            priority_queue.push( *it );
            inserted[(*it).id_] = true;
            num_inserted++;
        }
        else break;
        it++;
    }
}

Metrics SJF( const std::vector<Process> &vecProcess )
{
    const int num_processes = vecProcess.size();
    int time = 0;
    int remaining_processes = num_processes;
    const_iterator it = vecProcess.begin(), end_it = vecProcess.end();

    std::vector<Metrics> vecMetrics( num_processes );
    Metrics average_metrics = {};

    min_priority_queue priority_queue;

    Process process;
    int index;

    while ( remaining_processes )
    {
        InsertProcessInQueue( priority_queue, it, end_it, time, num_processes );

        process = priority_queue.top();

        index = process.id_;

        vecMetrics[index].response_time_ = time - process.arrive_time_;
        vecMetrics[index].return_time_ = vecMetrics[index].response_time_ + process.duration_;
        vecMetrics[index].waiting_time_ = vecMetrics[index].response_time_;

        time += process.duration_;

        priority_queue.pop();
        remaining_processes--;

        average_metrics.return_time_ += vecMetrics[index].return_time_;
        average_metrics.response_time_ += vecMetrics[index].response_time_;
        average_metrics.waiting_time_ += vecMetrics[index].waiting_time_;
    }

    average_metrics.return_time_ /= (float)num_processes;
    average_metrics.response_time_ /= (float)num_processes;
    average_metrics.waiting_time_ /= (float)num_processes;

    return average_metrics;
}
