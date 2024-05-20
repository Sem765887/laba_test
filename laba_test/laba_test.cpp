#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Contact {
    int id;
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
};

std::vector<Contact> contacts;

void saveContactsToFile() {
    json j;
    for (const auto& contact : contacts) {
        json jContact;
        jContact["id"] = contact.id;
        jContact["firstName"] = contact.firstName;
        jContact["lastName"] = contact.lastName;
        jContact["phoneNumber"] = contact.phoneNumber;
        j.push_back(jContact);
    }

    std::ofstream file("contacts.json");
    file << j.dump(4);
}

void loadContactsFromFile() {
    std::ifstream file("contacts.json");
    if (file.is_open()) {
        json j;
        file >> j;
        for (const auto& jContact : j) {
            Contact contact;
            contact.id = jContact["id"];
            contact.firstName = jContact["firstName"];
            contact.lastName = jContact["lastName"];
            contact.phoneNumber = jContact["phoneNumber"];
            contacts.push_back(contact);
        }
    }
}

void viewContacts() {
    std::cout << "Ваши контакты: " << std::endl;
    std::cout << "-----------------------" << std::endl;
    for (const auto& contact : contacts) {
        std::cout << contact.id << ". " << contact.lastName << " " << contact.firstName << ": " << contact.phoneNumber << std::endl;
    }
}

bool validLastName(const std::string& lastName) {
    for (char c : lastName) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool validFirstName(const std::string& firstName) {
    for (char c : firstName) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool validPhoneNumber(const std::string& phoneNumber) {
    for (char c : phoneNumber) {
        if (!isdigit(c) && c != ' ' || phoneNumber.length() != 11) {
            return false;
        }
    }
    return true;
}


bool addContact() {
    Contact newContact;
    newContact.id = contacts.empty() ? 1 : contacts.back().id + 1;
    std::cout << "Введите фамилию: ";
    std::cin >> newContact.lastName;
    if (!validLastName(newContact.lastName)) {
        std::cout << "Некорректная Фамилия. Пожалуйста, введите только буквы." << std::endl;
        return 1;
    }
    std::cout << "Введите имя: ";
    std::cin >> newContact.firstName;
    if (!validLastName(newContact.firstName)) {
        std::cout << "Некорректное Имя. Пожалуйста, введите только буквы." << std::endl;
        return 1;
    }
    std::cout << "Введите номер телефона: ";
    std::cin >> newContact.phoneNumber;
    if (!validPhoneNumber(newContact.phoneNumber)) {
        std::cout << "Некорректный номер телефона. Пожалуйста, введите ровно 11 цифр." << std::endl;
        return 1;
    }
    contacts.push_back(newContact);
        std::cout << "-----------------------" << std::endl;
        std::cout << "Контакт успешно создан!" << std::endl;
    saveContactsToFile();
}

bool editContact(int id) {
    std::cout << "-----------------------" << std::endl;
    std::cout << "Введите ID редактируемого контакта: ";
    std::cin >> id;
    for (auto& contact : contacts) {
        if (contact.id == id) {
            std::cout << "Введите новую фамилию: ";
            std::cin >> contact.lastName;
            if (!validLastName(contact.lastName)) {
                std::cout << "Некорректная Фамилия. Пожалуйста, введите только буквы." << std::endl;
                return 1;
            }
            std::cout << "Введите новое имя: ";
            std::cin >> contact.firstName;
            if (!validLastName(contact.lastName)) {
                std::cout << "Некорректная Фамилия. Пожалуйста, введите только буквы." << std::endl;
                return 1;
            }
            std::cout << "Введите новый номер телефона: ";
            std::cin >> contact.phoneNumber;
            if (!validPhoneNumber(contact.phoneNumber)) {
                std::cout << "Некорректный номер телефона. Пожалуйста, введите ровно 11 цифр." << std::endl;
                return 1;
            }
            saveContactsToFile();
            return 1;
        }
    }
    std::cout << "-----------------------" << std::endl;
    std::cout << "Контакт с ID " << id << " не найден." << std::endl;
}

void deleteContact(int id) {
    std::cout << "Введите ID удаляемого контакта: ";
    std::cin >> id;
    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].id == id) {
            contacts.erase(contacts.begin() + i);
            for (size_t j = i; j < contacts.size(); ++j) {
                contacts[j].id--;
            }
            break;
        }
    }
    std::cout << "-----------------------" << std::endl;
    std::cout << "Контакт успешно удалён!" << std::endl;
    saveContactsToFile();
}

void searchContact(std::string phoneNumber) {
    std::cout << "Введите номер телефона контакта для поиска: ";
    std::cin >> phoneNumber;
    for (const auto& contact : contacts) {
        if (contact.phoneNumber == phoneNumber) {
            std::cout << "-----------------------" << std::endl;
            std::cout << "Найден контакт: " << contact.lastName << " " << contact.firstName << " : " << contact.phoneNumber << std::endl;
            return;
        }
    }
    std::cout << "Контакт не найден." << std::endl;
}

void sortContactLastName() {
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.lastName < b.lastName;
        });
    std::cout << "Ваши контакты: " << std::endl;
    std::cout << "-----------------------" << std::endl;
    for (const auto& contact : contacts) {
        std::cout << " " << contact.id << " " << contact.lastName << " " << contact.firstName << " " << contact.phoneNumber << std::endl;
    }
}

void sortContactID() {
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.id < b.id;
        });
    std::cout << "Ваши контакты: " << std::endl;
    std::cout << "-----------------------" << std::endl;
    for (const auto& contact : contacts) {
        std::cout << " " << contact.id << " " << contact.firstName << " " << contact.lastName << " " << contact.phoneNumber << std::endl;
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    loadContactsFromFile();
    int choice;
    int choice2;

    Contact contacts;
    do {
        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "--------------------Телефонный справочник--------------------" << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "Выберете действие: " << std::endl;
        std::cout << "1. Показать контакты" << std::endl;
        std::cout << "2. Добавить контакт" << std::endl;
        std::cout << "3. Редактировать контакт" << std::endl;
        std::cout << "4. Удалить контакт" << std::endl;
        std::cout << "5. Найти контакт" << std::endl;
        std::cout << "6. Сортировать контакты" << std::endl;
        std::cout << "7. Сохранить и выйти" << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 1:
            viewContacts();
            break;
        case 2:
            addContact();
            break;
        case 3:
            editContact(contacts.id);
            break;
        case 4:
            deleteContact(contacts.id);
            break;
        case 5:
            searchContact(contacts.phoneNumber);
            break;
        case 6:
            std::cout << "1. Сортировка по Фамилии: " << std::endl;
            std::cout << "2. Сортировка по ID: " << std::endl;
            std::cin >> choice2;
            switch (choice2) {
            case 1:
                sortContactLastName();
                break;
            case 2:
                sortContactID();
                break;
            default:
                std::cout << "Ошибочный выбор, попробуйте ещё раз.";
                }
            break;
        default:
            std::cout << "Ошибочный выбор, попробуйте ещё раз." << std::endl;
        }   
    } while (choice != 7);

    saveContactsToFile();

    return 0;
}
