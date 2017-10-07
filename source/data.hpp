#ifndef DATA_HPP_
#define DATA_HPP_

struct Process
{
    int arrive_time_;
    int duration_;
    int id_;
};

struct Metrics
{
    float return_time_;
    float response_time_;
    float waiting_time_;
};

#endif // DATA_HPP_ 