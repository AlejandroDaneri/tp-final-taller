#include "World.h"
#include "BottomBorder.h"

World::World(const b2Vec2& gravity): world(gravity){
	this->world.SetAllowSleeping(true);
	this->world.SetContinuousPhysics(true);
	/////////////////this->world->SetContactListener(&colission);
	this->initialize();
}
		
World::~World(){}

void World::run(){
	float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	while(this->running){
		std::this_thread::sleep_for(std::chrono::milliseconds(15));

		std::lock_guard<std::mutex> lock(this->mutex);
		this->world.Step(timeStep, velocityIterations, positionIterations);
	}
}

void World::addObject(physical_object_ptr& object, const b2Vec2& pos){
	b2BodyDef body_def;
	object -> getBodyDef(body_def, pos);

	std::lock_guard<std::mutex> lock(this->mutex);
	object->initializeBody(this->world.CreateBody(&body_def));
	if (body_def.type != b2_staticBody){
		this->objects.push_back(std::move(object));
	}
}

void World::removeObject(PhysicalObject& object){
	std::lock_guard<std::mutex> lock(this->mutex);
	this->world.DestroyBody(object.getBody());
}

void World::initialize(){
	physical_object_ptr bottom_border(new BottomBorder(*this));
	this->addObject(bottom_border, b2Vec2(0, 900));///////////////////////////////////////////////////////////ver
}