#ifndef DRILL_H
#define DRILL_H
#include <iostream>
#include <sstream>

inline void print_call(const std::string& cl_name, const std::string& fn_name)
{
	std::cout << cl_name << "::" << fn_name << '\n';
}

inline void print_call(const std::string& cl_prefix,
                       int cl_num,
                       const std::string& fn_name)
{
	std::ostringstream ss;
	ss << cl_prefix << cl_num;
	print_call(ss.str(), "pvf()");
}
//------------------------------------------------------------------------------

namespace d_1_3 {
class B1 {
public:
	void f() const { print_call("B1", "f()"); };
	virtual void vf() const { print_call("B1", "vf()"); };
};

class D1 : public B1
{
public:
	void vf() const override { print_call("D1", "vf()"); };
};
} // namespace d_1_3
//------------------------------------------------------------------------------

namespace d_4 {
class B1
{
public:
	void f() const { print_call("B1", "f()"); };
	virtual void vf() const { print_call("B1", "vf()"); };
};

class D1 : public B1
{
public:
	void f() const { print_call("D1", "f()"); };
	void vf() const override { print_call("D1", "vf()"); };
};
} // namespace d_4
//------------------------------------------------------------------------------

namespace d_5 {
class B1
{
public:
	void f() const { print_call("B1", "f()"); };
	virtual void vf() const { print_call("B1", "vf()"); };
	virtual void pvf() const = 0;
};

class D1 : public B1
{
public:
	void f() { print_call("D1", "f()"); };
	void vf() const override { print_call("D1", "vf()"); };
};
} // namespace d_5
//------------------------------------------------------------------------------

namespace d_6 {
class B1
{
public:
	void f() const { print_call("B1", "f()"); };
	virtual void vf() const { print_call("B1", "vf()"); };
	virtual void pvf() const = 0;
};

class D1 : public B1
{
public:
	void f() { print_call("D1", "f()"); };
	void vf() const override { print_call("D1", "vf()"); };
};

class D2 : public D1
{
public:
	void pvf() const override { print_call("D2", "pvf()"); };
};
} // namespace d_6
//------------------------------------------------------------------------------

namespace d_7 {
class B2
{
public:
	virtual void pvf() const = 0;
};

class D21 : public B2
{
public:
	void pvf() const override { print_call(s, "pvf()"); };

private:
	std::string s{"D21"};
};

class D22 : public B2
{
public:
	void pvf() const override { print_call("D", i, "pvf()"); };

private:
	int i{22};
};

void f(B2& o)
{
	o.pvf();
}

} // namespace d_7

#endif // DRILL_H
