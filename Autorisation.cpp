// Autorisation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using std::string;
bool passwordLength(string userPassword);
void userInput();
bool usernameRegistrationCheck(string userChoise);
void userRegistration();
void fileOfPassword(string password);
bool passwordAutorisation(string password);
bool usernameAutorisation(string userChoise);
void userAutorisation();
void userManager();
int main()
{
    userInput();
}

void userInput() {
    int userChoise;
   
    do { 
        std::cout << "Select an action. \n1 - Registration \n2 - authorization \n3 - save logs and password \n0 - log out\n";
        std::cin >> userChoise;
        if (userChoise == 1) userRegistration();
        if (userChoise == 2) userAutorisation();
        if (userChoise == 3) userManager();
        if (userChoise == 0) return;
    } while (userChoise != 0);
    
}
void userRegistration() {
    string username, password;
    bool sub;
    std::cout << "Enter your username: ";
    do{
        std::cin >> username;
        sub = usernameRegistrationCheck(username);
        if (sub == false) std::cout << "This login is already occupied: ";
        else break;
    } while (sub != true);
    std::cout << "Enter your password: ";
    do {
        std::cin >> password;
        sub = passwordLength(password);
        if (sub == true) std::cout << "You have successfully registered!\n";
        else continue;
    } while (sub != true);
    fileOfPassword(password);

}
void userAutorisation() {
    string username, password;
    bool sub;
    std::cout << "Enter your username: ";
    do {
        std::cin >> username;
        sub = usernameAutorisation(username);
        if (sub == true) std::cout << "This login is already exists: ";
        else break;
    } while (sub != false);
    std::cout << "Enter your password: ";
    do {
        std::cin >> password;
        sub = passwordAutorisation(password);
        if (sub == false) std::cout << "You have successfully autorisation!\n";
        else {
            std::cout << "Incorrect password: ";
            continue;
        }
    } while (sub != false);
}
bool usernameAutorisation(string userChoise) {
    std::ifstream username;
    username.open("usernme.txt", std::ios_base::in);
    bool sub = true;
    string nameInFile = "";
    if (!username.is_open()) std::cout << "Critical error!";
    else {
        while (!username.eof()) {
            username >> nameInFile;
            if (nameInFile == userChoise) {
                sub = false;
            }
            else sub = true;
        }
        username.close();
        return sub;    
    }
}
bool passwordAutorisation(string password) {
    std::ifstream userPassword;
    string passwordInFile;
    bool sub;
    userPassword.open("userpassword.txt", std::ios_base::in);
    if (!userPassword.is_open()) std::cout << "Critical error!";
    else {
        while (!userPassword.eof()) {
            userPassword >> passwordInFile;
            if (passwordInFile == password) {
                sub = false;
            }
            else sub = true;
        }
        userPassword.close();
        return sub;
    }
}
bool usernameRegistrationCheck(string userChoise) {
    std::ifstream username;
    std::ofstream usernm;
    username.open("usernme.txt", std::ios_base::in);
    string nameInFile = "";
    if (!username.is_open()) std::cout << "Critical error!";
    else {
        if (username.peek() == '\n') {
            usernm.open("usernme.txt", std::ofstream::out);
            usernm << userChoise << '\n';
            usernm.close();
            return true;
        }
        else {
            username >> nameInFile;
            if (nameInFile == userChoise) {
                username.close();
                return false;
            } 
            else {
                usernm.open("usernme.txt", std::ios_base::app);
                usernm << userChoise << '\n';
                return true;
            }
        }
    }
}
bool passwordLength(string userPassword) {
    if (userPassword.length() < 4 || userPassword.length() > 12) {
        std::cout << "The password must be no shorter than 4 characters \n"
            "and no longer than 12: ";
        return false;
    }
    else return true;
}
void fileOfPassword(string password) {
    std::ofstream userPassword;
    userPassword.open("userpassword.txt", std::ios_base::app);
    userPassword << password;
    userPassword << '\n';
    userPassword.close();
    
}
void userManager() {
    std::ifstream userName, userPassword;
    std::ofstream manager;
    string userNameInFile, passwordInFile;
    userName.open("usernme.txt", std::ios_base::in);
    userPassword.open("userpassword.txt", std::ios_base::in);
    manager.open("manager.txt", std::ios_base::app);
    while (!userName.eof() || !userPassword.eof()) {
        userName >> userNameInFile;
        userPassword >> passwordInFile;
        manager << userNameInFile << " - " << passwordInFile << '\n';
    }
    userName.close();
    userPassword.close();
    manager.close();
}