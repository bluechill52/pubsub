#include "Broker.h"
#include "FrameInfo.h"
#include <queue>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class CalibEngine {
public:
    explicit CalibEngine(Broker<FrameInfo>& broker) : broker_(broker) {
        broker_.subscribe([this](const FrameInfo& info) {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                queue_.push(info);
            }

            cv_.notify_one();
        });

        // Wait for sometime before starting consumer thread
        this_thread::sleep_for(std::chrono::milliseconds(100));

        worker_ = std::thread([this]{ process(); });
    };

    void process() {
        // Get a frame from queue
        while(true) {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this]() {
                return !queue_.empty() || !running_;
            });

            if(!running_ || queue_.empty()) {
                break;
            }

            FrameInfo frameInfo = queue_.front();
            queue_.pop();
            lock.unlock();   // Release lock before doing expensive work

            
            // Do something expensive - simulate with a sleep
            cout << "[CalibEngine] Popped from queue. Data: Cam ID " << frameInfo.camId_ << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));    // 1 Hz
        }
    }

    ~CalibEngine() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            running_ = false;
        }
        cv_.notify_one();
        worker_.join();
    }

private:
    Broker<FrameInfo>& broker_;
    queue<FrameInfo> queue_;
    std::thread worker_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool running_ = true;
};