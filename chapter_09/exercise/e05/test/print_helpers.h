#ifndef PRINT_HELPERS_H
#define PRINT_HELPERS_H

#include "../lib/library.h"

namespace PRINT{ //-------------------------------------------------------------

void print(const std::vector<std::string>& v);
void print(const Book& b);
void print(const std::vector<Book>& books);
void print(const std::vector<Patron>& patrons);
void print(const Patron& p);
void print(const std::vector<Fee>& fees);
void print(const std::vector<Transaction>& transactions);

} // PRINT ---------------------------------------------------------------------

#endif // PRINT_HELPERS_H
