#include "Quaternion.h"

Quaternion::Quaternion(float angle, const Cartesian3& v)
{
    float angleRadians = angle * M_PI / 180.0;
    float rotAngle = angleRadians / 2;

    float cosAngle = std::cos(rotAngle);
    float sinAngle = std::sin(rotAngle);

    w = cosAngle;
    x = v.x * sinAngle;
    y = v.y * sinAngle;
    z = v.z * sinAngle;
}


Quaternion::Quaternion(float w, float x, float y, float z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Matrix4 Quaternion::ToRotationMatrix()
{
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    Matrix4 ret = Matrix4::Identity();

    ret.coordinates[0][0] = 1.0f - 2.0f * (y2 + z2);
    ret.coordinates[1][0] = 2.0f * (xy - wz);
    ret.coordinates[2][0] = 2.0f * (xz + wy);
    ret.coordinates[3][0] = 0.0f;

    ret.coordinates[0][1] = 2.0f * (xy + wz);
    ret.coordinates[1][1] = 1.0f - 2.0f * (x2 + z2);
    ret.coordinates[2][1] = 2.0f * (yz + wx);
    ret.coordinates[3][1] = 0.0f;

    ret.coordinates[0][2] = 2.0f * (xz + wy);
    ret.coordinates[1][2] = 2.0f * (yz - wx);
    ret.coordinates[2][2] = 1.0f - 2.0f * (x2 + y2);
    ret.coordinates[3][2] = 0.0f;

    ret.coordinates[0][3] = 0.0f;
    ret.coordinates[1][3] = 0.0f;
    ret.coordinates[2][3] = 0.0f;
    ret.coordinates[3][3] = 1.0f;

    return ret;
}

void Quaternion::Normalize()
{
    float magnitude = sqrt(w*w + x*x + y*y + z*z);

    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

Quaternion Quaternion::Conjugate()
{
    return {w, -x, -y, -z};
}

Quaternion Quaternion::operator*(float f)
{
    w = w * f;
    x = x * f;
    y = y * f;
    z = z * f;

    return *this;
}

Quaternion Quaternion::operator-(const Quaternion& other)
{
    return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
}

//https://github.com/IGME-RIT/math-quaternion-slerp/blob/master/QuaternionSlerp/QuaternionSlerp/Quaternion.cpp
Quaternion Quaternion::Slerp(Quaternion& a, Quaternion& b, float t)
{
    // Compute the cosine of the angle between the two vectors.
	// Quaternion r;
	// float t_ = 1 - t;
	// float Wa, Wb;
	// float theta = acos(a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w);
	// float sn = sin(theta);
	// Wa = sin(t_*theta) / sn;
	// Wb = sin(t*theta) / sn;
	// r.x = Wa*a.x + Wb*b.x;
	// r.y = Wa*a.y + Wb*b.y;
	// r.z = Wa*a.z + Wb*b.z;
	// r.w = Wa*a.w + Wb*b.w;
	// r.Normalize();
	// return r;


    Quaternion q = Quaternion();

	// Calculate angle between them
	double cosHalfTheta = (a.w * b.w) + (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

	if (abs(cosHalfTheta) >= 1.0)
	{
		q.w = a.w;
		q.x = a.x;
		q.y = a.y;
		q.z = a.z;

		return q;
	}

	// Calculate temporary values
	double halfTheta = acos(cosHalfTheta);
	double sinHalfTheta = sqrt(1.0f - cosHalfTheta * cosHalfTheta);

	// if theta = 180 degrees then result is not fully defined
	// we could rotate around any axis normal to a or b
	if (fabs(sinHalfTheta) < 0.001)
	{
		q.w = (a.w * 0.5 + b.w * 0.5);
		q.x = (a.x * 0.5 + b.x * 0.5);
		q.y = (a.y * 0.5 + b.y * 0.5);
		q.z = (a.z * 0.5 + b.z * 0.5);

		return q;
	}

	double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
	double ratioB = sin(t * halfTheta) / sinHalfTheta;

	// Calculate Quaternion
	q.w = (a.w * ratioA + b.w * ratioB);
	q.x = (a.x * ratioA + b.x * ratioB);
	q.y = (a.y * ratioA + b.y * ratioB);
	q.z = (a.z * ratioA + b.z * ratioB);

	return q;
}