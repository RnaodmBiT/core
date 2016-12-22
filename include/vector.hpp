#pragma once
#include <detail/vector_base.hpp>
#include <serialize.hpp>
#include <cmath>

namespace tk {
    namespace core {

        template <class T, int N>
        class Vector : public detail::VectorData<T, N> {
        public:

            Vector(T x = 0) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] = x;
                }
            }

            Vector(std::initializer_list<T> elements) {
                int i = 0;
                for (const T& e : elements) {
                    this->data[i++] = e;
                }
            }

            Vector(const Vector& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] = v.data[i];
                }
            }


            T dot(const Vector& v) const {
                T sum = 0;
                for (int i = 0; i < N; ++i) {
                    sum += this->data[i] * v.data[i];
                }
                return sum;
            }


            template <class U = T>
            typename std::enable_if<N == 3, Vector<U, 3>>::type cross(const Vector& v) const {
                return Vector{
                    this->y * v.z - this->z * v.y,
                    this->z * v.x - this->x * v.z,
                    this->x * v.y - this->y * v.x
                };
            }


            T lengthSquared() const {
                T sum = 0;
                for (int i = 0; i < N; ++i) {
                    sum += this->data[i] * this->data[i];
                }
                return sum;
            }


            T length() const {
                return std::sqrt(lengthSquared());
            }


            void normalize() {
                T l = length();
                for (int i = 0; i < N; ++i) {
                    this->data[i] /= l;
                }
            }


            Vector normalized() const {
                Vector v = *this;
                v.normalize();
                return v;
            }


            Vector operator-() const {
                Vector negate;
                for (int i = 0; i < N; ++i) {
                    negate.data[i] = -this->data[i];
                }
                return negate;
            }


            Vector& operator=(const Vector& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] = v.data[i];
                }
                return *this;
            }

            Vector& operator+=(const Vector& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] += v.data[i];
                }
                return *this;
            }

            Vector& operator-=(const Vector& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] -= v.data[i];
                }
                return *this;
            }

            Vector& operator*=(const Vector& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] *= v.data[i];
                }
                return *this;
            }

            Vector& operator/=(const Vector& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] /= v.data[i];
                }
                return *this;
            }

            Vector& operator+=(const T& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] += v;
                }
                return *this;
            }

            Vector& operator-=(const T& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] -= v;
                }
                return *this;
            }

            Vector& operator*=(const T& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] *= v;
                }
                return *this;
            }

            Vector& operator/=(const T& v) {
                for (int i = 0; i < N; ++i) {
                    this->data[i] /= v;
                }
                return *this;
            }

        };


        template <class T, int N>
        Vector<T, N> operator+ (Vector<T, N> a, const Vector<T, N>& b) {
            return a += b;
        }

        template <class T, int N>
        Vector<T, N> operator- (Vector<T, N> a, const Vector<T, N>& b) {
            return a -= b;
        }

        template <class T, int N>
        Vector<T, N> operator* (Vector<T, N> a, const Vector<T, N>& b) {
            return a *= b;
        }

        template <class T, int N>
        Vector<T, N> operator/ (Vector<T, N> a, const Vector<T, N>& b) {
            return a /= b;
        }

        template <class T, int N>
        Vector<T, N> operator+ (Vector<T, N> a, const T& b) {
            return a += b;
        }

        template <class T, int N>
        Vector<T, N> operator- (Vector<T, N> a, const T& b) {
            return a -= b;
        }

        template <class T, int N>
        Vector<T, N> operator* (Vector<T, N> a, const T& b) {
            return a *= b;
        }

        template <class T, int N>
        Vector<T, N> operator/ (Vector<T, N> a, const T& b) {
            return a /= b;
        }


        typedef Vector<float, 2> Vec2f;
        typedef Vector<float, 3> Vec3f;
        typedef Vector<float, 4> Vec4f;

        typedef Vector<double, 2> Vec2d;
        typedef Vector<double, 3> Vec3d;
        typedef Vector<double, 4> Vec4d;

        typedef Vector<int, 2> Vec2i;
        typedef Vector<int, 3> Vec3i;
        typedef Vector<int, 4> Vec4i;

        template <class T, int N>
        struct convert<Vector<T, N>> {
            void serialize(Blob& blob, const Vector<T, N>& vector) {
                tk::core::serialize(blob, vector.data);
            }

            void deserialize(Blob::const_iterator& it, Vector<T, N>& vector) {
                tk::core::deserialize(it, vector.data);
            }
        };

        static float angleBetween(const Vec2f& to, const Vec2f& from) {
            return std::atan2(to.y - from.y, to.x - from.x);
        }

    }
}
