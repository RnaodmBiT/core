#pragma once
#include <detail/vector_base.hpp>
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


            typename std::enable_if<N == 3, Vector>::type cross(const Vector& v) const {
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
            }


            T length() const {
                return std::sqrt(lengthSquared());
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

    }
}
