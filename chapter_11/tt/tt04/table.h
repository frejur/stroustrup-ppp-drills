#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Person {
public:
    Person(
        string first_name = "",
        string last_name = "",
        string phone = "",
        string email = ""
    );

    void setWidth(
        std::size_t first_name_w = 0,
        std::size_t last_name_w = 0,
        std::size_t phone_w = 0,
        std::size_t email_w = 0
    );

    void printHeaders();

    friend ostream& operator<< (ostream& out, Person& p);
    friend class Table;

private:
    const string _DELIMITER{ " | "};
    const char _BAR{ '-' };
    const string _HDR_FIRST_NAME{ "First Name" };
    const string _HDR_LAST_NAME{ "Last Name" };
    const string _HDR_PHONE{ "Phone" };
    const string _HDR_EMAIL{ "Email" };
    string _first_name {};
    string _last_name {};
    string _phone {};
    string _email {};
    std::size_t _first_name_w {};
    std::size_t _last_name_w {};
    std::size_t _phone_w {};
    std::size_t _email_w {};
    bool _printHeaders{ false };
};

class Table {
public:
    Table();
    void print();
    void addPerson(
        string first_name = "",
        string last_name = "",
        string phone = "",
        string email = ""
    );
private:
    std::vector<Person> _persons {};
    std::size_t _first_name_w {};
    std::size_t _last_name_w {};
    std::size_t _phone_w {};
    std::size_t _email_w {};
    void setWidth();
};

#endif // TABLE_H
