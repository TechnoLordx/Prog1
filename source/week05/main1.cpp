#include "Simple_window.h"
#include "Graph.h"

int mina(){

	using namespace Graph_lib;

	Simple_window win{Point{100,100}, 1920, 1080, "Vector_ref"};

	Vector_ref<Rectangle> vr;

	for (int i = 0; i < 8; ++i)
	{
		vr.push_back(new Rectangle(Point{i*100, i*100}, 100, 100));
		vr[i].set_color(Color::red);
		win.attach(vr[i]);
	}
	win.wait_for_button();
	return 0;
}