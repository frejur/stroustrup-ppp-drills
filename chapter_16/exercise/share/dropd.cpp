#include "dropd.h"
#include <algorithm>

namespace {
constexpr int default_font_size{12};

const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}

const Graph_lib::Color& default_fill_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::white};
	return c;
}

const Graph_lib::Font& default_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
}
} // namespace

//------------------------------------------------------------------------------

dropd::Dropdown_option::Dropdown_option(Graph_lib::Point top_left,
                                        int width,
                                        int height,
                                        const string& label,
                                        Graph_lib::Callback callback_fn,
                                        Graph_lib::Color bg_color)
    : Shape_button::Shape_button(top_left,
                                 width,
                                 height,
                                 label,
                                 callback_fn,
                                 bg_color)
    , o_idx(0)
{
	set_alignment(shp_btn::Text_box::Alignment::Left);
}

//------------------------------------------------------------------------------

dropd::Dropdown_menu::Dropdown_menu(Graph_lib::Point top_left,
                                    int w,
                                    int h,
                                    const string& label)
    : Graph_lib::Menu(top_left, w, h, Graph_lib::Menu::Kind::vertical, label)
    , has_sel(false)
    , sel_idx(0)
    , tl(top_left)
    , col(default_color())
    , fill(default_fill_color())
    , fnt(default_font())
    , fnt_sz(default_font_size)
{}

void dropd::Dropdown_menu::add(Graph_lib::Point top_left,
                               int width,
                               int height,
                               const string& label,
                               Graph_lib::Callback cb_function)
{
	attach_ordered(new_option(top_left, width, height, label, cb_function));
}

//------------------------------------------------------------------------------

string dropd::Dropdown_menu::get_label_by_index(int idx) const
{
	return static_cast<const Dropdown_option&>(selection[valid_sel_idx(idx)])
	    .label();
}

//------------------------------------------------------------------------------

void dropd::Dropdown_menu::hide()
{
	is_shown = false;
	Graph_lib::Menu::hide();
}

void dropd::Dropdown_menu::show()
{
	is_shown = true;
	for (int i = 0; i < selection.size(); ++i) {
		if (!static_cast<Dropdown_option&>(selection[i]).is_disabled()) {
			selection[i].show();
		}
	}
}

//------------------------------------------------------------------------------

void dropd::Dropdown_menu::set_font(Graph_lib::Font f)
{
	fnt = f;
	for (int i = 0; i < selection.size(); ++i) {
		static_cast<Dropdown_option&>(selection[i]).set_font(f);
	}
}

void dropd::Dropdown_menu::set_color(Graph_lib::Color c)
{
	col = c;
	for (int i = 0; i < selection.size(); ++i) {
		static_cast<Dropdown_option&>(selection[i]).set_color(c);
	}
}

void dropd::Dropdown_menu::set_fill_color(Graph_lib::Color c)
{
	fill = c;
	for (int i = 0; i < selection.size(); ++i) {
		static_cast<Dropdown_option&>(selection[i]).set_fill_color(c);
	}
}

void dropd::Dropdown_menu::set_font_size(int s)
{
	fnt_sz = s;
	for (int i = 0; i < selection.size(); ++i) {
		static_cast<Dropdown_option&>(selection[i]).set_font_size(s);
	}
}

//------------------------------------------------------------------------------

void dropd::Dropdown_menu::attach_ordered(New_option o)
{
	static_cast<Dropdown_option*>(o.get())->set_font(font());
	static_cast<Dropdown_option*>(o.get())->set_font_size(font_size());
	static_cast<Dropdown_option*>(o.get())->set_color(color());
	static_cast<Dropdown_option*>(o.get())->set_fill_color(fill_color());
	static_cast<Dropdown_option*>(o.get())->set_ordered_index(selection.size());
	Graph_lib::Menu::attach(static_cast<Graph_lib::Button*>(o.get()));
}

//------------------------------------------------------------------------------

void dropd::Dropdown_menu::sort()
{
	// Sort options by their names, determine order the 'ordered index'
	std::vector<int> oid_v;
	for (int i = 0; i < selection.size(); ++i) {
		Dropdown_option& o{static_cast<Dropdown_option&>(selection[i])};
		oid_v.push_back(o.ordered_index());
	}

	std::sort(oid_v.begin(), oid_v.end(), [this](int oid_a, int oid_b) {
		return static_cast<Dropdown_option&>(selection[oid_a]).label()
		       < static_cast<Dropdown_option&>(selection[oid_b]).label();
	});

	for (int j = 0; j < selection.size(); ++j) {
		Dropdown_option& s{static_cast<Dropdown_option&>(selection[oid_v[j]])};
		s.set_ordered_index(j);
	}
	rearrange();
}

void dropd::Dropdown_menu::select(int idx)
{
	using DDO = Dropdown_option;

	// Put previously selected back into the dropdown list (If present)
	if (has_sel) {
		DDO& o = static_cast<DDO&>(selection[valid_sel_idx(sel_idx)]);
		o.normalize();
		o.show();
	} else {
		has_sel = true;
	}

	// Update selection, remove selected from dropdown list
	sel_idx = valid_sel_idx(idx);
	DDO& o = static_cast<DDO&>(selection[valid_sel_idx(sel_idx)]);
	o.disable();
	o.hide();
	rearrange();
}

void dropd::Dropdown_menu::rearrange()
{
	using DDO = Dropdown_option;

	// Get a list of indices for options to be included on the dropdown list
	std::vector<int> idx_v;
	for (int i = 0; i < selection.size(); ++i) {
		const DDO& o{static_cast<const DDO&>(selection[i])};
		if (!o.is_disabled()) {
			idx_v.push_back(i);
		}
	}

	// Sort the inidices from last step by their 'ordered index' attribute
	std::sort(idx_v.begin(), idx_v.end(), [this](int oid_a, int oid_b) {
		return static_cast<const DDO&>(selection[oid_a]).ordered_index()
		       < static_cast<const DDO&>(selection[oid_b]).ordered_index();
	});

	// Stack the ordered options
	for (int j = 0; j < idx_v.size(); ++j) {
		static_cast<DDO&>(selection[idx_v[j]])
		    .move(0, (tl.y + j * height) - selection[idx_v[j]].loc.y);
	}
}

//------------------------------------------------------------------------------

int dropd::Dropdown_menu::valid_sel_idx(int idx) const
{
	if (idx < 0 || idx > selection.size() - 1) {
		throw std::runtime_error("Invalid selection index");
	}
	return idx;
}
