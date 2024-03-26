#ifndef DSTR_H
#define DSTR_H
#include <istream>

namespace dstr{

class Dict_stream {
public:
    Dict_stream(std::istream& is) : src(is), quote_mode(false) {};
private:
    std::istream& src;
    bool quote_mode;
};

} // namespace dstr

#endif // DSTR_H
