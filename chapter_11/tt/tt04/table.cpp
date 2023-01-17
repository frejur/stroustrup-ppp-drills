#include "table.h"

Person::Person(
    string first_name = "",
    string last_name = "",
    string phone = "",
    string email = ""
) :
    _first_name{ first_name },
    _last_name{ last_name },
    _phone{ phone },
    _email{ email }
{}

void Person::setWidth(
    int first_name_w,
    int last_name_w,
    int phone_w,
    int email_w
)
{
    _first_name_w = first_name_w;
    _last_name_w = last_name_w;
    _phone_w = phone_w;
    _email_w = email_w;
}
;
