#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <vector>

void swap(int& a, int& b);

void swap(std::string& a, std::string& b);

int find_element(const std::string& s,
                 const std::vector<std::string>& unsorted,
                 const std::vector<std::string>& sorted);

void clear_buffer(std::istream& is);

void keep_window_open();

#endif // HELPERS_H
