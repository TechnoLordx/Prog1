
#include "Simple_window.h"
#include "Graph.h"

int main(){

	using namespace Graph_lib;

	Simple_window win{Point{100,100}, 1920, 1080, "Vector_ref"};
/*
	Vector_ref<Rectangle> vr;

	for (int i = 0; i < 8; ++i)
	{
		vr.push_back(new Rectangle(Point{i*100, i*100}, 100, 100));
		vr[i].set_color(Color::red);
		vr[i].set_fill_color(Color::red);
		win.attach(vr[i]);
	}
*/ 
	Marked_polyline mpl ("prog1"); // Marks invisibl
	mpl.add(Point{100,100});
	mpl.add(Point{200,150});
	mpl.add(Point{300,100});
	mpl.add(Point{100,200});
	mpl.add(Point{300,500});
	mpl.add(Point{400,600});
	mpl.add(Point{400,800});

	Mark m (Point{300,300}, 'x' ); // tesz egy x markot 

	Image i(Point{100,100}, "space.jpg");

	win.attach(i);
	win.attach(m);
	win.attach(mpl);

	win.wait_for_button();
}