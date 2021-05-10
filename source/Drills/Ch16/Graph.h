#ifndef GRAPH_GUARD
#define GRAPH_GUARD

#include "Point.h"
#include <vector>
#include "fltk.h"
#include "std_lib_facilities.h"

namespace Graph_lib {

#undef major
#undef minor

bool intersect(Point p1, Point p2, Point p3, Point p4);
////oran néztuk/////////////
struct Color {
	enum Color_type { // enum felsoruljuk a szineket | fultik library -s FL_***
		red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
		yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
		magenta=FL_MAGENTA, cyan=FL_CYAN, dark_red=FL_DARK_RED,
		dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
		dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN
	};
	enum Transparency { invisible = 0, visible = 255 };
												//láthatóvá tesszük
	Color(Color_type cc): c(Fl_Color(cc)), v(visible) {} // konstruktorok
	Color(Color_type cc, Transparency vv): c(Fl_Color(cc)), v(vv) {}
	Color(int cc): c(Fl_Color(cc)), v(visible) {}
	Color(Transparency vv): c(Fl_Color()), v(vv) {} //csak a láthatóságot állítjuk be
													// ezzek segítségével tudjuk elkészíteni az objektumot és példényosítani
	int as_int() const { return c; }				// getter fv vissza adjuk a szint
	char visibility() const { return v; }			// getter fv 
	void set_visibility(Transparency vv) { v = vv; } // setter visiviliti -t

private:
	unsigned char v;
	Fl_Color c;
};
/////oran nztuk//////////
struct Line_style {
	enum Line_style_type {
		solid=FL_SOLID,				// -------
		dash=FL_DASH,				// - - - -
		dot=FL_DOT,					// ....... 
		dashdot=FL_DASHDOT,			// - . - . 
		dashdotdot=FL_DASHDOTDOT	// -..-..
	};

	Line_style(Line_style_type ss): s(ss), w(0) { } // w vonal vastagság | hany pixel vastagság legyen
	Line_style(Line_style_type ss, int ww): s(ss), w(ww) { }
	Line_style(int ss): s(ss), w(0) { }

	int width() const { return w; }  // getter fv
	int style() const { return s; }  // getter fv
private:
	int s;
	int w;
};
/////oran ////////
class Font {
	int f; // magunk által készített változótípus
public:    // az enum egy lista, konkrét értékekkel, amik olyanok mint az intek, és switch case-nél hasznos tud lenni pl 
	enum Font_type {
		helvetica=FL_HELVETICA,
		helvetica_bold=FL_HELVETICA_BOLD,
		helvetica_italic=FL_HELVETICA_ITALIC,
		helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
		courier=FL_COURIER,
  		courier_bold=FL_COURIER_BOLD,
  		courier_italic=FL_COURIER_ITALIC,
  		courier_bold_italic=FL_COURIER_BOLD_ITALIC,
		times=FL_TIMES,
		times_bold=FL_TIMES_BOLD,
		times_italic=FL_TIMES_ITALIC,
		times_bold_italic=FL_TIMES_BOLD_ITALIC,
		symbol=FL_SYMBOL,
		screen=FL_SCREEN,
		screen_bold=FL_SCREEN_BOLD,
		zapf_dingbats=FL_ZAPF_DINGBATS
	};

	Font(Font_type ff) :f(ff) { }
	Font(int ff) :f(ff) { }

	int as_int() const { return f; } // getter fv
};

struct Fill {
	Fill() :no_fill(true), fcolor(0) { } // alapértrlmrzrtt konstruktór
	Fill(Color c) :no_fill(false), fcolor(c) { }

	void set_fill_color(Color c) { fcolor = c; no_fill = false; } // setter fv
	Color fill_color() { return fcolor; }						  // getter fv
protected:
	bool no_fill;
	Color fcolor;
};

//class Shape
class Shape {
public:
	void draw() const;

	virtual void move(int dx, int dy);

	void set_color(Color col) { lcolor = col; }
	Color color() const { return lcolor; } // getter fv

	void set_style(Line_style sty) { ls = sty; }
	Line_style style() const { return ls; } // getter fv

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() const { return fcolor; } // getter fv

	Point point(int i) const { return points[i]; }
	int number_of_points() const { return int(points.size()); } // getter fv

	Shape(const Shape&) = delete; // letiltjuk a másoolást a =delete vel
	Shape& operator=(const Shape&) = delete;

	virtual ~Shape() { } // virtuális destruktor

protected:
	Shape() {}
	Shape(initializer_list<Point> lst) 
		{ for (Point p : lst) add(p); }

	void add(Point p) { points.push_back(p); }  	// push.back helyett add fv használunk
	void set_point(int i, Point p) { points[i] = p; }
	virtual void draw_lines() const;  				// ezt overridleni kell a hívófélnek

private:
	vector<Point> points;
	Color lcolor {fl_color()}; // fl_color() ful tikk nek az alapértelmezett linee color
	Line_style ls {0};			// line style 
	Color fcolor {Color::invisible}; // kitöltő szin
};

template <class T> class Vector_ref { // T tipusu objektumoknak lessz a tárolója
	vector<T*> v;
	vector<T*> owned;
public:
	Vector_ref(){} // alapértelmezett konstruktór
	Vector_ref(T* a, T* b=0, T* c=0, T* d=0)  // konstruktor ennek tudunk adni paramétereket
	{
		if (a) push_back (a); // ha nm null pointer akkor betesszük
		if (b) push_back (b);
		if (c) push_back (c);
		if (d) push_back (d);
	}
	~Vector_ref(){ for (int i = 0; i < owned.size(); ++i) delete owned[i]; } // végig megy a vectoron és eggyessével felsazbadítja az owned okat

	void push_back(T& s) { v.push_back(&s); }
	void push_back(T* p) { v.push_back(p); owned.push_back(p); }

	T& operator[](int i){ return *v[i]; } // mivel pointer
	const T& operator[](int i) const { return *v[i]; } //const korrektség miatt
	int size() { return v.size(); }
};

struct Line : Shape {
	Line (Point p1, Point p2) { add(p1); add(p2); }
};
////////////orán itt kezdtük//////////////////////
struct Lines : Shape {
	Lines(){} 													// alapértelemzett konstuktort létre hozunk --> üres
	Lines(initializer_list<Point> lst): Shape{lst} 				// itt inicializálunk, shape nek van initalizer_lsit-je -> átadjuk a shape osztálynak a list -et 
		{if ( lst.size() % 2 ) 
			error("páratlan számú pontok");}
	void draw_lines() const; 									// itt deklaráljuk a cpp be lessz deffiniálva
	void add(Point p1, Point p2) 								//pont párok lezsnek
		{ Shape::add(p1); Shape::add(p2); } 
};

struct Open_polyline : Shape {

	Open_polyline(){};
	Open_polyline(initializer_list<Point> lst): Shape(lst) {}
//	using Shape::Shape;
	void add(Point p) { Shape::add(p); }
	void draw_lines() const;
};

struct Closed_polyline : Open_polyline { // open polyline osztálynak a dolgai fognak öröklödni
	using Open_polyline::Open_polyline;
	void draw_lines() const;
};

struct Polygon : Closed_polyline {
	using Closed_polyline::Closed_polyline;
	void add(Point p);
	void draw_lines() const;
};

struct Rectangle : Shape {

	Rectangle(Point xy, int ww, int hh): w{ww}, h{hh}
	{
		if (h<=0 || w<=0) error("Nem jó oldalhossz w vagy h.");
		add(xy);
	}
	Rectangle(Point a, Point b): w{ b.x - a.x }, h{ b.y - a.y }
	{
		if (h<=0 || w<=0) error("Nem jó pontok. w vagy h");
		add(a);
	}
	
	void draw_lines() const;

	int height() const { return h; }// getter fv
	int width() const { return w; } // getter fv
private:
	int h, w;

};

struct Text : Shape {
private:
	string lab;
	Font fnt { fl_font() };
	int fnt_sz { 14<fl_size() ? fl_size() : 14 };
public:
	Text(Point x, const string& s): lab {s} { add(x); }

	void draw_lines() const;

	void set_label(const string& s) { lab = s; }
	string label() const { return lab; }

	void set_font(Font f) {fnt = f;}   			// setter fv
	Font font() const { return Font(fnt); }		// getter fv

	void set_font_size(int sz) { fnt_sz = sz; } // setter fv
	int font_size() const { return fnt_sz; }	// getter fv
};

struct Circle : Shape
{
private:
	int r;
public:
	Circle(Point p, int rr): r{rr} {
		add(Point{ p.x-r, p.y-r });
	}

	void draw_lines() const;

	Point center() const 
			{ return { point(0).x+r, point(0).y+r }; }

	void set_radius(int rr) { r=rr; }  // setter fv
	int radius() const { return r; }   // getter fv
};

struct Ellipse : Shape
{
	Ellipse(Point p, int ww, int hh): w(ww), h(hh)
	{ add(Point(p.x-ww, p.y-hh)); }

	void draw_lines() const;


private:
	int w,h;
};

struct Marked_polyline : Open_polyline
{
	Marked_polyline(const string& m): mark(m) { }
	void draw_lines() const;
private:
	string mark;
};

struct Marks : Marked_polyline
{
	Marks(const string& m) : Marked_polyline(m) //kostruktor | az ősosztály kostruktorát hivjuk meg
	{ set_color(Color(Color::invisible)); } // átlátszoság set --> átlátszóra

};

struct Mark : Marks
{
	Mark(Point p, char c) : Marks(string(1,c)) { add(p); }
};

struct Bad_image : Fl_Image {
	Bad_image(int h, int w) : Fl_Image(h,w,0) { }
	void draw(int x, int y, int, int, int, int) { draw_empty(x,y); }
};

struct Suffix {
	enum Encoding { none, jpg, gif, bmp };
};

Suffix::Encoding get_encoding(const string& s);

struct Image : Shape {
private:
	int w, h, cx, cy;
	Fl_Image* p; // a fultiknek egy kép kezelő típusa
	Text fn;
public: //honnantol    cím          
	Image(Point xy, const string s, Suffix::Encoding e = Suffix::none);
	~Image() { delete p; }
	void draw_lines() const;
	void set_mask(Point p, int ww, int hh) { w = ww; h = hh; cx = p.x; cy = p.y; }
	void move(int dx, int dy) 
	{ 
		Shape::move(dx,dy); 
		p->draw(point(0).x,point(0).y);  // meghyvjuk a shape ősosztályt
	} 
};

typedef double Fct(double);

struct Function : Shape {                              // pontok száma        
	Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
};

struct Axis : Shape {
	enum Orientation { x, y, z };                 // osztás közök
	Axis (Orientation d, Point xy, int length, int number_of_notches = 0, string label = "");
	void draw_lines() const; // 
	void move(int dx, int dy);
	void set_color(Color c);

	Text label;
	Lines notches;
};

}
#endif