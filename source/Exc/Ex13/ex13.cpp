/*
    g++ ex13.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`
*/
#include "Simple_window.h"
#include "Graph.h"
#include <exception>
#include "std_lib_facilities.h"

int main()
try {
    using namespace Graph_lib;

    Simple_window win{Point{100, 100}, 600, 400, "ch13-ex"};
    
    const int radius = 3;


    Box_text lline{Point{20, 350}, "Line", radius};
    Box_text llines{Point{80, 350}, "Lines", radius};
    Box_text ppolygon{Point{150, 350}, "Polygon", radius};
    Box_text aaxis{Point{240, 350}, "Axis", radius};
    Box_text rrectangle{Point{300, 350}, "Rectangle", radius};
    Box_text ttext{Point{420, 350}, "Text", radius};
    Box_text iimage{Point{480, 350}, "Image", radius};

    Box_text swind{Point{40, 150}, "Simple_window", radius};
    Box_text sshape{Point{240, 120}, "Shape", radius};
    Box_text ppoint{Point{370, 150}, "Point", radius};

    Box_text wwind{Point{70, 60}, "Window", radius};
    Box_text lstyle{Point{170, 60}, "Line_style", radius};
    Box_text ccolor{Point{350, 60}, "Color", radius};


    const int arr_size = 5;
    bool vegen = true, elejen = false;
    Arrow arr1{Point{40, 350}, Point{240, 150}, elejen, vegen, arr_size};
    Arrow arr2{Point{100, 350}, Point{250, 150}, elejen, vegen, arr_size};
    Arrow arr3{Point{180, 350}, Point{260, 150}, elejen, vegen, arr_size};
    Arrow arr4{Point{260, 350}, Point{270, 150}, elejen, vegen, arr_size};
    Arrow arr5{Point{330, 350}, Point{280, 150}, elejen, vegen, arr_size};
    Arrow arr6{Point{440, 350}, Point{290, 150}, elejen, vegen, arr_size};
    Arrow arr7{Point{510, 350}, Point{300, 150}, elejen, vegen, arr_size};
    Arrow arr8{Point{110, 150}, Point{110, 90}, elejen, vegen, arr_size};
  

    win.attach(lline); win.attach(llines);
    win.attach(ppolygon); win.attach(aaxis); win.attach(rrectangle); win.attach(ttext); win.attach(iimage);
    win.attach(swind); win.attach(sshape); win.attach(ppoint);
    win.attach(wwind); win.attach(lstyle); win.attach(ccolor);


    win.attach(arr1); win.attach(arr2); win.attach(arr3); win.attach(arr4); win.attach(arr5); win.attach(arr6); win.attach(arr7); win.attach(arr8);
    win.wait_for_button();
    return 0;
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 2;
}