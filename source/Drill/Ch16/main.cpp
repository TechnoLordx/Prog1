
//g++ main.cpp Graph.cpp Window.cpp GUI.cpp Lines_window.cpp -o main `fltk-config --ldflags --use-images`

#include "Graph.h"
#include "Lines_window.h"

int main()
{
	using namespace Graph_lib;

	Lines_window win{Point{100,100}, 1000, 900, "wHAt"};
	
	return gui_main();
}

