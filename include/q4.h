#ifndef Q4_H
#define Q4_H

#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace q4 {
struct Vector2D {
    Vector2D(double _x = 0, double _y = 0)
        : x(_x)
        , y(_y) {};
    double x {};
    double y {};
};

struct Sensor {
    Sensor(Vector2D _pos, double _accuracy)
        : pos(_pos)
        , accuracy(_accuracy) {};
    Vector2D pos;
    double accuracy;
};

struct xwieghted {
    double operator()(double average, Sensor& S)
    {
        return average + S.pos.x * S.accuracy;
    }
};
struct ywieghted {
    double operator()(double average, Sensor& S)
    {
        return average + S.pos.y * S.accuracy;
    }
};

inline Vector2D kalman_filter(std::vector<Sensor> sensors)
{

    double andaze {};
    andaze = std::accumulate(sensors.begin(), sensors.end(), andaze, [](double sum_result, Sensor s) { return sum_result + s.accuracy; });
    double x_wieghted = std::accumulate(sensors.begin(), sensors.end(), 0.0, xwieghted()) / andaze;
    double y_wieghted = std::accumulate(sensors.begin(), sensors.end(), 0.0, ywieghted()) / andaze;
    Vector2D v(x_wieghted, y_wieghted);
    return v;
}

}

#endif // Q4_H