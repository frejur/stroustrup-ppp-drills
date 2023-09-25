#include "new_win.h"

New_window::New_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title)
{
}

void New_window::attach(GraphBox & w)
{
    begin();         // FTLK: begin attaching new Fl_Wigets to this window
    w.attach(*this); // let the Widget create its Fl_Wigits
    end();           // FTLK: stop attaching new Fl_Wigets to this window
}
