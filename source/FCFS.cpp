#include "FCFS.hpp"

Metrics FCFS( const std::vector<Process> &vecProcess  )
{
    const int num_processes = vecProcess.size();
    int time = 0; 
    std::vector<Metrics> vecMetrics( num_processes );
    Metrics average = {};

    for ( int i = 0; i < num_processes; i++ )
    {
        if ( time < vecProcess[i].arrive_time_ )
        {
            time = vecProcess[i].arrive_time_;
            vecMetrics[i].waiting_time_ = 0;
        }
        else vecMetrics[i].waiting_time_ = time - vecProcess[i].arrive_time_;

        vecMetrics[i].return_time_ = vecMetrics[i].waiting_time_ + vecProcess[i].duration_;
        vecMetrics[i].response_time_ = vecMetrics[i].waiting_time_;

        time += vecProcess[i].duration_;

        average.return_time_ += vecMetrics[i].return_time_;
        average.response_time_ += vecMetrics[i].response_time_;
        average.waiting_time_ += vecMetrics[i].waiting_time_;
    }

    average.return_time_ /= (float)num_processes;
    average.response_time_ /= (float)num_processes;
    average.waiting_time_ /= (float)num_processes;

    return average;
}
