#include <iostream>
#include <ctime>
#include "../../util.h"
#include "./table.h"

/* Output a table using std::setw to list the following
 * info for 5 persons:
 * - First Name
 * - Last Name
 * - Phone Number
 * - Email address
 */

int main()
{
    Table t {};
    t.addPerson(
        "Michael", "Thian",
        "234 409 23", "mike1974@hotmail.com"
    );
    t.addPerson(
        "Paul", "Glucksspiel",
        "553 65 99", "paul.glucksspiel@proton.me"
    );
    t.addPerson(
        "Sven-Otto", "Lund",
        "753 655 76", "familjen.lund.dahlgren@gmail.com"
    );
    t.addPerson(
        "Mr. Caucasus", "Albertina",
        "555 476 943 99", "caucasusltd@microsoft.com"
    );
    t.addPerson(
        "Eveline", "Jacoby",
        "354 76 94 19", "evelinejacoby@gmx.net"
    );

    t.print();
    exit_on_return();
    return 0;
}
