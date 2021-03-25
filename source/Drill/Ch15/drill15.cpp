
//g++ drill12.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`

#include "Simple_window.h"
#include "Graph.h"

double one(double x ) { return 1; }
double slope(double x) { return x/2; }
double square(double x) { return x*x; }
double cosinus(double x) { return cos(x); }
double sloping_cos(double x) { return cos(x)+slope(x); }

int main()
try{

constexpr int x_origo = 300;
constexpr int y_origo = 300;

constexpr int length = 400;
constexpr int notch = 20;

Simple_window win (Point{100,100},600,600, "Function graphs");

Axis x {Axis::x, Point{100, y_origo}, length, 20, "1 == 20 pixels"};
Axis y {Axis::y, Point{x_origo, length + 100}, length, 20, "1 == 20 pixels"};

x.set_color(Color::red);
y.set_color(Color::red);
//Mark m (Point{300,300}, 'x' );

win.attach(x);
win.attach(y);

constexpr int min = -10;
constexpr int max = 11;
constexpr int points = 400;

const Point origo {300,300};

constexpr int x_scale = 20;
constexpr int y_scale = 20;

Function fv1(one, min, max, origo, points,1,1);
win.attach(fv1);

Function fv2(one, min, max, origo, points, x_scale, y_scale);
win.attach(fv2);

Function fv3(slope, min, max, origo, points, x_scale, y_scale);
win.attach(fv3);

Function fv4(square, min, max, origo, points, x_scale, y_scale);
win.attach(fv4);

Function fv5(cosinus, min, max, origo, points, x_scale, y_scale);
fv5.set_color(Color::blue);
win.attach(fv5);

Function fv6(sloping_cos, min, max, origo, points, x_scale, y_scale);
win.attach(fv6);

win.wait_for_button();

return 0;

}catch(exception& e){
	cerr << "Error: " << e.what() << "\n";
	return 1;
}catch(...){
	cerr << "Something went wrong <3\n";
}

