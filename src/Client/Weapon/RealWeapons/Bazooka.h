#ifndef __CLIENTBAZOOKA_H__
#define __CLIENTBAZOOKA_H__

#include "DistanceWeapon.h"

class Bazooka: public DistanceWeapon {
	public:
		Bazooka(int ammo);
		~Bazooka();
		Bazooka(Bazooka&& other);
};

#endif