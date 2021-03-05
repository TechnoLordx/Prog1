/*
    g++ main.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`
*/
#include "Simple_window.h"
#include "Graph.h"

int main()
{
	int xmax = 1000;
	int ymax = 800;
	Simple_window win {Point{100,100}, xmax, ymax, "Grid on"};

	int x_size = 800;
	int y_size = 800;
	int grid_size = 100;

	Lines grid;

	for (int x = grid_size; x <= x_size; x+=grid_size)
	{
		grid.add(Point(x,0),Point(x,y_size));
		grid.add(Point(0,x),Point(x_size,x));
	}

	win.attach(grid);

	Vector_ref<Rectangle> vr;
    for (int i = 0; i < 8; ++i)
    {
        vr.push_back(new Rectangle(Point{i*grid_size, i*grid_size}, grid_size, grid_size));
        vr[vr.size()-1].set_fill_color(Color::red); //  --> 1 --> 2 mindig ujjat készít és ezért az utolsot kell nézni mert az az újabb
        win.attach(vr[vr.size()-1]);
    }

    int kep_meret = 200;

    Image pic1{Point(600,200),"space.jpg"}; //Point(hol helyezkedjen el) x:200 y:0 
    pic1.set_mask(Point(200,0),kep_meret,kep_meret); //set mask kivág egy részt honnantól és hány pixelt | 
    win.attach(pic1);

    Image pic2{Point(0,400),"space.jpg"};
    pic2.set_mask(Point(200,0),kep_meret,kep_meret);
    win.attach(pic2);

    Image pic3{Point(400,0),"space.jpg"};
    pic3.set_mask(Point(200,0),kep_meret,kep_meret);
    win.attach(pic3);

    Image mpic{Point{0,0}, "space.jpg"};
    mpic.set_mask(Point{100,100} ,100,100);
     win.attach(mpic);

     for (int i = 0; i < 8; ++i)
         for (int j = 0; j < 8; ++j)
         {
            win.set_label("Grid");
            win.wait_for_button();
            if (j < 7 ) mpic.move(100,0);
            else mpic.move(-700,100);
        }

        win.set_label("Grid");
        win.wait_for_button();

        return 0;
    
}