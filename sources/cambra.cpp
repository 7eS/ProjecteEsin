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

cambra::~cambra() throw(){} //Utilitzem memòria estàtica. 


// Retorna si l'habitació té una porta oberta a la paret indicada.
bool cambra::porta_oberta(paret p) const throw(){						//AQUESTA FUNCIO ESTABA MALAMENT. ARA ESTÀ ARREGLADA.

    //Mirar si la paret es ==NORD, sud, etc. 
    
      
    if (p == paret::NORD) return _portaN; 		//FUNCIO ARREGLADA BY PATRICIA, 1 DE DECEMBRE. 
    else if (p == paret::SUD) return _portaS;
    else if (p == paret::EST) return _portaE;
    else if (p == paret::OEST) return _portaO; 		//enum de la classe paret. fa falta possar paret:: perque es a la classe paret a on esta definit. 
    else throw error (ParetInexistent); 			//ens pasen NODIR
    
    //retorna _portaX el qual es un boolea, si es true està oberta, altrament està tancada.
}

// Obre una nova porta a la paret indicada. Si la porta ja està oberta no fa res. Es produeix un error si la paret és NO_DIR.

void cambra::obre_porta(paret p) throw(error){						//AQUESTA FUNCIO ESTABA MALAMENT. ARA ESTÀ ARREGLADA.

    if(p == paret::NO_DIR)throw error (ParetInexistent);
    
    else if(not porta_oberta(p)){

        if(p == paret::NORD){			//FUNCIO ARREGLADA BY PATRICIA ,1 DE DECEMBRE. 
            _portaN = true;
            _quantesPO++;
        }
        else if(p == paret::SUD){
            _portaS = true;
            _quantesPO++;
        }
        else if(p == paret::EST){
            _portaE = true;
            _quantesPO++;
        }
        else if(p == paret::OEST){
            _portaO = true;
            _quantesPO++;
        }
    }
}

// Tanca la porta a la paret indicada. Si la porta ja estava tancada no fa res. Es produeix un error si la paret és NO_DIR.

void cambra::tanca_porta(paret p) throw(error){				//AQUESTA FUNCIO ESTABA MALAMENT. ARA ESTÀ ARREGLADA.

    if(p == paret::NO_DIR)throw error (ParetInexistent);
    
    else if(porta_oberta(p)){

        if(p == paret::NORD){				//FUNCIO ARREGLADA BY PATRICIA ,1 DE DECEMBRE. 
            _portaN = false;
            _quantesPO--;
        }
        else if(p == paret::SUD){
            _portaS = false;
            _quantesPO--;
        }
        else if(p == paret::EST){
            _portaE = false;
            _quantesPO--;
        }
        else if(p == paret::OEST){
            _portaO = false;
            _quantesPO--;
        }
    }
}

// Igualtat i desigualtat entre cambres. Dues cambres es consideren iguals si tenen les mateixes portes obertes a les mateixes parets.

bool cambra::operator==(const cambra & c) const throw(){
    bool iguals = true;

    if(_quantesPO != c._quantesPO) iguals = false;
    
    else{
        if(_portaN != c._portaN) iguals = false;
        else if(_portaS != c._portaS) iguals = false;
        else if(_portaE != c._portaE) iguals = false;
        else if (_portaO != c._portaO) iguals = false;
    }

    return iguals; // totes les portes estan igual.
}


bool cambra::operator!=(const cambra & c) const throw(){
    return not (*this==c);
}

// Operador "menor que" entre cambres. Una cambra és més petita que una altra si té més portes tancades que l'altra. Tenint en compte que una
// porta tancada és més petita que una porta oberta, en cas que tinguin el mateix número de portes tancades, per decidir qui és més petit es miraran
// les portes en aquest ordre NORD, EST, SUD i OEST. Per exemple:
//   cambra c1, c2(true,true), c3(true, false, true);
//   cout << (c1 < c2); // escriu 'true'
//   cout << (c2 < c3); // escriu 'true'

bool cambra::operator<(const cambra & c) const throw(){
   
    bool mesPetita = true;

    if(_quantesPO > c._quantesPO) mesPetita = false;

    else if((_quantesPO == 0 and c._quantesPO == 0)  or (_quantesPO == 4 and c._quantesPO == 4)) mesPetita = false; 
    else if((_quantesPO > 0 and c._quantesPO > 0) and (_quantesPO == c._quantesPO)){ 
        // Es podria optimitzar deixant només els 4 if d'abaix :)
        // El Jordi valorarà la senzillesa del codi
        // Per als casos on _quantesPO: 1-1, 2-2 i 3-3
        
        /*
        false - false -> pi == c 
        false - true -> pi < c
        true - false -> pi > c
        true - true  -> pi == c
        */

        if(not (_portaN == false and c._portaN == true)) mesPetita = false;
        else if(not (_portaE == false and c._portaE == true)) mesPetita = false;
        else if(not (_portaS == false and c._portaS == true)) mesPetita = false;
        else if(not (_portaO == false and c._portaO == true)) mesPetita = false;
    }
    return mesPetita;
}

