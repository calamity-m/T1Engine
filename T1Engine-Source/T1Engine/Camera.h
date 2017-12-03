#ifndef camera_h
#define camera_h
#pragma once

#include <cmath>
#include "glut.h"
#include "Transform.h"
#include "ResourceManager.h"

/*
Based off of the following (full referencing provided in report)
http://nghiaho.com/?p=1613
https://stackoverflow.com/questions/26133759/creating-an-fps-style-movement-system-with-opengl-and-glut
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
*/
class Camera {

public:
	// Transform vector of camera, rotation is replaced by a direction for glLookAt
	Transform transform;
	Transform prevTransform;

	// Transform vector of camera with world rotation
	Transform worldPlacement;

	// Do we fly?
	bool fly;

	// Initializes camera values
	void Initialize();
	// Updates camera position and rotations, should be called every frame and time the camera position is updated
	void Refresh();
	void SetTransform(Transform t);
	void setYaw(float f);
	void setPitch(float f);
	float getYaw();
	float getPitch();
	Transform getTransform();
	Transform getWorldPlacement();

	Camera();
	void MoveCamera(float distance);
	void StrafeCamera(float distance);
	void FlyCamera(float distance);
	void RotateCameraYaw(float angle);
	void RotateCameraPitch(float angle);
	void UpdateCameraDirection();

private:

	float yaw, pitch; // Rotations
	float strafex, strafez; // Strafing angle

};

#endif // !camera_h


