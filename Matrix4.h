
// include guard
#ifndef MATRIX4_H
#define MATRIX4_H

#include <iostream>
#include "Cartesian3.h"
#include "Homogeneous4.h"

#ifndef M_PI
#define M_PI 3.141592
#endif
#define DEG2RAD(x) (M_PI*(float)(x)/180.0)

// forward declaration
class Matrix4;

// this allows us to get a matrix in the 
// column-major form preferred by OpenGL
class columnMajorMatrix
    { // class columnMajorMatrix
    public:
    float coordinates[16];
    columnMajorMatrix()
    {
        for(int row = 0; row < 4; row++)
        {
            for(int col = 0; col < 4; col++)
            {
                coordinates[col * 4 + row] = 0.0f;
            }
        }
    }
    Homogeneous4 operator*(const Homogeneous4& v) const;
    Cartesian3 operator*(const Cartesian3& other) const
    {
        Cartesian3 result;
        result.x = coordinates[0] * other.x + coordinates[4] * other.y + coordinates[8] * other.z + coordinates[12];
        result.y = coordinates[1] * other.x + coordinates[5] * other.y + coordinates[9] * other.z + coordinates[13];
        result.z = coordinates[2] * other.x + coordinates[6] * other.y + coordinates[10] * other.z + coordinates[14];
        return result;
    }
    columnMajorMatrix operator*(const columnMajorMatrix& other) const
    {
        columnMajorMatrix result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.coordinates[i + j * 4] = 0;
                for (int k = 0; k < 4; ++k) {
                    result.coordinates[i + j * 4] += this->coordinates[i + k * 4] * other.coordinates[k + j * 4];
                }
            }
        }
        return result;
    }

 
    // Translation matrix to move objects around in the world
    static columnMajorMatrix Translate(const Cartesian3& vector)
    {
        columnMajorMatrix ret;

        ret.coordinates[0] = 1.0f;
        ret.coordinates[1] = 0.0f;
        ret.coordinates[2] = 0.0f;
        ret.coordinates[3] = 0.0f;

        ret.coordinates[4] = 0.0f;
        ret.coordinates[5] = 1.0f;
        ret.coordinates[6] = 0.0f;
        ret.coordinates[7] = 0.0f;

        ret.coordinates[8] = 0.0f;
        ret.coordinates[9] = 0.0f;
        ret.coordinates[10] = 1.0f;
        ret.coordinates[11] = 0.0f;

        ret.coordinates[12] = vector.x;
        ret.coordinates[13] = vector.y;
        ret.coordinates[14] = vector.z;
        ret.coordinates[15] = 1.0f;

        return ret;
    }
    // Matrix to scale so we can scale objects
    static columnMajorMatrix Scale(const Cartesian3& scale)
    {
        columnMajorMatrix ret;

        ret.coordinates[0] = scale.x;
        ret.coordinates[1] = 0.0f;
        ret.coordinates[2] = 0.0f;
        ret.coordinates[3] = 0.0f;

        ret.coordinates[4] = 0.0f;
        ret.coordinates[5] = scale.y;
        ret.coordinates[6] = 0.0f;
        ret.coordinates[7] = 0.0f;

        ret.coordinates[8] = 0.0f;
        ret.coordinates[9] = 0.0f;
        ret.coordinates[10] = scale.z;
        ret.coordinates[11] = 0.0f;

        ret.coordinates[12] = 0.0f;
        ret.coordinates[13] = 0.0f;
        ret.coordinates[14] = 0.0f;
        ret.coordinates[15] = 1.0f;

        return ret;
    }
    // Rotation around X axis
    static columnMajorMatrix RotateX(float degrees)
    {
        float toRadians = DEG2RAD(degrees);

        columnMajorMatrix rotationMatrix;
        rotationMatrix.coordinates[0] = 1.0f;
        rotationMatrix.coordinates[1] = 0.0f;
        rotationMatrix.coordinates[2] = 0.0f;
        rotationMatrix.coordinates[3] = 0.0f;

        rotationMatrix.coordinates[4] = 0.0f;
        rotationMatrix.coordinates[5] = std::cos(toRadians);
        rotationMatrix.coordinates[6] = std::sin(toRadians);
        rotationMatrix.coordinates[7] = 0.0f;

        rotationMatrix.coordinates[8] = 0.0f;
        rotationMatrix.coordinates[9] = -std::sin(toRadians);
        rotationMatrix.coordinates[10] = std::cos(toRadians);
        rotationMatrix.coordinates[11] = 0.0f;

        rotationMatrix.coordinates[12] = 0.0f;
        rotationMatrix.coordinates[13] = 0.0f;
        rotationMatrix.coordinates[14] = 0.0f;
        rotationMatrix.coordinates[15] = 1.0f;

        return rotationMatrix;
    }
    // Rotation around Y axis
    static columnMajorMatrix RotateY(float degrees)
    {
        float toRadians = DEG2RAD(degrees);

        columnMajorMatrix rotationMatrix;
        rotationMatrix.coordinates[0] = std::cos(toRadians);
        rotationMatrix.coordinates[1] = 0.0f;
        rotationMatrix.coordinates[2] = -std::sin(toRadians);
        rotationMatrix.coordinates[3] = 0.0f;

        rotationMatrix.coordinates[4] = 0.0f;
        rotationMatrix.coordinates[5] = 1.0f;
        rotationMatrix.coordinates[6] = 0.0f;
        rotationMatrix.coordinates[7] = 0.0f;

        rotationMatrix.coordinates[8] = std::sin(toRadians);
        rotationMatrix.coordinates[9] = 0.0f;
        rotationMatrix.coordinates[10] = -std::cos(toRadians);
        rotationMatrix.coordinates[11] = 0.0f;

        rotationMatrix.coordinates[12] = 0.0f;
        rotationMatrix.coordinates[13] = 0.0f;
        rotationMatrix.coordinates[14] = 0.0f;
        rotationMatrix.coordinates[15] = 1.0f;

        return rotationMatrix;
    }
    // Rotation around Z axis
    static columnMajorMatrix RotateZ(float degrees)
    {
        float toRadians = DEG2RAD(degrees);

        columnMajorMatrix rotationMatrix;
        rotationMatrix.coordinates[0] = std::cos(toRadians);
        rotationMatrix.coordinates[1] = std::sin(toRadians);
        rotationMatrix.coordinates[2] = 0.0f;
        rotationMatrix.coordinates[3] = 0.0f;

        rotationMatrix.coordinates[4] = -std::sin(toRadians);
        rotationMatrix.coordinates[5] = std::cos(toRadians);
        rotationMatrix.coordinates[6] = 0.0f;
        rotationMatrix.coordinates[7] = 0.0f;

        rotationMatrix.coordinates[8] = 0.0f;
        rotationMatrix.coordinates[9] = 0.0f;
        rotationMatrix.coordinates[10] = 1.0f;
        rotationMatrix.coordinates[11] = 0.0f;

        rotationMatrix.coordinates[12] = 0.0f;
        rotationMatrix.coordinates[13] = 0.0f;
        rotationMatrix.coordinates[14] = 0.0f;
        rotationMatrix.coordinates[15] = 1.0f;

        return rotationMatrix;
    }
    }; // class columnMajorMatrix
    
// the class itself, stored in row-major form
class Matrix4
    { // Matrix4
    public:
    // the coordinates
    float coordinates[4][4];

    // constructor - default to the zero matrix
    Matrix4();
    
    // equality operator
    bool operator ==(const Matrix4 &other) const;

    // indexing - retrieves the beginning of a line
    // array indexing will then retrieve an element
    float * operator [](const int rowIndex);
    
    // similar routine for const pointers
    const float * operator [](const int rowIndex) const;

    // scalar operations
    // multiplication operator (no division operator)
    Matrix4 operator *(float factor) const;

    // vector operations on homogeneous coordinates
    // multiplication is the only operator we use
    Homogeneous4 operator *(const Homogeneous4 &vector) const;

    // and on Cartesian coordinates
    Cartesian3 operator *(const Cartesian3 &vector) const;

    // matrix operations
    // addition operator
    Matrix4 operator +(const Matrix4 &other) const;
    // subtraction operator
    Matrix4 operator -(const Matrix4 &other) const;
    // multiplication operator
    Matrix4 operator *(const Matrix4 &other) const; 
    
    // matrix transpose
    Matrix4 transpose() const;
    
    // returns a column-major array of 16 values
    // for use with OpenGL
    columnMajorMatrix columnMajor() const;

	// routine that returns a row vector as a Homogeneous4
	Homogeneous4 row(int rowNum);
	
	// and similar for a column
	Homogeneous4 column(int colNum);

    // methods that return particular matrices
    static Matrix4 Zero();

    // the identity matrix
    static Matrix4 Identity();
    static Matrix4 Translate(const Cartesian3 &vector);

    // rotations around main axes
	static Matrix4 RotateX(float degrees);
    static Matrix4 RotateY(float degrees);
    static Matrix4 RotateZ(float degrees);

    static Matrix4 Scale(float x, float y, float z)
    {
        Matrix4 returnMatrix = Identity();

        returnMatrix[0][0] = x;
        returnMatrix[1][1] = y;
        returnMatrix[2][2] = z;

        return returnMatrix;
    }

    static Matrix4 RotateDirection(const Cartesian3& direction, const Cartesian3& up = Cartesian3(0.f, 1.f, 0.f))
   {
       Cartesian3 xaxis = up.cross(direction).unit();
       Cartesian3 yaxis = direction.cross(xaxis).unit();

       Matrix4 out;
       out.coordinates[0][0] = xaxis.x;
       out.coordinates[0][1] = yaxis.x;
       out.coordinates[0][2] = direction.x;
       out.coordinates[0][3] = 0.f;

       out.coordinates[1][0] = xaxis.y;
       out.coordinates[1][1] = yaxis.y;
       out.coordinates[1][2] = direction.y;
       out.coordinates[1][3] = 0.f;

       out.coordinates[2][0] = xaxis.z;
       out.coordinates[2][1] = yaxis.z;
       out.coordinates[2][2] = direction.z;
       out.coordinates[2][3] = 0.f;

       out.coordinates[3][0] = 0.f;
       out.coordinates[3][1] = 0.f;
       out.coordinates[3][2] = 0.f;
       out.coordinates[3][3] = 1.f;

       return out;
   }

   static Matrix4 ViewMatrix(const Cartesian3& camerpos, const Cartesian3& target, const Cartesian3& up)
   {
        Cartesian3 forward, Up, right;

        forward = camerpos - target;
        forward.unit();

        right = up.cross(forward);
        right.unit();

        Up = forward.cross(right);
        Up.unit();

        auto rotationMatrix = Matrix4::Identity();
        // col, row
        rotationMatrix.coordinates[0][0] = right.x;
        rotationMatrix.coordinates[1][0] = Up.x;
        rotationMatrix.coordinates[2][0] = forward.x;
        rotationMatrix.coordinates[3][0] = 0.0f;

        rotationMatrix.coordinates[0][1] = right.y;
        rotationMatrix.coordinates[1][1] = Up.y;
        rotationMatrix.coordinates[2][1] = forward.y;
        rotationMatrix.coordinates[3][1] = 0.0f;

        rotationMatrix.coordinates[0][2] = right.z;
        rotationMatrix.coordinates[1][2] = Up.z;
        rotationMatrix.coordinates[2][2] = forward.z;
        rotationMatrix.coordinates[3][2] = 0.0f;

        rotationMatrix.coordinates[0][3] = 0.0f;
        rotationMatrix.coordinates[1][3] = 0.0f;
        rotationMatrix.coordinates[2][3] = 0.0f;
        rotationMatrix.coordinates[3][3] = 1.0f;

        Matrix4 translation = Matrix4::Identity();

        translation.coordinates[0][0] = 1.0f;
        translation.coordinates[1][0] = 0.0f;
        translation.coordinates[2][0] = 0.0f;
        translation.coordinates[3][0] = 0.0f;

        translation.coordinates[0][1] = 0.0f;
        translation.coordinates[1][1] = 1.0f;
        translation.coordinates[2][1] = 0.0f;
        translation.coordinates[3][1] = 0.0f;

        translation.coordinates[0][2] = 0.0f;
        translation.coordinates[1][2] = 0.0f;
        translation.coordinates[2][2] = 1.0f;
        translation.coordinates[3][2] = 0.0f;

        translation.coordinates[0][3] = -camerpos.x;
        translation.coordinates[1][3] = -camerpos.y;
        translation.coordinates[2][3] = -camerpos.z;
        translation.coordinates[3][3] = 1.0f;
        
        return rotationMatrix * translation;
   }

    static Matrix4 GetRotation(const Cartesian3& vector1, const Cartesian3& vector2);

    static Matrix4 Look(const Cartesian3& position, const Cartesian3& target, const Cartesian3& up)
    {	
        Cartesian3 forward, Up, right;
        Cartesian3 x, y, z;

        forward = target - position;
        forward.unit();

        right = up.cross(forward);
        right.unit();

        Up = forward.cross(right);
        Up.unit();

        z = forward;
        y = Up;
        x = right;

        z = z.unit();
        y = y.unit();
        x = x.unit();

        // Set up rotation as a row major matrix
        Matrix4 rotation; // col, row 
        // x
        rotation.coordinates[0][0] = x.x;
        rotation.coordinates[1][0] = y.x;
        rotation.coordinates[2][0] = z.x;
        rotation.coordinates[3][0] = 0.0f;

        // y
        rotation.coordinates[0][1] = x.y;
        rotation.coordinates[1][1] = y.y;
        rotation.coordinates[2][1] = z.y;
        rotation.coordinates[3][1] = 0.0f;

        // z
        rotation.coordinates[0][2] = x.z;
        rotation.coordinates[1][2] = y.z;
        rotation.coordinates[2][2] = z.z;
        rotation.coordinates[3][2] = 0.0f;

        rotation.coordinates[0][3] = 0.0f;
        rotation.coordinates[1][3] = 0.0f;
        rotation.coordinates[2][3] = 0.0f;
        rotation.coordinates[3][3] = 1.0f;


        Matrix4 translation;
        translation.coordinates[0][0] = 1.0f;
        translation.coordinates[1][0] = 0.0f;
        translation.coordinates[2][0] = 0.0f;
        translation.coordinates[3][0] = 0.0f;

        translation.coordinates[0][1] = 0.0f;
        translation.coordinates[1][1] = 1.0f;
        translation.coordinates[2][1] = 0.0f;
        translation.coordinates[3][1] = 0.0f;

        translation.coordinates[0][2] = 0.0f;
        translation.coordinates[1][2] = 0.0f;
        translation.coordinates[2][2] = 1.0f;
        translation.coordinates[3][2] = 0.0f;

        translation.coordinates[0][3] = 0.0f;
        translation.coordinates[1][3] = 0.0f;
        translation.coordinates[2][3] = 0.0f;
        translation.coordinates[3][3] = 1.0f;
        
        return rotation * translation;
    }
    }; // Matrix4

// scalar operations
// additional scalar multiplication operator
Matrix4 operator *(float factor, const Matrix4 &matrix);

// stream input
std::istream & operator >> (std::istream &inStream, Matrix4 &value);

// stream output
std::ostream & operator << (std::ostream &outStream, const Matrix4 &value);
        
#endif

