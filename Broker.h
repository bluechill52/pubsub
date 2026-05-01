#pragma once

#include <functional>
#include <vector>
#include <iostream>

using namespace std;


template <typename T>
class Broker {
public:
    using Callback = std::function<void(const T&)>;
    void publish(const T& msg) {
        cout << "Pushing to queue" << endl;
        for(auto& cb : subscribers_) {
            cb(msg);
        }
    }

    void subscribe(Callback cb) {
        subscribers_.push_back(cb);
    }

private:
    std::vector<Callback> subscribers_;
};