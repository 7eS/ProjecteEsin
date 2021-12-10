#include "laberint.hpp"

//IMPLEMENTACIÓ DE LA CLASSE LABERINT. 

// Constructora d'un laberint buit sense excavar (sense cap porta oberta) de la mida indicada. 
// Totes les cambres del laberint no tenen cap porta.
// Es produeix un error si el número de files o de columnes del laberint és 0.

laberint::laberint(nat num_fil, nat num_col) throw(error){
    
    if(num_fil == 0 or num_col == 0) throw error(FilsColsIncorrecte);
    else{
        _nFil = num_fil;        // és correcte. 
        _nCol = num_col;        // és correcte.

        _lab = new cambra*[_nFil];
        for (int i=0; i < _nFil; i++) {
            _lab[i] = new cambra[_nCol];        // Treballem amb memòria dinàmica. Demanem memòria amb el new. Posteriorment farem deletes.    

        }
    }
}


// Constructora d'un laberint a partir d'un istream (canal d'entrada) is.
// El format de l'istream seguirà l'exposat a l'apartat 2.3. Es presuposa que el laberint és correcte.

laberint::laberint(std::istream & is) throw(error) {
     
     
    string linia;
    bool primLinia = true; //la primera linia correspon al numero de fils i cols. 
    int contLinia = 0;
    util::vector<string> infoLaberint;
    
    posicio p;
    bool nord = false;

    while (getline(is,linia)) {

        if (primLinia) {
            util::split(linia,infoLaberint); //split elimina els espais
            _nFil = util::toint(infoLaberint[0]); //transformem en int. 
            _nCol = util::toint(infoLaberint[1]);
            //std::cout<<"fil: "<<_nFil<<" col: "<<_nCol<<std::endl;
            primLinia = false;
        }
        else{

            // comprovem si estem mirant una linea corresponent a les portes verticals o horitzontals
            if (contLinia%2 != 0) nord = true; 
            else nord = false; 
            
            if (nord){
                std::cout<<"nord: "<<nord<<std::endl;

                for (int j = 1; j < _nCol; j+=2){  
                    
                    p.first = contLinia-1;
                    p.second = j; 
                    // creo que mejorable, las paredes por defecto ya estan cerradas. Entonces solo
                    // habria que tener en cuenta los espacios para abrirla.
                    if (linia[j] == ' ') obre_porta(paret::NORD, p); //funcio obre_porta de laberint.
                    //else obre_porta(paret::NORD,p);
                }
            }else{ //tractem les parets est i oest
            std::cout<<"nord: "<<nord<<std::endl;
                for (int j = 1; j <= _nCol; j+=2){ 
                    p.first = contLinia-1;
                    p.second = j; 
                    if (linia[j] == ' ') obre_porta(paret::OEST,p); //funcio obre_porta de laberint.
                }
            }
        }
        contLinia++;
    }
}
             

// Constructora per còpia, assignació i destructora.

//Constructora per còpia. 
laberint::laberint(const laberint & l) throw(error){

 /*   _nFil = l._nFil;
    _nCol = l._nCol; 
    
    //opcio 1. Modificariem també l(?)
    //cambra ** _lab = l._lab;        // Copiem les direccions de l al p.i. 
    
    //opcio 2
    cambra ** _lab = new cambra*[_nFil];
        for (int i=0; i < _nFil; i++) {
            _lab[i] = new cambra[_nCol];
            _lab[i] = l._lab[i];  
    }
    //opcio 3
    for (int i = 0; i<_nFil; i++) {     //REVISAR AQUESTA FUNCIÓ. segurament els jocs de prova no sortin bé. Fer servir sentinella(?)
        for (int j = 0; j<_nCol; j++) {
            _lab[i][j] = l._lab[i][j];
        }
    } */
}

//Assignació. 
laberint & laberint::operator=(const laberint & l) throw(error){
    
    /*if (*this != l._lab) {
        _nFil = l._nFil;
        _nCol = l._nCol;
    }
    return *this; */
}

//Destructora. 
laberint::~laberint() throw(){
    
    for(int i = 0; i<_nFil; i++) delete[] _lab[i]; //Eliminem les cel·les de la matriu dinàmica. 

    delete[] _lab;         // Eliminem el punter. 
}

// Retornen el número de files i columnes que té el laberint, respectivament.
nat laberint::num_files() const throw(){
    return _nFil; 
}

nat laberint::num_columnes() const throw(){
    return _nCol;
}

// Retorna la cambra situada a la posició especificada per pos.
// Aquest mètode permet utilitzar el laberint d'aquesta manera:
//   laberint l(3,4);
//   posicio pos(2,2);
//   cambra c = l(pos);
// Es produeix un error si la posició donada no existeix al laberint.

cambra laberint::operator()(const posicio & pos) const throw(error){
    if (pos.first >= _nFil or pos.second >= _nCol) {             // Al començar des de 0 li hem de restar 1, per això es >=.
        throw error (PosicioInexistent);
    } 
    else {
        int i = pos.first-1;
        int j = pos.second-1;

        return _lab[i][j];
    }
}

// Obre la porta en la paret donada de la cambra que està especificada per pos. 
// També obre la porta corresponent en la cambra adjacent. 
// Es produeix un error si la posició no existeix o no es pot obrir una porta en la direcció indicada perquè dóna a l'exterior.

void laberint::obre_porta(paret p, const posicio & pos) throw(error) {
    
    if (pos.first >= _nFil or pos.second >= _nCol) {             // Al començar des de 0 li hem de restar 1, per això es >=.
        throw error (PosicioInexistent);
    }
    else if (portaExterior(p, pos)) throw error (PortaExterior);                       // comprovar si la paret està al perímetre del laberint. 

    else{
        int i = pos.first-1;
        int j = pos.second-1;
        _lab[i][j].obre_porta(p);

        if (p == paret::NORD) _lab[i][j+1].obre_porta(p.SUD);    // and p == p.NORD.
        else if (p == paret::SUD) _lab[i][j-1].obre_porta(p.NORD);
        else if (p == paret::OEST) _lab[i-1][j].obre_porta(p.EST);
        else if (p == paret::EST) _lab[i+1][j].obre_porta(p.OEST);
    }
}

// Tanca la porta en la paret donada de la cambra que està especificada per pos. També tanca la porta corresponent en la cambra adjacent. 
//Es produeix un error si la posició no existeix.

void laberint::tanca_porta(paret p, const posicio & pos) throw(error){

    if (pos.first >= _nFil or pos.second >= _nCol) {             // Al començar des de 0 li hem de restar 1, per això es >=.
        throw error (PosicioInexistent);
    }
    
    else{
        int i = pos.first-1;
        int j = pos.second-1;
        _lab[i][j].tanca_porta(p);

        if (p == paret::NORD) _lab[i][j+1].tanca_porta(paret::SUD);       // and p == p.NORD.
        else if (p == paret::SUD) _lab[i][j-1].tanca_porta(paret::NORD);
        else if (p == paret::OEST) _lab[i-1][j].tanca_porta(paret::EST);
        else if (p == paret::EST) _lab[i+1][j].tanca_porta(paret::OEST);
    }
}

// Escriu el laberint a l'ostream (canal de sortida) os. El format per escriure el laberint seguirà l'exposat a l'apartat 2.3.

void laberint::print(std::ostream & os) const throw() {

    os<<_nFil<< " "<<_nCol<<std::endl; 
    for(nat i = 0; i<_nFil; i++){

        os<<"*";
        for (nat j = 0; j<_nCol; j++) { //Pintem parets verticals menys la última del sud

            if (_lab[i][j].porta_oberta(paret::NORD)){
                os<<" ";
                 //os<<"nord estic oberta";
                 }
            else os<<"*";

        os<<"*";
        }

        os<<std::endl;

        for (nat j = 0; j <_nCol; j++){ //Pintem partes horitzontals
        
            if (_lab[i][j].porta_oberta(paret::OEST)){
                 os<<" ";
                //os<<"oest estic oberta";
            } 
            else os<<"*";
        os<<" ";

        }
        os<<"*";
        os<<std::endl;    
    
        if(i == _nFil-1){
            os<<"*";
            for (nat j = 0; j <_nCol; j++){ //Pintem  la darrera paret sud
                os<<"*";
            os<<"*";
            }
            os<<std::endl; 
        }
    }

}

bool laberint::portaExterior(paret p, posicio pos) {
// Pre: p és una paret d'una cambra del laberint i pos es una posicio existent del laberint.
// Post: Retorna true si p és una porta exterior, altrament false. 

    // pos.first/second -1 es provisional, cal veure q tal funciona més endavant
    if (pos.first-1 == 0 and p == paret::NORD) return true;             // and p == p.NORD.               
    else if (pos.first-1 == _nFil and p == paret::SUD) return true;    
    else if (pos.second-1 == 0 and p == paret::OEST) return true;      
    else if (pos.second-1 == _nCol and p == paret::EST) return true;  

    return false; 
}

