
// Endliche Automaten

#ifndef __FSA__
#define __FSA__

#include <vector>
#include <string>
#include <algorithm>


using namespace std;

class Transition;
class NFA;
class FSA;



class Transition {
private:
    int from;
    char c;
    int to;
    bool epsilon;
public:
    
    Transition(int _from, int _to) {
        from = _from; to = _to;
        epsilon = true;
    }
    Transition(int _from, char _c, int _to) {
        from = _from; c = _c; to = _to;
        epsilon = false;
    }
    bool isEpsilonTransition() { return epsilon; }
    int toState() { return to; }
    bool trigger(int from, char c) {
        return (!epsilon && from == this->from && c == this->c);
    }
    bool trigger(int from) {
        return (epsilon && from == this->from);
    }
};

class NFA {
private:
    vector<Transition> ts;
    int init;
    vector<int> final;
    
public:
    NFA(vector<Transition> _ts, int _init, vector<int> _final) {
        ts = _ts;
        init = _init;
        final = _final;
    }
    NFA(vector<Transition> _ts, int _init, int _final) {
        ts = _ts;
        init = _init;
        final.push_back(_final);
    }
    vector<Transition> getTransitions() { return ts; }
    int getInitial() { return init; }
    vector<int> getFinals() { return final; }
    
    friend class FSA;
};

class FSA : public NFA {
private:
    vector<int> current;
    void closure();
public:
    FSA(NFA fsa) : NFA(fsa.ts,fsa.init,fsa.final) {
        current.push_back(init);
        closure();
    }
    void reset();
    void step(char c);
    bool isFinal();
    bool run(string s);
    
};

void FSA::reset() {
    current.clear();
    current.push_back(init);
    closure();
}

bool FSA::isFinal() {
    for(int i = 0; i < (signed)final.size(); i++) {
        if(find(current.begin(),current.end(),final[i]) != current.end()){
            return true;
        }
    }
    return false;
}

// Die Funktion closure soll alle *leere* Transitionen herausfiltern und
// läuft, solange ein Zustand gefunden wird. Denn nur Phi und Ch erzeugen
// keinen neuen Zustand. Oder solange bis das Ende des Wortes erreicht ist.
//
// Beispiel: ab
//
void FSA::closure() {
    
    bool changed;
    
    // Die Schleife läuft mindestens einmal und ewig
    // solange ein Zustand hinzugefügt wird
    do {
        changed = false;
        
        // Geht alle Übergänge im ausgewählten NFA durch
        for (int i = 0; i < ts.size(); i++) {
            Transition t = ts[i];
            
            // Wenn der aktuelle Übergang  ein Eps-Übergang ist,
            // Überspringt er diesen und filtert alle heraus.
            if (t.isEpsilonTransition()){
                
                // Überprüfen, ob ein Element in einem Vektor ist
                // Wenn das Element NICHT im Vektor ist, also find() != current.end
                // Dann gehe weiter
                if (find(current.begin(), current.end(), t.toState()) == current.end()) {
                    
                    
                    //aktuelle Zustände iterieren
                    for (int j = 0; j < current.size(); j++) {
                        
                        //Hat irgendeine Transition einen current als Startpunkt?
                        if (t.trigger((int)current[j])) {
                            
                            
                            //Falls ja: Zustand wird hinzugefügt
                            current.push_back(t.toState());
                            changed = true;
                            
                        }
                        
                        
                    }
                    
                }
                
            }
            
        }
        
    } while(changed);
    
}


void FSA::step(char c) {
    vector<int> next;
    for(int i=0; i < ts.size(); i++) {
        for (int j=0; j < current.size(); j++) {
            if(ts[i].trigger((int)current[j],c))
                next.push_back(ts[i].toState());
        }
    }
    current = next;
    closure();
}

bool FSA::run(string s) {
    reset();
    for(int i=0; i < s.length(); i++) {
        step(s[i]);
    }
    return isFinal();
}

#endif // __FSA__
