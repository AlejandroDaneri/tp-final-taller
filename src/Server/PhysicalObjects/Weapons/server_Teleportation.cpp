#include "server_Teleportation.h"
#include "Worm.h"
#include <mutex>

Teleportation::Teleportation(World& world, GameParameters& parameters):
	Weapon(world, parameters, 0){}
		
Teleportation::~Teleportation(){}

std::string Teleportation::getName(){
	return "Teleportation";
}

void Teleportation::shoot(char dir, int angle, int power, int time){}

void Teleportation::shoot(Worm& shooter, b2Vec2 pos){
	std::lock_guard<std::mutex> lock(this->world.getMutex());
	shooter.getBody()->SetTransform(pos, 0);
	shooter.getBody()->SetAwake(true);
}