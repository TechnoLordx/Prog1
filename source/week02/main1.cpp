#include "Simple_window.h"
#include "Graph.h"

int main()
{
	int max_witdh = 600;
	int max_height = 400;

	Simple_window win{Point{100,100},
			max_witdh,max_height, "Graphic classes"};
	/* 
	Line l (Point{200,200}, Point{300,300});

	Lines lines = {								// ez
		Point{100,100}, Point{200,100},
		Point{150,50}, Point{150,150}
	};

	lines.add(Point{400,340}, Point{450,250});  // és ez logikailag egy objektumot alkotnak

	lines.set_color(Color::red);

	win.attach(lines);

	win.wait_for_button();
	*/
/*
	Open_polyline opl = {
		Point{100,100},  Point{150,200},
		Point{250,100}, Point{150,150}
	};
	*/
	// Closed_polyline opl
/*
	Open_polyline opl;

	opl.add(Point{100,100});
	opl.add(Point{150,200});
	opl.add(Point{250,250});
	opl.add(Point{300,200});
*/
	//Line l ( Point{100,100}, Point{200,200});
	//win.attach(l);

	/*
	Lines l {Point{100,100}, Point{200,200}, 
			Point{400,400}, Point{500,500}
			};
*/
	Rectangle r (Point{100,100}, 300, 200);
	r.set_fill_color(Color::yellow);
	win.attach(r);

	Circle c (Point{110,110},40);
	c.set_fill_color(Color::red);

	Ellipse e (Point{150,120},50, 30);
	e.set_fill_color(Color::blue);



	win.attach(c);
	win.attach(e);

//	win.attach(opl);
	win.wait_for_button();

	return 0;
}