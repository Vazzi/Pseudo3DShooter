#ifndef __VECTOR2D__
#define __VECTOR2D__

#include <cmath>

class Vector2D {
    public:
        Vector2D(double x, double y): m_x(x), m_y(y) {}

        double getX() const { return m_x; }
        double getY() const { return m_y; }

        void setX(double x) { m_x = x; }
        void setY(double y) { m_y = y; }

        double length() const { return sqrt(m_x * m_x + m_y * m_y); }

        Vector2D operator+ (const Vector2D& v2) const {
            return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
        }

        friend Vector2D& operator+= (Vector2D& v1, const Vector2D& v2) {
            v1.m_x += v2.m_x;
            v1.m_y += v2.m_y;
            return v1;
        }

        Vector2D operator* (double scalar) {
            return Vector2D(m_x * scalar, m_y * scalar);
        }

        Vector2D& operator*= (double scalar) {
            m_x *= scalar;
            m_y *= scalar;
            return *this;
        }

        Vector2D operator- (const Vector2D& v2) const {
            return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
        }

        friend Vector2D& operator-= (Vector2D& v1, Vector2D& v2) {
            v1.m_x -= v2.m_x;
            v1.m_y -= v2.m_y;
            return v1;
        }

        Vector2D operator/(double scalar) {
            return Vector2D(m_x / scalar, m_y / scalar);
        }

        Vector2D& operator/= (double scalar) {
            m_x /= scalar;
            m_y /= scalar;
            return *this;
        }

        void normalize() {
            double l = length();
            if (l > 0) {
                (*this) *= 1/l;
            }
        }

    private:
        double m_x;
        double m_y;
};

#endif
