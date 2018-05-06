#ifndef __WORLDVIEW_H__
#define __WORLDVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>
#include "Position.h"

class WorldView{
	private:
		Gtk::Fixed world;
		Gtk::ScrolledWindow window;


	public:
		WorldView();
		~WorldView();

		void moveElement(Gtk::Widget& element, const Position& position);

		void removeElement(Gtk::Widget& element);

		void addElement(Gtk::Widget& element, const Position& position);

		Gtk::ScrolledWindow& getWindow();

};


#endif