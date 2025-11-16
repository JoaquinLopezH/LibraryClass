#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "Book.h"
#include "CD.h"
#include "Member.h"
#include "Loan.h"

using namespace std;

class Library {
private:
    vector<Book> books;
    vector<CD> cds;
    vector<Member> members;
    vector<Loan> loans;

    Book* findBook(const string& isbn);
    CD* findCD(const string& id);
    Member* findMember(const string& memberId);
    int countActiveLoansForMember(const string& memberId) const;
    bool isBookAvailable(const string& isbn) const;
    bool isCdAvailable(const string& id) const;
    Loan* findActiveLoan(const string& memberId, const string& isbn);

public:
    vector<Book> searchBooks(const string& query) const;
    // CD operations
    void addCD(const CD& cd);
    void listCDs() const;
    bool borrowCD(const string& memberId, const string& id, const string& borrowDate);
    bool returnCD(const string& memberId, const string& id, const string& returnDate);
    bool removeCD(const string& id);
    void addBook(const Book& book);
    void addMember(const Member& member);
    void listBooks() const;
    void listMembers() const;
    void listLoans(bool onlyActive = false) const;
    bool borrowBook(const string& memberId, const string& isbn, const string& borrowDate);
    bool returnBook(const string& memberId, const string& isbn, const string& returnDate);
    bool removeBook(const string& isbn);
    bool removeMember(const string& memberId);
};

#endif // LIBRARY_H

