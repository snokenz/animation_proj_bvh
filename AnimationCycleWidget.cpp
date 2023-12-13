
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

#include "AnimationCycleWidget.h"

// constructor
AnimationCycleWidget::AnimationCycleWidget(QWidget *parent, SceneModel *TheScene)
	: _GEOMETRIC_WIDGET_PARENT_CLASS(parent),
	theScene(TheScene)
	{ // constructor
	// we want to create a timer for forcing animation
	animationTimer = new QTimer(this);
	// connect it to the desired slot
	connect(animationTimer, SIGNAL(timeout()), this, SLOT(nextFrame()));
	// set the timer to fire 24 times a second
	animationTimer->start((double)41.6667);
	} // constructor

// destructor
AnimationCycleWidget::~AnimationCycleWidget()
	{ // destructor
	// nothing yet
	} // destructor																	

// called when OpenGL context is set up
void AnimationCycleWidget::initializeGL()
	{ // AnimationCycleWidget::initializeGL()
	} // AnimationCycleWidget::initializeGL()

// called every time the widget is resized
void AnimationCycleWidget::resizeGL(int w, int h)
	{ // AnimationCycleWidget::resizeGL()
	// reset the viewport
	glViewport(0, 0, w, h);
	
	// set projection matrix based on zoom & window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// compute the aspect ratio of the widget
	float aspectRatio = (float) w / (float) h;
	
	// we want a 90 degree vertical field of view, as wide as the window allows
	// and we want to see from just in front of us to 100km away
	gluPerspective(90.0, aspectRatio, 0.1, 100000);

	// set model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	} // AnimationCycleWidget::resizeGL()
	
// called every time the widget needs painting
void AnimationCycleWidget::paintGL()
	{ // AnimationCycleWidget::paintGL()
	// call the scene to render itself
	theScene->Render();
	} // AnimationCycleWidget::paintGL()

// called when a key is pressed
void AnimationCycleWidget::keyPressEvent(QKeyEvent *event)
	{ // keyPressEvent()
	// just do a big switch statement
	switch (event->key())
		{ // end of key switch
		// exit the program
		case Qt::Key_X:
			exit(0);
			break;
	
		// camera controls
		case Qt::Key_W:
			theScene->EventCameraForward();
			break;
		case Qt::Key_A:
			theScene->EventCameraLeft();
			break;
		case Qt::Key_S:
			theScene->EventCameraBackward();
			break;
		case Qt::Key_D:
			theScene->EventCameraRight();
			break;
		case Qt::Key_F:
			theScene->EventCameraDown();
			break;
		case Qt::Key_R:
			theScene->EventCameraUp();
			break;
		case Qt::Key_Q:
			theScene->EventCameraTurnLeft();
			break;
		case Qt::Key_E:
			theScene->EventCameraTurnRight();
			break;
			
		// resets the character's position and orientation
		case Qt::Key_P:
			theScene->EventCharacterReset();
			break;
			
		// keys for engaging character animation
		case Qt::Key_Up:
			theScene->EventCharacterForward();
			break;
		case Qt::Key_Down:
			theScene->EventCharacterBackward();
			break;
		case Qt::Key_Left:
			theScene->EventCharacterTurnLeft();
			break;
		case Qt::Key_Right:
			theScene->EventCharacterTurnRight();
			break;
		
		// just in case
		default:
			break;
		} // end of key switch
	} // keyPressEvent()

// called when a key is released: used to end animation cycle
void AnimationCycleWidget::keyReleaseEvent(QKeyEvent* event)
	{ // keyReleaseEvent()
	// when the character motion keys are released, revert to rest pose
	switch (event->key())
		{ // end of key switch
		case Qt::Key_Up:
		case Qt::Key_Down:
		case Qt::Key_Left:
		case Qt::Key_Right:
		
// 			if (!event->isAutoRepeat())
// 				theScene->EventCharacterRestPose();
			break;
		default:
			break;
		} // end of key switch
	} // keyReleaseEvent()

void AnimationCycleWidget::nextFrame()
	{ // nextFrame()
	// each time this gets called, we will update the scene
	theScene->Update();

	// now force an update
	update();
	} // nextFrame()

