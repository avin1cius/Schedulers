#include "RR.hpp"

inline void InsertProcessInQueue( std::queue<Process> &queue, const_iterator &it, const const_iterator end_it, int time, bool push_front )
{
    while ( it != end_it )
    {
        if ( queue.empty() )
        {
            time = (*it).arrive_time_;
        }
        if ( (*it).arrive_time_ <= time )
        {
            queue.push( *it );
            it++;
        }
        else break;  
    }

    if ( push_front )
    {
        queue.push( queue.front() );
        queue.pop();
    }
}

Metrics RR( const std::vector<Process> &vecProcess, int quantum )
{
    const int num_processes = vecProcess.size();
    const_iterator it = vecProcess.begin(), end_it = vecProcess.end();
    int remaining_processes = num_processes;
    int time = 0;

    std::vector<int> remaining_duration( num_processes );
    for ( int i = 0; i < num_processes; i++ )
    {
        remaining_duration[i] = vecProcess[i].duration_;
    } 

    std::vector<Metrics> vecMetrics( num_processes );
    Metrics average = {};

    std::queue<Process> queue;
    Process process;
    
    int index = 0;

    while ( it != end_it )
    {
        if ( (*it).arrive_time_ == vecProcess[0].arrive_time_ )
        {
            queue.push( *it );
        }
        else break;
        it++;
    }    

    while ( remaining_processes )
    {
        process = queue.front();
        index = process.id_;

        if( remaining_duration[index] == process.duration_ ) //First time being executed
        {
            if ( time < process.arrive_time_ ) time = process.arrive_time_;
            
            vecMetrics[index].response_time_ = time - process.arrive_time_;
        }

        remaining_duration[index] -= quantum;
        
        if ( remaining_duration[index] > 0 ) //If the process has not been completed
        {
            time += quantum;
            InsertProcessInQueue( queue, it, end_it, time, true );
        }
        else
        {
            time += quantum + remaining_duration[index];
            remaining_processes--;
            queue.pop();
            InsertProcessInQueue( queue, it, end_it, time, false );
            
            vecMetrics[index].return_time_ = time - process.arrive_time_;
            vecMetrics[index].waiting_time_ = vecMetrics[index].return_time_ - process.duration_;
        }
    }

    for ( int i = 0; i < num_processes; i++ )
    {
        average.return_time_ += vecMetrics[i].return_time_;
        average.response_time_ += vecMetrics[i].response_time_;
        average.waiting_time_ += vecMetrics[i].waiting_time_;
    }

    average.return_time_ /= (float)num_processes;
    average.response_time_ /= (float)num_processes;
    average.waiting_time_ /= (float)num_processes;

    return average;
}
