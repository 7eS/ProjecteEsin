#include "laberint.hpp"


// Constructora d'un laberint buit sense excavar (sense cap porta oberta)
// de la mida indicada. Totes les cambres del laberint no tenen cap porta.
// Es produeix un error si el número de files o de columnes del laberint és 0.
laberint::laberint(nat num_fil, nat num_col) throw(error){
    
    if(num_fil == 0 or num_col == 0) throw error(FilsColsIncorrecte);
    else{
        _nFil = num_fil;
        _nCol = num_col;
        _lab[_nFil][_nCol];
    }
}

// Constructora d'un laberint a partir d'un istream (canal d'entrada) is.
// El format de l'istream seguirà l'exposat a l'apartat 2.3. Es presuposa que
// el laberint és correcte.
laberint::laberint(std::istream & is) throw(error){
    
    // esta mal, pero compila. Toca rehacer bien esto
    is >> _nFil;
    is >> _nCol;
    _lab[_nFil][_nCol];

}

// Constructora per còpia, assignació i destructora.
laberint::laberint(const laberint & l) throw(error){}
laberint & laberint::operator=(const laberint & l) throw(error){}
laberint::~laberint() throw(){}

// Retornen el número de files i columnes que té el laberint, respectivament.
nat laberint::num_files() const throw(){}
nat laberint::num_columnes() const throw(){}

// Retorna la cambra situada a la posició especificada per pos.
// Aquest mètode permet utilitzar el laberint d'aquesta manera:
//   laberint l(3,4);
//   posicio pos(2,2);
//   cambra c = l(pos);
// Es produeix un error si la posició donada no existeix al laberint.
cambra laberint::operator()(const posicio & pos) const throw(error){}

// Obre la porta en la paret donada de la cambra que està especificada per pos.
// També obre la porta corresponent en la cambra adjacent. Es produeix un error
// si la posició no existeix o no es pot obrir una porta en la direcció
// indicada perquè dóna a l'exterior.
void laberint::obre_porta(paret p, const posicio & pos) throw(error){}

// Tanca la porta en la paret donada de la cambra que està especificada per pos.
// També tanca la porta corresponent en la cambra adjacent. Es produeix un error
// si la posició no existeix.
void laberint::tanca_porta(paret p, const posicio & pos) throw(error){}

// Escriu el laberint a l'ostream (canal de sortida) os. El format per escriure
// el laberint seguirà l'exposat a l'apartat 2.3.
void laberint::print(std::ostream & os) const throw(){}
