#include <iostream>

using namespace std;

// ha abstract az adott osztály még nincs teljesen megvalósítva. 
// Absztrakt osztály emiatt nem példányosítható, csak ősosztály lehet.
// Az absztraktként definiált metódusait a származtatott osztályban meg kell valósítani. 


// És ezek a virtualis void függvények csak akkor íródnak felül ha egy származtatott osztályban 1 ugyan olyan nevű változónk van
// ősosztály
struct B { //class  
public:
	virtual void f() const //virtuális hívás  				// pure virtual function csak abstract osztályban lehet 	|     // tehát nem lehet példányosítani a tartalmazó osztályt
			{ cout << "B::f\n"; print_message(8.5);}
	void g() const { cout << "B::g\n"; }				// g nem egy virtuális fv ezért ez nem fog felűl definiálódni marad B::g

	void print_message(int a) const
				{ cout << "Message: "<< a << endl;}

	//TODO
};

//class D : public B { ez a kettő u.a
struct D : B {       	// <--ez                   | D egy B tipus a D osztály az a B-t terjeszti ki
	void f() const override						  // felűl definiálódik az f mert egy virtuális fv
		 { cout << "D::f\n"; print_message(8.5);} // const és override felűlírás <-- helyes |const nlekűl nm
	void g()  { cout << "D::g\n"; }
	void print_message(double a) const
				{ cout << "Message: "<< a << endl;}

};

struct DD : B {
	void f() const { cout << "DD::f\n";} // ha nincs itt a const akkor csak B:f -et fog írni | ha van const akkor DD:f hívódik (fölűl definiálja)
	void g() const { cout << "DD::g\n"; }
};
// ős referenciával adjuk át
void call(const B& b) // hivja a tag fv eket  | átadunk egy konstans B& (referenciát) és hivjuk ennek a b nek az f és g tagját
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
	A referencia paraméternél 'érdekes' 
*/
/*
B::f
B::g

D::f |virtual call: ha az ős referenciályán keresztűl hívlyuk a virtuál fv -t akkor mindig az aktuális példány tipusának a fv -je fog hívódni
B::g   csak referencián és pointere keresztűl müködik

DD::f | itt is csak az ős fog hívódni
B::g

Call end

B::f
B::g
D::f
D::g
DD::f
DD::g


*/