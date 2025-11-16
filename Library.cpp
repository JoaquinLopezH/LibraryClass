#include "Library.h"
#include <iostream>

Book* Library::findBook(const string& isbn) {
    for (auto& book : books) {
        if (book.getIsbn() == isbn) {
            return &book;
        }
    }
    return nullptr;
}

Member* Library::findMember(const string& memberId) {
    for (auto& member : members) {
        if (member.getId() == memberId) {
            return &member;
        }
    }
    return nullptr;
}

int Library::countActiveLoansForMember(const string& memberId) const {
    int count = 0;
    for (const auto& loan : loans) {
        if (loan.getMemberId() == memberId && loan.isActive()) {
            count++;
        }
    }
    return count;
}

bool Library::isBookAvailable(const string& isbn) const {
    for (const auto& loan : loans) {
        if (loan.getIsbn() == isbn && loan.isActive()) {
            return false; // there is an active loan for this book
        }
    }
    return true;
}

Loan* Library::findActiveLoan(const string& memberId, const string& isbn) {
    for (auto& loan : loans) {
        if (loan.getMemberId() == memberId &&
            loan.getIsbn() == isbn &&
            loan.isActive()) {
            return &loan;
        }
    }
    return nullptr;
}

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::addMember(const Member& member) {
    members.push_back(member);
}

void Library::listBooks() const {
    cout << "=== Books in library ===" << endl;
    for (const auto& book : books) {
        book.printInfo();
    }
    cout << endl;
}

void Library::listMembers() const {
    cout << "=== Members ===" << endl;
    for (const auto& member : members) {
        member.printInfo();
    }
    cout << endl;
}

void Library::listLoans(bool onlyActive) const {
    cout << (onlyActive ? "=== Active loans ===" : "=== All loans ===") << endl;
    for (const auto& loan : loans) {
        if (onlyActive && !loan.isActive()) {
            continue;
        }
        loan.printInfo();
    }
    cout << endl;
}

bool Library::borrowBook(const string& memberId, const string& isbn, const string& borrowDate) {
    Member* member = findMember(memberId);
    if (!member) {
        cout << "Member not found." << endl;
        return false;
    }

    Book* book = findBook(isbn);
    if (!book) {
        cout << "Book not found." << endl;
        return false;
    }

    if (!isBookAvailable(isbn)) {
        cout << "Book is currently not available." << endl;
        return false;
    }

    int activeLoans = countActiveLoansForMember(memberId);
    if (activeLoans >= member->getMaxBooks()) {
        cout << "Member has reached the maximum number of active loans." << endl;
        return false;
    }

    // Create a new loan record
    loans.push_back(Loan(isbn, memberId, borrowDate));
    cout << "Book borrowed successfully." << endl;
    return true;
}

bool Library::returnBook(const string& memberId, const string& isbn, const string& returnDate) {
    Member* member = findMember(memberId);
    if (!member) {
        cout << "Member not found." << endl;
        return false;
    }

    Book* book = findBook(isbn);
    if (!book) {
        cout << "Book not found." << endl;
        return false;
    }

    Loan* loan = findActiveLoan(memberId, isbn);
    if (!loan) {
        cout << "No active loan found for this member and book." << endl;
        return false;
    }

    loan->setReturnDate(returnDate);
    cout << "Book returned successfully." << endl;
    return true;
}

bool Library::removeBook(const string& isbn) {
    // Find the book using iterator so we can erase it
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getIsbn() == isbn) {
            // Check active loans for this ISBN
            if (!isBookAvailable(isbn)) {
                cout << "Cannot remove book: it currently has an active loan." << endl;
                return false;
            }
            books.erase(it);
            cout << "Book removed successfully." << endl;
            return true;
        }
    }
    cout << "Book not found." << endl;
    return false;
}

