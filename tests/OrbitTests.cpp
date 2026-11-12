#include "OrbitCamera.h"
#include "CameraHandoff.h"
#include <cstdlib>
#include <iostream>

void Near(double actual, double expected)
{
    if (!std::isfinite(actual) || std::abs(actual - expected) > 0.00001) {
        std::cerr << "Expected " << expected << ", got " << actual << '\n';
        std::exit(1);
    }
}
int main()
{
    for (double heading : {-2.0, 0.0, 1.7})
        for (double attitude : {-1.0, 0.0, 1.0})
            for (double bank : {-2.4, 0.0, 2.1}) {
                float matrix[3][3]{};
                Orbit::Write(matrix, {heading, attitude, bank});
                const auto angles = Orbit::Read(matrix);
                Near(angles.heading, heading);
                Near(angles.attitude, attitude);
                Near(angles.bank, bank);
                // A rotation must preserve unit lengths and perpendicular axes.
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j) {
                        double dot{};
                        for (int k = 0; k < 3; ++k) dot += matrix[i][k] * matrix[j][k];
                        Near(dot, i == j ? 1 : 0);
                    }
            }
    for (double pole : {-std::numbers::pi/2, std::numbers::pi/2}) {
        float matrix[3][3]{};
        Orbit::Write(matrix, {0, pole, 0});
        const auto a = Orbit::Read(matrix);
        Near(a.attitude, pole);
        Near(a.bank, 0);
    }
    // Vertical rotation passes both poles and can complete full revolutions.
    Near(Orbit::VerticalAngle(2.0), 2.0);
    Near(Orbit::VerticalAngle(-2.0), -2.0);
    Near(Orbit::VerticalAngle(2 * std::numbers::pi + 0.2), 0.2);
    Near(Orbit::VerticalAngle(-2 * std::numbers::pi - 0.2), -0.2);
    double vertical{};
    for (int i = 0; i < 10000; ++i) vertical = Orbit::VerticalAngle(vertical + 0.01);
    Near(vertical, std::remainder(100.0, 2 * std::numbers::pi));
    // Wrapping the angle changes no matrix entries, even beyond the poles.
    for (double angle : {-7.0, -3.2, -2.0, 2.0, 3.2, 7.0}) {
        float raw[3][3]{}, wrapped[3][3]{};
        Orbit::Write(raw, {0.3, -0.5, angle});
        Orbit::Write(wrapped, {0.3, -0.5, Orbit::VerticalAngle(angle)});
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) Near(wrapped[i][j], raw[i][j]);
    }
    // The handoff preserves the orbit viewing ray, including rolled/inverted views.
    for (double h : {-2.0, 0.0, 1.7})
        for (double a : {-1.5, 0.0, 1.5})
            for (double b : {-3.0, -1.57, 0.0, 1.57, 3.0}) {
                float m[3][3]{};
                Orbit::Write(m, {h, a, b});
                const auto look = Handoff::FromCameraMatrix(m);
                Near(std::sin(look.yaw) * std::cos(look.pitch), m[0][1]);
                Near(std::cos(look.yaw) * std::cos(look.pitch), m[1][1]);
                Near(-std::sin(look.pitch), m[2][1]);
            }
    for (float direction : {-1.0F, 1.0F}) {
        float pole[3][3]{{1,0,0},{0,0,direction},{0,-direction,0}};
        const auto look = Handoff::FromCameraMatrix(pole);
        Near(-std::sin(look.pitch), pole[2][1]);
        Near(std::cos(look.pitch), 0);
    }
    float yaw[3][3]{};
    Orbit::Write(yaw, {0, std::numbers::pi/2, 0});
    Near(yaw[1][0], 1);
    float pitch[3][3]{};
    Orbit::Write(pitch, {0, 0, std::numbers::pi/2});
    Near(pitch[1][2], -1);
    std::cout << "Orbit rotation tests passed\n";
}



