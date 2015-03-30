
// Testrahmen fuer 1. Teilaufgabe

#include "RE.h"
#include "FSA.h"

#include "TestOrakel.h"

#include <iostream>
#include <string>

using namespace std;


// Systematischer Test

// Ein Testfall besteht aus einem regulaeren Ausdruck (RE)
// und einem Eingabestring.
// 
// Testorakel match ueberprueft ob string s enthalten in regex r.
// 
// Simplifizierer korrekt fuer Testfall, falls Testorakel gleiches
// Ergebnis liefert fuer Original regex r und simplifizierten regex r->simp()

bool testSimp(RE* r, string s) {
  bool b = (match(r,s) == match(r->simp(),s));

  cout << "Test case: " << r->pretty() << "   " << s << "\n";
  cout << "Test result: " << b << endl;

  return b;
}

int main() {

  cout << "Ein paar Testfaelle. Ueberpruefung per Auge" << endl;


  RE* r3 = new Alt (new Phi(), new Ch('c'));

  RE* r4 = new Alt (new Ch('c'), new Phi());

  cout << r3->pretty() << endl;

  cout << r3->simp()->pretty() << endl;

  RE* r5 = new Star(new Star (new Ch('c')));

  cout << r5->pretty() << endl;
  cout << r5->simp()->pretty() << endl;

  RE* r6 = new Star(new Phi());

  cout << r6->pretty() << endl;
  cout << r6->simp()->pretty() << endl;

  cout << "Verwende testSimp" << endl;

  testSimp(r5, "ab");

  // TODO: mehr Tests



}
