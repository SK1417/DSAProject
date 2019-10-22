#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;

class Route {
	public:
	string place;
	Route *Next;
	Route *Prev;
};

class Bus {
	public:
	string route_num;
	int first_serv_hour;
	int first_serv_min;
	int freq;
	int no_of_bus_stops;
	string place_name[50];
};

int menu(fstream &, Bus [], Route [], int *);
int user(Bus [], Route [], int *);
int admin(fstream &, Bus [], Route [], int *);

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
	if(ch == 'N' || ch == 'n')
		return ;
	cout<<"No. of buses in the directory: "<<*no_of_buses<<endl;
	cout<<"Enter the details of the bus:\n";
	cout<<"Enter the route number: ";
	cin>>bus[*no_of_buses].route_num;
	cout<<"Enter the hour when the first service of this bus starts (in 24 hours format): ";
	cin>>bus[*no_of_buses].first_serv_hour;
	cout<<"Enter that minute when the first service of this bus starts: ";
	cin>>bus[*no_of_buses].first_serv_min;
	cout<<"Enter the frequency of this bus (in minutes): ";
	cin>>bus[*no_of_buses].freq;
	int i, no;
	cout<<"Enter the no. of places connected by this service: ";
	cin>>no;
	cout<<"Enter the places connected by this bus starting from the source upto the destination:\n";
	Route *temp;
	route[*no_of_buses].place = bus[*no_of_buses].route_num;
	route[*no_of_buses].Next = new Route;
	Route *ptr = route[*no_of_buses].Next;
	ptr->Prev = &route[*no_of_buses];
	ptr->Next = NULL;
	cin.get();
	for(i = 0; i < no; i++) {
		cout<<i+1<<". ";
		temp = new Route;
		getline(cin, temp->place);
		bus[*no_of_buses].place_name[i] = temp->place;
		temp->Prev = ptr;
		temp->Next = NULL;
		ptr->Next = temp;
		ptr = temp;
	}
	cout<<"Do you want to add the details of this bus to the existing database? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		file.write((char *) &bus[*no_of_buses], sizeof(Bus));
		*no_of_buses += 1;
		bus[*no_of_buses].no_of_bus_stops = no;
		cin.get();
		cout<<"Details of the bus were successfully added! Press any key to continue...";
		cin.get();
	}
	else {
		cin.get();
		cout<<"Details of the bus were not added to the database. Press any key to continue...";
		cin.get();
	}
	delete ptr;
}

void modify_bus_route(fstream& file, Bus bus[], Route route[], int *no_of_buses) {
	system("clear");
	file.seekg(0);
	char ch;
	cout<<"Do you want to modify an existing bus route? (Y/N) ";
	cin>>ch;
	if(ch == 'N' || ch == 'n')
		return ;
	int i, n = -1;
	string route_num;
	cout<<"Enter the route number of the bus whose details are to be modified: ";
	cin>>route_num;
	for(i = 0; i<*no_of_buses; i++)
		if(bus[i].route_num == route_num)
			n = i;
	if(n == -1) {
		cout<<"No bus with the specified route number was found\n";
		cout<<"Do you want to modify any other bus route? (Y/N) ";
		cin>>ch;
		if(ch == 'Y' || ch == 'y') {
			modify_bus_route(file, bus, route, no_of_buses);
			return ;
		}
		else
			return ;
	}
	cout<<"Details of the bus (Each detail can be changed individually or not as per requirement):\n";
	cout<<"Route number: "<<bus[n].route_num<<endl;
	cout<<"Do you want to change this info? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		cout<<"Enter the new route number: ";
		cin>>bus[n].route_num;
	}
	cout<<"Time of first service: "<<bus[n].first_serv_hour<<':'<<bus[n].first_serv_min<<endl;
	cout<<"Do you want to change this info? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		cout<<"Do you want to change the hour of first service (in 24 hours format)? (Y/N) ";
		cin>>ch;
		if(ch == 'Y' || ch == 'y') {
			cout<<"Enter the new hour of first service: ";
			cin>>bus[n].first_serv_hour;
		}
		cout<<"Do you want to change the minute of first service? (Y/N) ";
		cin>>ch;
		if(ch == 'Y' || ch == 'y') {
			cout<<"Enter the new minute of first service: ";
			cin>>bus[n].first_serv_min;
		}
	}
	cout<<"Frequency of this bus: "<<bus[n].freq<<endl;
	cout<<"Do you want to change this info? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		cout<<"Enter the new frequency of the bus (in minutes): ";
		cin>>bus[n].freq;
	}





	/*int option, no;
	cout<<"Places connected by this bus starting from the source upto the destination:\n";
	for(i = 0; i<bus[n].no_of_bus_stops; i++)
		cout<<i+1<<". "<<bus[n].place_name[i]<<endl;
	int mod[50];
	int del[50];
	cout<<"Bus stops can be deleted, modified or added. Each operation can be done successively. Please choose the one you want to do..."<<endl;
	cout<<"Do you want to delete any bus stops? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		cout<<"Enter the numbers of the bus stops which are to be deleted (Type -1 when finished): ";
		for(int j = 0; ; j++) {
			cin>>no;
			if(no == -1)
				break;
			del[j] = no;
		}
	}
	cout<<"Do you want to modify any bus stops? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		cout<<"Enter the numbers of the bus stops which are to be modified (Type -1 when finished): ";
		for(int j = 0; ; j++) {
			cin>>no;
			if(no == -1)
				break;
			mod[j] = no;
		}
	}
	cout<<"Do you want to add bus stops? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		int iter;
		cout<<"Enter the number after which a bus stop is to be added: ";
		for(int j = 0; ; j++) {
			cin>>no;
			if(no == -1)
				break;
			Route *ptr = &route[n];
			if(no <= bus[n].no_of_bus_stops) {
				iter = no + j;																																								//Have to display all the elements before adding each element
				k = iter;
				while(iter--)
					ptr = ptr->Next;
				cout<<"Enter the name of the place to be added: ";
				Route *temp = new Route;
				getline(cin, temp->place);
				temp->Next = ptr->Next;
				ptr->Next = temp;
				bus[n].no_of_bus_stops++;
			}
			cout<<"Enter the number after which a new bus stop is to be added (Enter -1 if there is no need to add): ";
		}
	}*/




	
	cout<<"Do you want to add the modified details of this bus to the existing database? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		Route *ptr = route[*no_of_buses].Next;
		i=0;
		while(ptr != NULL) {
			bus[*no_of_buses].place_name[i++] = ptr->place;
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
	system("clear");
	file.seekg(0);
	char ch;
	int i, j;
	string route_num;
	cout<<"Do you want to delete an existing bus route? (Y/N) ";
	cin>>ch;
	if(ch == 'N' || ch == 'n')
		return ;
	cout<<"Enter the route number of the bus route to be deleted: ";
	cin>>route_num;
	for(i = 0; i < *no_of_buses; i++) {
		if(bus[i].route_num == route_num) {
			if(*no_of_buses == 1) {
				*no_of_buses--;
				cout<<"Details of the route number specified were deleted successfully. Press any key to continue...";
				cin.get();
			}
			else {
				for(j = i; j < *no_of_buses - 1; j++)
				bus[j] = bus[j+1];
				cin.get();
				cout<<*no_of_buses<<"!!";
				cin.get();
				*no_of_buses -= 1;
				cout<<*no_of_buses<<"!!!";
				cin.get();
				cout<<"Details of the route number specified were deleted successfully. Press any key to continue...";
				cin.get();
			}
		}
	}
	file.close();
	file.open("Buses.dat", fstream::in | fstream::out | fstream::binary);
	for(i = 0; i < *no_of_buses; i++)
		file.write((char *) &bus[i], sizeof(Bus));
}

void display_bus_routes(Bus bus[], Route route[], int *no_of_buses) {
	system("clear");
	int i;
	if(*no_of_buses == 0) {
		cin.get();
		cout<<"The directory is empty! Press any key to continue...";
		cin.get();
		return ;
	}
	cout<<"List of bus routes in the directory:"<<" "<<*no_of_buses<<endl;
	for(i = 0; i < *no_of_buses; i++) {
		cout<<i+1<<". "<<bus[i].route_num<<endl;
	}
	cout<<"Press any key to continue...";
	cin.get();
}

void change_password() {
	system("clear");
	fstream f;
	f.open("Password.dat");
	char ch, pass[20], check[20];
	if(!f) {
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
					f.open("Password.dat", fstream::in | fstream::app | fstream::binary);
					f.seekg(0);
					f.write((char *) &pass, sizeof(char[20]));
					cin.get();
					cout<<"The password was created successfully. ";
					ch = 'N';
				}
				else {
					cin.get();
					cout<<"The password wasn't created. Press any key to go back...";
					cin.get();
					return;
				}
			}
			else {
				cin.get();
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
		f.read((char *) &pass, sizeof(char [20]));
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
					cout<<"Do you really want to change the password? (Y/N) ";
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
			cin.get();
			cout<<"The password entered is wrong. Press any key to continue...";
			cin.get();
			f.close();
		}
		return;
	}
}

int menu(fstream& file, Bus bus[], Route route[], int *no_of_buses) {
	system("clear");
	cout<<"Menu\n1. User\n2. Admin\nChoose an option: ";
	int flag = 1;
	char option;
	cin>>option;
	if(option == '1')
		while(flag == 1)
			flag = user(bus, route, no_of_buses);
	else if(option == '2')
		while(flag == 1)	
			flag = admin(file, bus, route, no_of_buses);
	else {
		cin.get();
		cout<<"You have entered a wrong option. Press any key to go back... ";
		cin.get();
	}
	return 1;
}

int admin(fstream& file, Bus bus[], Route route[], int *no_of_buses) {
	ifstream fin;
	fin.open("Password.dat", fstream::in | fstream::binary);
	char pass[20], check[20];
	if(fin) {
		system("clear");
		fin.read((char *) &pass, sizeof(char [20]));
		cout<<"Enter the password to access the Admin menu: ";
		cin>>check;
		if(strcmp(pass, check) != 0) {
			fin.close();
			cin.get();
			cout<<"The password entered is wrong. Press any key to go back...";
			cin.get();
			return 0;
		}
	}
	fin.close();
	int flag = 1;
	while(flag) {
		system("clear");
		cout<<"1. Add bus route\n2. Modify bus route\n3. Delete bus route\n4. Display all bus routes\n5. Change password\n6. Log Out\n7. Exit\nChoose an option: ";
		char option;
		cin>>option;
		if(option == '1')
			add_bus_route(file, bus, route, no_of_buses);
		else if(option == '2')
			modify_bus_route(file, bus, route, no_of_buses);
		else if(option == '3')
			delete_bus_route(file, bus, route, no_of_buses);
		else if(option == '4')
			display_bus_routes(bus, route, no_of_buses);
		else if(option == '5')
			change_password();
		else if(option == '6')
			return 0;
		else if(option == '7') {
			cout<<"Do you really want to exit? (Y/N) ";
			char ch;
			cin>>ch;
			if(ch == 'y' || ch == 'Y')
				exit(0);
		}
		else {
			cin.get();
			cout<<"You have entered a wrong option. Press any key to go back... ";
			cin.get();
		}
	}
}

int user(Bus bus[], Route route[], int *no_of_buses) {
	system("clear");
	cout<<"1. List all places\n2. List bus routes\n3. Go back\nChoose an option: ";
	char option;
	cin>>option;
	if(option == '1')
		list_all_places(bus, route, no_of_buses);
	else if(option == '2')
		list_all_routes(bus, route, no_of_buses);
	else if(option == '3')
		return 0;
	else {
		cin.get();
		cout<<"You have entered a wrong option. Press any key to go back... ";
		cin.get();
		return 1;
	}
}

int main() {
	system("clear");
	Bus bus[100];
	Route route[100];
	fstream file("Buses.dat", fstream::app | fstream::in | fstream::binary);
	file.seekg(0, fstream::end);
	int no_of_buses = 0, flag = 1, size = file.tellg();
	file.seekg(0);
	int seek = 0;
	while(seek != size) {
		file.read((char*) &bus[no_of_buses], sizeof(Bus));
		no_of_buses++;
		seek = file.tellg();
	}
	while(flag == 1)
		flag = menu(file, bus, route, &no_of_buses);
	return 0;
}
