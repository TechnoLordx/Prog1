#include "std_lib_facilities.h"

class B1{
public:
	virtual void vf() { cout << "B1::vf\n"; }
	void f() { cout << "B1::f\n"; }
	virtual void pvf() = 0; // pure virtual function
};

class D1 : public B1{
public:
	void vf() override { cout << "D1::fv\n";}
	void f() { cout << "D1::f\n"; }

};

class D2 : public D1
{
	void pvf() override { cout << "D2::pvf\n"}
}

void f (B1& b)
{

}



int main()
{
	cout << "----------1---------\n";

	B1 b;
	b.vf();
	b.f();

	cout << "----------2---------\n";

	D1 d;
	d.vf();
	d.f();

	cout << "----------3---------\n";

	B1& bref = d;
	bref.vf();
	bref.f();

	cout << "----------4---------\n";

	D2 d2;
	d2.vf();
	d2.f();
	d2.pvf();

	cout << "----------5---------\n";



}