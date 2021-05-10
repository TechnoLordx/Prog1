#include "Simple_window.h"
#include "Graph.h"

int main()
try{

	constexpr int xmax = 1600;
	constexpr int ymax = 600;

	Point tl {100,100};

	Simple_window win {tl, xmax, ymax, "My window"};

	Rectangle rec {Point{100,500},100,50};
	rec.set_color(Color::blue);
	win.attach(rec);

	Polygon poly; 

	poly.add(Point{300,150}); 
	poly.add(Point{400,150});
	poly.add(Point{400,350});
	poly.add(Point{300,350});

	poly.set_color(Color::red);
	win.attach(poly);
	win.set_label("ex1");
	win.wait_for_button();

	Rectangle rec1 {Point{200,400},100,30};
	Text t {Point{215,415},"Howdy!"};
	win.attach(rec1);
	win.attach(t);
	win.set_label("ex2");
	win.wait_for_button();

	Line i (Point{500,150}, Point{500,300});
	Lines z ={
		Point{600,150} , Point{750,150}, 
		Point{750,150} , Point{600,300},
		Point{600,300}, Point{750,300}
	};
	z.set_style(Line_style(Line_style::solid, 4));
	i.set_style(Line_style(Line_style::solid, 4));
	
	i.set_color(Color::red);
	z.set_color(Color::dark_cyan);
	win.attach(i);
	win.attach(z);
	win.set_label("ex3");
	win.wait_for_button();

	int line_max = 300; // 3x3 as lessz 
	int grid_size = 100;
 // white and red
	Lines grid;

	for (int x = grid_size; x <= line_max; x+=grid_size)
	{
		grid.add(Point(x,0),Point(x,line_max));
		grid.add(Point(0,x),Point(line_max,x));
	}

	win.attach(grid);

	Vector_ref<Rectangle> vr;
	int width = 100;

//  |  |  
//  |  |  
//  |  |  

	for (int i = 0; i < 3; ++i) // sor
	{
		for (int j = 0; j < 3; ++j) // oszlop
		{
			vr.push_back(new Rectangle({i*100,j*100},width,width));
			int last = vr.size()-1;

			if( last % 2 == 0)
				vr[last].set_fill_color(Color::red);
			else 
				vr[last].set_fill_color(Color::white);

			win.attach(vr[last]);
		}
	}
	
	win.set_label("ex4");
	win.wait_for_button();

	int fx = (x_max()/4)*3;
	int fy = (y_max()/3)*2;

//	Rectangle rec2 (Point{1200, 300}, 200,100);
//	rec2.set_fill_color(Color::dark_cyan);

	Rectangle frame (Point{1300, 300}, fx, fy);
	frame.set_style(Line_style(Line_style::solid, 14));
	frame.set_color(Color::red);

//	win.attach(rec2);
	win.attach(frame);
	win.set_label("ex5");
	win.wait_for_button();


	int bmax = 3840;
	int bmay = 2160;

/*	Simple_window bigwin {tl , bmax , bmay , "Big window"};

	bigwin.attach(frame);
	win.set_label("ex6");
	win.wait_for_button();
*/

	int haz_magassag = 200;
    int haz_szelesseg = 400;
    Rectangle haztest {Point{800,300},haz_szelesseg, haz_magassag};
    win.attach(haztest);


    Polygon hazteto;
    hazteto.add(Point(800,300));
    hazteto.add(Point(1000,150));
    hazteto.add(Point(1200,300));
    win.attach(hazteto);


    int ajto_magassag = 150;
    int ajto_szelesseg = 100;
    Rectangle ajto {Point {950,350}, ajto_szelesseg, ajto_magassag};
    win.attach(ajto);
    Circle kilincs {Point{1025,435}, 7};
    win.attach(kilincs);


    int window_h = 40;
    int window_w = 40;
    Rectangle ablak1_1 {Point{820,335},window_w,window_h};     win.attach(ablak1_1);
    Rectangle ablak1_2 {Point{860,335},window_w,window_h};     win.attach(ablak1_2);
    Rectangle ablak1_3 {Point{820,375},window_w,window_h};     win.attach(ablak1_3);
    Rectangle ablak1_4 {Point{860,375},window_w,window_h};     win.attach(ablak1_4);
    Rectangle ablak2_1 {Point{1100,335},window_w,window_h};    win.attach(ablak2_1);
    Rectangle ablak2_2 {Point{1100,375},window_w,window_h};    win.attach(ablak2_2);
    Rectangle ablak2_3 {Point{1140,335},window_w,window_h};    win.attach(ablak2_3);
    Rectangle ablak2_4 {Point{1140,375},window_w,window_h};    win.attach(ablak2_4);


    Rectangle kemeny {Point{1100,160}, 50, 125};
    
    win.attach(kemeny);
    win.set_label("ex7");
    win.wait_for_button();

    Circle c1 {Point{550,450},50};
    	c1.set_color(Color::blue);
    Circle c2 {Point{625,450},50};
    	c2.set_color(Color::black);
    Circle c3 {Point{700,450},50};
    	c3.set_color(Color::red);
    Circle c4 {Point{582,500},50};
    	c4.set_color(Color::yellow);
    Circle c5 {Point{668,500},50};
    	c5.set_color(Color::green);

    win.attach(c1);
    win.attach(c2);
    win.attach(c3);
    win.attach(c4);
    win.attach(c5);

    win.set_label("Olipix");
    win.wait_for_button();
    

    Image pic {Point{100,100}, "gnome.jpg"};
    win.attach(pic);
    win.set_label("My Friend <3");
    win.wait_for_button();


	return 0;

}catch(exception& e){
	cerr << "error: " << e.what() << endl;
	return 1;
}catch(...){
	cerr << "Unknown exception!\n";
	return 2;
}