#include<mach/mach.h>
#include<stdio.h>

struct message{
	mach_msg_header_t header;
	int data;
};

mach_port_t client;
mach_port_t server;

struct message message;

int main()
{
	message.header.msgh_size = sizeof(message);
	message.header.msgh_remote_port = server;
	message.header.msgh_local_port = client;

	mach_msg(&message.header,  //message header
			MACH_SEND_MSG, //sending a message
			sizeof(message), //size of message sent
			0, // maximum size of received message - unnecessary
			MACH_PORT_NULL, //name of receive port - unnecessary
			MACH_MSG_TIMEOUT_NONE, //no time outs
			MACH_PORT_NULL // no notify port
	);
	printf("message-passing mach system");
	return 0;
}
