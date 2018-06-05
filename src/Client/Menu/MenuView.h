#ifndef __MENUVIEW_H__
#define __MENUVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/overlay.h>
#include <gtkmm/image.h>
#include <memory>
#include "ClientProtocol.h"

class MenuView{
	private:
		/* Muestra un mensaje de error */
		void showError(const std::string& error);

	protected:
		Gtk::Window& window;
		ClientProtocol& protocol;
		Gtk::Label* error;
		std::unique_ptr<MenuView> next_menu;
		MenuView& main_menu;
		Gtk::Container* menu;

		Gtk::Overlay menu_container;
		Gtk::Image background;

		/* Muestra un mensaje de error y cierra la aplicacion*/
		void showFatalError();

		/* Muestra un mensaje de error y reinicia */
		void showErrorAndRestart(const std::string& error);

		/* Agrega el menu al world y el world al window */
		void addMenu();

		/* Handler del boton de salir */
		void quitButtonPressed();

	public:
		/* Constructor */
		MenuView(Gtk::Window& window, MenuView& main_menu, ClientProtocol& protocol);

		/* Destructor */
		virtual ~MenuView();
};

#endif
