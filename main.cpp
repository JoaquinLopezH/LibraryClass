#include <iostream>
#include <string>
#include "Library.h"
#include <limits>

using namespace std;

// =========================
// main - Simple menu
// =========================
int main() {
    Library library;

    // Preload some sample data
    library.addBook(Book("Clean Code", "Robert C. Martin", "1111", 2008));
    library.addBook(Book("The Pragmatic Programmer", "Andrew Hunt", "2222", 1999));
    library.addBook(Book("Design Patterns", "Gamma et al.", "3333", 1994));

    // Preload some CDs
    library.addCD(CD("Thriller", "Michael Jackson", "C111", 1982));
    library.addCD(CD("Back in Black", "AC/DC", "C222", 1980));

    library.addMember(Member("Alice", "M01", 3));
    library.addMember(Member("Bob", "M02", 5));

    int option;
    do {
        cout << "===== Library Menu =====" << endl;
        cout << "1. List books" << endl;
        cout << "2. List members" << endl;
        cout << "3. List all loans" << endl;
        cout << "4. List active loans" << endl;
        cout << "5. Borrow a book" << endl;
        cout << "6. Return a book" << endl;
    cout << "0. Exit" << endl;
    cout << "7. Search book by title or ISBN" << endl;
    cout << "8. List CDs" << endl;
    cout << "9. Borrow a CD" << endl;
    cout << "10. Return a CD" << endl;
        cout << "Select option: ";
        cin >> option;

        if (option == 1) {
            library.listBooks();
        }
        else if (option == 2) {
            library.listMembers();
        }
        else if (option == 3) {
            library.listLoans(false);
        }
        else if (option == 4) {
            library.listLoans(true);
        }
        else if (option == 5) {
            string memberId, isbn, date;
            cout << "Member ID: ";
            cin >> memberId;
            cout << "Book ISBN: ";
            cin >> isbn;
            cout << "Borrow date (YYYY-MM-DD): ";
            cin >> date;
            library.borrowBook(memberId, isbn, date);
            cout << endl;
        }
        else if (option == 6) {
            string memberId, isbn, date;
            cout << "Member ID: ";
            cin >> memberId;
            cout << "Book ISBN: ";
            cin >> isbn;
            cout << "Return date (YYYY-MM-DD): ";
            cin >> date;
            library.returnBook(memberId, isbn, date);
            cout << endl;
        }
        else if (option == 7) {
            // consume leftover newline before getline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string query;
            cout << "Enter book title (partial) or ISBN: ";
            getline(cin, query);
            auto results = library.searchBooks(query);
            if (results.empty()) {
                cout << "No books found matching '" << query << "'." << endl;
            } else {
                cout << "Found " << results.size() << " book(s):" << endl;
                for (const auto& b : results) {
                    b.printInfo();
                }
            }
            cout << endl;
        }
        else if (option == 8) {
            library.listCDs();
        }
        else if (option == 9) {
            string memberId, id, date;
            cout << "Member ID: ";
            cin >> memberId;
            cout << "CD ID: ";
            cin >> id;
            cout << "Borrow date (YYYY-MM-DD): ";
            cin >> date;
            library.borrowCD(memberId, id, date);
            cout << endl;
        }
        else if (option == 10) {
            string memberId, id, date;
            cout << "Member ID: ";
            cin >> memberId;
            cout << "CD ID: ";
            cin >> id;
            cout << "Return date (YYYY-MM-DD): ";
            cin >> date;
            library.returnCD(memberId, id, date);
            cout << endl;
        }
    } while (option != 0);

    cout << "Goodbye!" << endl;
    return 0;
}