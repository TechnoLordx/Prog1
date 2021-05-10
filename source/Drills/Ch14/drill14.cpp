#include "std_lib_facilities.h"

// ha abstract az adott osztály még nincs teljesen megvalósítva. 
// Absztrakt osztály emiatt nem példányosítható, csak ősosztály lehet.
// Az absztraktként definiált metódusait a származtatott osztályban meg kell valósítani. 

class B{
public:						
	virtual void pvf() =0;	
};

class B1 : public B {
public:
    virtual void vf() { cout << "B1::vf()\n"; }
    void f() const { cout << "B1::f()\n"; }
    void pvf() { cout << "B1:pvf()\n"; }
    
};

class D1 : public B1 {
public:
    void vf() override { cout << "D1::vf()\n"; }
    void f() const { cout << "D1::f()\n"; }
    void pvf() { cout << "D1:pvf()\n"; }
};

class D2 : public D1 {
public:
    void pvf() override { cout << "D2::pvf()\n"; }
};

class B2{
public:
	virtual void pvf() =0;
};

class D21 : public B2 {
public:
	void pvf() override { cout << data << endl; }
	string data = "D21 string data";
};

class D22 : public B2 {
public:
	int data = 404;
	void pvf() override { cout << data << endl; }
};

void f( B2& b )
{
	b.pvf();
}


int main()
try{
	cout << "----------B1---------\n";

	B1 b;
	b.vf();
	b.f();

	cout << "----------D1---------\n";

	D1 d;
	d.vf();
	d.f();

	cout << "----------B&---------\n";

	B1& b_ref = d;
	b_ref.vf();
	b_ref.f();
	b_ref.pvf();

	cout << "----------D2---------\n";

	D2 d2;
	d2.vf();
	d2.f();
	d2.pvf();

	cout << "----------D21-D22--------\n";

	D21 d21;
	D22 d22;

	f(d21);
	f(d22);


}catch(exception& e){
	cerr << e.what() << "\n";
}catch(...){
	cerr << "Hmm it didn't worked \n";
}