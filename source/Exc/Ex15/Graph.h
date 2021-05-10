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

struct Color {
	enum Color_type {
		red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
		yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
		magenta=FL_MAGENTA, cyan=FL_CYAN, dark_red=FL_DARK_RED,
		dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
		dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN
	};
	enum Transparency { invisible = 0, visible = 255 };

	Color(Color_type cc): c(Fl_Color(cc)), v(visible) {}
	Color(Color_type cc, Transparency vv): c(Fl_Color(cc)), v(vv) {}
	Color(int cc): c(Fl_Color(cc)), v(visible) {}
	Color(Transparency vv): c(Fl_Color()), v(vv) {} // alap értelmezett szin a fltk -be

	int as_int() const { return c; }
	char visibility() const { return v; }
	void set_visibility(Transparency vv) { v = vv; }

private:
	unsigned char v; // visibility
	Fl_Color c; // fl tipus
};

struct Line_style {
	enum Line_style_type {
		solid=FL_SOLID,				// -------
		dash=FL_DASH,				// - - - -
		dot=FL_DOT,					// ....... 
		dashdot=FL_DASHDOT,			// - . - . 
		dashdotdot=FL_DASHDOTDOT,	// -..-..
	};

	Line_style(Line_style_type ss): s(ss), w(0) { }
	Line_style(Line_style_type ss, int ww): s(ss), w(ww) { }
	Line_style(int ss): s(ss), w(0) { }

	int width() const { return w; }
	int style() const { return s; }
private:
	int s; // stílus
	int w; // vastagság
};

class Font {
public: // publikus lessz az enum és így látjuk
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
	// Font type paramétret várunk
	Font(Font_type ff) :f(ff) { } // konstruktor
	Font(int ff) :f(ff) { }

	int as_int() const { return f; } // getter
private:
	int f;
};

struct Fill {
	Fill() :no_fill(true), fcolor(0) { } // alapértelmezett nincs kitöltöszin
	Fill(Color c) :no_fill(false), fcolor(c) { }

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() { return fcolor; }
protected:
	bool no_fill;
	Color fcolor;
};

//class Shape
class Shape {
public:
	void draw() const;

	virtual void move(int dx, int dy); // futásidőben 

	void set_color(Color col) { lcolor = col; }
	Color color() const { return lcolor; } 

	void set_style(Line_style sty) { ls = sty; }
	Line_style style() const { return ls; }

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() const { return fcolor; }

	Point point(int i) const { return points[i]; }
	int number_of_points() const { return int(points.size()); }

	Shape(const Shape&) = delete; // letiltjuk a másoló konstuktort 
	Shape& operator=(const Shape&) = delete;  // letiltjuk a másoló értékadást

	virtual ~Shape() { } 

protected:
	Shape() {}    	 // Pontok listája
	Shape(initializer_list<Point> lst) { for (Point p : lst) add(p); }
	void add(Point p) { points.push_back(p); }
	void set_point(int i, Point p) { points[i] = p; }
	virtual void draw_lines() const;  // azért virtuális mert override olnia kell a hívofélnek
	void clear_points() { points.clear(); }

private:
	vector<Point> points;
	Color lcolor {fl_color()};
	Line_style ls {0};
	Color fcolor {Color::invisible};
};

//----------------------------------------

template<class T> class Vector_ref {
	vector<T*> v;
	vector<T*> owned;
public:
	Vector_ref(){}
	Vector_ref(T* a, T* b=0, T* c=0, T* d=0) // utolso 3 opcionális
	{
		if (a) push_back (a); // teszteljük hogyezek a pointerek nullpointerek e vagy nm
		if (b) push_back (b);// ha nem nullpointer akkor hozzá adja
		if (c) push_back (c);
		if (d) push_back (d);
	}
	~Vector_ref(){ for (int i = 0; i < owned.size(); ++i) delete owned[i]; }

	void push_back(T& s) { v.push_back(&s); } // addressof opereator -ral elkérjük az első objektum címét
	void push_back(T* p) { v.push_back(p); owned.push_back(p); }

	T& operator[](int i){ return *v[i]; }
	const T& operator[](int i) const { return *v[i]; }
	int size() { return v.size(); } // v -t nm érjük el kivűlről
};

struct Line : Shape {
	Line (Point p1, Point p2) { add(p1); add(p2);}
};

//-----------------------------------------

struct Lines : Shape {
	Lines(){}									  // Shap nek hívjuk ugyanezen konstuktorat
	Lines(initializer_list<Point> lst): Shape{lst}// Shape nek van inicializáló listás konstruktora
		{if ( lst.size() % 2 ) error("páratlan számú pontok");}
	void draw_lines() const; // itt deklalráljuk
	void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); } // pont párokata adunk
};

struct Open_polyline : Shape {
	/*
	Open_polyline() {}
	Open_polyline(initializer_list<Point> ls): Shape(lst) {}
	*/
	using Shape::Shape;  // a Shape osztály dolgait fogja örökőllni | itt is a konstuktorok protected 
	void add(Point p) { Shape::add(p); }
	void draw_lines() const;
};

struct Closed_polyline : Open_polyline { // utolsó pontot hozzákötjuk az elsőhöz
	using Open_polyline::Open_polyline;
	void draw_lines() const;
};

struct Polygon : Closed_polyline {
	using Closed_polyline::Closed_polyline;
	void add(Point p); // deklaráljuk | hiba kezelni kell mert a Shape add jébe nincs 
	void draw_lines() const;
};

struct Rectangle : Shape {

	Rectangle(Point xy, int ww, int hh): w{ww}, h{hh}
	{
		if (h<=0 || w<=0) error("Nem jó oldalhossz.");
		add(xy);
	}
	Rectangle(Point x, Point y): w{ y.x - x.x }, h{ y.y - x.y } // balfelső sarok és a jobbalsó sarok megadásával is
	{
		if (h<=0 || w<=0) error("Nem jó pontok.");
		add(x); // elég az x pont mert az y bol már kizámoltuk az oldalhoosszokat
	}
	
	void draw_lines() const;

	int height() const { return h; }
	int width() const { return w; }
private:
	int h, w;

};

struct Text : Shape {
private:
	string lab;
	Font fnt  { fl_font() };
	int fnt_sz { 14<fl_size() ? fl_size() : 14 };
public:
	Text(Point x, const string& s): lab {s} { add(x); }

	void draw_lines() const;

	void set_label(const string& s) { lab = s; }
	string label() const { return lab; }

	void set_font(Font f) {fnt = f;}
	Font font() const { return Font(fnt); }

	void set_font_size(int sz) { fnt_sz = sz; }
	int font_size() const { return fnt_sz; }
};

struct Circle : Shape
{
private:
	int r;
public:
	Circle(Point p, int rr): r{rr} {
		add(Point{ p.x-r, p.y-r }); // eltoljuk r -rel 
	}

	void draw_lines() const;

	Point center() const { return { point(0).x+r, point(0).y+r }; }

	void set_radius(int rr) { r=rr; }
	int radius() const { return r; }
};

struct Ellipse : Shape{
	Ellipse(Point p, int ww , int hh): w{ww}, h{hh}
	{ add(Point{p.x-ww, p.y-hh}); }

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
	Marks(const string& m) : Marked_polyline(m) 
	{ set_color(Color(Color::invisible)); }

};

struct Mark : Marks
{					// az ösosztály konstuktorát delegáljuk 
	Mark(Point xy, char c) : Marks(string(1,c)) { add(xy); }
};

struct Bad_image : Fl_Image {
	Bad_image(int h, int w) : Fl_Image(h,w,0) { }
	void draw(int x, int y, int, int, int, int) { draw_empty(x,y); } // a fltk -ban  a draw empty mondja meg hogy üresképet rajoljunk
};

struct Suffix {
	enum Encoding { none, jpg, gif, bmp };
};

Suffix::Encoding get_encoding(const string& s);

struct Image : Shape {
private:
	int w, h, cx, cy; // cx, cy maszkoláshoz kell
	Fl_Image* p;
	Text fn;
public:
	Image(Point xy, string s, Suffix::Encoding e = Suffix::none);
	~Image() { delete p; }
	void draw_lines() const;			//	menniyt rajoljon // melyik pontol rajzoljuk ki cx cy 
	void set_mask(Point xy, int ww, int hh) { w = ww; h = hh; cx=xy.x; cy=xy.y; } // levágunk a képből
	void move(int dx, int dy) { Shape::move(dx,dy); p->draw(point(0).x,point(0).y); }
};

typedef double Fct(double);

struct Function : Shape {													// skálázás
	Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
};

struct Fv : Function {
	Fv(Fct f, double r1, double r2, Point orig, int cnt = 100, 
		double xsc = 25, double ysc = 25, double prec = 1);
	
	void reset_fct(Fct f) { fct = f; reset(); }
	void reset_range(double r1, double r2);
	void reset_orig(Point orig) { origin = orig; reset(); }
	void reset_count(int cnt);
	void reset_xscale(double xsc);
    void reset_yscale(double ysc);
    void reset_precision(double prec) { precision = prec; reset();}

private:
	Fct* fct;
	double range1;
	double range2;
	Point origin;
	int count;
	double xscale;
	double yscale;
	double precision;

	void reset();
};


struct Axis : Shape {
	enum Orientation { x, y, z }; // meg adjuk az irányultságot Axis::x 
	Axis (Orientation d, Point xy, int length, int number_of_notches = 0, string label = "");
	void draw_lines() const;
	void move(int dx, int dy);
	void set_color(Color c);

	Text label;
	Lines notches;
};
//---------------------Exc--------------------------------
class Arc : public Shape
{
	Point center;
	float radius;
	float start;
	float end;
public:
	Arc(Point c, double r, double s, double e) : center(c), radius(r), start(s), end(e) { add(c); }; //Add center point to shape
	void draw_lines() const;
};

struct Round_box : public Shape
{
	Round_box(Point origin, int width, int height, int radius) : o(origin), w(width), h(height), r(radius){
		a1 = Point(o.x + r, o.y); 

		b1 = Point(o.x + w - r, o.y);
		b2 = Point(o.x + w, o.y + r);

		c1 = Point(o.x + w, o.y + h - r);
		c2 = Point(o.x + w - r, o.y + h);

		d1 = Point(o.x + r, o.y + h);
		d2 = Point(o.x, o.y + h - r);

		a2 = Point(o.x, o.y + r);

		a3 = Point(o.x + r, o.y + r);
		b3 = Point(o.x + w - r, o.y + r);
		c3 = Point(o.x + w - r, o.y + h - r);
		d3 = Point(o.x + r, o.y + h - r);
	};

	void draw_lines() const;

private:
	Point o;
	Point a1, a2, b1, b2, c1, c2, d1, d2;
	Point a3, b3, c3, d3;
	int w, h, r;
};

//arrow class
double pointVecMag2(Point vec);

struct Arrow : public Shape
{
	Arrow(Point start, Point end, bool s, bool e, int size) :
		start(start), end(end), s(s), e(e), size(size) 
	{
		if (s){
			
			c = Point(end.x - start.x, end.y - start.y); 
			cMag = pointVecMag2(c); 
			cUnit = Point(c.x/cMag * size, c.y / cMag * size); 
			cTrans = Point(cUnit.x, cUnit.y); 

			//Arrow head start
			
			cPerp = Point(-cTrans.y, cTrans.x);
			arrowhead01 = Point(start.x + cPerp.x + cTrans.x, start.y + cPerp.y + cTrans.y); 
			arrowhead02 = Point(start.x - cPerp.x + cTrans.x, start.y - cPerp.y + cTrans.y); 
		}

		if (e){
			//start-end vector: d
			d = Point(start.x - end.x, start.y - end.y);
			dMag = pointVecMag2(d);
			dUnit = Point(d.x/dMag * size, d.y/dMag * size);
			dTrans = Point(dUnit.x, dUnit.y);

			//Arrow head End
			dPerp = Point(-dTrans.y, dTrans.x);
			arrowhead03 = Point(end.x + dPerp.x + dTrans.x, end.y + dPerp.y + dTrans.y);
			arrowhead04 = Point(end.x - dPerp.x + dTrans.x, end.y - dPerp.y + dTrans.y);
		}
	};

	void draw_lines() const;

private:
	//Line
	Point start;
	Point end;
	//Arrowhead at start
	Point c;
	Point cUnit;
	Point cTrans;
	Point cPerp;
	double cMag;

	Point arrowhead01;
	Point arrowhead02;

	//Arrowhead at end
	Point d;
	Point dUnit;
	Point dTrans;
	Point dPerp;
	double dMag;

	Point arrowhead03;
	Point arrowhead04;

	bool s;
	bool e;
	int size;
};

struct Box_text : public Shape
{
	Box_text(Point origin, string ss, int radius) : o(origin), lab(ss), r(radius), w(ss.size()*12), h(30)
	{
		a1 = Point(o.x + r, o.y); 

		b1 = Point(o.x + w - r, o.y);
		b2 = Point(o.x + w, o.y + r);

		c1 = Point(o.x + w, o.y + h - r);
		c2 = Point(o.x + w - r, o.y + h);

		d1 = Point(o.x + r, o.y + h);
		d2 = Point(o.x, o.y + h - r);

		a2 = Point(o.x, o.y + r);

		a3 = Point(o.x + r, o.y + r);
		b3 = Point(o.x + w - r, o.y + r);
		c3 = Point(o.x + w - r, o.y + h - r);
		d3 = Point(o.x + r, o.y + h - r);
	};

	void draw_lines() const;

	int get_width() const { return w; }
	int get_heigth() const { return h; }
	int get_radius() const { return r; }

private:
	string lab;
	Point o;
	Point a1, a2, b1, b2, c1, c2, d1, d2;
	Point a3, b3, c3, d3;
	int w, h, r;
};

/*
smiley
set, draw ... TODO
------------The-End-----------------
*/

} // end of Graph_lib
#endif
