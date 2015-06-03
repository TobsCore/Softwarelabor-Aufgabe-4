
// Testrahmen fuer 1. Teilaufgabe

#include "RE.h"


#include "TestOrakel.h"

#include <iostream>
#include <string>

using namespace std;


// Systematischer Test

// Ein Testfall besteht aus einem regulären Ausdruck (RE)
// und einem Eingabestring.
//
// Testorakel match ueberprueft ob string s enthalten in regex r.
//
// Simplifizierer korrekt fuer Testfall, falls Testorakel gleiches
// Ergebnis liefert fuer Original regex r und simplifizierten regex r->simp()

bool testSimp(RE* r, string s) {
    
    cout << "Ist " << r->pretty() << " gleich mit " << r->simp()->pretty() << endl;
    
    bool b = false;
    if(match(r,s) == match(r->simp(),s)){
        b = true;
        cout << "Ergebnis: WAHR" << endl;
    } else {
        cout << "Ergebnis: FALSCH" << endl;
    }
    return b;
}

// Testorakel match ueberprueft ob string s enthalten in regex r.
bool testeWortInReg(RE* r, string s) {
    
    cout << "Ist das Wort " << s << " enthalten in " << r->pretty() << endl;
    
    bool b = false;
    if(match(r,s) && match(r->simp(),s)){
        b = true;
        cout << "Ergebnis: WAHR" << endl;
    } else {
        cout << "Ergebnis: FALSCH" << endl;
    }
    return b;
}

// Testorakel match ueberprueft ob string s enthalten in regex r -> simp().
bool testeWortInRegSimp(RE* r, string s) {
    
    cout << "Ist das Wort " << s << " enthalten in " << r->simp()->pretty() << endl;
    
    bool b = false;
    if(match(r->simp(),s)){
        b = true;
        cout << "Ergebnis: WAHR" << endl;
    } else {
        cout << "Ergebnis: FALSCH" << endl;
    }
    return b;
}

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
    
    // testSimp() testet ob das gegebene Wort bei pretty() und simp()
    // funktioniert oder nicht, somit ist getestet ob simp() funktioniert
    cout << "--------------------------- Teste simp() -------------------------------" << endl;
    testSimp(r1Alt, "");
    testSimp(r1Alt, "c");
    testSimp(r3Alt, "c");
    testSimp(r3Alt, "cc");
    cout << "\n" << endl;
    
    testSimp(r1Star, "");
    testSimp(r1Star, "c");
    testSimp(r1Star, "cc");
    testSimp(r1Star, "ccc");
    testSimp(r4Star, "");
    testSimp(r4Star, "c");
    cout << "\n" << endl;
    
    testSimp(r1Conc, "c");
    testSimp(r1Conc, "cc");
    testSimp(r1Conc, "ccc");
    testSimp(r4Conc, "");
    testSimp(r4Conc, "a");
    testSimp(r4Conc, "ab");
    testSimp(r5Conc, "");
    testSimp(r5Conc, "a");
    testSimp(r5Conc, "ab");
    cout << "\n" << endl;
    
    testSimp(r1Komplex, "");
    testSimp(r1Komplex, "ab");
    testSimp(r1Komplex, "aaaaa");
    testSimp(r2Komplex, "");
    testSimp(r2Komplex, "ab");
    testSimp(r2Komplex, "aaaaa");
    testSimp(r3Komplex, "");
    testSimp(r3Komplex, "ab");
    testSimp(r3Komplex, "aaaaa");
    testSimp(r4Komplex, "");
    testSimp(r4Komplex, "ab");
    testSimp(r4Komplex, "aaaaa");
    testSimp(r5Komplex, "");
    testSimp(r5Komplex, "b");
    testSimp(r5Komplex, "baa");
    testSimp(r5Komplex, "baaaaaa");
    testSimp(r5Komplex, "ab");
    testSimp(r6Komplex, "");
    testSimp(r6Komplex, "b");
    testSimp(r6Komplex, "ab");
    testSimp(r6Komplex, "aaaaaab");
    testSimp(r6Komplex, "abbb");
    cout << "\n" << endl;
    
    // testeWortInReg() testet ob das gegebene Wort zu der regul‰ren
    // Sprache in normal und gek¸rzt gehˆrt
    cout << "------------------------- Teste testeWortInReg() ----------------------------" << endl;
    testeWortInReg(r1Alt, "");
    testeWortInReg(r1Alt, "c");
    testeWortInReg(r3Alt, "c");
    testeWortInReg(r3Alt, "cc");
    cout << "\n" << endl;
    
    testeWortInReg(r1Star, "");
    testeWortInReg(r1Star, "c");
    testeWortInReg(r1Star, "cc");
    testeWortInReg(r1Star, "ccc");
    testeWortInReg(r4Star, "");
    testeWortInReg(r4Star, "c");
    cout << "\n" << endl;
    
    testeWortInReg(r1Conc, "c");
    testeWortInReg(r1Conc, "cc");
    testeWortInReg(r1Conc, "ccc");
    testeWortInReg(r4Conc, "");
    testeWortInReg(r4Conc, "a");
    testeWortInReg(r4Conc, "ab");
    testeWortInReg(r5Conc, "");
    testeWortInReg(r5Conc, "a");
    testeWortInReg(r5Conc, "ab");
    cout << "\n" << endl;
    
    testeWortInReg(r1Komplex, "");
    testeWortInReg(r1Komplex, "ab");
    testeWortInReg(r1Komplex, "aaaaa");
    testeWortInReg(r2Komplex, "");
    testeWortInReg(r2Komplex, "ab");
    testeWortInReg(r2Komplex, "aaaaa");
    testeWortInReg(r3Komplex, "");
    testeWortInReg(r3Komplex, "ab");
    testeWortInReg(r3Komplex, "aaaaa");
    testeWortInReg(r4Komplex, "");
    testeWortInReg(r4Komplex, "ab");
    testeWortInReg(r4Komplex, "aaaaa");
    testeWortInReg(r5Komplex, "");
    testeWortInReg(r5Komplex, "b");
    testeWortInReg(r5Komplex, "baa");
    testeWortInReg(r5Komplex, "baaaaaa");
    testeWortInReg(r5Komplex, "ab");
    testeWortInReg(r6Komplex, "");
    testeWortInReg(r6Komplex, "b");
    testeWortInReg(r6Komplex, "ab");
    testeWortInReg(r6Komplex, "aaaaaab");
    testeWortInReg(r6Komplex, "abbb");
    cout << "\n" << endl;
    
}
