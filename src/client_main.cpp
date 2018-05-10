#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "WorldView.h"
#include "WormView.h"
#include "WeaponView.h"
#include "ViewsList.h"
#include "Socket.h"
#include "client_Protocol.h"
#include "client_Player.h"
#include "DataReceiver.h"

int main(int argc, char* argv[]){

	auto app = Gtk::Application::create(argc, argv);
    Gtk::Window window;
    window.resize(1280, 720);

    Socket socket(Socket::Client("127.0.0.1", "7777"));
    Protocol protocol(std::move(socket));
    
    Player player;  ////////////////////////////////////El player despues recibe el protocol
    WorldView world;////////////////////////////////////Estos se crean en player despues
    ViewsList list(world);////////////////////////////////////Estos se crean en player despues

    DataReceiver receiver(list, player, protocol);  ////////////////////////////////////Estos se crean en player despues

    window.add(world.getWindow());
    window.show_all();


    receiver.start();
    app->run(window);

    try{
        receiver.stop();
    } catch (const std::exception& e){}

    receiver.join();


	return 0;
}
