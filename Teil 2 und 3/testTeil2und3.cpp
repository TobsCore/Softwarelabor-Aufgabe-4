
// Testrahmen fuer 2. und 3. Teilaufgabe

#include <iostream>

using namespace std;

#include "FSA.h"
#include "RE.h"

#include "Transform.h"
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
// closure und Tranformater RE -> NFA korrekt, falls Testorakel gleiches
// Ergebnis liefert wie Ausfuehrung des resultierenden NFA.

bool testClosureTransform(RE* r, string s) {
    NFA nfa = transform(r);
    FSA fsa(nfa);
    bool bRun = fsa.run(s);     //schaut mit run ob der FSA den NFA so ausführen kann, dass er das Wort annimmt.
    bool bMatch = match(r,s);
    bool bTest = bRun == bMatch;
    
    string antwortTest;
    if(bTest == true){
        antwortTest = "Ja";
    } else if(bTest == 0){
        antwortTest = "Nein";
    }
    
    string antwortMatch;
    if(bMatch == true){
        antwortMatch = "Ja";
    } else if(bMatch == 0){
        antwortMatch = "Nein";
    }
    
    string antwortRun;
    if(bRun == true){
        antwortRun = "Ja";
    } else if(bRun == 0){
        antwortRun = "Nein";
    }
    
    cout << "Testdurchlauf: " << r->pretty() << " mit dem Wort " << s << "\n";
    cout << " - Testdurchlauf korrekt: " << antwortTest << endl;
    cout << " - Ein Wort der Sprache: " << antwortMatch << endl;
    cout << " - Laeuft im TestOrakle: " << antwortRun << "\n" << endl;
    
    return bTest;
}

int main() {
    // Erstelle Reguläre Ausdrücke mit new Alt (heißt + im Regulären Ausdruck)
    // und in denen sind die Objekte new Phi oder new Ch() gespeichert (r1,r2)
    // somit sieht der Reguläre Ausdruck so aus r3 = (r1 | r2)
    RE* r1Grund = new Phi();
    RE* r2Grund = new Eps();
    RE* r3Grund = new Ch('c');
    
    // Erstelle Reguläre Ausdrücke mit new Alt (heißt + im regulären Ausdruck)
    // und in denen sind die Objekte new Phi oder new Ch() gespeichert (r1,r2)
    // somit sieht der Reguläre Ausdruck so aus r3 = (r1 | r2)
    RE* r1Alt = new Alt (new Phi(), new Ch('c'));
    RE* r2Alt = new Alt (new Ch('c'), new Phi());
    RE* r3Alt = new Alt (new Ch('c'), new Ch('c'));
    RE* r4Alt = new Alt (new Ch('a'), new Ch('b'));
    RE* r5Alt = new Alt (new Ch('a'), new Eps());
    RE* r6Alt = new Alt (new Eps(), new Ch('b'));
    
    // Erstelle Reguläre Ausdrücke mit new Star, wo das Objekt r1 mit einem * versehen wird
    // z.B. hier wäre es c** oder {}*
    RE* r1Star = new Star(new Ch('c'));
    RE* r2Star = new Star(new Star (new Ch('c')));
    RE* r3Star = new Star(new Star(new Star (new Ch('c'))));
    RE* r4Star = new Star(new Phi());
    
    // Erstelle Reguläre Ausdrücke mit new Con (heißt Konkatination)
    // und in denen sind die Objekte new Phi oder new Ch() gespeichert (r1,r2)
    // somit sieht der Reguläre Ausdruck so aus r3 = (r1 + r2)
    RE* r1Conc = new Conc (new Phi(), new Ch('c'));
    RE* r2Conc = new Conc (new Ch('c'), new Phi());
    RE* r3Conc = new Conc (new Ch('c'), new Ch('c'));
    RE* r4Conc = new Conc (new Ch('a'), new Ch('b'));
    RE* r5Conc = new Conc (new Ch('a'), new Eps());
    RE* r6Conc = new Conc (new Eps(), new Ch('b'));
    
    cout << "---------------- testClosureTransform() mit Grundsätzlichen -------------------" << endl;
    testClosureTransform(r1Grund, "");
    testClosureTransform(r2Grund, "");
    testClosureTransform(r3Grund, "c");
    cout << "\n" << endl;
    
    cout << "---------------- testClosureTransform() mit Oder-Verknüpfung -------------------" << endl;
    testClosureTransform(r1Alt, "");
    testClosureTransform(r1Alt, "c");
    testClosureTransform(r3Alt, "c");
    testClosureTransform(r3Alt, "cc");
    cout << "\n" << endl;
    
    cout << "---------------- testClosureTransform() mit Kleenesche Huelle ------------------" << endl;
    testClosureTransform(r1Star, "");
    testClosureTransform(r1Star, "c");
    testClosureTransform(r1Star, "cc");
    testClosureTransform(r1Star, "ccc");
    testClosureTransform(r4Star, "");
    testClosureTransform(r4Star, "c");
    cout << "\n" << endl;
    
    cout << "----------------- testClosureTransform() mit Konkatination ---------------------" << endl;
    testClosureTransform(r1Conc, "c");
    testClosureTransform(r1Conc, "cc");
    testClosureTransform(r1Conc, "ccc");
    testClosureTransform(r4Conc, "");
    testClosureTransform(r4Conc, "a");
    testClosureTransform(r4Conc, "ab");
    testClosureTransform(r5Conc, "");
    testClosureTransform(r5Conc, "a");
    testClosureTransform(r5Conc, "ab");
    cout << "\n" << endl;
    
}
