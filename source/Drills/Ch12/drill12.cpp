#include "Simple_window.h"
#include "Graph.h"

double one(double){ return 1; }

int main()
try{
	constexpr int xmax = 600;
	constexpr int ymax = 400;

	Point tl {100,100};

	Simple_window win {tl, xmax, ymax, "My window"};

	constexpr int x_orig = xmax/2;
    constexpr int y_orig = ymax/2;

    Point origo {x_orig, y_orig};

	constexpr int xlength = xmax - 40;
	constexpr int ylength = ymax - 40;

	int xscal = 50, yscale = 50;

	constexpr int rmin = -11;
    constexpr int rmax = 11;
    constexpr int n_points = 400;

   
	// Koordináta rendszer & lin fv
	Axis x {Axis::x, Point{20, y_orig}, xlength, xlength/xscal,"x"};
    Axis y {Axis::y, Point{x_orig, ylength + 20}, ylength, ylength/yscale,"y"};

    Function lin (one, rmin, rmax, origo, n_points, xscal, yscale); 

    x.set_color(Color::cyan);
    y.set_color(Color::white);

    win.set_label("Canvas#1");
    lin.set_color(Color::red);
    win.attach(x);
	win.attach(y);
    win.wait_for_button();
   
	win.attach(lin);

	win.set_label("Canvas#2");
    win.wait_for_button();
    

    //Poligon
    Polygon poly; 
    // a pontokat köti össze
	poly.add(Point{400,250}); 
	poly.add(Point{500,50});
	poly.add(Point{320,100});
	poly.add(Point{300,200});

	poly.set_color(Color::green);
	poly.set_style(Line_style(Line_style::dash,6));
	win.attach(poly);

	win.set_label("Canvas#3");
	win.wait_for_button();
	

	//Négyzet
	Rectangle r {Point{200,200}, 100, 50}; // top left corner, width, height
	win.attach(r);
	r.set_color(Color::yellow);

	win.set_label("Canvas#4");
	win.wait_for_button();
	

	Closed_polyline poly_rect;
	poly_rect.add(Point{50,50});
	poly_rect.add(Point{300,50});
	poly_rect.add(Point{200,150});
	poly_rect.add(Point{75,100});
	poly_rect.set_color(Color::green);
	poly_rect.set_fill_color(Color::red);
	
	win.attach(poly_rect);
	win.set_label("Canvas#5");
	win.wait_for_button();
	

	//Szöveg
	Text text {Point{100,100},"Hello world !"};
	text.set_font(Font::times_bold);
	text.set_font_size(15);
	win.attach(text);
	win.set_label("Canvas#6");
	win.wait_for_button();
	
	Image gnome {Point{450,250}, "gnome.jpg"};
	win.attach(gnome);
	win.set_label("Canvas#7");
	win.wait_for_button();

	ostringstream oss;
	oss << "screen size: " << x_max() << '*' << y_max() << "; window size: " << win.x_max() << '*' << win.y_max();
	Text sizes {Point{0,380},oss.str()};
	win.attach(sizes);
	win.set_label("Canvas#8");
	win.wait_for_button();

	return 0;

}     
catch (exception& e) {
    cerr << "error: " << e.what() << '\n'; 
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n"; 
	keep_window_open();
    return 2;
}

/*

g++ drill12.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`

*/