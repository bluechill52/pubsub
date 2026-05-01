#pragma once

#include <vector>
#include <array>
#include <Eigen/Dense>


using namespace std;

struct FrameInfo {
    int camId_;
    Eigen::MatrixX2f points2D_;
    Eigen::MatrixX3f points3D_;
};