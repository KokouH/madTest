#if !defined(PATH_GET_HPP)
#define PATH_GET_HPP

#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include "structs.hpp"

class IPathGenerator
{
public:
    virtual std::vector<int> getPath(int end) = 0; // generate path from 0 to size
    virtual double getPathLength(std::vector<int>& path) = 0;
};

class PathGenerator : IPathGenerator
{
// По ближайшему соседу
public:
    PathGenerator(std::vector<Point>& points, std::vector<std::vector<int>>& connections);
    virtual std::vector<int> getPath(int end);
    virtual double getPathLength(std::vector<int>& path);

private:
    std::vector<Point>& m_points;
    std::vector<std::vector<int>>& m_connections;
    void genPath(std::list<int>& path, int cur, int end);

};

#endif