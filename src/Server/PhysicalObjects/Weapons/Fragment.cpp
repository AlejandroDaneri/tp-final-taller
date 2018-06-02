#include "Fragment.h"

Fragment::Fragment(World& world, GameParameters& parameters, int damage, int radius):
	Weapon(world, parameters, damage, radius){}
		
Fragment::~Fragment(){}

void Fragment::set_shoot_position(b2Vec2 pos){
	this->shoot_position = pos;
}

b2Vec2 Fragment::get_shoot_position(){
	return this->shoot_position;
}

void Fragment::shoot(int angle, int time){
	Weapon::shoot(1, angle, -1, time, -1);
}
