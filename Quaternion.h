#include <iostream>
#include "Matrix4.h"
// Quaternion class to allow us to rotate the plane movement using quaternions
class Quaternion
{
public:
    float w, x, y, z;
    Quaternion() = default;
    Quaternion(float angle, const Cartesian3& v); // Rotate by an angle around some axis
    Quaternion(float w, float x, float y, float z); // Set quaternion values
    Matrix4 ToRotationMatrix(); // Convert the quaternion to a rotation matrix
    void Normalize(); // Normalize the quaternion 
    Quaternion Conjugate(); // Get the conjugate of the quaternion
    Quaternion Slerp(Quaternion& q1, Quaternion& q2, float t);
    Quaternion operator*(float f);
    Quaternion operator-(const Quaternion& other);

};

// Multiply Quaternion by another quaternion 
inline Quaternion operator*(const Quaternion& left, const Quaternion& right)
{
    float w = (left.w * right.w) - (left.x * right.x) - (left.y * right.y) - (left.z * right.z);
    float x = (left.x * right.w) + (left.w * right.x) + (left.y * right.z) - (left.z * right.y);
    float y = (left.y * right.w) + (left.w * right.y) + (left.z * right.x) - (left.x * right.z);
    float z = (left.z * right.w) + (left.w * right.z) + (left.x * right.y) - (left.y * right.x);

    return {w, x, y, z};
}

// Multiply quaternion with a vector
inline Quaternion operator*(const Quaternion& rot, const Cartesian3& v)
{
    float w = - (rot.x * v.x) - (rot.y * v.y) - (rot.z * v.z);
    float x =   (rot.w * v.x) + (rot.y * v.z) - (rot.z * v.y);
    float y =   (rot.w * v.y) + (rot.z * v.x) - (rot.x * v.z);
    float z =   (rot.w * v.z) + (rot.x * v.y) - (rot.y * v.x);

    return {w, x, y, z};
}


