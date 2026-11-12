#pragma once
#include <algorithm>
#include <cmath>
#include <numbers>

namespace Motion
{
    inline float WrapAngle(float angle)
    {
        return std::remainder(angle, 2.0F * std::numbers::pi_v<float>);
    }
    struct Delta { float x{}, y{}, z{}; };
    inline Delta Calculate(float pitch, float yaw, float forward, float strafe,
        float flatForward, float dt, float speed, float boost, float wheel, float wheelStep)
    {
        const float magnitude = std::sqrt(forward * forward + strafe * strafe + flatForward * flatForward);
        if (magnitude > 1.0F) {
            forward /= magnitude;
            strafe /= magnitude;
            flatForward /= magnitude;
        }
        const float step = speed * std::clamp(dt, 0.0F, 0.05F) * boost;
        const float distance = forward * step + wheel * wheelStep;
        return {
            distance * std::cos(pitch) * std::sin(yaw) + strafe * step * std::cos(yaw) + flatForward * step * std::sin(yaw),
            distance * std::cos(pitch) * std::cos(yaw) - strafe * step * std::sin(yaw) + flatForward * step * std::cos(yaw),
            -distance * std::sin(pitch)
        };
    }
}

