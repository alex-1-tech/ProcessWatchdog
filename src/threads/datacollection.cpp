#include "datacollection.h"
#include <chrono>

DataCollectorThread::DataCollectorThread(int intervalMs, Callback callback)
    : intervalMs_(intervalMs), callback_(callback), running_(false) {}

DataCollectorThread::~DataCollectorThread()
{
    stop();
}

void DataCollectorThread::start()
{
    if (running_)
        return;

    running_ = true;
    thread_ = std::thread(&DataCollectorThread::run, this);
}

void DataCollectorThread::stop()
{
    if (!running_)
        return;

    running_ = false;
    if (thread_.joinable())
    {
        thread_.join();
    }
}

void DataCollectorThread::run()
{
    while (running_)
    {
        callback_();
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs_));
    }
}