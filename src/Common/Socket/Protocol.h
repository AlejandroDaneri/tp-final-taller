#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string>
#include <mutex>
#include "Buffer.h"
#include "Socket.h"

#define MAX_STRING_SIZE 200

#define CREATE_GAME_ACTION 0
#define JOIN_GAME_ACTION 1
#define START_GAME_ACTION 1

#define MOVING_OBJECT 0
#define DEAD_OBJECT 1
#define ACTION 2


#define START_TURN 3
#define END_TURN 4
#define MOVE_ACTION 5
#define CHANGE_WEAPON_ACTION 6
#define SHOOT_WEAPON 7
#define SHOOT_SELF_DIRECTED 8
#define MOVE_SCOPE 9


#define MOVE_RIGHT 1
#define MOVE_LEFT -1
#define JUMP 2
#define ROLLBACK 3

#define WORM_TYPE 0
#define WEAPON_TYPE 1
#define GIRDER_TYPE 2

/* Clase que se encarga de enviar y recibir mensajes por socket
 * utilizando un formato determinado */
class Protocol {
	private:
		Socket socket;
		std::mutex mutex_send;
	public:
		/* Constructor */
		Protocol(Socket&& socket);

		/* Constructor por copia */
		Protocol(Protocol&& other);

		/* Destructor */
		~Protocol();


		/* Envia el contenido del buffer */
		void sendBuffer(Buffer &buffer);

		/* Recibe un mensaje, lo almacena en un buffer y lo retorna */
		Buffer receiveBuffer();


		/* Agrega el valor al buffer cumpliendo las caracteristicas del protocolo */
		void sendIntBuffer(Buffer &buffer, int32_t value);

		/* Retorna el valor del entero recibido almacenado en el buffer */
		int receiveIntBuffer(Buffer &buffer);


		/* Almacena el string en el buffer  */
		void sendStringBuffer(Buffer &buffer, const std::string &string);

		/* Retorna el string recibido que se encuentra almacenado en el buffer */
		std::string receiveStringBuffer(Buffer &buffer);


		/* Envia la longitud */
		void sendLength(uint32_t length);

		/* Recibe la longitud y la retorna */
		size_t receiveLength();


		/* Cierra la comunicacion */
		void stop();

		/* Envia un char */
		void sendChar(unsigned char c);

		/* Recibe un char */
		unsigned char receiveChar();

		/* Envia un string */
		void sendString(const std::string &string);

		/* Recibe un string */
		std::string receiveString();
};

#endif
