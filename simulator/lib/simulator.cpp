#include "sumo.h"
#include "motor.h"

#include "ClientSocket.h"
#include "SocketException.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

ClientSocket client_socket("localhost", 30000);

void split(string str, string delim, vector<int> *results)
{
	int cutAt;
	while((cutAt = str.find_first_of(delim)) != str.npos)
	{
		if(cutAt > 0){
			results->push_back(atoi(str.substr(0, cutAt).c_str()));
		}
		str = str.substr(cutAt+1);
	}
	if(str.length() > 0){
		results->push_back(atoi(str.c_str()));
	}
}

string generateMessage(){
	ostringstream msg;
	// M1:M2:LED
	msg << (int)motor[0].getPower() << ":" << (int)motor[1].getPower() << ":" << led_state << endl;
	return msg.str();
}

void parseReply(string reply){
	// SW1:SW2:G1:G2:G3:G4
	vector<int> items;
	split(reply, ":", &items);
	int i=0;
	for(;i<2; i++) Switch[i] = items.at(i);
	for(;i<6; i++) Ground[i-2] = items.at(i);
}

void simulate(){
	try
	{
		string reply;
		try {
			client_socket << generateMessage();
			client_socket >> reply;
			parseReply(reply);
		}
		catch ( SocketException& ) {}

	} catch ( SocketException& e ) {
		cout << "Exception was caught:" << e.description() << "\n";
	}
}

