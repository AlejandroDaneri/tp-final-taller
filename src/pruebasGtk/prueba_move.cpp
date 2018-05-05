#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>

#include <iostream>
#include <cairo.h>

#include <thread>

class Functor{
	public:
		Gtk::Fixed& window;
		Gtk::Image& image;

		Functor(Gtk::Fixed& w, Gtk::Image& i):
			window(w), image(i){}

			~Functor(){}

			void operator()(){
					sleep(2);
					std::cout << "move" << std::endl;

					int x = 500;
					int y = 500;
					this->window.move(this->image,x, y);

					sleep(2);
					std::cout << "move" << std::endl;

					//this->window.move(this->image,1300, 500);
					
					this->window.move(this->image,x, y);
					// Muevo la imagen horizontalmente
					for (; x <= 1000; x++){
						std::this_thread::sleep_for (std::chrono::milliseconds(10));
						this->window.move(this->image,x , y);
					}
					// Muevo la imagen en diagonal
					for (; x >= 750; x--){
						std::this_thread::sleep_for (std::chrono::milliseconds(10));
						double aux = 0.4*x + 100;
						this->window.move(this->image,x, (int) aux);
					}
					// Muevo la imagen en diagonal hasta el inicio
					for (; x >= 500; x--){
						std::this_thread::sleep_for (std::chrono::milliseconds(10));
						double aux = -0.4*x + 700;
						this->window.move(this->image,x, (int) aux);
					}
					// Muevo la imagen en una parabola.
					for (; x <= 1000; x++){
						std::this_thread::sleep_for (std::chrono::milliseconds(10));
						double aux = 4.0/625*x*x - 48.0/5*x +3700;
						this->window.move(this->image,x, (int) aux);
					}
			}
};

void on_salir_clicked(Glib::RefPtr<Gtk::Application> app){
    std::cout << "[recibido el evento clicked]" << std::endl;
      //Salimos del loop de eventos
    app->quit();
}

int main(int argc, char** argv) {
    auto app = Gtk::Application::create(argc, argv);
    Gtk::Window ventana;
    Gtk::Fixed world_map;
    Gtk::ScrolledWindow map;
    map.add(world_map);
	Gtk::Button buttonQuit;
    ventana.resize(1000, 1000);
	Gtk::Image image;
	Gtk::Image bomba;
	image.set("resources/images/bomba2.png");
	bomba.set("resources/images/bomba.png");
	world_map.put(image,500,800);
	world_map.put(bomba,500, 800);
	
	buttonQuit.add_label("Quit");
	buttonQuit.signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app));
	
	world_map.put(buttonQuit,300, 300);
	ventana.add(map);
    ventana.show_all();

    Functor f(world_map, bomba);
    std::thread t(f);
    app->run(ventana);

    t.join();
	return 0;
}