#include "CameraMotion.h"
#include <cstdlib>
#include <iostream>
#include <numbers>

void Near(float actual, float expected)
{
    if (std::abs(actual - expected) > 0.005F) {
        std::cerr << "Expected " << expected << ", got " << actual << '\n';
        std::exit(1);
    }
}
int main()
{
    for (int fps : {30, 60, 144}) {
        float distance{};
        for (int frame = 0; frame < fps; ++frame)
            distance += Motion::Calculate(0, 0, 1, 0, 0, 1.0F/fps, 200, 1, 0, 8).y;
        Near(distance, 200);
    }
    // Engine-wrapped upward pitch must stay upward on the next frame.
    Near(Motion::WrapAngle(2 * std::numbers::pi_v<float> - 0.5F), -0.5F);
    float pitch = 0;
    for (int i = 0; i < 1000; ++i) {
        if (pitch < 0) pitch += 2 * std::numbers::pi_v<float>;
        pitch = Motion::WrapAngle(pitch - 0.01F);
        Near(pitch, Motion::WrapAngle(-0.01F * (i + 1)));
    }
    const auto diagonal = Motion::Calculate(0, 0, 1, 1, 0, 0.05F, 200, 1, 0, 8);
    Near(std::hypot(diagonal.x, diagonal.y), 10);
    const auto boosted = Motion::Calculate(0, 0, 1, 0, 0, 0.05F, 200, 4, 0, 8);
    Near(boosted.y, 40);
    const auto down = Motion::Calculate(std::numbers::pi_v<float>/2, 0, 1, 0, 0, 0.05F, 200, 1, 0, 8);
    Near(down.z, -10);
    const auto yaw = Motion::Calculate(0, std::numbers::pi_v<float>/2, 1, 0, 0, 0.05F, 200, 1, 0, 8);
    Near(yaw.x, 10);
    Near(yaw.y, 0);
    const auto wheel = Motion::Calculate(0, 0, 0, 0, 0, 0, 200, 1, -1, 8);
    Near(wheel.y, -8);
    Near(Motion::Calculate(0, 0, 1, 0, 0, 3, 200, 1, 0, 8).y, 10);
    Near(Motion::Calculate(0, 0, 1, 0, 0, -1, 200, 1, 0, 8).y, 0);
    std::cout << "Motion tests passed\n";
}

