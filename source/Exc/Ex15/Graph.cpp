#include "Graph.h"
#include <map>

namespace Graph_lib {

inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel) 
{
    double x1 = p1.x;
    double x2 = p2.x;
	double x3 = p3.x;
	double x4 = p4.x;
	double y1 = p1.y;
	double y2 = p2.y;
	double y3 = p3.y;
	double y4 = p4.y;

	double denom = ((y4 - y3)*(x2-x1) - (x4-x3)*(y2-y1));
	if (denom == 0){
		parallel= true;
		return pair<double,double>(0,0);
	}
	parallel = false;
	return pair<double,double>( ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
								((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}

bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
} 

//class Shape's functions
void Shape::draw_lines() const
{
	if (color().visibility() && 1<points.size())
		for(int i = 1; i < points.size(); ++i)
			fl_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
}

void Shape::move(int dx, int dy)
{
	for(int i = 0; i < points.size(); ++i){
		points[i].x += dx;
		points[i].y += dy;
	}
}

void Shape::draw() const
{
	Fl_Color oldc = fl_color();
	fl_color(lcolor.as_int());
	fl_line_style(ls.style(), ls.width());
	draw_lines();
	fl_color(oldc);
	fl_line_style(0);
}

void Lines::draw_lines() const
{
	if (color().visibility())
		for (int i = 1; i < number_of_points(); i+=2)
			fl_line(point(i-1).x, point(i-1).y, point(i).x, point(i).y);
}

void Open_polyline::draw_lines() const
{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for(int i=0; i<number_of_points(); ++i){
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());
		}
		
		if (color().visibility())
			Shape::draw_lines();
}

void Closed_polyline::draw_lines() const
{
	Open_polyline::draw_lines();

	if (color().visibility())
		fl_line(point(number_of_points()-1).x, point(number_of_points()-1).y, point(0).x, point(0).y);
}

void Polygon::add(Point p)
{
	int np = number_of_points();

	if (1<np) {
		if (p==point(np-1)) error("Ugyanaz mint az előző pont");
		bool parallel;
		line_intersect(point(np-1),p,point(np-2),point(np-1),parallel);
		if (parallel)
			error("két poligon pont ugyanazon a vonalon");
	}

	for (int i = 1; i<np-1; ++i) {
		Point ignore(0,0);
		if (line_segment_intersect(point(np-1),p,point(i-1),point(i),ignore))
			error("kereszteződés");
	}
	

	Closed_polyline::add(p);
}


void Polygon::draw_lines() const
{
		if (number_of_points() < 3) error("kevesebb mint 3 pont");
		Closed_polyline::draw_lines();
}

void Rectangle::draw_lines() const
{
	if (fill_color().visibility()){
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x, point(0).y, w, h);
		fl_color(color().as_int());
	}

	if (color().visibility()){
		fl_color(color().as_int());
		fl_rect(point(0).x, point(0).y, w, h);
	}
}

void Text::draw_lines() const
{
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(), fnt_sz);
	fl_draw(lab.c_str(), point(0).x, point(0).y);
	fl_font(ofnt, osz);
}

void Circle::draw_lines() const
{
	if (fill_color().visibility()){
		fl_color(fill_color().as_int());
		fl_pie(point(0).x, point(0).y, r+r-1, r+r-1, 0, 360);
		fl_color(color().as_int());
	}

	if (color().visibility()){
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, r+r, r+r, 0, 360);
	}
}

void draw_mark(Point x, char c){
	
	static const int dx = 4;
	static const int dy = 4;
	string m(1,c);
	fl_draw(m.c_str(), x.x-dx,x.y-dy);

}

void Marked_polyline::draw_lines() const
{
	Open_polyline::draw_lines();
	for( int i = 0; i < number_of_points(); ++i)
		draw_mark(point(i), mark[i%mark.size()]);
}

std::map<string,Suffix::Encoding> suffix_map;

int init_suffix_map()
{
	suffix_map["jpg"] = Suffix::jpg;
	suffix_map["JPG"] = Suffix::jpg;
	suffix_map["jpeg"] = Suffix::jpg;
	suffix_map["JPEG"] = Suffix::jpg;
	suffix_map["gif"] = Suffix::gif;
	suffix_map["GIF"] = Suffix::gif;
	suffix_map["bmp"] = Suffix::bmp;
	suffix_map["BMP"] = Suffix::bmp;
	return 0;
}

Suffix::Encoding get_encoding(const string& s)
{
	static int x = init_suffix_map();

	string::const_iterator p = find(s.begin(),s.end(),'.');
	if (p==s.end()) return Suffix::none;

	string suf(p+1,s.end());
	return suffix_map[suf];
}

bool can_open(const string& s){
	ifstream ff(s.c_str());
	return ff.is_open();
}

Image::Image(Point xy, string s, Suffix::Encoding e)
	:w(0), h(0), fn(xy,"")
{
	add(xy);

	if (!can_open(s)){
		fn.set_label("Nem nyithato a file!");
		p = new Bad_image(30,20);
		return;
	}

	if (e == Suffix::none) e = get_encoding(s);
/*
	switch(e){
		case Suffix::jpg:
		p = new Fl_JPEG_Image(s.c_str());
		break;
		case Suffix::gif:
		p = new Fl_GIF_Image(s.c_str());
		break;
		default:
		fn.set_label("Nem tamogatott formatum!");
		p = new Bad_image(30,20);
	}

*/
}

void Image::draw_lines() const
{
	if (fn.label() != "") fn.draw_lines();

	if (w && h){
		p->draw(point(0).x, point(0).y, w, h, cx, cy);
	}
	else {
		p->draw(point(0).x, point(0).y);
	}
}

Function::Function(Fct f, double r1, double r2, Point xy, int count, double xscale, double yscale){
	if (r2-r1<=0) error ("Rossz range!");
	if (count<=0) error ("Rossz count!");
	double dist = (r2-r1)/count;
	double r = r1;
	for (int i = 0; i < count; ++i){
		add(Point(xy.x+int(r*xscale), xy.y-int(f(r)*yscale)));
		r += dist;
	}
}

Fv::Fv(Fct f, double r1, double r2, Point xy, int cnt,
			 double xsc, double ysc, double prec)
    :Function(f,r1,r2,xy,cnt,xsc,ysc), fct(f), 
    range1(r1), range2(r2), origin(xy),
     count(cnt), xscale(xsc), yscale(ysc), precision(prec)
{
    reset();
}

void Fv::reset_range(double r1, double r2)
{
	if(r2 <= r1) error("Rossz tartomány");
	range1 = r1;
	range2 = r2;

	reset();
}

void Fv::reset_count(int cnt)
{
	if(cnt <= 0) error("Negatív pontszámot adtál meg");
	count = cnt;

	reset();
}

void Fv::reset_xscale(double xsc)
{
	if(xsc == 0) error("Az xscale értéke nem lehet nulla");
	xscale = xsc;

	reset();
}
/*
void Fv::reset_yscale(int ysc)
{
	if(ysc == 0) error("Az yscale értéke nem lehet nulla");
	yscale = ysc;

	reset();
}
 */
void Fv::reset()
{
	double dist = (range2 - range1)/count;
	double r = range1;
	clear_points();
	for (int i = 0; i < count; ++i)
	{
		add(Point(origin.x+int(int(r*xscale)/precision)*precision,
			origin.y-int(int(fct(r)*yscale)/precision)*precision));
		
		r += dist;
	}
}

Axis::Axis(Orientation d, Point xy, int length, int n, string lab )
	:label(Point(0,0), lab)
{
	if (length < 0) error ("Rossz tengely méret.");
	switch (d){
		case Axis::x:
		{
			Shape::add(xy);
			Shape::add(Point(xy.x+length, xy.y));
			if (1<n){
				int dist = length/n;
				int x = xy.x+dist;
				for (int i = 0; i < n; ++i){
					notches.add(Point(x, xy.y), Point(x, xy.y-5));
					x += dist;
				}
			}
			label.move(length/3, xy.y+20);
			break;
		}
		case Axis::y:
		{
			Shape::add(xy);
			Shape::add(Point(xy.x, xy.y-length));
			if (1<n){
				int dist = length/n;
				int y = xy.y-dist;
				for (int i = 0; i < n; ++i){
					notches.add(Point(xy.x, y), Point(xy.x+5, y));
					y -= dist;
				}
			}
			label.move(xy.x-10, xy.y-length-10);
			break;
		}
		case Axis::z:
			error("Nincs z!");
	}
}

void Axis::draw_lines() const
{
	Shape::draw_lines();
	notches.draw();
	label.draw();
}

void Axis::set_color(Color c)
{
	Shape::set_color(c);
	notches.set_color(c);
	label.set_color(c);
}

void Axis::move(int dx, int dy)
{
	Shape::move(dx, dy);
	notches.move(dx, dy);
	label.move(dx, dy);
}
//---------------------------------
void Arc::draw_lines() const{
	int w = radius + radius;
	int h = w;
	if (color().visibility()){
		fl_arc(point(0).x, point(0).y, w, h, start, end);
	}
}

void Round_box::draw_lines() const
{
	if(color().visibility()){
		fl_line(a1.x, a1.y, b1.x, b1.y);
		fl_line(b2.x, b2.y, c1.x, c1.y);
		fl_line(c2.x, c2.y, d1.x, d1.y);
		fl_line(d2.x, d2.y, a2.x, a2.y);

		fl_arc(o.x, o.y, r+r, r+r, 90, 180); 							//bf
		fl_arc(o.x + w - (r+r), o.y, r+r, r+r, 0, 90); 					//jf
		fl_arc(o.x + w - (r+r), o.y + h - (r+r), r+r, r+r, 270, 360); 	//ja
		fl_arc(o.x, o.y + h - (r+r), r+r, r+r, 180, 270); 				//ba
	}
}

void Box_text::draw_lines() const
{
	if(color().visibility()){
		fl_line(a1.x, a1.y, b1.x, b1.y);
		fl_line(b2.x, b2.y, c1.x, c1.y);
		fl_line(c2.x, c2.y, d1.x, d1.y);
		fl_line(d2.x, d2.y, a2.x, a2.y);

		fl_arc(o.x, o.y, r+r, r+r, 90, 180); 							//bf
		fl_arc(o.x + w - (r+r), o.y, r+r, r+r, 0, 90); 					//jf
		fl_arc(o.x + w - (r+r), o.y + h - (r+r), r+r, r+r, 270, 360);	//ja
		fl_arc(o.x, o.y + h - (r+r), r+r, r+r, 180, 270); 				//ba
	}

	fl_draw(lab.c_str(), d1.x + w/7, d1.y - h/2 + 5); // kicsit jobb ha +5 
}

double pointVecMag2(Point vec){
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

void Arrow::draw_lines() const
{
	if (color().visibility()){
		
		fl_line(start.x, start.y, end.x, end.y);

		//start
		if (s){
		fl_line(start.x, start.y, arrowhead01.x, arrowhead01.y);
		fl_line(start.x, start.y, arrowhead02.x, arrowhead02.y);
		}

		//end
		if (e){
			fl_line(end.x, end.y, arrowhead03.x, arrowhead03.y);
			fl_line(end.x, end.y, arrowhead04.x, arrowhead04.y);
		}
	}
}
/*
smiley
set, draw ... TODO
------------The-End-----------------
*/
} //end Graph
