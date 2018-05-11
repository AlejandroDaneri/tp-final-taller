#include "client_Weapon.h"

Weapon::Weapon(std::string name, int ammo) :
	name(name), ammo(ammo), has_Scope(false), is_Timed(false),
	is_Fragmentable(false) {}

bool Weapon::hasScope() {
	return this->has_Scope;
}

bool Weapon::isSelfDirected() {
	return false;
}

bool Weapon::isFragmentable() {
	return this->is_Fragmentable;
}

bool Weapon::isTimed() {
	return this->is_Timed;
}

bool Weapon::hasVariablePower() {
	return false;
}

int Weapon::getTime() {
	return -1;
}

std::string Weapon::getName() {
	return this->name;
}
