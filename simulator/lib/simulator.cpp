#include "sumo.h"

#include "ClientSocket.h"
#include "SocketException.h"

#include <iostream>
#include <string>

using namespace std;

ClientSocket client_socket("localhost", 30000);

void simulate(){
	cout << "Initializing simulator" << endl;
	try
	{
		string reply;
		
		cout << "sending" << endl;
		
		try {
			client_socket << "Test message.";
			client_socket >> reply;
		}
		catch ( SocketException& ) {}

		cout << "We received this response from the server:\n\"" << reply << "\"\n";;

	} catch ( SocketException& e ) {
		cout << "Exception was caught:" << e.description() << "\n";
	}
}
