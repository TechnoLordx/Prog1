#include "Simple_window.h"
#include "Graph.h"
#include<exception>
#include "std_lib_facilities.h"

int main()
try {
    using namespace Graph_lib;

    Simple_window win{Point{100, 100},650, 350, "ch13_7"};
    Vector_ref<Rectangle> rect;

    for (int i = 0; i < 16; ++i)
    for (int j = 0; j < 16; ++j){
        rect.push_back(new Rectangle{Point{i*20,j*20},20, 20});
        rect[rect.size()-1].set_fill_color(i*16+j);
        win.attach(rect[rect.size()-1]);
    }


    win.wait_for_button();
    return 0;
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Unexpected error" << endl;
    return 2;
}
