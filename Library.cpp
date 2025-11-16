#include "Library.h"
#include <iostream>
#include <algorithm>
#include <cctype>

#include "CD.h"

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

CD* Library::findCD(const string& id) {
    for (auto& cd : cds) {
        if (cd.getId() == id) return &cd;
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

bool Library::isCdAvailable(const string& id) const {
    for (const auto& loan : loans) {
        if (loan.getIsbn() == id && loan.isActive()) {
            return false;
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

void Library::addCD(const CD& cd) {
    cds.push_back(cd);
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

void Library::listCDs() const {
    cout << "=== CDs in library ===" << endl;
    for (const auto& cd : cds) {
        cd.printInfo();
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

bool Library::borrowCD(const string& memberId, const string& id, const string& borrowDate) {
    Member* member = findMember(memberId);
    if (!member) {
        cout << "Member not found." << endl;
        return false;
    }

    CD* cd = findCD(id);
    if (!cd) {
        cout << "CD not found." << endl;
        return false;
    }

    if (!isCdAvailable(id)) {
        cout << "CD is currently not available." << endl;
        return false;
    }

    int activeLoans = countActiveLoansForMember(memberId);
    if (activeLoans >= member->getMaxBooks()) {
        cout << "Member has reached the maximum number of active loans." << endl;
        return false;
    }

    loans.push_back(Loan(id, memberId, borrowDate));
    cout << "CD borrowed successfully." << endl;
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

bool Library::returnCD(const string& memberId, const string& id, const string& returnDate) {
    Member* member = findMember(memberId);
    if (!member) {
        cout << "Member not found." << endl;
        return false;
    }

    CD* cd = findCD(id);
    if (!cd) {
        cout << "CD not found." << endl;
        return false;
    }

    Loan* loan = findActiveLoan(memberId, id);
    if (!loan) {
        cout << "No active loan found for this member and CD." << endl;
        return false;
    }

    loan->setReturnDate(returnDate);
    cout << "CD returned successfully." << endl;
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

bool Library::removeCD(const string& id) {
    for (auto it = cds.begin(); it != cds.end(); ++it) {
        if (it->getId() == id) {
            if (!isCdAvailable(id)) {
                cout << "Cannot remove CD: it currently has an active loan." << endl;
                return false;
            }
            cds.erase(it);
            cout << "CD removed successfully." << endl;
            return true;
        }
    }
    cout << "CD not found." << endl;
    return false;
}

bool Library::removeMember(const string& memberId) {
    // Find the member using iterator so we can erase
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it->getId() == memberId) {
            // Check active loans for this member
            int active = countActiveLoansForMember(memberId);
            if (active > 0) {
                cout << "Cannot remove member: they have active loans." << endl;
                return false;
            }
            members.erase(it);
            cout << "Member removed successfully." << endl;
            return true;
        }
    }
    cout << "Member not found." << endl;
    return false;
}

// Helper to convert string to lowercase
static string toLower(const string& s) {
    string out = s;
    std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c){ return std::tolower(c); });
    return out;
}

vector<Book> Library::searchBooks(const string& query) const {
    vector<Book> results;
    if (query.empty()) return results;

    // exact ISBN match first
    for (const auto& book : books) {
        if (book.getIsbn() == query) {
            results.push_back(book);
            // continue - there could be multiple books? ISBNs are expected unique but don't assume
        }
    }

    // case-insensitive substring match on title
    string qLower = toLower(query);
    for (const auto& book : books) {
        string titleLower = toLower(book.getTitle());
        if (titleLower.find(qLower) != string::npos) {
            // avoid duplicating if exact ISBN already matched this same book
            bool already = false;
            for (const auto& r : results) {
                if (r.getIsbn() == book.getIsbn()) {
                    already = true;
                    break;
                }
            }
            if (!already) results.push_back(book);
        }
    }

    return results;
}

