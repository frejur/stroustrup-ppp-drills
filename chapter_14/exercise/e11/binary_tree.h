#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "../../lib/Graph.h"
#include "../share/geo/box.h"
#include <algorithm>
#include <string>

namespace ch14_e11 {

namespace {
const Graph_lib::Font& label_font()
{
	static const Graph_lib::Font& f{Graph_lib::Font::courier};
	return f;
}
constexpr int default_node_height{10};
constexpr int default_minimum_node_padding{10};
constexpr float node_label_padding_factor{0.1};
} // namespace

//------------------------------------------------------------------------------

enum class Line_type { Plain, Down_arrow, Up_arrow };

//------------------------------------------------------------------------------

class Binary_tree : public Graph_lib::Shape
{
public:
	Binary_tree(Graph_lib::Point root_position,
	            int level,
	            int node_height = default_node_height,
	            int min_node_padding = default_minimum_node_padding)
	    : lv(valid_level(level))
	    , num_nodes(std::pow(2, lv) - 1)
	    , node_h(valid_node_h(node_height))
	    , min_node_pad(valid_node_pad(min_node_padding))
	    , fnt(label_font())
	    , fnt_sz(calc_font_size(node_h))
	    , ln_t(Line_type::Plain)
	    , labels(num_nodes)
	{
		add(root_position);
	};

	virtual int node_width(int n) const = 0;
	virtual Graph_lib::Point node_position(int n) const = 0;
	virtual void move(int offset_x, int offset_y) override;
	virtual void draw_lines() const override;

	Line_type line_type(Line_type type) const { return ln_t; };
	void set_line_type(Line_type type) { ln_t = type; };

	void move_sub_tree(const int parent, int offset_x, int offset_y);
	void set_label(const std::string& address, const std::string& new_txt);

	int find_node_at_point(Graph_lib::Point pt) const;

	int address_to_index(const std::string& address) const;
	std::string index_to_address(int index) const;

	int levels() const { return lv; };
	int number_of_nodes() const { return num_nodes; };
	int node_height() const { return node_h; };
	int min_node_padding() const { return min_node_pad; };

private:
	const int lv;
	const int num_nodes;
	const int node_h;
	const int min_node_pad;
	const float lb_pad_f{node_label_padding_factor};
	const Graph_lib::Font fnt;
	const int fnt_sz;
	Line_type ln_t;

protected:
	Graph_lib::Vector_ref<Shape> nodes;
	std::vector<std::string> labels;

	Graph_lib::Font font() const { return fnt; };
	int font_size() const { return fnt_sz; };

	virtual void draw_node(int index) const = 0;
	virtual void add_node(int y, int height) = 0;
	virtual void upd_node_w(int index) = 0;
	virtual bool point_is_on_node(Graph_lib::Point pt, int index) const = 0;

	void add_nodes();
	void upd_nodes_x_pos();

	int sub_tree_min_x(int n) const;
	int sub_tree_max_x(int n) const;
	int sub_tree_width(int n) const;

	int parent_index(int index) const;
	int l_child_index(int index) const { return 2 * index + 1; };
	int r_child_index(int index) const { return 2 * index + 2; };
	int calc_font_size(int height) const;
	int calc_lb_width(const std::string& s,
	                  Graph_lib::Font font,
	                  int font_size) const;
	int label_pad() const
	{
		return static_cast<int>(std::round(node_h * lb_pad_f));
	}

	int node_level(int n) const;
	bool is_leaf_node(int n) const;
	bool index_is_valid(int i) const;
	bool is_l_child(int i) const { return (i % 2 == 1); };
	bool is_r_child(int i) const { return (i % 2 == 0) && (i); };
	bool is_lmost(int i) const;
	bool is_rmost(int i) const;

	// Validates values, will throw an exception if not valid
	int valid_index(int i) const;
	int valid_level(int l) const;
	int valid_node_h(int h) const;
	int valid_node_pad(int p) const;

	void draw_arrow(Graph_lib::Point start,
	                Graph_lib::Point end,
	                int head_size) const;
	void draw_arrow_head(Graph_lib::Point start,
	                     Graph_lib::Point end,
	                     int head_size) const;
};

//------------------------------------------------------------------------------
class Circle_binary_tree : public Binary_tree
{
public:
	Circle_binary_tree(Graph_lib::Point root_position,
	                   int level,
	                   int node_height = default_node_height,
	                   int min_node_padding = default_minimum_node_padding)
	    : Binary_tree::Binary_tree(root_position,
	                               level,
	                               node_height,
	                               min_node_padding)
	{
		add_nodes();
	}

	virtual int node_width(int n) const;
	virtual Graph_lib::Point node_position(int n) const;

protected:
	virtual void draw_node(int index) const;
	virtual void add_node(int y, int height);
	virtual void upd_node_w(int index);
	virtual bool point_is_on_node(Graph_lib::Point pt, int index) const;
};

class Box_binary_tree : public Binary_tree
{
public:
	Box_binary_tree(Graph_lib::Point root_position,
	                int level,
	                int node_height = default_node_height,
	                int min_node_padding = default_minimum_node_padding)
	    : Binary_tree::Binary_tree(root_position,
	                               level,
	                               node_height,
	                               min_node_padding)
	{
		add_nodes();
	}

	virtual int node_width(int n) const;
	virtual Graph_lib::Point node_position(int n) const;

protected:
	virtual void draw_node(int index) const;
	virtual void add_node(int y, int height);
	virtual void upd_node_w(int index);
	virtual bool point_is_on_node(Graph_lib::Point pt, int index) const;
};

} // namespace ch14_e11

#endif // BINARY_TREE_H
