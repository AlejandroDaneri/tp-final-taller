
#ifndef WORMS_WEAPONSAREA_H
#define WORMS_WEAPONSAREA_H


#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include "editor_Weapon.h"

class WeaponsArea : public Gtk::Grid{
    Gtk::Button back;
    Weapon wep;
    Gtk::Button m_default;
public:
    WeaponsArea();

protected:
    bool on_button_release_event(GdkEventButton *release_event) override;

    void on_reset_clicked();
};


#endif //WORMS_WEAPONSAREA_H
