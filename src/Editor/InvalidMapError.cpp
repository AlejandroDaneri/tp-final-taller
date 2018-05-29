
#include <gtkmm/enums.h>
#include <gtkmm/messagedialog.h>
#include "InvalidMapError.h"

InvalidMapError::InvalidMapError(const char *message) noexcept : message(message){
}

const char *InvalidMapError::what() const noexcept{
    Gtk::MessageDialog dialog("Error al guardar archivo",false,Gtk::MESSAGE_WARNING);
    dialog.set_secondary_text(message);
    dialog.run();
    return exception::what();
}

InvalidMapError::~InvalidMapError() {

}