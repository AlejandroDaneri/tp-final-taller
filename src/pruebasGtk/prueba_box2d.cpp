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
#include "Box2D.h"

#include "Thread.h"

class Imagen: public Thread{
public:
	Gtk::Image& image;
	Gtk::Fixed& map;
	b2Body* body;

	Imagen(Gtk::Image& i, Gtk::Fixed& f):image(i), map(f){}

	~Imagen(){}

	void addToWorld(b2World* world){
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(5,500);
		bodyDef.userData = this;
		bodyDef.fixedRotation = true;
		this->body = world->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(1,1);
		  
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		this->body->CreateFixture(&boxFixtureDef);
	}

	b2Vec2 getPosition(){
		return this->body->GetPosition();
	}

	void stop(){
		this->running = false;
	}

	void run(){
		body->SetLinearVelocity(b2Vec2(100.0f, -100.0));
		while (this->running){
			b2Vec2 pos = this->getPosition();
			std::cout << "Pos x: " << pos.x << "  y: " << pos.y << std::endl;
			std::this_thread::sleep_for (std::chrono::milliseconds(10));
			map.move(image, pos.x, pos.y);
		}
	}
};

class MyWorld: public Thread{
public:
	b2World* world;

	MyWorld(){
		world = new b2World(b2Vec2(0.0f, 10.0));
		world->SetAllowSleeping(true);
		world->SetContinuousPhysics(true);
		//world->SetContactListener(this);
	}

	~MyWorld(){
		delete this->world;
	}

	void stop(){
		this->running = false;
	}

	void run(){
		while(this->running){
			float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
			  int32 velocityIterations = 8;   //how strongly to correct velocity
			  int32 positionIterations = 3;   //how strongly to correct position
			  std::this_thread::sleep_for (std::chrono::milliseconds(10));
			  this->world->Step( timeStep, velocityIterations, positionIterations);
		}
	}

	void add_imagen(Imagen& imagen){
		imagen.addToWorld(this->world);
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
    //map.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
	Gtk::Button buttonQuit;
    ventana.resize(1000, 1000);
	Gtk::Image bomba;
	bomba.set("resources/images/bomba.png");
	world_map.put(bomba,500, 500);
	
	buttonQuit.add_label("Quit");
	buttonQuit.signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app));
	
	world_map.put(buttonQuit,300, 300);
	ventana.add(map);
    ventana.show_all();

    Imagen imagen(bomba, world_map);
    MyWorld w;
    w.add_imagen(imagen);
    w.start();
    imagen.start();
    app->run(ventana);
    imagen.stop();
    imagen.join();
    w.stop();
    w.join();
	return 0;
}