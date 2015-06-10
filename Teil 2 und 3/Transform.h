
// Ein moeglicher Rahmen fuer Aufgabe 4, zweite Teilaufgabe,
// uebersetze regulaeren Ausdruck in einen NFA.
// Der Einfachheit in ein .h File gepackt.


#include <iostream>

using namespace std;

#include "FSA.h"
#include "RE.h"


int nameSupply;

void init() {
    nameSupply = 0;
}

int fresh() {
    return nameSupply++;
}


// Macht die eigentliche Arbeit
NFA transformWorker(RE *r);

// Schnittstelle fuer Benutzer
// Ruecksetzen des "name supplies" zur Generierung von eindeutigen Zustaenden
// Aufruf von transform2
NFA transform(RE *r) {
    init();
    return transformWorker(r);
}


// Wir liefern einen NFA zurueck mit genau einem Start und
// genau einem Stop(end)zustand.
NFA transformWorker(RE *r) {
    vector<Transition> ts;
    int start, stop;
    
    switch(r->ofType()) {
            
            // Eps akzeptiert das leere Wort. Deswegen besteht das NFA aus
            // einem Start und Stopzustand und die Vectorliste fügt eine leere Transition
            // mit Start- zum Stopzustand hinzu
            //
            // Beispiel: start -----> stop
            //
        case EpsType: {
            start = fresh();
            stop = fresh();
            ts.push_back(Transition(start,stop));
            return NFA(ts, start, stop);
        }
            
            // Ch akzeptiert ein einzelnes Zeichen. Deswegen besteht das NFA aus
            // einem Start und Stopzustand und die Vectorliste fügt eine Transition
            // mit dem Zeichen und dem Start- und Stopzustand hinzu
            //
            // Beispiel: start --- c ---> stop
            //
        case ChType: {
            Ch* r2 = (Ch*) r;
            start = fresh();
            stop = fresh();
            ts.push_back(Transition(start, r2->getChar(), stop));
            return NFA(ts, start, stop);
        }
            
            // Phi akzeptiert kein Wort. Deswegen besteht das NFA aus einem
            // Start und Stopzustand und *keiner* Transition (Übergang)
            //
            // Beispiel: kein ‹bergang
            //
        case PhiType: {
            start = fresh();
            stop = fresh();
            return NFA(ts, start, stop);
        }
            
            // Alt hat 2 verschiedene Zeichen, von denen 1 Zeichen akzeptiert wird.
            // Deswegen ergibt es sich im NFA nur ein Start- und Stopzustand. Jedoch hat
            // es 4 *leere* Transition (Übergänge).
            //
            // Denn wenn man das linke Zeichen wählt. Baut man zu Beginn den Übergang von dem Startzustand zum
            // linken NFA und dann vom linken NFA zum Stopzustand.
            //
            // Beispiel: a | b
            // start ----> startVonTyp --- a ---> stopVonTyp ----> stop
            // start ----> startVonTyp --- b ---> stopVonTyp ----> stop
            //
        case AltType: {
            Alt* r2 = (Alt*) r;
            
            // 1. Baue NFAs der linken und rechten Alternative
            NFA n1 = transformWorker(r2->getLeft());
            NFA n2 = transformWorker(r2->getRight());
            
            // 2. Generieren neuen Start-/Stopzustand.
            //    Sammle Start-/Stopzustaende von n1 und n2
            // N.B. Annahme: finals besteht aus genau einem Zustand
            start = fresh();
            stop = fresh();
            int n1_start = n1.getInitial();
            int n1_stop  = n1.getFinals()[0];
            int n2_start = n2.getInitial();
            int n2_stop  = n2.getFinals()[0];
            
            
            // 3. Sammle Transitionen auf von n1 und n2.
            //    Verbinde neuen Start-/Endzustand mit alten Start-/Endzustaenden.
            vector<Transition> t1 = n1.getTransitions();
            vector<Transition> t2 = n2.getTransitions();
            
            ts.insert(ts.end(),t1.begin(),t1.end());
            ts.insert(ts.end(),t2.begin(),t2.end());
            ts.push_back(Transition(start, n1_start));
            ts.push_back(Transition(start, n2_start));
            ts.push_back(Transition(n1_stop, stop));
            ts.push_back(Transition(n2_stop, stop));
            
            return NFA(ts,start,stop);
        }
            
            // Conc hat 2 verschiedene Zeichen, die hintereinander ausgeführt werden.
            // Es ergibt sich im NFA, dass Startzustand, der Startzustand vom linken NFA
            // und Stopzustand, der Stopzustand vom rechten NFA ist. Deswegen hat es eine
            // *leere* Transition (Übergang) vom linken zum rechten NFA.
            //
            // Beispiel: ab
            // startVonTyp --- a ---> stopVonTyp ----> startVonTyp --- b ---> stopVonTyp
            //
            //Erst muss geschaut werden, welche beiden regulären Ausdrücke kontateniert werden

        case ConcType: {
            Conc* r2 = (Conc*) r;
            NFA n1 = transformWorker(r2->getLeft());
            NFA n2 = transformWorker(r2->getRight());
            
            start = n1.getInitial();
            stop = n2.getFinals()[0];
            
            int n1_end = n1.getFinals()[0];
            int n2_start = n2.getInitial();
            
            vector<Transition> t1 = n1.getTransitions();
            vector<Transition> t2 = n2.getTransitions();
            
            ts.insert(ts.end(), t1.begin(), t1.end());
            ts.push_back(Transition(n1_end, n2_start));
            ts.insert(ts.end(), t2.begin(), t2.end());
            
            return NFA(ts, start, stop); 
        }
            
            // Star hat 1 Zeichen, das keinmal oder unendlichmal ausgeführt werden kann.
            // Es ergibt sich im NFA, dass ein Startzustand und Stopzustand erstellt wird. 
            // Jedoch benötigt es 3 *leere* Transition (Übergang).
            //
            // Beispiel: a*
            
            // start ----> stop		// Dies ist die Transition wenn es keinmal wiederholt werden soll.
            // start ----> startVonTyp --- b ---> stopVonTyp ----> stop		// unendliche Transition 
            //
        case StarType: {
            Star* r2 = (Star*) r;
            NFA n1 = transformWorker(r2->getRE());
            start = fresh();
            stop = fresh();
            int n1_start = n1.getInitial();
            int n1_stop = n1.getFinals()[0];
            
            
            vector<Transition> t1 = n1.getTransitions();
            
            ts.insert(ts.end(), t1.begin(), t1.end());
            //Für Epsilon
            ts.push_back(Transition(start, stop));
            
            //Vom Startzustand muss der Startzustand des regulären ausdrucks unter dem
            //* erreicht werden können
            ts.push_back(Transition(start, n1_start));
            //Nachdem der reguläre Ausdruck abgearbeitet wurden, muss er sich nochmal ausführen lassen
            //(Beispiel a*, nun ersetze a* durch z.b (ab)*. Man muss von b immer wieder zu a kommen.
            ts.push_back(Transition(n1_stop, n1_start));
            
            //Ist der reguläre Ausdruck abgearbeitet, kann er zum stop zustand führen
            ts.push_back(Transition(n1_stop, stop)); 
            return NFA(ts, start, stop);
        }
            
            
    } // switch
    
    
} // transformWorker