#include <iostream>
#include <conio.h>
#include <fstream>

class Contact {
private:
    char FirstName[50], LastName[50];
    long long PhoneNumber;

public:
    void CreateContact() {
        std::cout << "Enter the first name:";
        std::cin >> FirstName;
        std::cout << "Enter the last name: ";
        std::cin >> LastName;
        std::cout << "Enter Phone Number: ";
        std::cin >> PhoneNumber;
    }

    void ShowContact() {
        std::cout << "Name: " << FirstName << " " << LastName << std::endl;
        std::cout << "Phone: " << PhoneNumber << std::endl;
    }
	
	void writeOnFile() {
		char ch;
		std::ofstream f1;
		f1.open("CMS.dat", std::ios::binary | std::ios::app);

		do {
			CreateContact();
			f1.write(reinterpret_cast<char*>(this), sizeof(*this));
			std::cout << "Would you like to add another contact?(y/n)";
			std::cin >> ch;
		} while (ch == 'y');

		std::cout << "Contact has been Sucessfully Created...";
		f1.close();
	}

	void readFromFile() {
		std::ifstream f2;
		f2.open("CMS.dat", std::ios::binary);

		std::cout << "\n================================\n";
		std::cout << "LIST OF CONTACTS";
		std::cout << "\n================================\n";

		while (!f2.eof()) {
			if (f2.read(reinterpret_cast<char*>(this), sizeof(*this)))
			{
				ShowContact();
				std::cout << "\n================================\n";
			}
		}
		f2.close();
	}

	void searchOnFile() {
		std::ifstream f3;
		long long phone;
		std::cout << "Enter phone no.: ";
		std::cin >> phone;
		f3.open("CMS.dat", std::ios::binary);

		while (!f3.eof()) {
			if (f3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (phone == PhoneNumber) {
					ShowContact();
					return;
				}
			}
		}
		std::cout << "\n\n No record found";
		f3.close();
	}

	void deleteFromFile() {
		long long num;
		int flag = 0;
		std::ofstream f4;
		std::ifstream f5;

		f5.open("CMS.dat", std::ios::binary);
		f4.open("temp.dat", std::ios::binary);

		std::cout << "Enter phone number to delete: ";
		std::cin >> num;

		while (!f5.eof()) {
			if (f5.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (PhoneNumber != num) {
					f4.write(reinterpret_cast<char*>(this), sizeof(*this));
				}
				else
					flag = 1;
			}
		}
		f5.close();
		f4.close();
		remove("CMS.dat");
		rename("temp.dat", "CMS.dat");

		flag == 1 ?
			std::cout << std::endl << std::endl << "\tContact Deleted..." :
			std::cout << std::endl << std::endl << "\tContact Not Found...";
	}

	void editContact() {
		long long num;
		std::fstream f6;

		std::cout << "Edit contact";
		std::cout << "\n===============================\n\n";
		std::cout << "Enter the phone number to be edit: ";
		std::cin >> num;

		f6.open("CMS.dat", std::ios::binary | std::ios::out | std::ios::in);

		while (!f6.eof()) {
			if (f6.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (PhoneNumber == num) {
					std::cout << "Enter new record\n";
					CreateContact();
					int pos = -1 * sizeof(*this);
					f6.seekp(pos, std::ios::cur);
					f6.write(reinterpret_cast<char*>(this), sizeof(*this));
					std::cout << std::endl << std::endl << "\t Contact Successfully Updated...";
					return;
				}
			}
		}
		std::cout << "\n\n Record not found";
		f6.close();
	}
};


int main() {
	system("cls");
	system("Color 3F"); // "Color XY", X - backgroung color, Y - text color

	std::cout << "\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO CONTACT MANAGEMENT SYSTEM *";
	_getch();

	while (1) {
		Contact c1;
		int choice;

		system("cls");
		system("Color 05");

		std::cout << "\nCONTACT MANAGEMENT SYSTEM";
		std::cout << "\n\nMAIN MENU";
		std::cout << "\n=====================\n";
		std::cout << "[1] Add a new Contact\n";
		std::cout << "[2] List all Contacts\n";
		std::cout << "[3] Search for contact\n";
		std::cout << "[4] Delete a Contact\n";
		std::cout << "[5] Edit a Contact\n";
		std::cout << "[0] Exit";
		std::cout << "\n=====================\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			system("cls");
			c1.writeOnFile();
			break;

		case 2:
			system("cls");
			c1.readFromFile();
			break;

		case 3:
			system("cls");
			c1.searchOnFile();
			break;

		case 4:
			system("cls");
			c1.deleteFromFile();
			break;

		case 5:
			system("cls");
			c1.editContact();
			break;

		case 0:
			system("cls");
			std::cout << "\n\n\n\t\t\tThank you for using CMS." << std::endl << std::endl;
			exit(0);
			break;

		default:
			continue;
		}

		int opt;
		std::cout << "\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
		std::cin >> opt;

		switch (opt) {
		case 0:
			system("cls");
			std::cout << "\n\n\n\t\t\tThank you for using CMS." << std::endl << std::endl;
			exit(0);
			break;

		default:
			continue;
		}
	}

	return 0;
}