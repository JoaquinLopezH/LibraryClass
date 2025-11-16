#ifndef CD_H
#define CD_H

#include <string>
#include <iostream>

using namespace std;

class CD {
private:
    string title;
    string artist;
    string id; // unique CD identifier (e.g., UPC)
    int releaseYear;

public:
    CD(string t, string a, string i, int year);
    string getId() const;
    string getTitle() const;
    void printInfo() const;
};

#endif // CD_H
