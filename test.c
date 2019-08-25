#include <stdio.h>
#include <conio.h>

struct Route {
	char *place[30];
	struct Route *Next;
	struct Route *Previous;
}Bus_Route[50];

struct Bus {
	char route_no[5];
	int hours;
	int minutes;
	int freq;
	char route_name[50][30];
}bus[10];

void list_places(FILE *places) {
	
}

void list_routes(FILE *places) {

}

void add_bus_route(FILE *places) {

}

void modify_bus_route(FILE *places) {

}

void delete_bus_route(FILE *places) {

}

void change_password() {

}

void admin(places) {
	clrscr();
	printf("1. Add bus route\n2. Modify bus route\n3. Delete bus route\n4. Change password\n5. Log Out\n6. Exit\nChoose an option: ");
	int option;
	scanf("%d", &option);
	if(option == 1)
		add_bus_route(places);
	else if(option == 2)
		modify_bus_route(places);
	else if(option == 3)
		delete_bus_route(places);
	else if(option == 4) {
		change_password();
		admin(places);
	}
	else if(option == 5) {
		menu(places);
	}
	else if(option == 6) {
		printf("Are you really sure you want to exit? y/n");
		char ch;
		scanf("%c", &ch);
		if(ch == 'y' || ch == 'Y')
		exit(0);
		else
		admin(places);
	}
	else {
		printf("You have entered a wrong option. Press any key to continue... ");
		getch();
		admin(places);
	}	
}

void user(FILE *places) {
	clrscr();
	printf("1. List all places\n2. List bus routes\n3. Go back\nChoose an option: ");
	int option;
	scanf("%d", &option);
	if(option == 1)
		list_places(places);
	else if(option == 2)
		list_routes(places);
	else if(option == 3)
		menu(places);
	else {
		printf("You have entered a wrong option. Press any key to continue... ");
		getch();
		user(places);
	}
}

void menu(FILE *places) {
	clrscr();
	printf("1. User\n2. Admin\nChoose an option: ");
	int option;
	scanf("%d", &option);
	if(option == 1)
		user(places);
	else if(option == 2)
		admin(places);
	else {
		printf("You have entered a wrong option. Press any key to continue... ");
		getch();
		menu(places);
	}
}

int main() {
	clrscr();
	FILE *places;
	places = fopen("places.txt", "ab+");
	menu(places);
	fclose(places);
	return 0;
}
