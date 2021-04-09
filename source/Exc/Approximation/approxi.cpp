/*
g++ approxi.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o approxi `fltk-config --ldflags --use-images`
*/
#include "std_lib_facilities.h"
#include "Graph.h"
#include "Simple_window.h"

double fac(int n)
{
	return n > 1 ? n*(fac(n-1)) : 1;
}

double term(double x, int n) { return pow(x,n)/fac(n); }

double expe(double x, int n)
{
	double sum = 0;
	for (int i = 0; i < n; ++i) sum += term(x,i);
	return sum;

}

int num = 0;
double expN(double x) // eggyesével
{
	return expe(x,num);
}

int main()
try{
	using namespace Graph_lib;

	constexpr int width = 600;
	constexpr int height = 600;

	Simple_window win(Point{100,100}, width, height, "Approximation");

	Axis x{Axis::x, Point{30, height/2}, width-60, 18,"1 notch = 1" };
	Axis y{Axis::y, Point{width/2, height-30}, height-60, 12,"1 notch = 1" };

	x.set_color(Color::red);
	y.set_color(Color::red);

	Point orig{width/2, height/2};

	const double x_scale = 10;
	const double y_scale = 10;

	Function real_exp {exp,-5,5,orig,200,x_scale,y_scale};
	real_exp.set_color(Color::blue);

	win.attach(x);
	win.attach(y);
	win.attach(real_exp);

	for (int i = 0; i < 50; ++i)
	{
		num = i;
		Function n{expN, -25,25,orig,200,x_scale,y_scale};
		
		win.attach(n);
		win.set_label("Approximation");
		win.wait_for_button();
		win.attach(n);
	}

	return 0;
}catch(exception& e){
	cerr << e.what() << endl;
	return 1 ;
}catch(...){
	cerr << "I don't know what happend here my friend" << endl;;
	return 2;
}
