#include "WeaponView.h"
#include <glibmm/main.h>
#include <string>
#include <utility>
#include "Player.h"
#include "WeaponList.h"
#include "WeaponButton.h"

WeaponView::WeaponView(WeaponList& weapons, Player& player) :
		weapons(weapons), player(player) {}

WeaponView::~WeaponView() {}

void WeaponView::update() {
	WeaponList::iterator iter;
	int row = 1, column = 1;
	for (iter = this->weapons.begin(); iter != this->weapons.end(); iter++) {
		std::unique_ptr<WeaponButton> p(
				new WeaponButton(iter->second->getName(),
								 iter->second->getAmmo(), this->player));
		this->buttons.insert(
				std::pair<std::string, std::unique_ptr<WeaponButton>>(
						iter->second->getName(), std::move(p)));
		this->window.attach(
				this->buttons.at(iter->second->getName())->getButton(), column,
				row, 1, 1);
		row++;
	}
}

Gtk::Grid& WeaponView::getWindow() {
	return this->window;
}

void WeaponView::updateAmmo(const Weapon& weapon) {
	this->buttons[weapon.getName()]->setLabel(weapon.getAmmo());
}
