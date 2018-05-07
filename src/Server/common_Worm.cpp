#include "Worm.h"
#include "b2PolygonShape.h"
#include "b2Fixture.h"

Worm::Worm(World& world, int id): PhysicalObject(world, id, "Worm"){}

Worm::~Worm(){}

void Worm::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_dynamicBody;
	body_def.position.Set(pos.x, pos.y);
	body_def.fixedRotation = true;
}

void Worm::createFixtures(){
	b2PolygonShape boxShape;
	boxShape.SetAsBox(1,1);
		  
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 4;
	this->body->CreateFixture(&boxFixtureDef);
}

int Worm::getLife(){
	return this->life;
}

char Worm::getDir(){
	return this->dir;
}

void Worm::move(char action){
	////////////////////////////////////////
}

void Worm::changeWeapon(const std::string& weapon){
	///////////////////////////////////////////////////////////
}

void Worm::shoot(int angle, int power, int time){
	////////////////////////////////////////////////////////
}

void Worm::shoot(b2Vec2 pos){
	///////////////////////////////////////////////////
}