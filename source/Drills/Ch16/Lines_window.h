#include "GUI.h"

using namespace Graph_lib;

struct Lines_window : Graph_lib::Window
{

	Lines_window(Point xy, int w, int h, const string& title);

	Open_polyline lines;
	Menu color_menu;
	Menu line_style_menu;

	Button menu_button;
	Button line_style_menu_button;


	static void cb_red(Address, Address);
	static void cb_blue(Address, Address);
	static void cb_black(Address, Address);
	static void cb_menu(Address, Address);

	static void cb_solid(Address, Address);
	static void cb_dash(Address, Address);
	static void cb_dot(Address, Address);
	static void cb_line_style_menu(Address, Address);

// pressed actions color & menu
	void red_pressed() { change(Color::red); hide_menu();}
	void blue_pressed() { change(Color::blue); hide_menu();}
	void black_pressed() { change(Color::black); hide_menu();}
	void menu_pressed() { menu_button.hide(); color_menu.show(); }

	void hide_menu() { color_menu.hide(); menu_button.show(); }
	void hide_line_style_menu() { line_style_menu.hide(); line_style_menu_button.show(); }

	void change_line_style(Line_style ls) {lines.set_style(ls); }
	void change(Color c) { lines.set_color(c); }

// pressed action style
	void solid_pressed() { change_line_style(Line_style::solid); hide_line_style_menu(); }
	void dotted_pressed() { change_line_style(Line_style::dot); hide_line_style_menu(); }
	void dash_pressed() { change_line_style(Line_style::dash); hide_line_style_menu(); }
	void line_style_menu_pressed() { line_style_menu_button.hide(); line_style_menu.show(); }

private:
	Button next_button;
	Button quit_button;

	In_box next_x;
	In_box next_y;

	Out_box xy_out;

	void next();
	void quit();
};