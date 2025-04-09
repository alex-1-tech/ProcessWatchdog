#pragma once

#include <thread>
#include <atomic>
#include <functional>

class DataCollectorThread
{
public:
    using Callback = std::function<void()>;

    DataCollectorThread(int intervalMs, Callback callback);
    ~DataCollectorThread();

    void start();
    void stop();

private:
    void run();

    std::thread thread_;
    std::atomic<bool> running_;
    int intervalMs_;
    Callback callback_;
};