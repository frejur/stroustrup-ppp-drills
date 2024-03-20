#ifndef PUNCT_STREAM_H
#define PUNCT_STREAM_H
#include <istream>
#include <sstream>
#include <string>

namespace pstr {

class Punct_stream
{
public:
	Punct_stream(std::istream& is, bool case_sensitive = true)
	    : src(is)
	    , sens(case_sensitive)
	    , ln_num(0){};
	void set_whitespace(const std::string& s) { ws_chars = s; };
	void add_whitespace(char c) { ws_chars.push_back(c); };
	bool is_whitespace(char c) const;
	void set_case_sensitive(bool b) { sens = b; };
	bool is_case_sensitive() const { return sens; };
	int line_number() const { return ln_num; };
	std::string line_as_string() const { return ln_str; };
	Punct_stream& operator>>(std::string& s);
	operator bool()
	{
		return !(src.fail() || src.bad()) && (buf.good() || buf.eof());
	};
	bool eol() const { return (buf.eof() && src.good()); };

	std::istream& src;
	std::istringstream buf;

private:
	std::string ws_chars;
	std::string ln_str;
	bool sens;
	int ln_num;
};

} // namespace pstr

#endif // PUNCT_STREAM_H
