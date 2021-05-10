#include "Lines_window.h"

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window{xy, w, h, title},
    next_button{Point{x_max()-300, 0}, 150, 40, "Next point",
        [](Address, Address pw) { reference_to<Lines_window>(pw).next(); }}, 
    quit_button{Point{x_max()-150, 0}, 150, 40, "Quit",
        [](Address, Address pw) { reference_to<Lines_window>(pw).quit(); }}, 
    next_x{Point{300, 0}, 50, 40, "next x:"},
    next_y{Point{450, 0}, 50, 40, "next y:"},
    xy_out{Point{100, 0}, 100, 40, "Current (x,y):"},
    color_menu{Point{x_max()-150, 40}, 150, 40, Menu::vertical, "color"},
    menu_button{Point{x_max()-150, 40}, 150, 40, "color menu", cb_menu},
    line_style_menu{Point{x_max()-300, 40}, 150, 40, Menu::vertical, "line style"},
    line_style_menu_button{Point{x_max()-300, 40}, 150, 40, "style_menu", cb_line_style_menu}
{
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);


    color_menu.attach(new Button{Point{0, 0}, 0, 0, "red", cb_red});
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "blue", cb_blue});
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "black", cb_black});

    line_style_menu.attach(new Button{Point{0,0},0,0,"solid", cb_solid});
    line_style_menu.attach(new Button{Point{0,0},0,0,"dash", cb_dash});
    line_style_menu.attach(new Button{Point{0,0},0,0,"dot", cb_dot});

    attach(color_menu);
    attach(line_style_menu);

    color_menu.hide(); // elvan rejtve csak a gomb van ott
    line_style_menu.hide(); //u.a

    attach(menu_button); // a gombokat felcstoljuk
    attach(line_style_menu_button);

    attach(lines);
}

void Lines_window::quit()
{
    hide();
}

void Lines_window::next()
{
    int x = next_x.get_int(); // amint beirunk azt adja oda
    int y = next_y.get_int();

    lines.add(Point{x,y});

    ostringstream ss;
    ss << '(' << x << ',' << y << ')';
    xy_out.put(ss.str());

    redraw(); // rajzol
}

void Lines_window::cb_red(Address, Address pw)
{
    reference_to<Lines_window>(pw).red_pressed(); 
}

void Lines_window::cb_blue(Address, Address pw)
{
    reference_to<Lines_window>(pw).blue_pressed();
}

void Lines_window::cb_black(Address, Address pw)
{
    reference_to<Lines_window>(pw).black_pressed();
}

void Lines_window::cb_menu(Address, Address pw)
{
    reference_to<Lines_window>(pw).menu_pressed();
}

void Lines_window::cb_solid(Address, Address pw)
{
    reference_to<Lines_window>(pw).solid_pressed();
}

void Lines_window::cb_dash(Address, Address pw)
{
    reference_to<Lines_window>(pw).dash_pressed();
}

void Lines_window::cb_dot(Address, Address pw)
{
    reference_to<Lines_window>(pw).dotted_pressed();
}

void Lines_window::cb_line_style_menu(Address, Address pw)
{
    reference_to<Lines_window>(pw).line_style_menu_pressed();
}