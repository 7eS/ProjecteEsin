#include "cambra.hpp"

// // IMPLEMENTACIÓ DE LA CLASSE CAMBRA. 

// Construeix una cambra amb les portes als llocs indicats.
cambra::cambra(bool n, bool s, bool e, bool o) throw(error){	
                   
    _portaN = n;
    _portaS = s;
    _portaE = e;
    _portaO = o;
    //incializar 
    _quantesPO = 0;
    if(n == true) _quantesPO++;
    if(s == true) _quantesPO++;
    if(e == true) _quantesPO++;
    if(o == true) _quantesPO++;
}

// Constructora per còpia, assignació i destructora.
cambra::cambra(const cambra & c) throw(error){
    _portaN = c._portaN;
    _portaS = c._portaS;
    _portaE = c._portaE;
    _portaO = c._portaO;
    _quantesPO = c._quantesPO;

}

cambra & cambra::operator=(const cambra & c) throw(error){
    _portaN = c._portaN;
    _portaS = c._portaS;
    _portaE = c._portaE;
    _portaO = c._portaO;
    _quantesPO = c._quantesPO;

    return *this;
}

cambra::~cambra() throw(){}     //Utilitzem memòria estàtica. 


// Retorna si l'habitació té una porta oberta a la paret indicada.
bool cambra::porta_oberta(paret p) const throw(){						

    //Mirar si la paret es ==NORD, sud, etc. 
    
    bool oberta = false;
      
    if (p == paret::NORD) return _portaN; 		
    else if (p == paret::SUD) return _portaS;
    else if (p == paret::EST) return _portaE;
    else if (p == paret::OEST) return _portaO; 		//enum de la classe paret. fa falta possar paret:: perque es a la classe paret a on esta definit. 
    //else throw error (ParetInexistent); 			//ens pasen NODIR. No hem de posar error ja que a la capçalera no hi ha res al parentesi. 
    else return oberta;
    
    //retorna _portaX el qual es un boolea, si es true està oberta, altrament està tancada.
}

// Obre una nova porta a la paret indicada. Si la porta ja està oberta no fa res. Es produeix un error si la paret és NO_DIR.

void cambra::obre_porta(paret p) throw(error){						

    if (p == paret::NO_DIR)throw error (ParetInexistent);
    
    else if (not porta_oberta(p)) {

        if (p == paret::NORD) {			
            _portaN = true;
            _quantesPO++;
        }
        else if (p == paret::SUD) {
            _portaS = true;
            _quantesPO++;
        }
        else if (p == paret::EST) {
            _portaE = true;
            _quantesPO++;
        }
        else if (p == paret::OEST) {
            _portaO = true;
            _quantesPO++;
        }
    }
}

// Tanca la porta a la paret indicada. Si la porta ja estava tancada no fa res. Es produeix un error si la paret és NO_DIR.

void cambra::tanca_porta(paret p) throw(error) {

    if (p == paret::NO_DIR) throw error (ParetInexistent);
    
    else if (porta_oberta(p)) {

        if (p == paret::NORD) {
            _portaN = false;
            _quantesPO--;
        }
        else if (p == paret::SUD) {
            _portaS = false;
            _quantesPO--;
        }
        else if (p == paret::EST) {
            _portaE = false;
            _quantesPO--;
        }
        else if (p == paret::OEST) {
            _portaO = false;
            _quantesPO--;
        }
    }
}

// Igualtat i desigualtat entre cambres. Dues cambres es consideren iguals si tenen les mateixes portes obertes a les mateixes parets.

bool cambra::operator==(const cambra & c) const throw() {
    bool iguals = true;

    if (_quantesPO != c._quantesPO) iguals = false;
    
    else {
        if (_portaN != c._portaN) iguals = false;
        else if (_portaS != c._portaS) iguals = false;
        else if (_portaE != c._portaE) iguals = false;
        else if (_portaO != c._portaO) iguals = false;
    }

    return iguals; // totes les portes estan igual.
}


bool cambra::operator!=(const cambra & c) const throw() {
    return not (*this==c);
}

// Operador "menor que" entre cambres. Una cambra és més petita que una altra si té més portes tancades que l'altra. Tenint en compte que una
// porta tancada és més petita que una porta oberta, en cas que tinguin el mateix número de portes tancades, per decidir qui és més petit es miraran
// les portes en aquest ordre NORD, EST, SUD i OEST. Per exemple:
//   cambra c1, c2(true,true), c3(true, false, true); //nord, sud, est, oest.
//   cout << (c1 < c2); // escriu 'true'
//   cout << (c2 < c3); // escriu 'true'

bool cambra::operator<(const cambra & c) const throw() {
   

    if(_quantesPO < c._quantesPO){
        return true;
        }
    if(_quantesPO > c._quantesPO){
        return false;
        }

    else if((_quantesPO == 0 and c._quantesPO == 0)  or (_quantesPO == 4 and c._quantesPO == 4)) return false; 
    else if((_quantesPO > 0 and c._quantesPO > 0) and (_quantesPO == c._quantesPO)) { 
        // Per als casos on _quantesPO: 1-1, 2-2 i 3-3 (_quantesPO == 1 and c._quantesPO == 1 etc etc)
        
        /*
        false - false -> pi == c 
        false - true -> pi < c
        true - false -> pi > c
        true - true  -> pi == c
        */
        bool mesPetita = false;
        bool surt = false;

       if(not _portaN and c._portaN){
           mesPetita = true;
           surt = true;
           }
       else if(_portaN and not c._portaN){
           surt = true;
           mesPetita = false;
       }
       else{ //Ambdues portes Nord iguals
            if((not _portaE and c._portaE) and not surt){
                surt = true;
                mesPetita = true;
            }
            else if(_portaE and not c._portaE){
                surt = true;
                mesPetita = false;
            }
            else { //Ambdues portes EST iguals
                if((not _portaS and c._portaS) and not surt){
                    mesPetita = true;
                    surt = true;
                }
                else if(_portaS and not c._portaS){
                    mesPetita = false;
                    surt = true;
                }
                else{
                    if((not _portaO and c._portaO) and not surt){
                        mesPetita = true;
                }
                    else if(_portaO and not c._portaO){
                        mesPetita = false;
                }
            }
         }
       }
       return mesPetita;
    }
    return false;
}

