
#include <gtkmm/builder.h>
#include <utility>
#include "ToolBoxView.h"

ToolBoxView::ToolBoxView(BaseObjectType *cobject,
                 const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Grid(cobject),
          m_builder(builder) {
    builder->get_widget("btn_undo", erase);
    builder->get_widget("btn_clean", btn_clean);
    builder->get_widget("tbtn_worm", worm);
    worm->set_active(true);
    builder->get_widget("tbtn_grd", girder);
    builder->get_widget("btn_move", move);
    builder->get_widget("btn_turn", turn);
    turn->set_sensitive(false);
    builder->get_widget("btn_save", save);
    builder->get_widget("btn_load", load);

    worm->signal_clicked().connect(sigc::bind<int>
                                           (sigc::mem_fun(*this,
                                                          &ToolBoxView::on_button_clicked),
                                            WORM_BUTTON_ID));
    girder->signal_clicked().connect(sigc::bind<int>
                                             (sigc::mem_fun(*this,
                                                            &ToolBoxView::on_button_clicked),
                                              GIRDER_BUTTON_ID));
}

void ToolBoxView::linkController(std::shared_ptr<MapController> controller) {
    this->map_controller = std::move(controller);

    erase->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::undo));

    btn_clean->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::clean));

    move->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::moveSignal));

    turn->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::turnSignal));

    save->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::saveSignal));

    load->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::loadSignal));
}

void ToolBoxView::on_button_clicked(unsigned id) {
    if (id == WORM_BUTTON_ID) {
        if (worm->get_active()) {
            girder->set_active(false);
            turn->set_sensitive(false);
        }
    } else {
        if (girder->get_active()) {
            worm->set_active(false);
            turn->set_sensitive(true);
        }
    }
    map_controller->itemSelectedSignal(id);
}
