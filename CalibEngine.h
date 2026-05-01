#include "Broker.h"
#include "FrameInfo.h"
#include <queue>
#include <thread>
#include <iostream>

using namespace std;

class CalibEngine {
public:
    explicit CalibEngine(Broker<FrameInfo>& broker) : broker_(broker) {
        broker_.subscribe([this](const FrameInfo& info) {
            queue_.push(info);
        });

        worker_ = std::thread([this]{ process(); });
    };

    void process() {
        // Get a frame from queue
        while(!queue_.empty()) {
            FrameInfo frameInfo = queue_.front();
            cout << "Popped from queue. Data: Cam ID " << frameInfo.camId_ << endl;
            queue_.pop();
            
            // Do something expensive - simulate with a sleep
            this_thread::sleep_for(std::chrono::milliseconds(1000));    // 1 Hz
        }
    }
private:
    Broker<FrameInfo>& broker_;
    queue<FrameInfo> queue_;
    std::thread worker_;
};