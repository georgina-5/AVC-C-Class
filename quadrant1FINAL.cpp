//Quadrant 1
#include "E101.h"
//GATE IS OPEN FOR 4.2 SECONDS!

int main() {

	char address[15] = "130.195.6.196"; //server address
	char message[24] = "Please"; //message sent to server 
	//int connected = connect_to_server (address, 1024);

	connect_to_server(address, 1024);
	send_to_server(message); //asks server for the password
	receive_from_server(message); //receive password from the server
	send_to_server(message); //send password back to server ---> opens gate
}
