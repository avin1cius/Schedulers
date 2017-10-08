#include "SJF.hpp"

void InsertProcessInQueue( const std::vector<Process> &vecProcess, min_priority_queue &priority_queue, int &time )
{
    static int last_inserted;
    int num_inserted = 0;    
    std::vector<Process>::const_iterator it = ( vecProcess.begin() + last_inserted );

    while ( it != vecProcess.end() )
    {
        if ( (*it).arrive_time_ <= time )
        {
            priority_queue.push( *it );
            last_inserted = (*it).id_ + 1;
            num_inserted++;
            it++;
        }
        else if ( !num_inserted )
        {
            priority_queue.push( *it );
            last_inserted = (*it).id_ + 1;
            num_inserted++;      
            time = (*it).arrive_time_;
            it++;
        }
        else break;
    }
}

Metrics SJF( const std::vector<Process> &vecProcess )
{
    const int num_processes = vecProcess.size();
    int time = 0;
    int remaining_processes = num_processes;

    std::vector<Metrics> vecMetrics( num_processes );
    Metrics average_metrics = {};

    min_priority_queue priority_queue;

    Process process;
    int index;

    while ( remaining_processes )
    {
        InsertProcessInQueue( vecProcess, priority_queue, time );

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
