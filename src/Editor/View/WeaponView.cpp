#include "WeaponView.h"

WeaponView::WeaponView(const Glib::RefPtr<Gtk::Builder> &builder,
                       const unsigned int &id) {
    builder->get_widget("sc_wep" + std::to_string(id), ammo_selector);
    builder->get_widget("cb_wep" + std::to_string(id), infinite);

    default_checkbox_state = infinite->get_active();
    default_ammo_selector_value = ammo_selector->get_value();

    ammo_selector->set_sensitive(!default_checkbox_state);

    ammo_selector->signal_value_changed().connect(
            sigc::mem_fun(*this, &WeaponView::onAmmoValueChanged));

    infinite->signal_clicked().connect(
            sigc::mem_fun(*this, &WeaponView::onCheckboxClicked));
}

void WeaponView::onAmmoValueChanged() {
    controller->updateAmmo(ammo_selector->get_value());
}

void WeaponView::onCheckboxClicked() {
    ammo_selector->set_sensitive(!infinite->get_active());
    if (infinite->get_active()) {
        controller->updateAmmo(-1);
    } else {
        controller->updateAmmo(ammo_selector->get_value());
    }
}

void WeaponView::resetAmmo() {
    ammo_selector->set_sensitive(!default_checkbox_state);
    ammo_selector->set_value(default_ammo_selector_value);
    infinite->set_active(default_checkbox_state);
}

void WeaponView::bindController(WeaponController *controller) {
    this->controller = controller;
}

const int WeaponView::getInitialAmmo() {
    return default_checkbox_state ? -1 : default_ammo_selector_value;
}

void WeaponView::setAmmo(const int &ammo) {
    if (ammo < 0) {
        infinite->set_active(true);
        ammo_selector->set_sensitive(false);
    } else {
        infinite->set_active(false);
        ammo_selector->set_sensitive(true);
        ammo_selector->set_value(ammo);
    }
}
