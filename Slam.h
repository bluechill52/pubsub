#include <memory>
#include "Broker.h"
#include "FrameInfo.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <random>

using namespace std;


static float getRandomReal() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

class Slam {
public:
    explicit Slam(Broker<FrameInfo>& broker) : broker_(broker) {};
    void tick() {
        // Computes frame info at 4Hz
        // publishes frame info to subcribers through broker
        auto t0 = std::chrono::steady_clock::now();
        FrameInfo frame;
        frame.camId_ = rand() % 100; // Random ID between 0-99

        int numPoints = 5; // Let's create 5 points
        
        // Resize and fill with random values
        // .setRandom() produces values between -1 and 1
        frame.points2D_.resize(numPoints, Eigen::NoChange);
        frame.points2D_.setRandom();
        
        frame.points3D_.resize(numPoints, Eigen::NoChange);
        frame.points3D_.setRandom();
        broker_.publish(frame);
        auto dt = std::chrono::steady_clock::now() - t0;
        std::cout << "[SLAM] Published data: Cam ID " << frame.camId_ << endl;
        /* std::cout << "[SLAM] publish() returned in "
                  << std::chrono::duration_cast<std::chrono::microseconds>(dt).count()
                  << " µs\n"; */
        return;
    }

private:
    Broker<FrameInfo>& broker_;
};