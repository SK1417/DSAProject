#include <stdio.h>
#include <conio.h>

void list_places() {
	
}

void list_routes() {}

void add_bus_route() {}

void modify_bus_route() {}

void delete_bus_route() {}

void change_password() {}

void log_out() {}

void admin() {
	clrscr();
	printf("1. Add bus route\n2. Modify bus route\n3. Delete bus route\n4. Change password\n5. Log Out\n6. Exit\nChoose an option: ");
	int option;
	scanf("%d", &option);
	if(option == 1)
		add_bus_route();
	else if(option == 2)
		modify_bus_route();
	else if(option == 3)
		delete_bus_route();
	else if(option == 4)
		change_password();
	else if(option == 5)
		log_out();
	else if(option == 6) {
		printf("Are you really sure you want to exit? y/n");
		char ch;
		scanf("%c", &ch);
		if(ch == 'y' || ch == 'Y')
		exit(0);
		else
		admin();
	}
	else {
		printf("You have entered a wrong option. Press any key to continue... ");
		getch();
		admin();
	}	
}

void user() {
	clrscr();
	printf("1. List all places\n2. List bus routes\n3. Go back\nChoose an option: ");
	int option;
	scanf("%d", &option);
	if(option == 1)
		list_places();
	else if(option == 2)
		list_routes();
	else if(option == 3)
		menu();
	else {
		printf("You have entered a wrong option. Press any key to continue... ");
		getch();
		user();
	}
}

void menu() {
	clrscr();
	printf("1. User\n2. Admin\nChoose an option: ");
	int option;
	scanf("%d", &option);
	if(option == 1)
		user();
	else if(option == 2)
		admin();
	else {
		printf("You have entered a wrong option. Press any key to continue... ");
		getch();
		menu();
	}
}

int main() {
	clrscr();
	menu();
	return 0;
}
