#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;

class Route {
	public:
	char place[30];
	Route *Next;
	Route *Prev;
};

class Bus {
	public:
	char route_num[5];
	int first_serv_hour;
	int first_serv_min;
	int freq;
	int no_of_bus_stops;
	string place_name[50];
};

void menu(fstream &, Bus [], Route [], int *);
void user(Bus [], Route [], int *);
void admin(fstream &, Bus [], Route [], int *);

void list_all_places(Bus bus[], Route route[], int *no_of_buses) {
	
}

void list_all_routes(Bus bus[], Route route[], int *no_of_buses) {

}

void add_bus_route(fstream& file, Bus bus[], Route route[], int *no_of_buses) {
	system("clear");
	file.seekg(0);
	char ch;
	cout<<"Do you want to add a new bus route? (Y/N) ";
	cin>>ch;
	if(ch != 'Y' || ch != 'y')
		return ;
	cout<<"Enter the details of the bus:\n";
	cout<<"Enter the route number: ";
	cin>>bus[*no_of_buses].route_num;
	cout<<"Enter the hour when the first service of this bus starts: ";
	cin>>bus[*no_of_buses].first_serv_hour;
	cout<<"Enter that minute when the first service of this bus starts: ";
	cin>>bus[*no_of_buses].first_serv_min;
	cout<<"Enter the frequency of this bus: ";
	cin>>bus[*no_of_buses].freq;
	cout<<"Enter the places connected by this bus starting from the source upto the destination:\n";
	int i = 0;
	Route *temp;
	strcpy(route[*no_of_buses].place, bus[*no_of_buses].route_num);
	route[*no_of_buses].Next = new Route;
	Route *ptr = route[*no_of_buses].Next;
	ptr->Prev = &route[*no_of_buses];
	ptr->Next = NULL;
	ch = 'Y';
	while(ch == 'Y' || ch == 'y') {
		temp = new Route;
		cin.getline(temp->place, 30);
		bus[*no_of_buses].place_name[i++] = temp->place;
		temp->Prev = ptr;
		temp->Next = NULL;
		ptr->Next = temp;
		ptr = temp;
		cout<<"Do you want to add more bus stops? (Y/N) ";
		cin>>ch;
	}
	cout<<"Do you want to add the details of this bus to the existing database? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		file.write((char *) &bus[*no_of_buses], sizeof(Bus));
		*no_of_buses += 1;
		cout<<"Details of the bus were successfully added! Press any key to continue...";
		cin.get();
	}
	delete ptr;
	delete temp;
}

void modify_bus_route(fstream& file, Bus bus[], Route route[], int *no_of_buses) {
	system("clear");
	file.seekg(0);
	char ch;
	cout<<"Do you want to modify an existing bus route? (Y/N) ";
	cin>>ch;
	if(ch != 'Y' || ch != 'y')
		return ;
	int i, n = -1;
	char route_num[5];
	cout<<"Enter the route number of the bus whose details are to be modified: ";
	cin>>route_num;
	for(i = 0; i<*no_of_buses; i++)
		if(!strcmp(bus[i].route_num, route_num))
			n = i;
	if(n == -1) {
		cout<<"No bus with the specified route number was found\n";
		cout<<"Do you want to modify any other bus route? (Y/N) ";
		cin>>ch;
		if(ch == 'Y' || ch == 'y')
			modify_bus_route(file, bus, route, no_of_buses);
		else
			return ;
	}
	cout<<"Details of the bus:\n";
	cout<<"Route number: "<<bus[n].route_num<<endl;
	cout<<"Do you want to change this info? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y')
		cin>>bus[n].route_num;
	cout<<"Time of first service: "<<bus[n].first_serv_hour<<':'<<bus[n].first_serv_min<<endl;
	cout<<"Do you want to change this info? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		cout<<"Do you want to change the hour of first service? (Y/N) ";
		cin>>ch;
		if(ch == 'Y' || ch == 'y')
			cin>>bus[n].first_serv_hour;
		cout<<"Do you want to change the minute of first service? (Y/N) ";
		cin>>ch;
		if(ch == 'Y' || ch == 'y')
			cin>>bus[n].first_serv_min;
	}
	cout<<"Frequency of this bus: "<<bus[n].freq<<endl;
	cout<<"Do you want to change this info? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y')
		cin>>bus[n].freq;

	int option, no;
	cout<<"Places connected by this bus starting from the source upto the destination:\n";
	int size = sizeof(bus[n].place_name)/sizeof(bus[n].place_name[0]);
	for(i = 0; i<n; i++)
		cout<<i+1<<". "<<bus[n].place_name[i]<<endl;
	int mod[50];
	int del[50];
	cout<<"Bus stops can be deleted, modified or added. Please choose the one you want to do..."<<endl;
	cout<<"Do you want to delete any bus stops? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		while(1) {
			cout<<"Enter the numbers of the bus stops which are to be deleted (Type -1 when finished): ";
			for(int j = 0; ; j++) {
				cin>>no;
				if(no == -1)
					break;
				del[j] = no;
			}
		}
	}
	cout<<"Do you want to modify any bus stops? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		
	}
	cout<<"Do you want to add bus stops? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		
	}
	cout<<"Do you want to add the modified details of this bus to the existing database? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		Route *ptr = route[*no_of_buses].Next;
		i=0;
		while(ptr != NULL) {
			bus[*no_of_buses].place_name[i++] = ptr->place;									// Here problem comes as extra strings at the end which were deleted (not indexed) will also be there when writing to the file
			ptr = ptr->Next;
		}
		file.seekg((n - 1) * sizeof(Bus));
		file.write((char *) &bus[*no_of_buses], sizeof(Bus));
		no_of_buses += 1;
		cout<<"Details of the bus were successfully modified! Press any key to continue...";
		cin.get();
	}
}

void delete_bus_route(fstream& file, Bus bus[], Route route[], int *no_of_buses) {
	file.seekg(0);
}

void change_password() {
	system("clear");
	fstream f;
	f.open("Password.dat", fstream::in | fstream::app | fstream::binary);
	f.seekg(0);
	char ch, pass[20], check[20];
	if(f.eof()) {																																																				//The only error is that when the file is empty f.eof() gives 0 as output instead of 1
		cout<<"Password is not created yet... It is highly recommended to create a password! Do you want to create one now? (Y/N) ";
		cin>>ch;
		while(ch == 'Y' || ch == 'y') {
			cout<<"Create a password: ";
			cin>>pass;
			cout<<"Confirm your password: ";
			cin>>check;
			if(strcmp(pass, check) == 0) {
				cout<<"Do you want to have this as your password? (Y/N) ";
				cin>>ch;
				if(ch == 'Y' || ch == 'y') {
					f.write((char *) &pass, sizeof(char[20]));
					cout<<"The password was created successfully";
					ch = 'N';
				}
				else
					cout<<"The password wasn't created. Press any key to go back...";
					cin.get();
					return;
			}
			else {
				cout<<"The password didn't match."<<endl;
				ch = 'Y';
			}
		}
		f.close();
		cout<<"Press any key to continue...";
		cin.get();
	}
	else {
		char change_pass[20];
		f.read((char *) &pass, sizeof(char[20]));
		cout<<"Enter your current password: ";
		cin>>check;
		if(strcmp(check, pass) == 0) {
			ch = 'Y';
			while(ch == 'Y' || ch == 'y') {
				cout<<"Enter the new password: ";
				cin>>change_pass;
				cout<<"Confirm the new password: ";
				cin>>check;
				if(strcmp(change_pass, check) == 0) {
					cout<<"Do you really want to change the password? (Y/N)";
					cin>>ch;
					if(ch == 'Y' || ch == 'y') {
						f.close();
						f.open("Password.dat", fstream::out | fstream::binary);
						f.write((char *) &change_pass, sizeof(char[20]));
						cout<<"The password was successfully changed! Press any key to continue...";
						cin.get();
						ch = 'N';
						f.close();
					}
					else {
						cout<<"The password wasn't changed. Press any key to go back...'";
						cin.get();
						f.close();
						return;
					}
				}
				else {
					ch = 'Y';
					cout<<"The password didn't match"<<endl;
				}
			}	
		}
		else {
			cout<<"The password entered is wrong. Press any key to continue...";
			cin.get();
			f.close();
		}
		return;
	}
}

void menu(fstream& file, Bus bus[], Route route[], int *no_of_buses) {
	system("clear");
	cout<<"1. User\n2. Admin\nChoose an option: ";
	int option;
	cin>>option;
	if(option == 1)
		user(bus, route, no_of_buses);
	else if(option == 2)
		admin(file, bus, route, no_of_buses);
	else {
		cout<<"You have entered a wrong option. Press any key to go back... ";
		cin.get();
		menu(file, bus, route, no_of_buses);
	}
	menu(file, bus, route, no_of_buses);
}

void admin(fstream& file, Bus bus[], Route route[], int *no_of_buses) {
	ifstream fin;
	fin.open("Password.dat", fstream::in | fstream::binary);
	char pass[20], check[20];
	if(fin) {
		system("clear");
		fin.read((char *) &pass, sizeof(char [20]));
		cout<<"Enter the password to continue: ";
		cin>>check;
		if(strcmp(pass, check) != 0) {
			fin.close();
			cout<<"The password entered is wrong. Press any key to go back...";
			cin.get();
			return;
		}
	}
	fin.close();
	system("clear");
	cout<<"1. Add bus route\n2. Modify bus route\n3. Delete bus route\n4. Change password\n5. Log Out\n6. Exit\nChoose an option: ";
	int option;
	cin>>option;
	if(option == 1)
		add_bus_route(file, bus, route, no_of_buses);
	else if(option == 2)
		modify_bus_route(file, bus, route, no_of_buses);
	else if(option == 3)
		delete_bus_route(file, bus, route, no_of_buses);
	else if(option == 4) {
		change_password();
		admin(file, bus, route, no_of_buses);
	}
	else if(option == 5) {
		menu(file, bus, route, no_of_buses);
	}
	else if(option == 6) {
		cout<<"Do you really want to exit? (Y/N) ";
		char ch;
		cin>>ch;
		if(ch == 'y' || ch == 'Y')
			exit(0);
		else
			admin(file, bus, route, no_of_buses);
	}
	else {
		cout<<"You have entered a wrong option. Press any key to go back... ";
		cin.get();
		admin(file, bus, route, no_of_buses);
	}
	admin(file, bus, route, no_of_buses);
}

void user(Bus bus[], Route route[], int *no_of_buses) {
	system("clear");
	cout<<"1. List all places\n2. List bus routes\n3. Go back\nChoose an option: ";
	int option;
	cin>>option;
	if(option == 1)
		list_all_places(bus, route, no_of_buses);
	else if(option == 2)
		list_all_routes(bus, route, no_of_buses);
	else if(option == 3)
		return;
	else {
		cout<<"You have entered a wrong option. Press any key to go back... ";
		cin.get();
		user(bus, route, no_of_buses);
	}
	user(bus, route, no_of_buses);
}

int main() {
	system("clear");
	Bus bus[100];
	Route route[100];
	fstream file("Buses.dat", fstream::app | fstream::in | fstream::binary);
	file.seekg(0);
	int no_of_buses = 0;
	while(!file.eof()) {
		file.read((char*) &bus[no_of_buses++], sizeof(bus));
	}
	menu(file, bus, route, &no_of_buses);
	file.close();
	return 0;
}
