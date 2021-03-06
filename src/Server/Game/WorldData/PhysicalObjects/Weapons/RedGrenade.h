#ifndef __SERVERREDGRENADE_H__
#define __SERVERREDGRENADE_H__

#include "FragmentableWeapon.h"
#include <string>

class RedGrenade: public FragmentableWeapon{
	public:
		RedGrenade(World& world, GameParameters& parameters);
		~RedGrenade();

		const std::string& getName() override;
};

#endif
