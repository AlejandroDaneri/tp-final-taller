#ifndef __SERVERTELEPORTATION_H__
#define __SERVERTELEPORTATION_H__

#include "Weapon.h"
#include <string>

class Teleportation: public Weapon{
	public:
		Teleportation(World& world, GameParameters& parameters);
		~Teleportation();

		const std::string& getName() override;

		void shoot(char dir, int angle, int power, int time, int shooter_id) override;

		//Teletransporta al gusano
		void shoot(Worm& shooter, b2Vec2 pos) override;
};

#endif
