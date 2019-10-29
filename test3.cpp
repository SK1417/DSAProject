#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <string.h>
#include <iomanip>
using namespace std;

class node {
    public:
    char place_name[30];
    class node* next;
};
node* head = NULL;

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
	char place_name[50][30];
};

int menu(fstream &, Bus [], Route [], int *);
void insert_node(Bus bus);
int user(Bus [], int *);
int admin(fstream &, Bus [], Route [], int *);

Bus search_for_route(string route_num, Bus bus[], int *no_of_buses) {
    for(int i = 0; i < *no_of_buses; i++) {
            if(bus[i].route_num == route_num) {
                return bus[i];
                break;
            }
    }
}

bool search_for_buses(Bus bus, string place) {
    bool temp = false;
    for(int j = 0; j < bus.no_of_bus_stops; j++) {
        if(bus.place_name[j] == place)
            return true;
    }
    return temp;
}

void return_subsequent_timings(char place[], Bus bus[], int *no_of_buses, string route_num = "null") {
    time_t tt = time(0);
    tm* now = localtime(&tt);
    int curr_hour = now->tm_hour;
    int curr_min = now->tm_min;
    int curr_time = curr_hour*60 + curr_min;
    if(route_num != "null") {
        Bus specified_bus = search_for_route(route_num, bus, no_of_buses);
        int i, index_of_route = 0;
        for(i = 0; i < specified_bus.no_of_bus_stops; i++) 
            if(strcasecmp(specified_bus.place_name[i], place) == 0) {
                index_of_route = i + 1;
                break;
            }
        int first_serv_time = specified_bus.first_serv_hour*60 + specified_bus.first_serv_min;
        int next_serv_time = curr_time - (curr_time - first_serv_time) % (60 / specified_bus.freq) + (60 / specified_bus.freq) + (i * 5);
        cin.get();
        printf("The next service for bus %s at %s would be at %02d:%02d\n", specified_bus.route_num, place, (next_serv_time / 60), (next_serv_time % 60));
        cout<<"Press any key to continue...";
        cin.get();
    }
    else {
        for(int i = 0; i < *no_of_buses; i++) {
            if(search_for_buses(bus[i], place))
                return_subsequent_timings(place, bus, no_of_buses, bus[i].route_num);
        }
    }
}

void list_all_places(Bus bus[] , int *no_of_buses) {
	 node* ptr = head;
	 if(head == NULL) {
	 	cin.get();
	 	cout<<"No places are entered into the database..Press any key to continue...";
	 	cin.get(); 
	 	return;
	 }
    while(ptr->next!=NULL) {
    	  cin.get();
        cout<<ptr->place_name<<endl;
        ptr = ptr->next;
    }
    cout<<ptr->place_name<<endl;
    cout<<"Press any key to continue...";
    cin.get();
}

node* create_node(char x[]) {
    node* temp = (node*)malloc(sizeof(class node));
    strcpy(temp->place_name , x);
    temp->next = NULL;
    return temp;
}


void list_all_routes(Bus bus[], int *no_of_buses) {
	system("clear");
	if(*no_of_buses == 0) {
		cin.get();
		cout<<"The directory is empty. Press any key to continue...";
		cin.get();
		return ;
	}
	cout<<"List of bus routes: \n";
    for(int i = 0; i < *no_of_buses; i++)
        cout<<i + 1<<") "<<bus[i].route_num<<endl;
    cout<<"Enter your choice (Enter -1 to return to previous menu): ";
    int choice;
    cin>>choice;
    if(choice == -1)
        return ;
    else
    {
        cout<<endl<<"Please choose your location: \n";
        for(int i = 0; i < bus[choice - 1].no_of_bus_stops; i++) 
            cout<<i + 1<<") "<<bus[choice - 1].place_name[i]<<endl;
        int c2;
        cout<<"Enter your choice: ";
        cin>>c2;
        cout<<endl<<"Bus Details \nRoute number: "<<bus[choice - 1].route_num<<endl;
        cout<<bus[choice - 1].place_name[0]<<" to "<<bus[choice - 1].place_name[bus[choice - 1].no_of_bus_stops - 1]<<endl;
        cout<<"Frequency: Every "<<(60 / bus[choice - 1].freq)<<" minutes"<<endl;
        return_subsequent_timings(bus[choice - 1].place_name[c2 - 1], bus, no_of_buses, bus[choice - 1].route_num);
    }
}

void add_bus_route(fstream &file, Bus bus[], Route route[], int *no_of_buses) {
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
	cout<<"Enter the frequency of this bus (no. of times per hour): ";
	cin>>bus[*no_of_buses].freq;
	int i;
	cout<<"Enter the no. of places connected by this service: ";
	cin>>bus[*no_of_buses].no_of_bus_stops;
	cout<<"Enter the places connected by this bus starting from the source upto the destination:\n";
	Route *temp;
	strcpy(route[*no_of_buses].place, bus[*no_of_buses].route_num);
	route[*no_of_buses].Next = new Route;
	Route *ptr = route[*no_of_buses].Next;
	ptr->Prev = &route[*no_of_buses];
	ptr->Next = NULL;
	cin.get();
	for(i = 0; i < bus[*no_of_buses].no_of_bus_stops; i++) {
		cout<<i+1<<". ";
		temp = new Route;
		cin.getline(temp->place, 30);
		strcpy(bus[*no_of_buses].place_name[i], temp->place);
		temp->Prev = ptr;
		temp->Next = NULL;
		ptr->Next = temp;
		ptr = temp;
	}
	cout<<"Do you want to add the details of this bus to the existing database? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		file.seekg(0, fstream::end);
		file.write((char *) &bus[*no_of_buses], sizeof(Bus));
		*no_of_buses += 1;
		cin.get();
		cout<<"Details of the bus were successfully added! Press any key to continue...";
		cin.get();
		insert_node(bus[*no_of_buses-1]);
	}
	else {
		cin.get();
		cout<<"Details of the bus were not added to the database. Press any key to continue...";
		cin.get();
	}
	delete ptr;
}

void delete_bus_route(fstream &file, Bus bus[], Route route[], int *no_of_buses) {
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
				*no_of_buses -= 1;
				cin.get();
				cout<<"Details of the route number specified were deleted successfully. Press any key to continue...";
				cin.get();
				file.close();
				file.open("Buses.dat", fstream::in | fstream::out | fstream::trunc | fstream::binary);
				file.close();
				file.open("Buses.dat", fstream::in | fstream::app | fstream::binary);
				return ;
			}
			else {
				for(j = i; j < *no_of_buses - 1; j++) {
					bus[j] = bus[j + 1];
					route[j] = route[j + 1];
				}
				*no_of_buses -= 1;
				cin.get();
				cout<<"Details of the route number specified were deleted successfully. Press any key to continue...";
				cin.get();
				file.close();
				file.open("Buses.dat", fstream::in | fstream::out | fstream::trunc | fstream::binary);
				file.seekg(0);
				for(j = 0; j < *no_of_buses; j++)
					file.write((char *) &bus[j], sizeof(Bus));
				file.close();
				file.open("Buses.dat", fstream::in | fstream::app | fstream::binary);
				return ;
			}
		}
	}
	cin.get();
	cout<<"Not found in the directory! Press any key to continue...";
	cin.get();
}



void display_bus_routes(Bus bus[], int *no_of_buses) {
	system("clear");
	int i, j;
	char ch;
	if(*no_of_buses == 0) {
		cin.get();
		cout<<"The directory is empty! Press any key to continue...";
		cin.get();
		return ;
	}
	cout<<"List of bus routes in the directory (Total: "<<*no_of_buses<<"):"<<endl;
	for(i = 0; i < *no_of_buses; i++) {
		cout<<i+1<<". "<<bus[i].route_num<<endl;
	}
	cout<<"Do you want to view the details of any bus? (Y/N) ";
	cin>>ch;
	if(ch == 'Y' || ch == 'y') {
		cout<<"Enter the index of the bus to display its details: ";
		cin>>i;
		i--;
		if(i < *no_of_buses && i >= 0) {
			cout<<endl<<"Route number: ";
			cout<<bus[i].route_num<<endl;
			cout<<"Hour of first service (in 24 hours format): ";
			cout<<bus[i].first_serv_hour<<endl;
			cout<<"Minute of first service: ";
			cout<<bus[i].first_serv_min<<endl;
			cout<<"Frequency of this bus (no. of times per hour): ";
			cout<<bus[i].freq<<endl;
			cout<<"No. of places connected by this service: ";
			cout<<bus[i].no_of_bus_stops<<endl;
			cout<<"Places connected by this bus starting from the source upto the destination:\n";
			for(j = 0; j < bus[i].no_of_bus_stops; j++)
				cout<<j+1<<". "<<bus[i].place_name[j]<<endl;
		}
		else
			cout<<"You've entered the wrong number. ";
	}
	cin.get();
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
			if(strcasecmp(pass, check) == 0) {
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
		if(strcasecmp(check, pass) == 0) {
			ch = 'Y';
			while(ch == 'Y' || ch == 'y') {
				cout<<"Enter the new password: ";
				cin>>change_pass;
				cout<<"Confirm the new password: ";
				cin>>check;
				if(strcasecmp(change_pass, check) == 0) {
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

int menu(fstream &file, Bus bus[], Route route[], int *no_of_buses) {
	system("clear");
	cout<<"Menu\n1. User\n2. Admin\nChoose an option: ";
	int flag = 1;
	char option;
	cin>>option;
	if(option == '1')
		while(flag == 1)
			flag = user(bus, no_of_buses);
	else if(option == '2')
		while(flag == 1)	
			flag = admin(file, bus, route, no_of_buses);
	else {
		cin.get();
		cout<<"You have entered a wrong option. Press any key to go back... ";
		cin.get();
	}
	if(flag == -1)
		return 0;
	return 1;
}

int admin(fstream &file, Bus bus[], Route route[],  int *no_of_buses) {
	ifstream fin;
	fin.open("Password.dat", fstream::in | fstream::binary);
	char pass[20], check[20];
	if(fin) {
		system("clear");
		fin.read((char *) &pass, sizeof(char [20]));
		cout<<"Enter the password to access the Admin menu: ";
		cin>>check;
		if(strcasecmp(pass, check) != 0) {
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
		cout<<"1. Add bus route\n2. Delete bus route\n3. Display all bus routes\n4. Change password\n5. Log Out\n6. Exit\nChoose an option: ";
		char option;
		cin>>option;
		if(option == '1')
			add_bus_route(file, bus, route, no_of_buses);
		else if(option == '2')
			delete_bus_route(file, bus, route, no_of_buses);
		else if(option == '3')
			display_bus_routes(bus, no_of_buses);
		else if(option == '4')
			change_password();
		else if(option == '5') {
			return 0;
		}
		else if(option == '6') {
			cout<<"Do you really want to exit? (Y/N) ";
			char ch;
			cin>>ch;
			if(ch == 'y' || ch == 'Y')
				return -1;
			else
				return 1;
		}
		else {
			cin.get();
			cout<<"You have entered a wrong option. Press any key to go back... ";
			cin.get();
		}
	}
}

int user(Bus bus[], int *no_of_buses) {
	system("clear");
	cout<<"1. List all places\n2. List bus routes\n3. Go back\nChoose an option: ";
	char option;
	cin>>option;
	if(option == '1')
		list_all_places(bus, no_of_buses);
	else if(option == '2') {
		list_all_routes(bus, no_of_buses);
		return 1;
	}
	else if(option == '3')
		return 0;
	else {
		cin.get();
		cout<<"You have entered a wrong option. Press any key to go back... ";
		cin.get();
		return 1;
	}
}

bool find(node* head , char x[]) {
    if(head==NULL)
        return 0;
    if(strcasecmp(head->place_name , x)==0) {
        return 1;
    }
    else {
        find(head->next , x);
    }
}

void insert_node(Bus bus) {
	for(int j=0 ; j<bus.no_of_bus_stops ; j++) {
		if(head==NULL) {
			node* t = create_node(bus.place_name[j]);
			head = t;
            fstream file;
            file.open("places.dat", fstream::app | fstream::binary);
            file.write((char*)&bus.place_name, sizeof(bus.place_name));
            file.close();
		}
		else {
			if(find(head , bus.place_name[j]))
				break;
			else {
                fstream file;
                file.open("places.dat", fstream::app | fstream::binary);
                file.write((char*)&bus.place_name, sizeof(bus.place_name));
                file.close();
				node* ptr = head;
				node* n = create_node(bus.place_name[j]);
				while(ptr->next!=NULL) {
					ptr = ptr->next;
				}
				ptr->next = n;
			}
		}
	}
}

void make_linked_list() {
    fstream file2;
    head = new node;
    head->next = NULL;
    node* ptr = head;
    file2.open("places.dat", fstream::app | fstream::in | fstream::binary);
    int seek = 0, size;
    file2.seekg(0, fstream::end);
    size = file2.tellg();
    file2.seekg(0);
    while(seek!=size) {
        file2.read((char *)&ptr->place_name, sizeof(ptr->place_name));
        node* ptr2 = new node;
        ptr2->next = NULL;
        ptr->next = ptr2;
        ptr = ptr2;
        seek = file2.tellg();
    }
    file2.close();
}

int main() {
	system("clear");
	Bus bus[100];
	Route route[100];
	fstream file;
	file.open("Buses.dat", fstream::app | fstream::in | fstream::binary);
	file.seekg(0, fstream::end);
	int no_of_buses = 0, flag = 1, size = file.tellg();
	file.seekg(0);
	int seek = 0;
	while(seek != size) {
		file.read((char *) &bus[no_of_buses], sizeof(Bus));
		no_of_buses++;
		seek = file.tellg();
	}

    make_linked_list();

	while(flag == 1)
		flag = menu(file, bus, route, &no_of_buses);
	file.close();
	return 0;
}
