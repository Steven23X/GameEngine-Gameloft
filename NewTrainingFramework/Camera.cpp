#include "stdafx.h"
#include "Camera.h"

// Constructors

Camera::Camera()
{
	position = Vector3(0.0f, 0.0f, 1.0f);
	target = Vector3(0.0f, 0.0f, -1.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);

	deltaTime = 1.0f;
	moveSpeed = 300.5f;
	rotateSpeed = 1.5f;

	xAxis = Vector3(1.0f, 0.0f, 0.0f);
	yAxis = Vector3(0.0f, 1.0f, 0.0f);
	zAxis = Vector3(0.0f, 0.0f, -1.0f);

	nearCamera = 0.1f;
	farCamera = 1000.0f;
	fovCamera = 45.0f;
}

Camera::Camera(Vector3 position, Vector3 target, Vector3 up, const GLfloat movespeed, const GLfloat rotatespeed, const GLfloat nearCamera,
	const GLfloat farCamera, const GLfloat fovCamera)
{
	this->position = position;
	this->target = target;
	this->up = up;

	deltaTime = 1.0f;
	moveSpeed = movespeed;
	rotateSpeed = rotatespeed;

	xAxis = Vector3(1.0f, 0.0f, 0.0f);
	yAxis = Vector3(0.0f, 1.0f, 0.0f);
	zAxis = Vector3(0.0f, 0.0f, -1.0f);

	this->nearCamera = nearCamera;
	this->farCamera = farCamera;
	this->fovCamera = fovCamera;
}

// Methods

void Camera::MoveOy(const float direction)
{
	position += yAxis * direction * moveSpeed * deltaTime;
	target += yAxis * direction * moveSpeed * deltaTime;
}

void Camera::MoveOx(const float direction)
{
	position += xAxis * direction * moveSpeed * deltaTime;
	target += xAxis * direction * moveSpeed * deltaTime;
}

void Camera::MoveOz(const float direction)
{
	position += zAxis * direction * moveSpeed * deltaTime;
	target += zAxis * direction * moveSpeed * deltaTime;
}

void Camera::RotateOy(const float direction)
{
	Matrix mRotateOy;

	mRotateOy.SetRotationY(rotateSpeed * deltaTime * direction);

	Vector4 localTarget(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOy;

	const Vector4 targetV4 = rotatedTarget * worldMatrix;

	target.x = targetV4.x;
	target.y = targetV4.y;
	target.z = targetV4.z;
}

void Camera::RotateOx(const float direction)
{
	Vector4 localUp(0.0f, 1.0f, 0.0f, 0.0f);
	Matrix mRotateOx;

	mRotateOx.SetRotationX(rotateSpeed * deltaTime * direction);

	Vector4 rotatedLocalUp = localUp * mRotateOx;

	const Vector4 upV4 = rotatedLocalUp * worldMatrix;

	up.x = upV4.x;
	up.y = upV4.y;
	up.z = upV4.z;

	up.Normalize();


	Vector4 localTarget(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOx;

	const Vector4 targetV4 = rotatedTarget * worldMatrix;

	target.x = targetV4.x;
	target.y = targetV4.y;
	target.z = targetV4.z;
}

void Camera::RotateOz(const float direction)
{
	Vector4 localUp(0.0f, 1.0f, 0.0f, 0.0f);
	Matrix mRotateOz;

	mRotateOz.SetRotationZ(rotateSpeed * deltaTime * direction);

	Vector4 rotatedLocalUp = localUp * mRotateOz;

	const Vector4 upV4 = rotatedLocalUp * worldMatrix;

	up.x = upV4.x;
	up.y = upV4.y;
	up.z = upV4.z;

	up.Normalize();

	Vector4 localTarget(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOz;

	const Vector4 targetV4 = rotatedTarget * worldMatrix;

	target.x = targetV4.x;
	target.y = targetV4.y;
	target.z = targetV4.z;
}

void Camera::UpdateWorldView()
{
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();


	Matrix translationMatrix;
	translationMatrix.SetTranslation(position.x, position.y, position.z);

	auto rMatrix = Matrix(Vector4(xAxis.x, xAxis.y, xAxis.z, 0.0f),
		Vector4(yAxis.x, yAxis.y, yAxis.z, 0.0f),
		Vector4(zAxis.x, zAxis.y, zAxis.z, 0.0f),
		Vector4(0.0f, 0.0f, 0.0f, 1.0f));

	// worldMatrix

	worldMatrix = rMatrix * translationMatrix;

	// viewMatrix
	viewMatrix = translationMatrix.SetTranslation(-position.x, -position.y, -position.z) * rMatrix.Transpose();
}


// Getters

Vector3 Camera::GetPosition()
{
	return position;
}

Vector3 Camera::GetTarget()
{
	return target;
}

Vector3 Camera::GetUp()
{
	return up;
}

GLfloat Camera::GetMoveSpeed() const
{
	return moveSpeed;
}

GLfloat Camera::GetDeltaTime() const
{
	return deltaTime;
}

Vector3 Camera::GetxAxis()
{
	return xAxis;
}

Vector3 Camera::GetyAxis()
{
	return yAxis;
}

Vector3 Camera::GetzAxis()
{
	return zAxis;
}

GLfloat Camera::GetNear() const
{
	return nearCamera;
}

GLfloat Camera::GetFar() const
{
	return farCamera;
}

GLfloat Camera::GetFov() const
{
	return fovCamera;
}

Matrix Camera::GetViewMatrix()
{
	return viewMatrix;
}

Matrix Camera::GetWorldMatrix()
{
	return worldMatrix;
}

Matrix Camera::GetProjectionMatrix()
{
	return projectionMatrix.SetPerspective(fovCamera, 800.0f / 600.0f, nearCamera, farCamera);
}


// Setters
void Camera::SetPosition(Vector3 position)
{
	this->position = position;
}

void Camera::SetTarget(Vector3 target)
{
	this->target = target;
}

void Camera::SetUp(Vector3 up)
{
	this->up = up;
}

void Camera::SetMoveSpeed(const GLfloat moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void Camera::SetDeltaTime(const GLfloat deltaTime)
{
	this->deltaTime = deltaTime;
}

void Camera::SetNear(const GLfloat nearCamera)
{
	this->nearCamera = nearCamera;
}

void Camera::SetFar(const GLfloat farCamera)
{
	this->farCamera = farCamera;
}

void Camera::SetFov(const GLfloat fovCamera)
{
	this->fovCamera = fovCamera;
}
