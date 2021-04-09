#ifndef POINT_GUARD
#define POINT_GUARD

namespace Graph_lib {

struct Point {
	int x, y;
	Point(): x(0), y(0) { }
	Point(int xx, int yy): x(xx), y(yy) { }
};

// inline nm fv hivas folytatólagos lessz a vezérlés

inline bool operator==(Point a, Point b) //2 pont megegyezik e vagy sem
	{ return a.x==b.x && a.y==b.y; }

inline bool operator!=(Point a, Point b)
	{ return !(a==b); }

}

#endif