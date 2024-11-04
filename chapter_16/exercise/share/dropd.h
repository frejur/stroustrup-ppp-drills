#ifndef DROPDOWN_MENU_H
#define DROPDOWN_MENU_H
#include "shape_button.h"

namespace dropd {

class Dropdown_option : public shp_btn::Shape_button
{
public:
	Dropdown_option(Graph_lib::Point top_left,
	                int width,
	                int height,
	                const std::string& label,
	                Graph_lib::Callback callback_fn,
	                Graph_lib::Color bg_color);
	void set_ordered_index(int idx) { o_idx = idx; };
	int ordered_index() const { return o_idx; };

private:
	int o_idx;
};

//------------------------------------------------------------------------------

class Dropdown_menu : public Graph_lib::Menu
{
protected:
	struct New_option
	{
		New_option(Dropdown_option* o)
		    : option_ptr(o){};
		Dropdown_option* get() const { return option_ptr; };

	private:
		Dropdown_option* option_ptr;
	};

public:
	Dropdown_menu(Graph_lib::Point top_left,
	              int w,
	              int h,
	              const std::string& label);

	// The only way to add elements is to use this method in conjunction with
	// the add() method. This is a pure virtual function, and its implementation
	// needs to ensure the right type of derived class is added, e.g.
	// Derived class 'My_dropdown_menu' may want to return a New_option object
	// that contains a pointer to a 'My_dropdown_option' object.
	virtual New_option new_option(Graph_lib::Point top_left,
	                              int width,
	                              int height,
	                              const std::string& label,
	                              Graph_lib::Callback cb_function)
	    = 0;

	void add(Graph_lib::Point top_left,
	         int width,
	         int height,
	         const std::string& label,
	         Graph_lib::Callback cb_function);

	void select(int idx);
	int get_selection() const { return valid_sel_idx(sel_idx); };

	std::string get_label_by_index(int idx) const;

	void sort();

	// Visibility (Hides base class methods)
	void hide();
	void show();

	bool is_hidden() const { return !is_shown; };

	// Appearance
	void set_font(Graph_lib::Font f);
	void set_color(Graph_lib::Color c);
	void set_fill_color(Graph_lib::Color c);
	void set_font_size(int s);
	Graph_lib::Font font() const { return fnt; };
	Graph_lib::Color color() const { return col; };
	Graph_lib::Color fill_color() const { return fill; };
	int font_size() const { return fnt_sz; };

	int number_of_options() const { return selection.size(); };

protected:
	// Position according to ordered_idx and visibility
	void rearrange();
	int valid_sel_idx(int idx) const;

private:
	bool is_shown;
	bool has_sel;
	int sel_idx;
	Graph_lib::Point tl;

	// Appearance
	Graph_lib::Color col;
	Graph_lib::Color fill;
	Graph_lib::Font fnt;
	int fnt_sz;

	// Used instead of the base class attach() methods
	void attach_ordered(New_option o);

	// Hide base class methods
	int attach(Graph_lib::Button& b) = delete;
	int attach(Graph_lib::Button* p) = delete;
};

} // namespace dropd

#endif // DROPDOWN_MENU_H
