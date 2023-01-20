#include "table.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstddef>

Person::Person(
    string first_name,
    string last_name,
    string phone,
    string email
) :
    _first_name{ first_name },
    _last_name{ last_name },
    _phone{ phone },
    _email{ email }
{
    this->setWidth();
};

void Person::setWidth(
    std::size_t first_name_w,
    std::size_t last_name_w,
    std::size_t phone_w,
    std::size_t email_w
)
{
    _first_name_w = std::max(
        first_name_w,
        this->_HDR_FIRST_NAME.length()
    );
    _last_name_w = std::max(
        last_name_w,
        this->_HDR_LAST_NAME.length()
    );
    _phone_w = std::max(
        phone_w,
        this->_HDR_LAST_NAME.length()
    );
    _email_w = std::max(
        email_w,
        this->_HDR_EMAIL.length()
    );
}

void Person::printHeaders()
{
    this->_printHeaders = true;
}

std::ostream& operator<< (std::ostream& out, Person& p)
{
    if (p._printHeaders) {
        out << p._DELIMITER <<
            std::setw(p._first_name_w)   << p._HDR_FIRST_NAME <<
                p._DELIMITER <<
            std::setw(p._last_name_w)    << p._HDR_LAST_NAME <<
                p._DELIMITER <<
            std::setw(p._phone_w)        << p._HDR_PHONE <<
                p._DELIMITER <<
            std::setw(p._email_w)        << p._HDR_EMAIL <<
                p._DELIMITER;
        out << '\n';
        out << std::setw(
            p._DELIMITER.length() * 5 +
            p._first_name_w + p._last_name_w +
            p._phone_w + p._email_w);
        out << std::setfill(p._BAR);
        out << p._BAR;
        out << std::setfill(' ');
        p._printHeaders = false;
    } else {
        out << p._DELIMITER <<
            std::setw(p._first_name_w)   << p._first_name <<
                p._DELIMITER <<
            std::setw(p._last_name_w)    << p._last_name <<
                p._DELIMITER <<
            std::setw(p._phone_w)        << p._phone <<
                p._DELIMITER <<
            std::setw(p._email_w)        << p._email <<
                p._DELIMITER;
    }
    return out;
}

Table::Table() {};

void Table::addPerson(
    string first_name,
    string last_name,
    string phone,
    string email
)
{
    this->_persons.push_back(
        Person{ first_name, last_name, phone, email }
    );
}

void Table::setWidth()
{
    if (this->_persons.size() < 1) return;
    this->_first_name_w = (
        _persons.front()._HDR_FIRST_NAME.length()
    );
    this->_last_name_w = _persons.front()._HDR_LAST_NAME.length();
    this->_phone_w = _persons.front()._HDR_PHONE.length();
    this->_email_w = _persons.front()._HDR_EMAIL.length();

    for (Person &p: this->_persons) {
        this->_first_name_w = std::max(
            p._first_name.length(),
            this->_first_name_w
        );
        this->_last_name_w = std::max(
            p._last_name.length(),
            this->_last_name_w
        );
        this->_phone_w = std::max(
            p._phone.length(),
            this->_phone_w
        );
        this->_email_w = std::max(
            p._email.length(),
            this->_email_w
        );
    }
}

void Table::print()
{
    if (this->_persons.size() < 1) return;
    this->setWidth();

    for (Person &p : this->_persons) {
        p.setWidth(
            this->_first_name_w,
            this->_last_name_w,
            this->_phone_w,
            this->_email_w
        );
        if (&p == &this->_persons.front()) {
            p.printHeaders();
            std::cout << p << '\n';
        }
        std::cout << p << '\n';
    }
}

