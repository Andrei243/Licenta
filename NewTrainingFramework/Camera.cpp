#pragma once
#include "stdafx.h"
#include "Camera.h"
#include "SceneManager.h"



void Camera::refacereVector3(Vector3 &a) {
	if (a.x == -0.0f)a.x = 0.0f;
	if (a.y == -0.0f)a.y = 0.0f;
	if (a.z == -0.0f)a.z = 0.0f;
}
void Camera::refacereAxis() {
	refacereVector3(xAxis);
	refacereVector3(yAxis);
	refacereVector3(zAxis);
}

void Camera::updateAxis() {
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
	refacereAxis();
};

Matrix Camera::generareR() {
	Matrix R;
	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0;
	R.m[3][0] = 0; R.m[3][1] = 0; R.m[3][2] = 0; R.m[3][3] = 1;

	return R;
}

void Camera::setDeltaTime(GLfloat _dt) { deltaTime = _dt; }
GLfloat Camera::getDeltaTime() { return deltaTime; }
void Camera::setposition(Vector3 _pos) { position = _pos; }
Vector3 Camera::getposition() { return position; }
void Camera::settarget(Vector3 _target) { target = _target; }
Vector3 Camera::gettarget() { return target; }
void Camera::setup(Vector3 _up) { up = _up; }
Vector3 Camera::getup() { return up; }
void Camera::setMoveSpeed(GLfloat _speed) { moveSpeed = _speed; }
GLfloat Camera::getMoveSpeed() { return moveSpeed; }
void Camera::setRotateSpeed(GLfloat _speed) { rotateSpeed = _speed; }
GLfloat Camera::getRotateSpeed() { return rotateSpeed; }
void Camera::setNear(GLfloat _near) { nears = _near; }
GLfloat Camera::getNear() { return nears; }
void Camera::setFar(GLfloat _far) { fars = _far; }
GLfloat Camera::getFar() { return fars; }
void Camera::setFOV(GLfloat _fov) { fov = _fov; }
GLfloat Camera::getFOV() { return fov; }
void Camera::setxAxis(Vector3 _x) { xAxis = _x; }
Vector3 Camera::getxAxis() { return xAxis; }
void Camera::setyAxis(Vector3 _y) { yAxis = _y; }
Vector3 Camera::getyAxis() { return yAxis; }
void Camera::setzAxis(Vector3 _z) { zAxis = _z; }
Vector3 Camera::getzAxis() { return zAxis; }
void Camera::setviewMatrix(Matrix _view) { viewMatrix = _view; }
Matrix Camera::getviewMatrix() { return viewMatrix; }
void Camera::setworldMatrix(Matrix _world) { worldMatrix = _world; }
Matrix Camera::getworldMatrix() { return worldMatrix; }

void Camera::MoveOz(GLfloat directie) {
	Vector3 forward = zAxis * directie;
	Vector3 vectorDeplasare = forward * moveSpeed*deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateAxis();
	updateWorldView();
}

void Camera::MoveOy(GLfloat directie) {
	Vector3 upward = yAxis * directie;
	Vector3 vectorDeplasare = upward * moveSpeed*deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateAxis();
	updateWorldView();
}

void Camera::MoveOx(GLfloat directie) {
	Vector3 right = xAxis * directie;
	Vector3 vectorDeplasare = right * moveSpeed*deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateAxis();
	updateWorldView();
}

void Camera::rotateOy(GLfloat directie) {
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Matrix rotatie;
	rotatie.SetRotationY(directie*deltaTime*rotateSpeed);
	Vector4 rotatedTarget = localTarget * rotatie;
	localTarget = rotatedTarget * worldMatrix;
	target.x = localTarget.x;
	target.y = localTarget.y;
	target.z = localTarget.z;
	updateAxis();
	updateWorldView();
}

void Camera::rotateOz(GLfloat directie) {
	Vector4 localup(0.0f, 1.0f, 0.0f, 0.0f);
	Matrix rotatie;
	rotatie.SetRotationZ(directie*deltaTime*rotateSpeed);
	Vector4 rotatedLocalUp = localup * rotatie;
	Vector4 auxup = rotatedLocalUp * worldMatrix;
	up = Vector3(auxup.x, auxup.y, auxup.z);
	up = up.Normalize();
	updateAxis();
	updateWorldView();
}

void Camera::rotateOx(GLfloat directie) {
	Vector4 localup(0.0f, 1.0f, 0.0f, 0.0f);
	Matrix rotatie;
	rotatie.SetRotationX(directie*deltaTime*rotateSpeed);
	Vector4 rotatedLocalUp = localup * rotatie;
	Vector4 auxup = rotatedLocalUp * worldMatrix;
	up = Vector3(auxup.x, auxup.y, auxup.z);
	up = up.Normalize();
	Vector4 localTarget(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * rotatie;
	Vector4 auxtarget = rotatedTarget * worldMatrix;
	target = Vector3(auxtarget.x, auxtarget.y, auxtarget.z);
	updateAxis();
	updateWorldView();
}

void Camera::updateWorldView() {
	Matrix R = generareR();
	Matrix translatie;
	translatie.SetTranslation(position.x, position.y, position.z, SceneManager::getsceneManager()->getTypeOfSpace());
	worldMatrix = R * translatie;
	R = R.Transpose();
	translatie.SetTranslation(-position.x, -position.y, -position.z, SceneManager::getsceneManager()->getTypeOfSpace());
	viewMatrix = translatie * R;
}

Matrix Camera::getmat() {

	Matrix aux = viewMatrix * perspectiveMatrix;
	return aux;


}
