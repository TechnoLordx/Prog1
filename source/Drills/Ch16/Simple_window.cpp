// WEEK 05 BEN VAN JEGYZET
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"

//------------------------------------------------------------------------------

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title), // hivjuk az ősosztély konstuktorát u.a paraméterekre
    next_button(Point(x_max()-70,0), 70, 20, "Next", cb_next),
    button_pushed(false)
{
    attach(next_button);
}

//------------------------------------------------------------------------------

bool Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show(); // ős fv je
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait(); 
    Fl::redraw(); 
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run(); // közvetlenűl hívjuk az fltk nak a run fv jét lehetővé teszi hogy az X is mukodjön
#endif
    return button_pushed;  

    // fordításkor ha 1 akkor a felso kód részlet kerűlbe a futtathatóba 
    // ha 0 akkor az also kód részlet
}

//------------------------------------------------------------------------------

void Simple_window::cb_next(Address, Address pw)
// call Simple_window::next() for the window located at pw
{  
    reference_to<Simple_window>(pw).next();  // egy simple_window referenciánk van aminek hivhatjuk a next tagját
}

//------------------------------------------------------------------------------

void Simple_window::next()
{
    button_pushed = true;
    hide(); // elrejti az ablakokt
}

//------------------------------------------------------------------------------