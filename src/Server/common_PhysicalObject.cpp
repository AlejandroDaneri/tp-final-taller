#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(World& world, int id, std::string type):
	world(world), is_dead(false), id(id), type(type){}

PhysicalObject::~PhysicalObject(){}

void PhysicalObject::initializeBody(b2Body* body){
	this->body = body;
	/////////////this->body->SetUserData(this->getData());
	this->createFixtures();
	this->setInitialVelocity();
}

b2Vec2 PhysicalObject::getPosition(){
	return this->body->GetPosition();
}

b2Body* PhysicalObject::getBody(){
	return this->body;
}

bool PhysicalObject::isMoving(){
	return this->body->IsAwake();
}

bool PhysicalObject::isDead(){
	return this->is_dead;
}

int PhysicalObject::getId(){
	return this->id;
}

std::string& PhysicalObject::getType(){
	return this->type;
}

void PhysicalObject::setInitialVelocity(){}
