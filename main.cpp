#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <utility>

#include "structs.hpp"
#include "pathGen.hpp"

# define M_PI 3.14159265358979323846  // pi 

std::random_device rd;

Point generateRandomPointInCircle(double r) {
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double theta = dis(gen) * 2 * M_PI;
    double radius = r * std::sqrt(dis(gen));

    return {radius * std::cos(theta), radius * std::sin(theta)};
}

double getAngle(const Point& p) {
    return std::atan2(p.y, p.x);
}

int main() {
    const int numberOfPoints = 100;
    const double circleRadius = 1.0;
    int neighborsCount;
    std::random_device gen;
    std::vector<Point> points;

    for (int i = 0; i < numberOfPoints; ++i) {
        points.push_back(generateRandomPointInCircle(circleRadius));
    }

    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return getAngle(a) < getAngle(b);
    });

    std::vector<std::vector<int>> neighbors(numberOfPoints);

    // Соединяем точки
    for (int i = 0; i < numberOfPoints; ++i) {
        neighborsCount = gen() % 5 + 2;

        for (int j = -(neighborsCount/2); j < neighborsCount/2; ++j)
            neighbors[i].push_back((i + j + numberOfPoints) % numberOfPoints);
    }

    // Сохранениее точек и соседния
    std::ofstream file;
    file.open("Points.txt");
    for (int i = 0; i < numberOfPoints; ++i)
    {
        file << points[i].x << " " << points[i].y << "\n";
    }
    file << "\n";
    for (int i = 0; i < numberOfPoints; ++i)
    {
        for (int j = 0; j < neighbors[i].size(); ++j)
            file << neighbors[i][j] << " ";
        file << "\n";
    }
    file.close();
    
    PathGenerator pathGen(points, neighbors);
    std::vector<int> path = pathGen.getPath(99);
    for (auto& i: path)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
