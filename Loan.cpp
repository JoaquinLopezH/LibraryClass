#include "Loan.h"

Loan::Loan(string i, string m, string bDate)
    : isbn(i), memberId(m), borrowDate(bDate), returnDate("") {}

string Loan::getIsbn() const {
    return isbn;
}

string Loan::getMemberId() const {
    return memberId;
}

string Loan::getBorrowDate() const {
    return borrowDate;
}

string Loan::getReturnDate() const {
    return returnDate;
}

bool Loan::isActive() const {
    return returnDate == "";
}

void Loan::setReturnDate(const string& rDate) {
    returnDate = rDate;
}

void Loan::printInfo() const {
    cout << "Loan - Item ID: " << isbn
         << " | Member ID: " << memberId
         << " | Borrowed: " << borrowDate
         << " | Returned: "
         << (returnDate == "" ? "NOT RETURNED" : returnDate)
         << endl;
}

