#include <fstream>
#include<iostream>


class User {
public:
	std::string login, password;
	User(std::string login, std::string password) {
		this->login = login;
		this->password = password;
	}
};

class Action {
public:
	User* user[256];
	int userCount;
	bool SUB = 0;

	Action() {
		std::fstream logs;
		logs.open("logs.txt", std::fstream::app);
		std::string login, password;
		int i;
		for (i = 0; true; i++) {
			if (logs.eof()) break;
				logs >> login >> password;
				User* user = new User(login, password);
				this->user[i] = user;
		}
		this->userCount = i;
		logs.close();
	}

	void autorization() {
		std::string login, password;
		int i;
		do {
			std::cout << "Enter your login: ";
			std::cin >> login;
			if (password == "0") return;
			for (i = 0; true; i++) {
				if (i == userCount) {
					std::cout << "This login not found!\n";
					return;
				}
				else if (user[i]->login == login) break;
			}
			if (user[i]->login == login) break;
		} while (true);

		do {
			std::cout << "Enter your password: ";
			std::cin >> password;
			if (password == "0") return;
			if (user[i]->password == password) break;
			std::cout << "Incorrect password!\n";
		} while (true);

		this->SUB = 1;
	}
	void registration() {
		std::string login, password;

		do {
			std::cout << "Enter your login - ";
			std::cin >> login;
			if (login == "0") return;
			for (int i = 0; i < userCount; i++) {
				if (user[i]->login == login) {
					std::cout << "This login already exists!\n";
					return;
				}
			}
			if (login.size() >= 4) break;
		} while (true);

		do {
			std::cout << "Enter your password - ";
			std::cin >> password;
			if (password == "0") return;
			if (password.size() >= 8) break;
		} while (true);

		User* user = new User(login, password);
		this->user[userCount] = user;
		std::ofstream logs("logs.txt", std::ios::app);
		logs << this->user[userCount]->login << " " << this->user[userCount]->password << "\n";
		logs.close();
		this->userCount++;
		std::cout << "You have successfully registered!\n";
		delete(user)
	}
};

int main() {
	char userChoice;
	Action* action = new Action();


	do {
		std::cout << "Registration - 1\nAutorisation - 2\n";
		std::cin >> userChoice;
		if (userChoice == '1') action->registration();
		else if (userChoice == '2') action->autorization();
	} while (action->SUB != 1);
	delete(action);
	std::cout << "you have successfully autorization!";
	return 0;
}
