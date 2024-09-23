#ifndef E17_HELPERS_H
#define E17_HELPERS_H
#include "../../lib/Debug_window.h"
#include "distr_ctrl.h"
#include "shp_distr.h"

namespace ch14_e17 {

void add_node_refs(Graph_lib::Vector_ref<Node>& nodes_v,
                   std::initializer_list<Node*> nodes);

void add_controller_refs(Graph_lib::Vector_ref<Controller>& ctrl_v,
                         std::initializer_list<Controller*> controllers);

void batch_attach(Debug_window& win, Graph_lib::Vector_ref<Node>& nodes);

void batch_add_node(ch14_e17::Node_distributor& d,
                    Graph_lib::Vector_ref<Node>& nodes);

void batch_tie_to_point(Graph_lib::Point pt, Graph_lib::Vector_ref<Node>& nodes);

void batch_hide(Graph_lib::Vector_ref<Controller>& nodes);

void move_node_forward(Node_distributor& dist, const Graph_lib::Shape& node);

Graph_lib::Point node_center(const Node_distributor& dist,
                             const Graph_lib::Shape& node);

void init_sub_tree(Graph_lib::Point tied_pt,
                   Node_distributor& sub_dist,
                   Graph_lib::Vector_ref<Node>& all_nodes);

void init_sub_node(const Node_distributor& dist,
                   Node& sub_node,
                   const Node& parent_node);

} // namespace ch14_e17

#endif // E17_HELPERS_H
