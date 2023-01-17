#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Person {
public:
    Person(
        string first_name,
        string last_name,
        string phone,
        string email
    );

    void setWidth(
        int first_name_w,
        int last_name_w,
        int phone_w,
        int email_w
    );

    friend ostream& operator<< (ostream& out, const Person& p);

private:
    string _first_name {};
    string _last_name {};
    string _phone {};
    string _email {};
    int _first_name_w {};
    int _last_name_w {};
    int _phone_w {};
    int _email_w {};
};

#endif // TABLE_H
