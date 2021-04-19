#include "std_lib_facilities.h"

template<typename T>
struct S {

    S(T vall = T()) : val(vall) {}

    T& get();
    T get() const { return val; } // getter fv 
    //T set_val(T newee) { val = newee; }
    T operator=(const T&);

private:
    T val;
};

template<typename T> T& S<T>::get() { return val; } // külső getter fv  
//template<typename T> T const S<T>::get() { return val; } // const gettrt fv

template<typename T> T S<T>::operator=(const T& newee) { val = newee; }

template<typename T>
istream& operator>>(istream& is, S<T>& vall){
    is >> vall.get();
    return is;
}

template<typename T> void read_val(T& v) { cin >> v; }

int main()
try {
    S<int> szam {69};
    S<char> abc {'x'};
    S<double> tort {69.6969};
    S<string> szoveg {"cica"};
    S<vector<int>> tarolo {{1, 2, 3, 4, 5, 6 }};

    // 4-es feladat
    //cout << szam.val << " " << abc.val << " " << tort.val << " " << szoveg.val << endl;

    cout << "8-as feladat" << endl;
    cout << szam.get() << " " << abc.get() << " " << tort.get() << " " << szoveg.get() << endl;
    vector<int> tempy = tarolo.get();
    for (int& n : tempy) cout << n << " ";
    cout << endl;

    cout << "10-es feladat" << endl;
    S<int> masik {5};
    cout << "Regi szam: " << szam.get() << endl;
    szam = masik;
    cout << "Uj szam: " << szam.get() << endl;

    cout << "13-as feladat" << endl;
    S<int> v1;
    S<double> v2;
    S<string> v3;
    S<char> v4;
    cout << "Kerem irjon be egy int -t egy double -t, string -t és egy char -tipust !" << endl;
    read_val(v1); read_val(v2); read_val(v3); read_val(v4);
    cout << v1.get() << " " << v2.get() << " " << v3.get() << " " << v4.get() << endl;

    return 0;
} catch (exception& e) {
    cerr << e.what() << endl;
    return 1;
} catch (...) {
    cerr << "Something went wrong!" << endl;
    return 2;
}
