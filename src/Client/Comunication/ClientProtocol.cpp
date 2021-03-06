#include "ClientProtocol.h"
#include <string>
#include "Player.h"
#include "WeaponList.h"
#include "ObjectSizes.h"
#include "ServerFatalError.h"

ClientProtocol::ClientProtocol(Socket&& socket, Gtk::Window& window) :
		Protocol(std::move(socket)), window(window) {}

ClientProtocol::ClientProtocol(ClientProtocol&& other) :
		Protocol(std::move(other)), window(other.window) {}

ClientProtocol::~ClientProtocol() {}

void ClientProtocol::sendMoveAction(char action) {
	Buffer buffer;
	buffer.setNext(ACTION);
	buffer.setNext(MOVE_ACTION);
	buffer.setNext(action);
	this->sendBuffer(buffer);
}

void ClientProtocol::sendChangeWeapon(const std::string& weapon) {
	Buffer buffer;
	buffer.setNext(ACTION);
	buffer.setNext(CHANGE_WEAPON_ACTION);
	this->sendStringBuffer(buffer, weapon);
	this->sendBuffer(buffer);
}

void
ClientProtocol::sendWeaponShoot(int32_t angle, int32_t power, int32_t time) {
	Buffer buffer;
	buffer.setNext(ACTION);
	buffer.setNext(SHOOT_WEAPON);
	this->sendIntBuffer(buffer, angle);
	this->sendIntBuffer(buffer, power);
	this->sendIntBuffer(buffer, time);
	this->sendBuffer(buffer);
}

void ClientProtocol::sendWeaponSelfDirectedShoot(const Position& pos) {
	Buffer buffer;
	buffer.setNext(ACTION);
	buffer.setNext(SHOOT_SELF_DIRECTED);

	this->sendIntBuffer(buffer, pos.getX() * UNIT_TO_SEND);
	this->sendIntBuffer(buffer, pos.getY() * UNIT_TO_SEND);

	this->sendBuffer(buffer);
}

void ClientProtocol::updateScope(int angle) {
	Buffer buffer;
	buffer.setNext(ACTION);
	buffer.setNext(MOVE_SCOPE);

	this->sendIntBuffer(buffer, angle);

	this->sendBuffer(buffer);
}

void ClientProtocol::sendEndGame() {
	Buffer buffer;
	buffer.setNext(END_GAME);
	this->sendBuffer(buffer);
}

void ClientProtocol::receiveStartGame() {
	Buffer buffer = std::move(this->receiveBuffer());
}

void ClientProtocol::receiveBackgroundImage(WorldView& world) {
	Buffer buffer = std::move(this->receiveBuffer());
	world.setBackgroundImage(buffer);
}

void ClientProtocol::receiveTurnData(Turn& turn) {
	Buffer buffer = std::move(this->receiveBuffer());
	int max_time = this->receiveIntBuffer(buffer);
	int time_after_shoot = this->receiveIntBuffer(buffer);
	turn.setTime(max_time, time_after_shoot);
}

void ClientProtocol::receivePlayers(PlayersList& players_list) {
	Buffer buffer = std::move(this->receiveBuffer());
	int quantity = this->receiveIntBuffer(buffer);

	for (int i = 0; i < quantity; i++) {
		Buffer buffer = std::move(this->receiveBuffer());

		int id = this->receiveIntBuffer(buffer);
		std::string name = this->receiveStringBuffer(buffer);

		players_list.addPlayer(id, name);
	}
}

void ClientProtocol::receiveGirders(ViewsList& viewsList) {
	Buffer buffer = std::move(this->receiveBuffer());
	int quantity = this->receiveIntBuffer(buffer);

	for (int i = 0; i < quantity; i++) {
		Buffer buffer = std::move(this->receiveBuffer());;

		int size = this->receiveIntBuffer(buffer);
		float pos_x = this->receiveIntBuffer(buffer) / UNIT_TO_SEND;
		float pos_y = this->receiveIntBuffer(buffer) / UNIT_TO_SEND;
		int rotation = this->receiveIntBuffer(buffer);
		viewsList.addGirder(size, pos_x, pos_y, rotation);
	}
}

void ClientProtocol::receiveWeaponsAmmo(WeaponList& weapon_list) {
	Buffer buffer = std::move(this->receiveBuffer());
	int quantity = this->receiveIntBuffer(buffer);

	for (int i = 0; i < quantity; i++) {
		Buffer buffer = std::move(this->receiveBuffer());

		std::string name = this->receiveStringBuffer(buffer);
		int ammo = this->receiveIntBuffer(buffer);
		weapon_list.add(name, ammo);
	}
}

void ClientProtocol::sendBuffer(Buffer& buffer) {
	try {
		Protocol::sendBuffer(buffer);
	} catch(const std::exception& e) {
		ServerFatalError error(this->window);
	}
}
