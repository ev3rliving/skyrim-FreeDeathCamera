#pragma once
#include <algorithm>
#include <cmath>

namespace Handoff
{
    struct Look { float pitch{}, yaw{}; };
    inline Look FromCameraMatrix(const float (&m)[3][3])
    {
        // Skyrim cameras look along local +Y (the matrix's second column).
        const float horizontal = std::hypot(m[0][1], m[1][1]);
        const float pitch = -std::atan2(m[2][1], horizontal);
        // At a vertical pole, use the right axis to avoid atan2(0,0).
        const float yaw = horizontal > 0.00001F ? std::atan2(m[0][1], m[1][1]) :
            std::atan2(-m[1][0], m[0][0]);
        return {pitch, yaw};
    }
}

