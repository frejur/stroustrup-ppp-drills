#ifndef NODES_H
#define NODES_H
#include "../share/geo/box.h"
#include "../share/geo/box_helpers.h"

namespace ch14_e17 {

class Node : public BOX::Box
{
public:
	Node(Graph_lib::Point origin, const std::string& label, int height);
	;
	Node(Graph_lib::Point origin,
	     const std::string& label,
	     int height,
	     Graph_lib::Point tied_point);

	std::string label() const { return lb; };
	bool label_matches(const std::string& s) const { return lb == s; };

	void tie_to_point(Graph_lib::Point pt);
	void cut_tie();

	virtual void draw_lines() const override;
	bool point_is_on_node(Graph_lib::Point point) const;

	void toggle_symbol() { has_sym = !has_sym; };

protected:
	Graph_lib::Font font() const;
	int font_size() const;

private:
	bool has_tie;
	bool has_sym;
	int h;
	Graph_lib::Point tie;
	std::string lb;

	static void draw_label(Graph_lib::Point pos, const std::string& s);
	static void draw_arrow(Graph_lib::Point start,
	                       Graph_lib::Point end,
	                       int head_size);

	static void draw_arrow_head(Graph_lib::Point start,
	                            Graph_lib::Point end,
	                            int head_size);

	static void draw_symbol(Graph_lib::Point origin,
	                        int height,
	                        Graph_lib::Color bg_color,
	                        Graph_lib::Color fg_color);

	static int calc_lb_width(const std::string& s,
	                         Graph_lib::Font font,
	                         int font_size);

	// Validate, will throw e
	constexpr int valid_h(const int hh) const;
};

BOX::ConnectionPointHelper::PtID best_aligned_direction(
    const Node& node, Graph_lib::Point tied_pt);

} // namespace ch14_e17

#endif // NODES_H
