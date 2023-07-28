#include "Behavior.h"
#include<cmath>

void BehaviorSpring(Spring* spring, Ball* ball) {

	MyVector3 diff = ball->position - spring->anchor;
	float length = diff.Length();

	if (length != 0) {
		MyVector3 restPosition = spring->anchor + diff.Normalize() * spring->naturalLength;
		MyVector3 displacement = length * (ball->position - restPosition);
		MyVector3 restoringForce = -spring->stiffness * displacement;
		MyVector3 dampingForce = -spring->dampingCoefficient * ball->velocity;
		MyVector3 force = restoringForce + dampingForce;
		ball->acceleration = force / ball->mass;
	}
	float deltaTime = 1.0f / 60.0f;

	ball->velocity += ball->acceleration * deltaTime;
	ball->position += ball->velocity * deltaTime;
}

void BehaviorSpring(Spring* spring, Ball* ball, const MyVector3& gravity) {

	MyVector3 diff = ball->position - spring->anchor;
	float length = diff.Length();

	if (length != 0) {
		MyVector3 restPosition = spring->anchor + diff.Normalize() * spring->naturalLength;
		MyVector3 displacement = length * (ball->position - restPosition);
		MyVector3 restoringForce = -spring->stiffness * displacement;
		MyVector3 dampingForce = -spring->dampingCoefficient * ball->velocity;
		MyVector3 force = restoringForce + dampingForce + gravity;
		ball->acceleration = force / ball->mass;
	}
	float deltaTime = 1.0f / 60.0f;

	ball->velocity += ball->acceleration * deltaTime;
	ball->position += ball->velocity * deltaTime;

}

void BehaviorCircleMovement(MyVector3* position, const float& angularVelocity, float* angle, const float& radius, const MyVector3& point) {

	float deltaTime = 1.0f / 60.0f;
	*angle += angularVelocity * deltaTime;

	position->x = point.x + std::cos(*angle) * radius;
	position->y = point.y + std::sin(*angle) * radius;
	position->z = point.z;

}

void BehaviorCircleMovement(Ball* ball, const float& angularVelocity, float* angle, const float& radius, const MyVector3& point) {

	float deltaTime = 1.0f / 60.0f;
	*angle += angularVelocity * deltaTime;

	ball->position.x = point.x + std::cos(*angle) * radius;
	ball->position.y = point.y + std::sin(*angle) * radius;
	ball->position.z = point.z;

	/*float n = -powf(angularVelocity, 2.0f) * radius;
	ball->acceleration.x = n * std::cos(*angle) + point.x;
	ball->acceleration.y = n * std::sin(*angle) + point.z;
	ball->acceleration.z = 0.0f;

	ball->velocity += ball->acceleration * deltaTime;
	ball->position += ball->velocity * deltaTime;*/
}