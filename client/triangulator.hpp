#ifndef TRIANGULATOR_HPP
#define TRIANGULATOR_HPP

#include <vector>

#include "primitives.hpp"



class Triangulate {
public:
    typedef std::vector<pr::Vec2> PointsArray;

    // triangulate a contour/polygon, places results in STL vector
    // as series of triangles.
    static bool Process(const PointsArray &contour, PointsArray &result);

    // compute area of a contour/polygon
    static float Area(const PointsArray &contour);

    // decide if point Px/Py is inside triangle defined by
    // (Ax,Ay) (Bx,By) (Cx,Cy)
    static bool InsideTriangle(float Ax, float Ay,
                      float Bx, float By,
                      float Cx, float Cy,
                      float Px, float Py);

private:
    static bool Snip(const PointsArray &contour,int u,int v,int w,int n,int *V);
};


#endif
