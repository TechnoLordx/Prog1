/*
    g++ main.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`
*/
#include "Simple_window.h"
#include "Graph.h"

double one(double){ return 1; }

double square(double x) { return x*x; }

int main()
{
    using namespace Graph_lib;
    
    Point tl {100, 100};

    int xmax = 1280;
    int ymax = 720;

    int x_orig = xmax/2;
    int y_orig = ymax/2;

    int rmin = -11;
    int rmax = 11;

    int n_points = 400;

    Simple_window win {Point{100,100}, xmax, ymax, "Canvas"};

    Point origo {x_orig, y_orig};

    int xlength = xmax - 40;
    int ylength = ymax - 40;

    int xscal = 30, yscale = 30;

   //Simple_window win {tl, 1280, 720, "Canvas"};

   // Polygon poly;

   // poly.add(Point{640,360});
   // poly.add(Point{350,100});
   // poly.add(Point{400,200});

   // win.attahc();

    //Axis x {Axis::x, Point{20, 360}, 1240, 12,"x"};
    //Axis y {Axis::y, Point{640, 10}, 1240, 12,"y"};

    Function s (one, rmin, rmax, origo, n_points, xscal, yscale); 
    Function sq (square, rmin, rmax, origo, n_points, xscal, yscale); 

  	Function cos_func ( [] (double x) {return cos(x);} 
    						, rmin, rmax, origo, n_points, xscal, yscale);

    Axis x {Axis::x, Point{20, y_orig}, xlength, xlength/xscal,"x"};
    Axis y {Axis::y, Point{x_orig, ylength + 20}, ylength, ylength/yscale,"y"};


    Rectangle r {Point{200,200}, 100, 50};


    r.set_fill_color(Color::yellow);
    r.set_style(Line_style(Line_style::dash, 4));


    Text t {Point{200, 400}, "Hello graphics!"};


    t.set_font(Font::times_bold);
    t.set_font_size(20);


    Image ii {Point{100,100}, "badge.jpg"};

    Circle c {Point{400,400},50}; // 400,400 honnantol rajzolja ki a kőrt

    Polygon poly;

    poly.add(Point{300,200});
   	poly.add(Point{350,100});
    poly.add(Point{400,200});

    poly.set_color(Color::red);
    poly.set_color(Line_style::dash);


    Closed_polyline poly_rect;
    poly_rect.add(Point{100,50});
   	poly_rect.add(Point{200,50});
    poly_rect.add(Point{400,100});
    poly_rect.add(Point{100,100});
   	poly_rect.add(Point{50,75});

   //Ellipse e {Point{100,200}, 75, 25};
   //e.set_color(Color::dark_red);

   	Mark m {Point{100,200},'x'};

   	ostringstream oss;

   	oss << "screen size: " << x_max() << "*" << y_max() // x_max , y_max a képernyő lekérdezésére
   		<< "; Window size: " << win.x_max() << "*" << win.y_max(); 

   	Text sizes {Point{300,300},oss.str()}; // az str visszadja a fentisort 102,103

   	
 // win.attach(ii); // a háttérben van
    win.attach(t);
    win.attach(r);
    win.attach(s);
    win.attach(sq);
 	  win.attach(cos_func);
    win.attach(x);
    win.attach(y);
    win.attach(ii); // az elötérben van
    win.attach(c);

/////////////Laboron csinaltuk/////////////////////////

    win.attach(poly);
    win.attach(poly_rect);
    win.attach(m);
    win.attach(sizes);
 //   win.attach(e);

    win.wait_for_button();

}