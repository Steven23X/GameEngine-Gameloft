#pragma once
#include "../Utilities/utilities.h"

class Camera {

	// Camera attributes
	Vector3 position;
	Vector3 target;
	Vector3 up;

	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat deltaTime;

	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;

	GLfloat nearCamera;
	GLfloat farCamera;
	GLfloat fovCamera;

	Matrix viewMatrix;
	Matrix worldMatrix;
	Matrix projectionMatrix;

public:
	// Constructors
	Camera();
	Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat movespeed, GLfloat rotatespeed, GLfloat nearCamera, GLfloat farCamera, GLfloat fovCamera);

	// Methods
	void MoveOx(const float direction);
	void MoveOy(const float direction);
	void MoveOz(const float direction);

	void RotateOx(const float direction);
	void RotateOy(const float direction);
	void RotateOz(const float direction);

	void UpdateWorldView();

	// Getters
	Vector3 GetPosition();
	Vector3 GetTarget();
	Vector3 GetUp();

	GLfloat GetMoveSpeed() const;
	GLfloat GetDeltaTime() const;

	Vector3 GetxAxis();
	Vector3 GetyAxis();
	Vector3 GetzAxis();

	GLfloat GetNear() const;
	GLfloat GetFar() const;
	GLfloat GetFov() const;

	Matrix GetViewMatrix();
	Matrix GetWorldMatrix();
	Matrix GetProjectionMatrix();

	// Setters
	void SetPosition(Vector3 position);
	void SetTarget(Vector3 target);
	void SetUp(Vector3 up);

	void SetMoveSpeed(GLfloat moveSpeed);
	void SetDeltaTime(GLfloat deltaTime);

	void SetNear(GLfloat nearCamera);
	void SetFar(GLfloat farCamera);
	void SetFov(GLfloat fovCamera);
};