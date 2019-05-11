#pragma once

#include "../Utilities/utilities.h"
#include "Globals.h"


const GLfloat dt = 0.5f;
const GLfloat rs = 0.2f;
const GLfloat ms = 50.0f;
const GLfloat _fov = 45;
const GLfloat PI = 3.14;

class Camera {
private:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat nears;
	GLfloat fars;
	GLfloat fov;
	GLfloat deltaTime;
	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;
	Matrix viewMatrix;
	Matrix worldMatrix;
	Matrix perspectiveMatrix;

	void updateAxis();
	Matrix generareR();
	void refacereAxis();
	

public:
	void refacereVector3(Vector3 &);

	Camera() {};

	Camera(Vector3 _position, Vector3 _target) :position(_position), target(_target),nears(0.1),fars(1000),fov(_fov) {
		perspectiveMatrix.SetPerspective(fov, ((GLfloat)Globals::screenWidth) / Globals::screenHeight, nears, fars);
		deltaTime = dt;
		moveSpeed = ms;
		rotateSpeed = rs;

		up = Vector3(0.0f, 1.0f, 0.0f);
		updateAxis();
		updateWorldView();

	};

	Camera(Vector3 _position, Vector3 _target, Vector3 _up) :position(_position), target(_target), up(_up),nears(0.1),fars(1000),fov(_fov) {
		perspectiveMatrix.SetPerspective(fov, ((GLfloat)Globals::screenWidth) / Globals::screenHeight, nears, fars);
		deltaTime = dt;
		moveSpeed = ms;
		rotateSpeed = rs;

		updateAxis();
		updateWorldView();

	};

	Camera(Vector3 _position, Vector3 _target, Vector3 _up, GLfloat _movespeed, GLfloat _rotatespeed, GLfloat _fov, GLfloat _near, GLfloat _far) {
		_fov = (PI * _fov) / 180;
		perspectiveMatrix.SetPerspective(_fov, ((GLfloat)Globals::screenWidth) / Globals::screenHeight, _near, _far);
		nears = _near;
		fars = _far;
		fov = _fov;
		position = _position;
		target = _target;
		up = _up;
		moveSpeed = _movespeed;
		rotateSpeed = _rotatespeed;
		updateAxis();
		updateWorldView();
	}

	void setDeltaTime(GLfloat _dt);
	GLfloat getDeltaTime();
	void setposition(Vector3 _pos);
	Vector3 getposition();
	void settarget(Vector3 _target);
	Vector3 gettarget();
	void setup(Vector3 _up);
	Vector3 getup();
	void setMoveSpeed(GLfloat _speed);
	GLfloat getMoveSpeed();
	void setRotateSpeed(GLfloat _speed);
	GLfloat getRotateSpeed();
	void setNear(GLfloat _near);
	GLfloat getNear();
	void setFar(GLfloat _far);
	GLfloat getFar();
	void setFOV(GLfloat _fov);
	GLfloat getFOV();
	void setxAxis(Vector3 _x);
	Vector3 getxAxis();
	void setyAxis(Vector3 _y);
	Vector3 getyAxis();
	void setzAxis(Vector3 _z);
	Vector3 getzAxis();
	void setviewMatrix(Matrix _view);
	Matrix getviewMatrix();
	void setworldMatrix(Matrix _world);
	Matrix getworldMatrix();

	void MoveOz(GLfloat directie);

	void MoveOy(GLfloat directie);

	void MoveOx(GLfloat directie);

	void rotateOy(GLfloat directie);

	void rotateOz(GLfloat directie);

	void rotateOx(GLfloat directie);

	void updateWorldView();

	Matrix getmat();
};


