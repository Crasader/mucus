#ifndef _MUCUS_PRIMITIVES_HPP_
#define _MUCUS_PRIMITIVES_HPP_

# include "defs.hpp"

# include "master.hpp"

namespace pr {

float worldToPixel(float world);
float pixelToWorld(float pixel);

struct Vec2 {
    float x;
    float y;

    Vec2()
        : x(0)
        , y(0)
    {}
    
    Vec2(cc::Size const& s)
        : x(pixelToWorld(s.width))
        , y(pixelToWorld(s.height))
    {}
    
    Vec2(cc::Point const& s)
        : x(pixelToWorld(s.x))
        , y(pixelToWorld(s.y))
    {}
    
    Vec2(b2Vec2 const& v)
        : x(v.x)
        , y(v.y)
    {}

    Vec2(float x, float y)
        : x(x)
        , y(y)
    {}
    
    cc::Size toCCSize() const
    {
        return cc::Size(worldToPixel(x), worldToPixel(y));
    }

    cc::Point toCCPoint() const
    {
        return cc::Point(worldToPixel(x), worldToPixel(y));
    }
    
    b2Vec2 tob2Vec2() const
    {
        return b2Vec2(x, y);
    }
    
    Vec2 operator-() const
    {
        Vec2 v(-x, -y);
        return v;
    }
    
    void operator+=(const Vec2& v)
    {
        x += v.x;
        y += v.y;
    }
    
    void operator-=(const Vec2& v)
    {
        x -= v.x;
        y -= v.y;
    }
    
    void operator*=(float a)
    {
        x *= a;
        y *= a;
    }

    void operator/=(float a)
    {
        x /= a;
        y /= a;
    }

    Vec2 operator*(float a) const
    {
        return Vec2(x*2, y*2);
    }

    Vec2 operator/(float a) const
    {
        return Vec2(x/2, y/2);
    }

    Vec2& absolutize();
    Vec2& normalize();

    float length() const;

    bool operator==(Vec2 const& b)
    {
        return (x == b.x) && (y == b.y);
    }

    bool operator!=(Vec2 const& b)
    {
        return !(*this == b);
    }

    Vec2 operator-(Vec2 const& b)
    {
        return Vec2(x - b.x, y - b.y);
    }
    
    Vec2 operator+(Vec2 const& b)
    {
        return Vec2(x + b.x, y + b.y);
    }
};

float distance(Vec2 const& a, Vec2 const& b);
float angle(Vec2 const& a, Vec2 const& b);
float angleAxisX(Vec2 const& v);

}

#endif
