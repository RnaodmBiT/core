#pragma once
#include <array>
#include <vector.hpp>

namespace tk {
    namespace core {

        template <class T, int Rows, int Cols>
        class Matrix {
        public:
            static const int Size = Rows * Cols;
            std::array<T, Size> data;

            Matrix() {
                for (int y = 0; y < Rows; ++y) {
                    for (int x = 0; x < Cols; ++x) {
                        at(y, x) = (x == y ? T(1) : T(0));
                    }
                }
            }

            template <int X, int Y>
            Matrix(const Matrix<T, X, Y>& other) {
                static_assert(X <= Rows, "Matrix must be of smaller dimensions");
                static_assert(Y <= Cols, "Matrix must be of smaller dimensions");
                for (int y = 0; y < Rows; ++y) {
                    for (int x = 0; x < Cols; ++x) {
                        if (x < X && y < Y) {
                            at(y, x) = other(y, x);
                        } else {
                            at(y, x) = (x == y ? T(1) : T(0));
                        }
                    }
                }
            }

            void operator=(const Matrix& other) {
                for (int y = 0; y < Rows; ++y) {
                    for (int x = 0; x < Cols; ++x) {
                        at(y, x) = other(y, x);
                    }
                }
            }

            void operator*=(const Matrix& other) {
                static_assert(Rows == Cols, "Can only multiply-assign two matrices of the same dimensions.");
                Matrix result;
                for (int row = 0; row < Rows; ++row) {
                    for (int col = 0; col < Cols; ++col) {
                        result(row, col) = T(0);
                        for (int i = 0; i < Cols; ++i) {
                            result(row, col) += at(row, i) * other(i, col);
                        }
                    }
                }

                *this = result;
            }

            T& at(int row, int col) {
                return data[col + row * Cols];
            }

            const T& at(int row, int col) const {
                return data[col + row * Cols];
            }

            T& operator()(int row, int col) {
                return at(row, col);
            }

            const T& operator()(int row, int col) const {
                return at(row, col);
            }

        };


        template <class T, int Rows, int Inner, int Cols>
        Matrix<T, Rows, Cols> operator*(const Matrix<T, Rows, Inner>& left, const Matrix<T, Inner, Cols>& other) {
            Matrix<T, Rows, Cols> result;
            for (int row = 0; row < Rows; ++row) {
                for (int col = 0; col < Cols; ++col) {
                    result(row, col) = T(0);
                    for (int i = 0; i < Inner; ++i) {
                        result(row, col) += left(row, i) * other(i, col);
                    }
                }
            }
            return result;
        }

        template <class T, int Rows, int Cols>
        Vector<T, Rows> operator*(Matrix<T, Rows, Cols>& left, Vector<T, Cols>& right) {
            Vector<T, Rows> result;
            for (int i = 0; i < Rows; ++i) {
                result.data[i] = T(0);
                for (int j = 0; j < Cols; ++j) {
                    result.data[i] += left(i, j) * right.data[j];
                }
            }
            return result;
        }

        typedef Matrix<float, 4, 4> Mat4f;
        typedef Matrix<float, 3, 3> Mat3f;


        static Mat4f orthographic(float left, float top, float right, float bottom, float near = 0.0f, float far = 1.0f) {
            Mat4f ortho;
            ortho(0, 0) = 2.0f / (right - left);
            ortho(0, 3) = -(right + left) / (right - left);
            ortho(1, 1) = 2.0f / (top - bottom);
            ortho(1, 3) = -(top + bottom) / (top - bottom);
            ortho(2, 2) = -2.0f / (far - near);
            ortho(2, 3) = -(far + near) / (far - near);
            return ortho;
        }

        template <class T>
        Matrix<T, 4, 4> translate(T x, T y, T z) {
            Matrix<T, 4, 4> ret;
            ret(0, 3) = x;
            ret(1, 3) = y;
            ret(2, 3) = z;
            return ret;
        }

        template <class T>
        Matrix<T, 4, 4> translate(const Vector<T, 3>& vec) {
            return translate(vec.x, vec.y, vec.z);
        }

        static Mat4f rotate(float angle, const Vec3f& axis) {
            Mat4f mat;
            float c = std::cos(angle);
            float s = std::sin(angle);

            mat.at(0, 0) = c + axis.x * axis.x * (1 - c);
            mat.at(0, 1) = axis.x * axis.y * (1 - c) - axis.z * s;
            mat.at(0, 2) = axis.x * axis.z * (1 - c) + axis.y * s;

            mat.at(1, 0) = axis.x * axis.y * (1 - c) + axis.z * s;
            mat.at(1, 1) = c + axis.y * axis.y * (1 - c);
            mat.at(1, 2) = axis.y * axis.z * (1 - c) + axis.x * s;

            mat.at(2, 0) = axis.x * axis.z * (1 - c) - axis.y * s;
            mat.at(2, 1) = axis.y * axis.z * (1 - c) + axis.x * s;
            mat.at(2, 2) = c + axis.z * axis.z * (1 - c);

            return mat;
        }

    }
}
