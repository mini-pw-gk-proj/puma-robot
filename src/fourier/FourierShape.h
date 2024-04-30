//
// Created by faliszewskii on 29.04.24.
//

#ifndef PUMAROBOT_FOURIERSHAPE_H
#define PUMAROBOT_FOURIERSHAPE_H

#include <utility>
#include <vector>
#include <valarray>

class FourierShape {
    struct FourierCoefficient {
        float frequency;
        float amplitude;
        float phase;
    };

    std::vector<FourierCoefficient> xCoeffs;
    std::vector<FourierCoefficient> yCoeffs;

public:
    FourierShape(std::vector<FourierCoefficient> xCoeffs, std::vector<FourierCoefficient> yCoeffs) :
        xCoeffs(std::move(xCoeffs)), yCoeffs(std::move(yCoeffs)) {}

    double getX(double xStart, double t, double rotation) {
        double x = xStart;
        for(auto &coeff : xCoeffs)
            x += coeff.amplitude * cos(coeff.frequency * t + coeff.phase + rotation);
        return x;
    };

    double getY(double yStart, double t, double rotation) {
        double y = yStart;
        for(auto &coeff : yCoeffs)
            y += coeff.amplitude * sin(coeff.frequency * t + coeff.phase + rotation);
        return y;
    };
};

#endif //PUMAROBOT_FOURIERSHAPE_H
