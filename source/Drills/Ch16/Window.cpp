#include "Window.h"
#include "Graph.h"
#include "GUI.h"

namespace Graph_lib {

Window::Window(int ww, int hh, const string& title)
:Fl_Window(ww,hh,title.c_str()),w(ww),h(hh) // c string re kasztolva
{
	init();
}

Window::Window(Point xy, int ww, int hh, const string& title)
:Fl_Window(xy.x,xy.y,ww,hh,title.c_str()),w(ww),h(hh)
{ 
	init();// fltk
}

void Window::init()
{
   resizable(this); // fltk létrehozza az ablakot
   show();
} 

//---------------------------------------------------- 

void Window::draw()
{
	Fl_Window::draw(); // előjel nélküli az unsigned
	for (unsigned int i=0; i<shapes.size(); ++i) shapes[i]->draw();
}

void Window::attach(Widget& w)
{
	begin();			// FTLK: begin attaching new Fl_Wigets to this window
		w.attach(*this);	// let the Widget create its Fl_Wigits
	end();				// FTLK: stop attaching new Fl_Wigets to this window
}

void Window::detach(Widget& w)
{
	  w.hide();
}

void Window::attach(Shape& s)
{
		shapes.push_back(&s);
//		s.attached = this;
}
void Window::detach(Shape& s)
{
		for (unsigned int i = shapes.size(); i > 0; --i)	// guess last attached will be first released
			if (shapes[i-1]==&s)
				shapes.erase(shapes.begin()+(i-1));//&shapes[i-1]);  kitöröljük az utolsót
}


void Window::put_on_top(Shape& p) {
	for (int i=0; i<shapes.size(); ++i) {
		if (&p==shapes[i]) {
			for (++i; i<shapes.size(); ++i)
				shapes[i-1] = shapes[i];
			shapes[shapes.size()-1] = &p;
			return;
		}
	}
}

int gui_main() { return Fl::run(); } // hivunk kell a fltk run fv jét

} // Graph