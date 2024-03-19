#ifndef PUNCT_STREAM_H
#define PUNCT_STREAM_H
#include <istream>
#include <sstream>
#include <string>

class Punct_stream
{
public:
	Punct_stream(std::istream& is, bool case_sensitive = true)
	    : src(is)
	    , sens(case_sensitive)
	    , line(0){};
	void set_whitespace(const std::string& s) { ws_chars = s; };
	void add_whitespace(char c) { ws_chars.push_back(c); };
	void set_case_sensitive(bool b) { sens = b; };
	bool is_case_sensitive() { return sens; };
	int line_number() { return line; };
	Punct_stream& operator>>(std::string& s);
	operator bool();

private:
	std::istream& src;
	std::istringstream buf;
	std::string ws_chars;
	bool sens;
	int line;
};

#endif // PUNCT_STREAM_H
