
// Testrahmen fuer 1. Teilaufgabe

#include "RE.h"


#include "TestOrakel.h"

#include <iostream>
#include <string>

using namespace std;



int main() {
    
    // Erstelle Regul‰re Ausdr¸cke mit new Alt (heiﬂt + im regul‰ren Ausdruck)
    // und in denen sind die Objekte new Phi oder new Ch() gespeichert (r1,r2)
    // somit sieht der Regul‰re Ausdruck so aus r3 = (r1 | r2)
    RE* r1Alt = new Alt (new Phi(), new Ch('c'));
    RE* r2Alt = new Alt (new Ch('c'), new Phi());
    RE* r3Alt = new Alt (new Ch('c'), new Ch('c'));
    RE* r4Alt = new Alt (new Ch('a'), new Ch('b'));
    RE* r5Alt = new Alt (new Ch('a'), new Eps());
    RE* r6Alt = new Alt (new Eps(), new Ch('b'));
    
    // Erstelle Regul‰re Ausdr¸cke mit new Star, wo das Objekt r1 mit einem * versehen wird
    // z.B. hier w‰re es c** oder {}*
    RE* r1Star = new Star(new Ch('c'));
    RE* r2Star = new Star(new Star (new Ch('c')));
    RE* r3Star = new Star(new Star(new Star (new Ch('c'))));
    RE* r4Star = new Star(new Phi());
    
    // Erstelle Regul‰re Ausdr¸cke mit new Con (heiﬂt Konkatination)
    // und in denen sind die Objekte new Phi oder new Ch() gespeichert (r1,r2)
    // somit sieht der Regul‰re Ausdruck so aus r3 = (r1 r2)
    RE* r1Conc = new Conc (new Phi(), new Ch('c'));
    RE* r2Conc = new Conc (new Ch('c'), new Phi());
    RE* r3Conc = new Conc (new Ch('c'), new Ch('c'));
    RE* r4Conc = new Conc (new Ch('a'), new Ch('b'));
    RE* r5Conc = new Conc (new Ch('a'), new Eps());
    RE* r6Conc = new Conc (new Eps(), new Ch('b'));
    RE* r7Conc = new Conc (new Eps(), new Eps());
    RE* r8Conc = new Conc (new Phi(), new Phi());
    
    // Erstelle Regul‰re Ausdr¸cke die mehrere Funktionen von *, r3 = (r1 r2) und r3 = (r1 | r2)
    RE* r1Komplex = new Conc(new Eps, new Star(new Star(new Ch('a'))));
    RE* r2Komplex = new Conc(new Star(new Star(new Ch('a'))),new Eps());
    RE* r3Komplex = new Alt(new Eps, new Star(new Star(new Ch('a'))));
    RE* r4Komplex = new Alt(new Star(new Star(new Ch('a'))),new Eps());
    RE* r5Komplex = new Conc(new Ch('b'), new Star(new Star(new Ch('a'))));
    RE* r6Komplex = new Conc(new Eps(), new Conc(new Conc(new Eps, new Star(new Star(new Ch('a')))), new Alt(new Phi(), new Ch('b'))));
    
    
    
    // ->pretty gibt den regulären Ausdruck aus
    // ->simp() k¸rzt den Regulären Ausdruck,
    // wenn r1 oder r2 die Leere Menge ist
    cout << "--------------------- Oder-Verknuepfung ------------------------" << endl;
    cout << r1Alt->pretty() << " = ";
    cout << r1Alt ->simp()->pretty() << endl;
    cout << r2Alt->pretty() << " = ";
    cout << r2Alt ->simp()->pretty() << endl;
    cout << r3Alt->pretty() << " = ";
    cout << r3Alt ->simp()->pretty() << endl;
    cout << r4Alt->pretty() << " = ";
    cout << r4Alt ->simp()->pretty() << endl;
    cout << r5Alt->pretty() << " = ";
    cout << r5Alt ->simp()->pretty() << endl;
    cout << r6Alt->pretty() << " = ";
    cout << r6Alt ->simp()->pretty() << "\n" << endl;
    
    // ->pretty gibt den regulären Ausdruck aus
    // ->simp() k¸rzt den Regul‰ren Ausdruck, wenn ** ist das gleiche wie * und
    // wenn r1 ist gleich Phi ergibt es Eps
    cout << "--------------------- Kleenesche Huelle ------------------------" << endl;
    cout << r1Star->pretty() << " = ";
    cout << r1Star->simp()->pretty() << endl;
    cout << r2Star->pretty() << " = ";
    cout << r2Star->simp()->pretty() << endl;
    cout << r3Star->pretty() << " = ";
    cout << r3Star->simp()->pretty() << endl;
    cout << r4Star->pretty() << " = ";
    cout << r4Star->simp()->pretty() << "\n" << endl;
    
    // ->pretty gibt den regul‰ren Ausdruck aus
    // ->simp() k¸rzt den Regul‰ren Ausdruck, wenn ** ist das gleiche wie * und
    // wenn r1 ist gleich Phi ergibt es Eps
    cout << "--------------------- Konkatination ------------------------" << endl;
    cout << r1Conc->pretty() << " = ";
    cout << r1Conc->simp()->pretty() << endl;
    cout << r2Conc->pretty() << " = ";
    cout << r2Conc->simp()->pretty() << endl;
    cout << r3Conc->pretty() << " = ";
    cout << r3Conc->simp()->pretty() << endl;
    cout << r4Conc->pretty() << " = ";
    cout << r4Conc->simp()->pretty() << endl;
    cout << r5Conc->pretty() << " = ";
    cout << r5Conc->simp()->pretty() << endl;
    cout << r6Conc->pretty() << " = ";
    cout << r6Conc->simp()->pretty() << endl;
    cout << r7Conc->pretty() << " = ";
    cout << r7Conc->simp()->pretty() <<  endl;
    cout << r8Conc->pretty() << " = ";
    cout << r8Conc->simp()->pretty() << "\n" <<  endl;
    
    // ->pretty gibt den regul‰ren Ausdruck aus
    // ->simp() k¸rzt den Regul‰ren Ausdruck
    cout << "--------------------------- Komplexere Ausdruecke -----------------------------" << endl;
    cout << r1Komplex->pretty() << " = ";
    cout << r1Komplex->simp()->pretty() << endl;
    cout << r2Komplex->pretty() << " = ";
    cout << r2Komplex->simp()->pretty() << endl;
    cout << r3Komplex->pretty() << " = ";
    cout << r3Komplex->simp()->pretty() << endl;
    cout << r4Komplex->pretty() << " = ";
    cout << r4Komplex->simp()->pretty() << endl;
    cout << r5Komplex->pretty() << " = ";
    cout << r5Komplex->simp()->pretty() << endl;
    cout << r6Komplex->pretty() << " = ";
    cout << r6Komplex->simp()->pretty() << "\n" << endl;
}
