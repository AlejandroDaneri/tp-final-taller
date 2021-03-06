#ifndef __TURNLABEL_H__
#define __TURNLABEL_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <string>

/* Clase que se encarga de controlar los labels que indican
 * el estado del turno */
class TurnLabel {
private:
	Gtk::Label message;
	Gtk::Label time;
	Gtk::HBox label;

public:
	/* Constructor */
	TurnLabel();

	/* Destructor */
	~TurnLabel();


	/* Cambia el label indicando que es el turno del jugador */
	void beginTurn();

	/* Cambia el label indicando que es el turno del jugador
	 * con nombre pasado por parametro */
	void beginTurn(const std::string& player_name);

	/* Cambia el label indicando que finalizo el turno del jugador */
	void endTurn();

	/* Cambia el label mostrando al ganador */
	void setEndGame();

	/* Cambia el label de tiempo al tiempo pasado por parametro */
	void setTime(int time);

	/* Devuelve el contenedor de la vista */
	Gtk::Container& getWindow();
};


#endif
