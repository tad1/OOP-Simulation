#pragma once
#include <cmath>
#include <string>
/// <summary>
/// Representation of vector in Cartesian coordinate system 
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class Vector2T {
public:
    T x;
    T y;

    Vector2T(T x_ = 0, T y_ = 0) : x(x_), y(y_) {};

    //casting
    template <class T2>
    operator Vector2T<T2>() {
        Vector2T<T2> result;
        result.x = (T2)x;
        result.y = (T2)y;
        return result;
    }


#pragma region UnaryOperators

    Vector2T operator- () {
        Vector2T<T> result = *this;
        result.x *= -1;
        result.y *= -1;
        return result;
    };

    template <class T2>
    Vector2T operator + (const Vector2T<T2> arg) {
        Vector2T<T2> result = *this;
        result.x += arg.x;
        result.y += arg.y;
        return result;
    };

    template <class T2>
    Vector2T operator - (const Vector2T<T2> arg) {
        Vector2T<T2> result = *this;
        result.x -= arg.x;
        result.y -= arg.y;
        return result;
    };

    template <class T2>
    Vector2T operator * (const Vector2T<T2> arg) {
        Vector2T<T2> result = *this;
        result.x *= arg.x;
        result.y *= arg.y;
        return result;
    };

    template <class T2>
    Vector2T operator * (const T2 arg) {
        Vector2T<T> result = *this;
        result.x *= arg;
        result.y *= arg;
        return result;
    };

    template <class T2>
    Vector2T operator / (const T2 arg) {
        Vector2T<T> result = *this;
        result.x /= arg;
        result.y /= arg;
        return result;
    };



    template <class T2>
    Vector2T operator / (const Vector2T<T2> arg) {
        Vector2T<T2> result = *this;
        result.x /= arg.x;
        result.y /= arg.y;
        return result;
    };

    bool operator !() {
        return !this->x && !this->y;
    }
#pragma endregion

#pragma region BinaryOperators


    template <class T2>
    void operator+= (const Vector2T<T2> arg) {
        this->x += arg.x;
        this->y += arg.y;
    }

    template <class T2>
    void operator-= (const Vector2T<T2> arg) {
        this->x -= arg.x;
        this->y -= arg.y;
    }

    template <class T2>
    bool operator == (Vector2T<T2> param) {
        return this->x == param.x && this->y == param.y;
    }

    template <class T2>
    bool operator != (Vector2T<T2> param) {
        return this->x != param.x || this->y != param.y;
    }
#pragma endregion



    T quadMagnitude() {
        return this->x * this->x + this->y * this->y;
    }

    T magnitude() {
        return sqrt(quadMagnitude());
    }

    Vector2T<T> normalize() {
        Vector2T<float> result = *this;
        if (result.Magnitude() < 0.00001f) {
            result = 0.0f;
        }
        else {
            result = result / result.Magnitude();
        }
        return result;
    }

    std::string toString() {
        return "Vector2(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
    }

};

typedef Vector2T<float> Vector2;
typedef Vector2T<int> GridVector;
