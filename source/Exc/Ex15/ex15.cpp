/*
	g++ ex15.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`
*/


#include "Simple_window.h"
#include "Graph.h"

double one(double x) {return 1; }
double slope(double x) {return x/2; }
double square(double x) {return x*x; }
double sloping_cos(double x) {return cos(x) + slope(x); }

double fac(int n) {return n > 1 ? n*(fac(n-1)) : 1;}

int main()
try{
	//------------------------1------------------------
	for (int i = 0; i <= 20; ++i)
	{
		cout << i << "! = " << fac(i) << endl;
	}
	//------------------------1------------------------

	int ablak_szelesseg = 800;
	int ablak_magassag = 600;

	Simple_window win{Point{100,100},
			ablak_szelesseg, ablak_magassag, "ch15_exe"};
	
	Axis x(Axis::x,Point(100,300),400,20,"1 == 20 pixels");
	Axis y(Axis::y,Point(300,500),400,20,"1 == 20 pixels");
	win.attach(x);
	win.attach(y);
	win.set_label("ch15_exe");
	win.wait_for_button();

	Fv f1(one,-10,11,Point(300,300),400, 10 ,30);

	win.attach(f1);
	win.set_label("ch15_exe");
	win.wait_for_button();


	f1.reset_xscale(20);
	f1.reset_yscale(20); 
	win.set_label("ch15_exe");
	win.wait_for_button();

	f1.reset_fct(sloping_cos); // megváltoztatja a fv -t
	f1.reset_orig(Point(350,250)); // reset origó
	win.set_label("ch15_exe");
	win.wait_for_button();

	f1.reset_range(-8,8);
	win.set_label("ch15_exe");
	win.wait_for_button();

	f1.reset_precision(8); 
	win.set_label("ch15_exe");// x > --> pontatlanabb
	win.wait_for_button();


}catch(exception& e){
	cerr << e.what() << endl;
	return 1;
}catch(...){ 
	cerr << "Van valami baj" << endl;
	return 2;
}