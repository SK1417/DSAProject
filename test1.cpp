#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;


class Route {
	char place[30];
	Route *Next;
	Route *Previous;
};

class Bus {
	char route_num[5];
	int first_serv_hour;
	int first_serv_min;
	int freq;
	char route_name[50][30];
};

void list_all_places(fstream& file) {
	
}

void list_all_routes(fstream& file) {

}

void add_bus_route(fstream& file) {

}

void modify_bus_route(fstream& file) {

}

void delete_bus_route(fstream& file) {

}

void change_password() {

}

void menu(fstream&);
void user(fstream&);
void admin(fstream&);

void menu(fstream& file) {
	system("CLS");
	cout<<"1. User\n2. Admin\nChoose an option: ";
	int option;
	cin>>option;
	if(option == 1)
		user(file);
	else if(option == 2)
		admin(file);
	else {
		cout<<"You have entered a wrong option. Press any key to continue... ";
		cin.get();
		menu(file);
	}
}

void admin(fstream& file) {
	system("CLS");
	cout<<"1. Add bus route\n2. Modify bus route\n3. Delete bus route\n4. Change password\n5. Log Out\n6. Exit\nChoose an option: ";
	int option;
	cin>>option;
	if(option == 1)
		add_bus_route(file);
	else if(option == 2)
		modify_bus_route(file);
	else if(option == 3)
		delete_bus_route(file);
	else if(option == 4) {
		change_password();
		admin(file);
	}
	else if(option == 5) {
		menu(file);
	}
	else if(option == 6) {
		cout<<"Are you really sure you want to exit? y/n";
		char ch;
		cin>>ch;
		if(ch == 'y' || ch == 'Y')
		exit(0);
		else
		admin(file);
	}
	else {
		cout<<"You have entered a wrong option. Press any key to continue... ";
		cin.get();
		admin(file);
	}	
}

void user(fstream& file) {
	system("CLS");
	cout<<"1. List all places\n2. List bus routes\n3. Go back\nChoose an option: ";
	int option;
	cin>>option;
	if(option == 1)
		list_all_places(file);
	else if(option == 2)
		list_all_routes(file);
	else if(option == 3)
		menu(file);
	else {
		cout<<"You have entered a wrong option. Press any key to continue... ";
		cin.get();
		user(file);
	}
}



int main() {
	system("CLS");
	fstream file("buses.dat", ios::app | ios::in| ios::binary);
	menu(file);
	file.close();
	return 0;
}