#pragma once

#include <glm\vec3.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>
#include <glm\gtx\euler_angles.hpp>

class TTransform;
class TGraphicEngine;
class TCamara;
class TNodo;
class Pared

{
public:
	Pared(TGraphicEngine * motorApp,glm::vec3 tras, glm::vec3 rot, glm::vec3 sca);
	~Pared();
	float getVelocity();
	float getYaw();
	float getPitch();
	TTransform* Rotation();
	TTransform* Scale();
	TTransform* Translation();
	void setVelocity(float);
	void setYaw(float);
	void setPitch(float);
private:
	float velocity;
	float yaw;
	float pitch;
	TTransform *rotation;
	TTransform *scale;
	TTransform *translation;
};
