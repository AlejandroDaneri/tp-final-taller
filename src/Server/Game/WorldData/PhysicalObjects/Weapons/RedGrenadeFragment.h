#ifndef __SERVERREDGRENADEFRAGMENT_H__
#define __SERVERREDGRENADEFRAGMENT_H__

#include "Fragment.h"
#include <string>

class RedGrenadeFragment: public Fragment{
	public:
		RedGrenadeFragment(World& world, GameParameters& parameters);
		~RedGrenadeFragment();

		const std::string& getName() override;
};

#endif
