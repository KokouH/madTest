#include "pathGen.hpp"

PathGenerator::PathGenerator(std::vector<Point>& points, std::vector<std::vector<int>>& connections)
    : m_points(points),
    m_connections(connections)
{}

std::vector<int> PathGenerator::getPath(int end)
{
    std::list<int> path;

    genPath(path, 0, end);

    return std::vector<int>(path.begin(), path.end());
}

double lenPoints(Point& a, Point& b)
{
    return std::sqrt(
        (a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y)
    );
}

void PathGenerator::genPath(std::list<int>& path, int cur, int end)
{
    if (path.size() == 100)
        return;

    std::vector<int> notVisit;

    auto getNoVisit = [&path, cur, end, this](){
        std::vector<int> notVisit;
        for (int& j: m_connections[cur])
        {
            if (std::find(path.begin(), path.end(), j) == path.end() // no visit conf
                && !(j == end && path.size() == 99) // if not last way
            )
                notVisit.push_back(j);
        }
        return notVisit;
    };
    notVisit = getNoVisit();
    if (notVisit.size() == 0)
    {
        path.pop_front();
        return;
    }

    std::sort(notVisit.begin(), notVisit.end(), [&](int a, int b){
        return lenPoints(m_points[cur], m_points[a])
            < lenPoints(m_points[cur], m_points[b]);
    });

    for (auto& i: notVisit)
    {
        path.push_front(i);
        genPath(path, i, end);
        if (path.size() == 100)
            break;
        notVisit = getNoVisit();
        if (notVisit.size() == 0)
        {
            path.pop_front();
            return;
        }
    }
}

double PathGenerator::getPathLength(std::vector<int>& path)
{
    double len = 0.0;
    int a, b;

    for (int i = 0; i < path.size() - 1; ++i)
    {
        a = path[i];
        b = path[i + 1];
        len += std::sqrt(
                (m_points[a].x - m_points[b].x) * (m_points[a].x - m_points[b].x) +
                (m_points[a].y - m_points[b].y) * (m_points[a].y - m_points[b].y)
        );
    }

    return len;
}