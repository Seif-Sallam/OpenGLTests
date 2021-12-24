#pragma once
#include <iostream>
#include <math.h>
#include "glm/glm.hpp"

template <class T>
struct Vec2
{
    union
    {
        struct
        {
            T x, y;
        };
        int data[2];
    };

    Vec2()
        : x(0), y(0)
    {
    }
    Vec2(T x, T y)
        : x(x), y(y)
    {
    }
    Vec2(const glm::vec2 &v2)
        : x(v2.x), y(v2.y)
    {
    }

    Vec2(const Vec2<T> &v2)
        : x(v2.x), y(v2.y)
    {
    }
    Vec2<T> &Zeros()
    {
        this->x = 0;
        this->y = 0;
        return *this;
    }
    Vec2<T> &Ones()
    {
        this->x = 1;
        this->y = 1;
        return *this;
    }

    Vec2<T> &Normalize()
    {
        float length = sqrt(pow(x, 2) + pow(y, 2));
        x /= length;
        y /= length;
        return *this;
    }

    operator glm::vec2()
    {
        return glm::vec2(x, y);
    }
    Vec2<T> operator+(const Vec2<T> &v2)
    {
        return Vec2<T>(x + v2.x, y + v2.y);
    }
    Vec2<T> operator-(const Vec2<T> &v2)
    {
        return Vec2<T>(x - v2.x, y - v2.y);
    }
    Vec2<T> &operator+=(const Vec2<T> &v2)
    {
        x += v2.x;
        y += v2.y;
        return *this;
    }
    Vec2<T> &operator-=(const Vec2<T> &v2)
    {
        x -= v2.x;
        y -= v2.y;
        return *this;
    }

    Vec2<T> operator+(const glm::vec2 &v2)
    {
        return Vec2<T>(x + v2.x, y + v2.y);
    }
    Vec2<T> operator-(const glm::vec2 &v2)
    {
        return Vec2<T>(x - v2.x, y - v2.y);
    }
    Vec2<T> &operator+=(const glm::vec2 &v2)
    {
        x += v2.x;
        y += v2.y;
        return *this;
    }
    Vec2<T> &operator-=(const glm::vec2 &v2)
    {
        x -= v2.x;
        y -= v2.y;
        return *this;
    }
};

template <class T>
struct Vec3
{
    union
    {
        struct
        {
            union
            {
                Vec2<T> xy;
                struct
                {
                    T x, y;
                };
            };
            T z;
        };
        int data[3];
    };
    Vec3()
        : x(0), y(0), z(0)
    {
    }
    Vec3(T x, T y, T z)
        : x(x), y(y), z(z)
    {
    }
    Vec3(const Vec2<T> &xy, T z)
        : xy(xy), z(z)
    {
    }
    Vec3(const Vec3<T> &v2)
        : xy(v2.xy), z(v2.z)
    {
    }
    Vec3(const glm::vec3 &v2)
        : x(v2.x), y(v2.y), z(v2.z)
    {
    }
    Vec3<T> &Zeros()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        return *this;
    }
    Vec3<T> &Ones()
    {
        this->x = 1;
        this->y = 1;
        this->z = 1;
        return *this;
    }
    Vec3<T> &Normalize()
    {
        float length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        x /= length;
        y /= length;
        z /= length;
        return *this;
    }
    operator glm::vec3()
    {
        return glm::vec3(x, y, z);
    }
    Vec3<T> operator+(const Vec3<T> &v2)
    {
        return Vec3<T>(x + v2.x, y + v2.y, z + v2.z);
    }
    Vec3<T> operator-(const Vec3<T> &v2)
    {
        return Vec3<T>(x - v2.x, y - v2.y, z - v2.z);
    }
    Vec3<T> &operator+=(const Vec3<T> &v2)
    {
        x += v2.x;
        y += v2.y;
        z += v2.z;
        return *this;
    }
    Vec3<T> &operator-=(const Vec3<T> &v2)
    {
        x -= v2.x;
        y -= v2.y;
        z -= v2.z;
        return *this;
    }

    Vec3<T> operator+(const glm::vec3 &v2)
    {
        return Vec3<T>(x + v2.x, y + v2.y, z + v2.z);
    }
    Vec3<T> operator-(const glm::vec3 &v2)
    {
        return Vec3<T>(x - v2.x, y - v2.y, z - v2.z);
    }
    Vec3<T> &operator+=(const glm::vec3 &v2)
    {
        x += v2.x;
        y += v2.y;
        z += v2.z;
        return *this;
    }
    Vec3<T> &operator-=(const glm::vec3 &v2)
    {
        x -= v2.x;
        y -= v2.y;
        z -= v2.z;
        return *this;
    }
};

template <class T>
struct Vec4
{
    union
    {
        union
        {
            struct
            {
                Vec2<T> xy;
                Vec2<T> zw;
            };
            struct
            {
                union
                {
                    struct
                    {
                        union
                        {
                            Vec3<T> xyz;
                            struct
                            {
                                T x, y, z;
                            };
                        };
                        T w;
                    };
                    struct
                    {
                        T r, g, b, a;
                    };
                };
            };
        };
        int data[4];
    };

    Vec4()
        : x(0), y(0), z(0), w(0)
    {
    }
    Vec4(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w)
    {
    }
    Vec4(const Vec2<T> &xy, const Vec2<T> &zw)
        : xy(xy), zw(zw)
    {
    }
    Vec4(const Vec2<T> &xy, T z, T w)
        : xy(xy), z(z), w(w)
    {
    }
    Vec4(const Vec3<T> &xyz, T w)
        : xyz(xyz), w(w)
    {
    }
    Vec4(const Vec4<T> &v2)
        : xyz(v2.xyz), w(v2.w)
    {
    }
    Vec4(const glm::vec4 &v2)
        : x(v2.x), y(v2.y), z(v2.z), w(v2.w)
    {
    }
    Vec4<T> &Zeros()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
        return *this;
    }
    Vec4<T> &Ones()
    {
        this->x = 1;
        this->y = 1;
        this->z = 1;
        this->w = 1;
        return *this;
    }
    Vec4<T> &Normalize()
    {
        float length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
        x /= length;
        y /= length;
        z /= length;
        w /= length;
        return *this;
    }
    operator glm::vec4()
    {
        return glm::vec4(x, y, z, w);
    }

    Vec4<T> operator+(const Vec4<T> &v2)
    {
        return Vec4<T>(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
    }
    Vec4<T> operator-(const Vec4<T> &v2)
    {
        return Vec4<T>(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
    }
    Vec4<T> &operator+=(const Vec4<T> &v2)
    {
        x += v2.x;
        y += v2.y;
        z += v2.z;
        w += v2.w;
        return *this;
    }
    Vec4<T> &operator-=(const Vec4<T> &v2)
    {
        x -= v2.x;
        y -= v2.y;
        z -= v2.z;
        w -= v2.w;
        return *this;
    }

    Vec4<T> operator+(const glm::vec4 &v2)
    {
        return Vec4<T>(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
    }
    Vec4<T> operator-(const glm::vec4 &v2)
    {
        return Vec4<T>(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
    }
    Vec4<T> &operator+=(const glm::vec4 &v2)
    {
        x += v2.x;
        y += v2.y;
        z += v2.z;
        w += v2.w;
        return *this;
    }
    Vec4<T> &operator-=(const glm::vec4 &v2)
    {
        x -= v2.x;
        y -= v2.y;
        z -= v2.z;
        w -= v2.w;
        return *this;
    }
};

template <class T>
std::ostream &operator<<(std::ostream &stream, const Vec2<T> &v)
{
    stream << "(" << v.x << ", " << v.y << ")";
    return stream;
}

template <class T>
std::ostream &operator<<(std::ostream &stream, const Vec3<T> &v)
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return stream;
}

template <class T>
std::ostream &operator<<(std::ostream &stream, const Vec4<T> &v)
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return stream;
}

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2u = Vec2<unsigned int>;

using Vec3i = Vec3<int>;
using Vec3f = Vec3<float>;
using Vec3u = Vec3<unsigned int>;

using Vec4i = Vec4<int>;
using Vec4f = Vec4<float>;
using Vec4u = Vec4<unsigned int>;