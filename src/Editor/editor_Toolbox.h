
#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/layout.h>
#include <gtkmm/togglebutton.h>
#include "editor_Map.h"


#define WORM_BUTTON_ID 1
#define GIRDER_BUTTON_ID 2

class Toolbox : public Gtk::Grid {
private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Button* btn_clean;
    Gtk::Button* undo;
    Map* map;
    Gtk::ToggleButton* worm;
    Gtk::ToggleButton* girder;
    bool item_pressed;

public:
    Toolbox(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

    void link_map(Map *pMap);
    void on_button_clicked(int id) ;
};


#endif //WORMS_TOOLBOX_H
