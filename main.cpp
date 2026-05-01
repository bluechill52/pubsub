#include "Broker.h"
#include "Slam.h"
#include "CalibEngine.h"

using namespace std;


int main() {
    Broker<FrameInfo> broker;

    // Create a slam object
    Slam slam(broker);
    
    // Create a calib engine object
    CalibEngine calibEngine(broker);

    for (int i = 0; i < 1000; ++i) {
        slam.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // 4 Hz
    }
}