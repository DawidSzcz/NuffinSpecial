#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "types.hpp"

extern const unsigned short int window_w,window_h;

class Camera {
public:
	void GetControls(Time_t delta_time);
	void Bind() const;
protected:
	const unsigned short int initial_mouse_x = window_w/2;
	const unsigned short int initial_mouse_y = window_h/2;

	void updatePosition(Time_t delta_time);
	Position_t position = Position_t(0.0,0.0,-10.0);

	void updateDirection(Time_t delta_time);
	Position_t upVector = Position_t(0.0,1.0,0.0);
	Position_t rightVector = Position_t(1.0,0.0,0.0);
	Position_t getDirectionVector() const { return glm::cross(upVector,rightVector); };
	
	void updateAngle();
	float angle = 0.3*M_PI;
	float cameraAngleStep = 0.01;
	float cameraAngleMin = 0.1*M_PI;
	float cameraAngleMax = 0.45*M_PI;
	
	void updateMoveSpeed();
	Coord_t moveSpeed = 6.0;
	Coord_t moveSpeedStep = 0.01; //fraction
	Coord_t moveSpeedMin = 0.0;

	
	Coord_t rotatingSpeed = 0.5;	
};

#endif