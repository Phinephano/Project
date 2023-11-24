#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

class Book {
public:
    char title[50];
    char author[50];
    int copies;

    Book(const char* t, const char* a, int c) : copies(c) {
        strcpy(title, t);
        strcpy(author, a);
    }

    void display() {
        cout << "Title: " << title << "\nAuthor: " << author << "\nCopies: " << copies << endl;
    }
};

class Bookstore {
private:
    static const int MAX_BOOKS;
    Book* books[100];
    int bookCount;
    char userRequests[100][50];
    int requestCount;

public:
    Bookstore() : bookCount(0), requestCount(0) {
        addBook("The Mahabharata", "Anonymous & J.A.B", 5);
        addBook("Godaan", "Premchand Munshi", 3);
        addBook("The Golden Gate", "Vikram Seth", 8);
        addBook("Sea of Poppies", "Amitav Ghosh", 3);
        addBook("The Sari Shop", "Rupa Bajwa", 3);
    }

    void addBook(const char* title, const char* author, int copies) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount++] = new Book(title, author, copies);
        }
    }

    void displayBooks() {
        clrscr();
        for (int i = 0; i < bookCount; i++) {
            books[i]->display();
            cout << "---------------------" << endl;
        }
    }

    Book* searchBook(const char* title) {
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i]->title, title) == 0) {
                return books[i];
            }
        }
        return NULL;
    }

    int requestBook(const char* title) {
        Book* book = searchBook(title);
        if (book != NULL && book->copies > 0) {
            book->copies--;
            strcpy(userRequests[requestCount], title);
            requestCount++;
            return 1;
        }
        return 0;
    }

    void updateBook(const char* title, int newCopies) {
        Book* book = searchBook(title);
        if (book != NULL) {
            book->copies = newCopies;
        }
    }

    void deleteBook(const char* title) {
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i]->title, title) == 0) {
                delete books[i];
                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }
                bookCount--;
                break;
            }
        }
    }

    void displayUserRequests() {
        clrscr();
        cout << "User Requests:" << endl;
        for (int i = 0; i < requestCount; i++) {
            cout << userRequests[i] << endl;
        }
    }

    ~Bookstore() {
        for (int i = 0; i < bookCount; i++) {
            delete books[i];
        }
    }
};

const int Bookstore::MAX_BOOKS = 100;

void displayUserMenu(Bookstore& bookstore) {
    while (1) {
        clrscr();
        cout << "User Panel Menu:" << endl;
        cout << "1. Display all books" << endl;
        cout << "2. Search for a book" << endl;
        cout << "3. Request a book" << endl;
        cout << "4. Return to Main Menu" << endl;

        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookstore.displayBooks();
                break;
            case 2: {
                cin.ignore();
                cout << "Enter book title to search: ";
                char title[50];
                cin.getline(title, sizeof(title));
                Book* foundBook = bookstore.searchBook(title);
                if (foundBook != NULL) {
                    foundBook->display();
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            }
            case 3: {
                cin.ignore();
                cout << "Enter book title to request: ";
                char title[50];
                cin.getline(title, sizeof(title));
                int x = bookstore.requestBook(title);
                if (x) {
                    cout << "Book requested successfully." << endl;
                } else {
                    cout << "Book not available or not found." << endl;
                }
                break;
            }
            case 4:
                cout << "Returning to the Main Menu." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        getch();
    }
}

void displayAdminMenu(Bookstore& bookstore) {
    while (1) {
        clrscr();
        cout << "Admin Panel Menu:" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. Update book copies" << endl;
        cout << "3. Delete a book" << endl;
        cout << "4. View User Requests" << endl;
        cout << "5. Return to Main Menu" << endl;

        int adminChoice;
        cout << "\nEnter your choice: ";
        cin >> adminChoice;
        cin.ignore();

        switch (adminChoice) {
            case 1: {
		    	char newTitle[50], newAuthor[50];
			int newCopies;
	
			cout << "Enter book title: ";
			cin.ignore(); // Ignore any residual newline character
			cin.getline(newTitle, sizeof(newTitle));

    			cout << "Enter book author: ";
    			cin.getline(newAuthor, sizeof(newAuthor));

    			cout << "Enter the number of copies: ";
    			cin >> newCopies;

    			bookstore.addBook(newTitle, newAuthor, newCopies);
    			cout << "Book added successfully." << endl;
    			break;
}

            case 2: {
                char updateTitle[50];
                int updatedCopies;
                cin.ignore();
                cout << "Enter book title to update copies: ";
                cin.get(updateTitle, sizeof(updateTitle));
                cout << "Enter the new number of copies: ";
                cin >> updatedCopies;
                bookstore.updateBook(updateTitle, updatedCopies);
                cout << "Book copies updated successfully." << endl;
                break;
            }
            case 3: {
                char deleteTitle[50];
                cin.ignore();
                cout << "Enter book title to delete: ";
                cin.get(deleteTitle, sizeof(deleteTitle));
                bookstore.deleteBook(deleteTitle);
                cout << "Book deleted successfully." << endl;
                break;
            }
            case 4:
                bookstore.displayUserRequests();
                break;
            case 5:
                cout << "Returning to the Main Menu." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        getch();
    }
}

void main() {
    Bookstore bookstore;

    while (1) {
        clrscr();
        cout << "Main Menu:" << endl;
        cout << "1. User Panel" << endl;
        cout << "2. Admin Panel" << endl;
        cout << "3. Exit" << endl;

        int mainChoice;
        cout << "\nEnter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                displayUserMenu(bookstore);
                break;
            case 2:
                displayAdminMenu(bookstore);
                break;
            case 3:
                cout << "Exiting the application." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        getch();
    }
}
