

#ifndef __SCENE_MODEL_H
#define __SCENE_MODEL_H

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "Terrain.h"
#include "BVHData.h"
#include "Matrix4.h"
#include "Camera.h"
#include <memory.h>
#include <chrono>

enum CharacterState
{
	Running,
	TurnLeft,
	TurnRight,
	Idle
};

class SceneModel										
	{ // class SceneModel
	public:	
	// a terrain model 
	Terrain groundModel;

	// animation cycles (which implicitly have geometric data for a character)
	BVHData restPose;
	BVHData runCycle;
	BVHData veerLeftCycle;
	BVHData veerRightCycle;

	BVHData playerController;

	// location & orientation of character
	Cartesian3 characterLocation;
	Matrix4 characterRotation;

	// a matrix that specifies the mapping from world coordinates to those assumed
	// by OpenGL
	Matrix4 world2OpenGLMatrix;

	// matrix for user camera
	Matrix4 viewMatrix;
	Matrix4 CameraTranslateMatrix;
	Matrix4 CameraRotationMatrix;
	
	// the frame number for use in animating
	unsigned long frameNumber;
	
	// constructor
	SceneModel();

	// routine that updates the scene for the next frame
	void Update();

	// routine to tell the scene to render itself
	void Render();

	// camera control events: WASD for motion
	void EventCameraForward();
	void EventCameraLeft();
	void EventCameraRight();
	void EventCameraBackward();
	// camera control events: RF for vertical motion
	void EventCameraUp();
	void EventCameraDown();
	// camera rotation events: QE for left and right
	void EventCameraTurnLeft();
	void EventCameraTurnRight();
	
	// character motion events: arrow keys for forward, backward, veer left & right
	void EventCharacterTurnLeft();
	void EventCharacterTurnRight();
	void EventCharacterForward();
	void EventCharacterBackward();

	// reset character to original position: p
	void EventCharacterReset();

	// needed for now for Xiaoyuan's code
	void EventSwitchMode();

	int updateCount = 0;
	int frameDelay = 0.1;

	Cartesian3 characterPosition;
	Cartesian3 characterDirection;

	Matrix4 lookMatrix;

	std::unique_ptr<Camera> m_camera;

	Cartesian3 controllerLessRunCyclePosition;

	CharacterState m_AnimState;

	}; // class SceneModel

#endif
	
