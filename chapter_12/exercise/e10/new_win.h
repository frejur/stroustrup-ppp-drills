#ifndef NEW_WIN_H
#define NEW_WIN_H

#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "graph_box.h"
using namespace Graph_lib;

class New_window : public Graph_lib::Window {
public:
    New_window(Graph_lib::Point xy, int w, int h, const string& title );
    using Graph_lib::Window::attach;
    void attach(GraphBox & w);
};

#endif // NEW_WIN_H
