#include <iostream>

using namespace std;

struct B {
public:
	virtual void f() const 
			{ cout << "B::f\n"; print_message(8.5);}
	void g() const { cout << "B::g\n"; }

	void print_message(int a) const
				{ cout << "Message: "<< a << endl;}

	//TODO
};

//class D : public B { ez a kettő u.a
struct D : B {       	// <--ez
	void f() const override
		 { cout << "D::f\n"; print_message(8.5);} // const és override felűlírás <-- helyes |const nlekűl nm
	void g()  { cout << "D::g\n"; }
	void print_message(double a) const
				{ cout << "Message: "<< a << endl;}

};

struct DD : B {
	void f() const { cout << "DD::f\n";}
	void g() const { cout << "DD::g\n"; }
};

void call(const B& b)
{
	b.f();
	b.g();
};

int main()
{
	B b;
	D d;
	DD dd;

	call(b);
	call(d);
	call(dd);

	cout << "Call end\n";

	b.f();
	b.g();

	d.f();
	d.g();

	dd.f();
	dd.g();

	return 0;
}

/*
B::f
B::g
D::f
B::g
DD::f
B::g
Call end

B::f
B::g
D::f
D::g
DD::f
DD::g


*/