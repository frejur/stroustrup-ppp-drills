#define _USE_MATH_DEFINES
#include "e17_helpers.h"
#include <cmath>

void ch14_e17::add_node_refs(Graph_lib::Vector_ref<Node>& nodes_v,
                             std::initializer_list<Node*> nodes)
{
	for (auto n : nodes) {
		if (n != nullptr) {
			nodes_v.push_back(*n);
		}
	}
}

void ch14_e17::add_controller_refs(Graph_lib::Vector_ref<Controller>& ctrl_v,
                                   std::initializer_list<Controller*> controllers)
{
	for (auto c : controllers) {
		if (c != nullptr) {
			ctrl_v.push_back(*c);
		}
	}
}

void ch14_e17::batch_attach(Debug_window& win,
                            Graph_lib::Vector_ref<Node>& nodes)
{
	for (int i = 0; i < nodes.size(); ++i) {
		win.attach(nodes[i]);
	}
}

void ch14_e17::batch_add_node(Node_distributor& d,
                              Graph_lib::Vector_ref<Node>& nodes)
{
	for (int i = 0; i < nodes.size(); ++i) {
		d.add_node(nodes[i]);
	}
}

void ch14_e17::batch_tie_to_point(Point pt, Graph_lib::Vector_ref<Node>& nodes)
{
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i].tie_to_point(pt);
	}
}

void ch14_e17::batch_hide(Graph_lib::Vector_ref<Controller>& nodes)
{
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i].hide();
	}
}

//------------------------------------------------------------------------------

void ch14_e17::move_node_forward(Node_distributor& dist,
                                 const Graph_lib::Shape& node)
{
	Graph_lib::Point o = dist.element_origin(node);
	int w = dist.element_width(node);
	int h = dist.element_height(node);

	const Graph_lib::Shape& below{dist.element_below(node)};
	Graph_lib::Point below_o = o;
	int below_w = 0;
	int below_h = 0;
	if (!is_sentinel(below)) {
		below_o = dist.element_origin(below);
		below_w = dist.element_width(below);
		below_h = dist.element_height(below);
	}
	double a{std::atan2((o.y + h * 0.5) - dist.origin().y,
	                    (o.x + w * 0.5) - dist.origin().x)};

	int delta_x = 0;
	int delta_y = 0;
	double a_f{a / M_PI};
	if (a_f < 0.25 || a_f > 0.75) {
		int h_sp_mult = (a_f < 0.15 || a_f > 0.85) ? 3 : 1;
		if (dist.origin().x > o.x) {
			delta_x = (below_o.x - dist.horizontal_space() * h_sp_mult)
			          - (o.x + w);
		} else {
			delta_x = (below_o.x + below_w)
			          + dist.horizontal_space() * h_sp_mult - o.x;
		}
		delta_y = static_cast<int>(
		    std::round(dist.horizontal_space() + h * 0.75));
	} else {
		delta_y = h + below_h + dist.vertical_space() * 2;

		delta_x = static_cast<int>(
		    std::round((delta_y / std::sin(a)) * std::cos(a)));
	}
	dist.move_element(delta_x, delta_y, node);
}

Graph_lib::Point ch14_e17::node_center(const Node_distributor& dist,
                                       const Graph_lib::Shape& node)
{
	Graph_lib::Point o{dist.element_origin(node)};
	o.x += static_cast<int>(std::round(dist.element_width(node) * 0.5));
	o.y += static_cast<int>(std::round(dist.element_height(node) * 0.5));
	return o;
}

void ch14_e17::init_sub_tree(Graph_lib::Point tied_pt,
                             Node_distributor& sub_dist,
                             Graph_lib::Vector_ref<Node>& all_nodes)
{
	batch_tie_to_point(tied_pt, all_nodes);
	sub_dist.distribute();
	sub_dist.move(tied_pt.x - sub_dist.origin().x,
	              tied_pt.y - sub_dist.origin().y);
}

void ch14_e17::init_sub_node(const Node_distributor& dist,
                             Node& sub_node,
                             const Node& parent_node)
{
	sub_node.move(parent_node.bbox_origin().x - sub_node.bbox_origin().x,
	              parent_node.bbox_origin().y - sub_node.bbox_origin().y);
	sub_node.move(static_cast<int>(std::round(
	                  (parent_node.width() - sub_node.width()) * 0.5)),
	              parent_node.height() + dist.horizontal_space() * 4);
	sub_node.tie_to_point(node_center(dist, parent_node));
}
