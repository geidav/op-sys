#ifndef TYPES_HPP
#define TYPES_HPP

struct Vector2
{
    float x, y;
};

struct Vector3
{
    float x, y, z;
};

struct Vector4
{
    float x, y, z, w;
};

struct Size2
{
    int x, y;
};

struct Size3
{
    int x, y, z;
};

struct Rect
{
    int x0, y0, x1, y1;
};

#endif