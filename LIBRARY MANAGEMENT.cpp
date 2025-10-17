#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Book {
    int bookID;
    string title;
    string author;

public:
    void addBook() {
        cout << "\nEnter Book ID: ";
        cin >> bookID;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
    }

    void showBook() const {
        cout << left << setw(10) << bookID
             << setw(30) << title
             << setw(30) << author << endl;
    }

    int getBookID() const { return bookID; }

    void saveToFile() {
        ofstream file("library.dat", ios::app | ios::binary);
        file.write((char*)this, sizeof(*this));
        file.close();
        cout << "\nBook added successfully!\n";
    }

    static void displayAll() {
        ifstream file("library.dat", ios::binary);
        Book b;
        if (!file) {
            cout << "No records found!\n";
            return;
        }

        cout << "\n" << left
             << setw(10) << "Book ID"
             << setw(30) << "Title"
             << setw(30) << "Author" << endl;
        cout << string(70, '-') << endl;

        while (file.read((char*)&b, sizeof(b))) {
            b.showBook();
        }

        file.close();
    }

    static void searchBook(int id) {
        ifstream file("library.dat", ios::binary);
        Book b;
        bool found = false;
        while (file.read((char*)&b, sizeof(b))) {
            if (b.getBookID() == id) {
                cout << "\nBook Found:\n";
                b.showBook();
                found = true;
                break;
            }
        }
        file.close();
        if (!found)
            cout << "\nBook not found!\n";
    }

    static void deleteBook(int id) {
        ifstream fin("library.dat", ios::binary);
        ofstream fout("temp.dat", ios::binary);
        Book b;
        bool found = false;

        while (fin.read((char*)&b, sizeof(b))) {
            if (b.getBookID() != id)
                fout.write((char*)&b, sizeof(b));
            else
                found = true;
        }

        fin.close();
        fout.close();

        remove("library.dat");
        rename("temp.dat", "library.dat");

        if (found)
            cout << "\nBook deleted successfully!\n";
        else
            cout << "\nBook not found!\n";
    }
};

int main() {
    int choice, id;

    while (true) {
        cout << "\n====== Library Management System ======\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        Book b;

        switch (choice) {
        case 1:
            b.addBook();
            b.saveToFile();
            break;
        case 2:
            Book::displayAll();
            break;
        case 3:
            cout << "\nEnter Book ID to search: ";
            cin >> id;
            Book::searchBook(id);
            break;
        case 4:
            cout << "\nEnter Book ID to delete: ";
            cin >> id;
            Book::deleteBook(id);
            break;
        case 5:
            cout << "\nExiting... Thank you!\n";
            return 0;
        default:
            cout << "\nInvalid choice. Try again!\n";
        }
    }
}