#include "cambra.hpp"

// Construeix una cambra amb les portes als llocs indicats.
cambra::cambra(bool n, bool s,
                bool e, bool o) throw(error){
                    _portaN = n;
                    _portaS = s;
                    _portaE = e;
                    _portaO = o;
                }

// Constructora per còpia, assignació i destructora.
cambra::cambra(const cambra & c) throw(error){}
cambra & cambra::operator=(const cambra & c) throw(error){}
cambra::~cambra() throw(){}

// Retorna si l'habitació té una porta oberta a la paret indicada.
bool cambra::porta_oberta(paret p) const throw(){}

// Obre una nova porta a la paret indicada. Si la porta ja està oberta no
// fa res. Es produeix un error si la paret és NO_DIR.
void cambra::obre_porta(paret p) throw(error){}

// Tanca la porta a la paret indicada. Si la porta ja estava tancada no
// fa res. Es produeix un error si la paret és NO_DIR.
void cambra::tanca_porta(paret p) throw(error){}

// Igualtat i desigualtat entre cambres. Dues cambres es consideren iguals
// si tenen les mateixes portes obertes a les mateixes parets.
bool cambra::operator==(const cambra & c) const throw(){}
bool cambra::operator!=(const cambra & c) const throw(){}

// Operador "menor que" entre cambres. Una cambra és més petita que una
// altra si té més portes tancades que l'altra. Tenint en compte que una
// porta tancada és més petita que una porta oberta, en cas que tinguin el
// mateix número de portes tancades, per decidir qui és més petit es miraran
// les portes en aquest ordre NORD, EST, SUD i OEST. Per exemple:
//   cambra c1, c2(true,true), c3(true, false, true);
//   cout << (c1 < c2); // escriu 'true'
//   cout << (c2 < c3); // escriu 'true'
bool cambra::operator<(const cambra & c) const throw(){}