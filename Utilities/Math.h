#pragma once

#include "esUtil.h"

//Vector2

class Vector2
{
public:
	//Constructors
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(GLfloat _x, GLfloat _y) : x(_x), y(_y) {}
	Vector2(GLfloat* pArg) : x(pArg[0]), y(pArg[1]) {}
	Vector2(Vector2& vector) : x(vector.x), y(vector.y) {}
	Vector2(const Vector2& vector) : x(vector.x), y(vector.y) {}

	//Vector's operations
	GLfloat Length();
	Vector2& Normalize();
	Vector2 operator + (Vector2& vector);
	Vector2& operator += (Vector2& vector);
	Vector2 operator - ();
	Vector2 operator - (Vector2& vector);
	Vector2& operator -= (Vector2& vector);
	Vector2 operator * (GLfloat k);
	Vector2& operator *= (GLfloat k);
	Vector2 operator / (GLfloat k);
	Vector2& operator /= (GLfloat k);
	Vector2& operator = (Vector2& vector);
	Vector2 Modulate(Vector2& vector);
	GLfloat Dot(Vector2& vector);

	//access to elements
	GLfloat operator [] (unsigned int idx);

	//data members
	GLfloat x;
	GLfloat y;
};

//Vector3

class Vector3
{
public:
	//Constructors
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z) {}
	Vector3(GLfloat* pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]) {}
	Vector3(Vector3& vector) : x(vector.x), y(vector.y), z(vector.z) {}
	Vector3(const Vector3& vector) : x(vector.x), y(vector.y), z(vector.z) {}

	//Vector's operations
	GLfloat Length();
	Vector3& Normalize();
	Vector3 operator + (Vector3& vector);
	Vector3& operator += (Vector3& vector);
	Vector3 operator - ();
	Vector3 operator - (Vector3& vector);
	Vector3& operator -= (Vector3& vector);
	Vector3 operator * (GLfloat k);
	Vector3& operator *= (GLfloat k);
	Vector3 operator / (GLfloat k);
	Vector3& operator /= (GLfloat k);
	Vector3& operator = (Vector3& vector);
	Vector3 Modulate(Vector3& vector);
	GLfloat Dot(Vector3& vector);
	Vector3 Cross(Vector3& vector);

	//access to elements
	GLfloat operator [] (unsigned int idx);

	// data members
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

//Vector4

class Matrix;

class Vector4
{
public:
	//Constructors
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z), w(1.0f) {}
	Vector4(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4(GLfloat* pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]), w(pArg[3]) {}
	Vector4(Vector3& vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0f) {}
	Vector4(Vector3& vector, GLfloat _w) : x(vector.x), y(vector.y), z(vector.z), w(_w) {}
	Vector4(Vector4& vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

	//Vector's operations
	GLfloat Length();
	Vector4& Normalize();
	Vector4 operator + (Vector4& vector);
	Vector4& operator += (Vector4& vector);
	Vector4 operator - ();
	Vector4 operator - (Vector4& vector);
	Vector4& operator -= (Vector4& vector);
	Vector4 operator * (GLfloat k);
	Vector4& operator *= (GLfloat k);
	Vector4 operator / (GLfloat k);
	Vector4& operator /= (GLfloat k);
	Vector4& operator = (Vector4& vector);
	Vector4 Modulate(Vector4& vector);
	GLfloat Dot(Vector4& vector);

	explicit operator const Vector3() const;

	//matrix multiplication
	Vector4 operator * (Matrix& m);

	//access to elements
	GLfloat operator [] (unsigned int idx);

	//data members
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};

//Matrix 4 X 4


class Matrix
{
public:
	//constructors
	Matrix() : m() {}
	Matrix(GLfloat val);
	Matrix(Matrix& mat);
	Matrix(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);

	// Matrix operations
	Matrix& SetZero();
	Matrix& SetIdentity();

	Matrix& SetRotationX(GLfloat angle);
	Matrix& SetRotationY(GLfloat angle);
	Matrix& SetRotationZ(GLfloat angle);
	Matrix& SetRotationAngleAxis(float angle, float x, float y, float z);

	Matrix& SetScale(GLfloat scale);
	Matrix& SetScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
	Matrix& SetScale(GLfloat* pScale);
	Matrix& SetScale(Vector3& scaleVec);

	Matrix& SetTranslation(GLfloat x, GLfloat y, GLfloat z);
	Matrix& SetTranslation(GLfloat* pTrans);
	Matrix& SetTranslation(Vector3& vec);

	Matrix& SetPerspective(GLfloat fovY, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane);

	Matrix Transpose();

	Matrix operator + (Matrix& mat);
	Matrix& operator += (Matrix& mat);
	Matrix operator - (Matrix& mat);
	Matrix& operator -= (Matrix& mat);

	Matrix operator * (Matrix& mat);
	Matrix operator * (GLfloat k);
	Matrix& operator *= (GLfloat k);

	Vector4 operator * (Vector4& vec);

	Matrix& operator = (Matrix& mat);

	//data members
	GLfloat m[4][4];
};