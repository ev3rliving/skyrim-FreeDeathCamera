#pragma once
#include <cmath>

#include <numbers>

namespace Orbit
{
    inline double VerticalAngle(double angle)
    {
        // Wrap full turns to retain precision without limiting rotation.
        return std::remainder(angle, 2 * std::numbers::pi);
    }
    struct Angles { double heading{}, attitude{}, bank{}; };
    // Preserve the original mod's matrix convention, including its poles.
    inline Angles Read(const float (&mat)[3][3])
    {
        if (mat[1][0] > 0.998F)
            return {std::atan2(mat[0][2], mat[2][2]), std::numbers::pi / 2, 0};
        if (mat[1][0] < -0.998F)
            return {std::atan2(mat[0][2], mat[2][2]), -std::numbers::pi / 2, 0};
        return {std::atan2(-mat[2][0], mat[0][0]), std::asin(mat[1][0]),
            std::atan2(-mat[1][2], mat[1][1])};
    }
    inline void Write(float (&mat)[3][3], const Angles& a)
    {
        const double ch = std::cos(a.heading), sh = std::sin(a.heading);
        const double ca = std::cos(a.attitude), sa = std::sin(a.attitude);
        const double cb = std::cos(a.bank), sb = std::sin(a.bank);
        mat[0][0] = static_cast<float>(ch * ca);
        mat[0][1] = static_cast<float>(sh * sb - ch * sa * cb);
        mat[0][2] = static_cast<float>(ch * sa * sb + sh * cb);
        mat[1][0] = static_cast<float>(sa);
        mat[1][1] = static_cast<float>(ca * cb);
        mat[1][2] = static_cast<float>(-ca * sb);
        mat[2][0] = static_cast<float>(-sh * ca);
        mat[2][1] = static_cast<float>(sh * sa * cb + ch * sb);
        mat[2][2] = static_cast<float>(-sh * sa * sb + ch * cb);
    }
}



