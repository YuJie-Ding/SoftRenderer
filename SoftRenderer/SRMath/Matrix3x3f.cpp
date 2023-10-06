#include "Matrix3x3f.h"
#include "Matrix4x4f.h"

namespace  SR
{
    SR::Matrix3x3f::Matrix3x3f()
    {
        memset(mat, 0, sizeof(mat));
    }

    SR::Matrix3x3f::Matrix3x3f(const float mat_[3][3])
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                mat[i][j] = mat_[i][j];
    }

    SR::Matrix3x3f::Matrix3x3f(const Vector3f mat_[3])
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                mat[i][j] = mat_[i][j];
    }

    Matrix3x3f::Matrix3x3f(const Matrix4x4f& mat_)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                mat[i][j] = mat_[i][j];
    }

    Vector3f Matrix3x3f::operator*(const Vector3f& v) const
    {
        Vector3f vec;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                vec[i] += mat[i][j] * v[j];
            }
        }
        return vec;
    }

    Matrix3x3f Matrix3x3f::operator*(const float n) const
    {
        Matrix3x3f m = *this;
        for (int i = 0; i < 3; i++)
        {
            m[i] *= n;
        }
        return m;
    }

    Vector3f& SR::Matrix3x3f::operator[](unsigned int index)
    {
        return mat[index];
    }

    const Vector3f SR::Matrix3x3f::operator[](unsigned int index) const
    {
        return mat[index];
    }

    Matrix3x3f SR::Matrix3x3f::Transpose() const
    {
        Matrix3x3f m;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                m[i][j] = mat[j][i];
            }
        }
        return m;
    }

    Matrix3x3f SR::Matrix3x3f::Inverse() const
    {
        Matrix3x3f adjoint;
        adjoint[0][0] = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
        adjoint[0][1] = -(mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]);
        adjoint[0][2] = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];
        adjoint[1][0] = -(mat[0][1] * mat[2][2] - mat[0][2] * mat[2][1]);
        adjoint[1][1] = mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0];
        adjoint[1][2] = -(mat[0][0] * mat[2][1] - mat[0][1] * mat[2][0]);
        adjoint[2][0] = mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1];
        adjoint[2][1] = -(mat[0][0] * mat[1][2] - mat[0][2] * mat[1][0]);
        adjoint[2][2] = mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
        float det = Det();
        return adjoint * (1.0f / det);
    }

    float SR::Matrix3x3f::Det() const
    {
        float A = mat[0][0] * mat[1][1] * mat[2][2] + 
                  mat[0][1] * mat[1][2] * mat[2][0] + 
                  mat[0][2] * mat[1][0] * mat[2][1];
        
        float B = mat[0][2] * mat[1][1] * mat[2][0] + 
                  mat[0][1] * mat[1][0] * mat[2][2] + 
                  mat[0][0] * mat[1][2] * mat[2][1];
        return A - B;
    }

}

