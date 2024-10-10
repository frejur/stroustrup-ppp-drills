#ifndef CSV_PARSER_H
#define CSV_PARSER_H
#include <functional>
#include <iostream>
#include <string>
#include <vector>

struct CSV_value
{
	std::string value;
};

class CSV_value_vector
{
public:
	void push_back(const std::string& col_name, const std::string& value);
	void clear()
	{
		cols.clear();
		vals.clear();
	};
	int as_int(const std::string& col_name) const;
	double as_double(const std::string& col_name) const;
	std::string as_string(const std::string& col_name) const
	{
		return vals[col_idx(col_name)];
	};
	int size() const { return cols.size(); };

private:
	std::vector<std::string> cols;
	std::vector<std::string> vals;
	int col_idx(const std::string& hdr) const;
};

std::istream& operator>>(std::istream& is, CSV_value& val);

class CSV_parser
{
public:
	CSV_parser(const std::string& filename);
	void perform_action_on(std::initializer_list<const std::string> column_names,
	                       std::function<void(CSV_value_vector)> action);

private:
	const std::string fname;
	std::vector<std::string> cols;
	CSV_value_vector values;
	int col_idx(const std::string& hdr) const;
};

#endif // CSV_PARSER_H
