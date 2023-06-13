/**
 * This file implements a "UDP ping server".
 *
 * It basically waits for datagrams to arrive, and for each one received, it responds to the original sender
 * with another datagram that has the same payload as the original datagram. The server must reply to 3
 * datagrams and then quit.
 *
 * Test with:
 *
 * $ netcat -u 127.0.0.1 8080
 * ping
 * ping
 * pong
 * pong
 *
 * (assuming that this program listens at localhost port 8080)
 *
 */

// TODO: some includes here
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>

int main(int argc, char **argv) {

	(void) argc; // This is how an unused parameter warning is silenced.
	(void) argv;


	// TODO: some socket stuff here
	int s = socket(AF_INET, SOCK_DGRAM, 0); //Creacion del socket
	if(s == -1) //Comprobacion de error al crear el socket
	{
		perror("Socker could not be created");
		return 1;
	}


	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);


	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(8080);
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int bind_control = bind(s, (struct sockaddr*) &server_addr, sizeof(server_addr)); //Enlaza la direccion del server con el socket
	if(bind_control < 0) //Comprobacion de error del bind
	{
		perror("Bind error");
		return 1;
	}

	char buffer[65535] = {0}; //Creacion del buffer con un tamaño lo bastante grande para no dar error.
	socklen_t addr_len = sizeof(client_addr);
	for(int i = 0; i < 3; i++) //Bucle de los mensajes (recvfrom and sendto)
	{
		//Recibe el mensaje del socket
		ssize_t  message_recived  = recvfrom(s, buffer, 65535, 0,(struct sockaddr*) &client_addr, &addr_len);
		if(message_recived < 0) //Combrovacion de error del recvfrom()
		{
			perror("Error reciving message");
			return 1;
		}
		//Enviar mensaje en el socket
		ssize_t  message_sendto = sendto(s, buffer, (size_t)message_recived, 0, (struct sockaddr*) &client_addr, addr_len);
		if(message_sendto < 0) //Combrovacion de error del sendto()
		{
			perror("Error sending message");
			return 1;
		}
	}

	close(sock);
	return 0;
}
