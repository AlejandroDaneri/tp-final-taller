
#ifndef WORMS_WEAPONSLISTCONTROLLER_H
#define WORMS_WEAPONSLISTCONTROLLER_H


#include <gtkmm/button.h>
#include <gtkmm/spinbutton.h>
#include "Weapon.h"
#include "WeaponView.h"
#include "LifeView.h"

class UsablesController {
private:
    LifeView *life_spinner;
    Gtk::Button *reset_button;
    std::vector<std::shared_ptr<Weapon>> weapons;
    std::vector<std::shared_ptr<WeaponView>> weapons_view;
    std::vector<std::shared_ptr<WeaponController> > wep_controllers;

    bool isValidWeaponSet(std::vector<int> &ammo_vector) const;
public:
    explicit UsablesController(
            const Glib::RefPtr<Gtk::Builder> &builder);

    void onResetSignal();

    void getWeapons(std::vector<int> &weps_ammo, unsigned int &life) const;

    void
    loadWeapons(std::vector<int> &weps_ammo, const unsigned int &life) const;


};


#endif //WORMS_WEAPONSLISTCONTROLLER_H