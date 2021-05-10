#include "std_lib_facilities.h"

const int  min_age = 1;
const int max_age = 150;

void age_check(int age){
	if (age < min_age || age >= max_age) error("Age is invalid!");
}

void name_check(string name){
	for (int i = 0; i < name.length(); ++i)
	{
		if(!isalpha(name[i])) error("Name is invalid!"); 
	}
}

struct Person
{
	Person(string fn = "Pop" , string sn = "Simon" , int a = 26 ): firstname{fn}, lastname{sn}, age{a} 
	{
		age_check(age);
		name_check(firstname);
		name_check(lastname);
	}

	string name() const { return firstname + " " + lastname; }
	int ages() const { return age; }

	void set_fname(string fname) { firstname = fname; }
	void set_lname(string lname) { lastname = lname; }
	void set_age(int n ) { age = n; }

private:
	string firstname;
	string lastname;
	int age;
};

istream& operator>>(istream& is, Person& pp)
{
	string fn, ln;
	int a;

	is >> fn;
	pp.set_fname(fn);
	for (int i = 0; i < fn.size(); ++i) if (!isalpha(fn[i])) error("Firstname is invalid!");
	
	is >> ln;
	pp.set_lname(ln);
	for (int i = 0; i < ln.size(); ++i) if (!isalpha(ln[i])) error("Lastname is invalid!");

	is >> a;
	pp.set_age(a);
	if (a <= min_age || a > max_age) error ("Age is invalid!");  
	

	return is;
}

ostream& operator<<(ostream& os, const Person& pp) 
{
	os << pp.name() <<  " age: " << pp.ages() << endl;  
	return os;
}

int main()
try{

	Person pp {"Goofy","Puffy", 34};
	cout << pp;

	vector<Person> group;
	
	for (int i = 0; i < 2; ++i)
	{
		Person var;
		cin >> var;
		group.push_back(var);
	}
	for(Person ppl : group)
		cout << ppl;

	return 0;


}catch(exception& e){
	cerr << e.what() << '\n';
	return 1;
}catch(...){
	cerr << "Well it did't worked! \n";
	return 2;
}