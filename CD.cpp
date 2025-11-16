#include "CD.h"

CD::CD(string t, string a, string i, int year)
    : title(t), artist(a), id(i), releaseYear(year) {}

string CD::getId() const {
    return id;
}

string CD::getTitle() const {
    return title;
}

void CD::printInfo() const {
    cout << "Title: " << title
         << " | Artist: " << artist
         << " | ID: " << id
         << " | Year: " << releaseYear
         << endl;
}
