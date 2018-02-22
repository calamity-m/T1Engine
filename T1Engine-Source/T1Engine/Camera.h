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

Camera class mostly concerned with simple controls/FPS mechanics

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
	// Set camera transform
	void SetTransform(Transform t);
	// Set camera yaw
	void setYaw(float f);
	// Set camera pitch
	void setPitch(float f);
	// Return camera yaw
	float getYaw();
	// Return camera pitch
	float getPitch();
	// Return camera transform
	Transform getTransform();
	// Return camera world placement
	Transform getWorldPlacement();

	// Base constructor
	Camera();
	// Move camera forward/backward by distance
	void MoveCamera(float distance);
	// Strafe camera left/right by distance
	void StrafeCamera(float distance);
	// Fly camera up/down by distance
	void FlyCamera(float distance);
	// Rotate camera yaw by given angle
	void RotateCameraYaw(float angle);
	// Rotate camera pitch by given angle
	void RotateCameraPitch(float angle);
	// Update the internal camera's direction
	void UpdateCameraDirection();

private:

	float yaw, pitch; // Rotations
	float strafex, strafez; // Strafing angle

};

#endif // !camera_h


