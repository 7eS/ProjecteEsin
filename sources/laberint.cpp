#include "laberint.hpp"

// IMPLEMENTACIÓ DE LA CLASSE LABERINT.

// Constructora d'un laberint buit sense excavar (sense cap porta oberta) de la
// mida indicada. Totes les cambres del laberint no tenen cap porta. Es produeix
// un error si el número de files o de columnes del laberint és 0.

laberint::laberint(nat num_fil, nat num_col) throw(error) {
    if (num_fil == 0 or num_col == 0)
        throw error(FilsColsIncorrecte);
    else {
        _nFil = num_fil;  // és correcte.
        _nCol = num_col;  // és correcte.

        _lab = new cambra *[_nFil];
        for (int i = 0; i < _nFil; i++) {
            _lab[i] = new cambra[_nCol];  // Treballem amb memòria dinàmica.
                                          // Demanem memòria amb el new.
                                          // Posteriorment farem deletes.
        }
    }
}

// Constructora d'un laberint a partir d'un istream (canal d'entrada) is.
// El format de l'istream seguirà l'exposat a l'apartat 2.3. Es presuposa que el
// laberint és correcte.

laberint::laberint(std::istream &is) throw(error) {
    string linia;
    bool primLinia = true;  // la primera linia correspon al numero de fils i cols.
    int contLinia = 0;
    util::vector<string> infoLaberint;

    posicio p;
    bool nord = false;

    while (getline(is, linia)) {
        if (primLinia)  // Obtenim el tamany de les files i de les columnes
        {
            util::split(linia, infoLaberint);      // split elimina els espais
            _nFil = util::toint(infoLaberint[0]);  // transformem en int.
            _nCol = util::toint(infoLaberint[1]);

            _lab = new cambra *[_nFil];

            for (int i = 0; i < _nFil; i++) {
                _lab[i] = new cambra[_nCol];  // Treballem amb memòria dstinàmica.
                                        // Demanem memòria amb el new.
                                        // Posteriorment farem deletes.
            }
        }
        if (not primLinia and contLinia-1 < _nFil*2)  // Obtenim les linies del laberint.
        {
            // comprovem si estem mirant una linea corresponent a les portes
            // verticals o horitzontals
            if (contLinia % 2 != 0)
                nord = true;
            else
                nord = false;

            for (int j = 0; j < _nCol; j++) {
                int jlin;

                if (nord) {
                    jlin = j * 2 + 1;   // obtenim la pos de la porta quan mirem el nord.
                } else {
                    jlin = j * 2;       // obtenim la pos de la porta quan mirem oest.
                }

                // La funcio obre porta ja s'encarrega de restar una unitat a la
                // coordenada
                int i = (contLinia-1)/2;
                p.first = i + 1;
                p.second = j + 1;  // la primera cambra és la pos 1,1.
                // if(contLinia < 5)

                if (linia[jlin] == ' ') {
                    //std::cout<<"contLinia: "<<contLinia<<std::endl;
                    if (nord) {
                        obre_porta(paret::NORD, p);  // funcio obre_porta de laberint.
                        // no pasa el obre porta
                    } else {
                        obre_porta(paret::OEST, p);
                    }
                }
            }
        }
        contLinia++;
        if (primLinia) primLinia = false;

    }
}

// Constructora per còpia, assignació i destructora.

// Constructora per còpia.
laberint::laberint(const laberint &l) throw(error) {
    
    _nFil = l._nFil;
    _nCol = l._nCol;

    _lab = new cambra *[_nFil];

    for (int i = 0; i < _nFil; i++) {
        _lab[i] = new cambra[_nCol];
    }
    for (int i = 0; i < _nFil; i++) { 
        for (int j = 0; j < _nCol; j++) {
            _lab[i][j] = l._lab[i][j];
        }
    }
}

// Assignació.
laberint &laberint::operator=(const laberint &l) throw(error) {
    if (this != &l) {
        if (_nFil != l._nFil and _nCol != l._nCol) {
            // Si són de mides diferents els destruim.
            for (int i = 0; i < _nFil; i++)
                delete[] _lab[i];  // Eliminem les cel·les de la matriu
                                   // dinàmica.
            
            delete[] _lab;  // Eliminem el punter.
            _nFil = l._nFil;
            _nCol = l._nCol;
            
            _lab = new cambra *[_nFil];

            for (int i = 0; i < _nFil; i++) {
                _lab[i] = new cambra[_nCol];
            }
        }
        for (int i = 0; i < _nFil; i++) { 
            for (int j = 0; j < _nCol; j++) {
                _lab[i][j] = l._lab[i][j];
            }
        }
    }
    return *this;
}

// Destructora.
laberint::~laberint() throw() {
    for (int i = 0; i < _nFil; i++)
        delete[] _lab[i];  // Eliminem les cel·les de la matriu dinàmica.

    delete[] _lab;  // Eliminem el punter.
}

// Retornen el número de files i columnes que té el laberint, respectivament.
nat laberint::num_files() const throw() { 
    return _nFil; 
    }

nat laberint::num_columnes() const throw() { 
    return _nCol;
    }

// Retorna la cambra situada a la posició especificada per pos.
// Aquest mètode permet utilitzar el laberint d'aquesta manera:
//   laberint l(3,4);
//   posicio pos(2,2);
//   cambra c = l(pos);
// Es produeix un error si la posició donada no existeix al laberint.

cambra laberint::operator()(const posicio &pos) const throw(error) {
    if (pos.first > _nFil or pos.second > _nCol or pos.first < 1 or pos.second < 1) {  // Al començar des de 0 li hem de restar 1, per això es >=.
        throw error(PosicioInexistent);

    } else {
        int i = pos.first - 1;
        int j = pos.second - 1;

        return _lab[i][j];
    }
}

// Obre la porta en la paret donada de la cambra que està especificada per pos.
// També obre la porta corresponent en la cambra adjacent.
// Es produeix un error si la posició no existeix o no es pot obrir una porta en
// la direcció indicada perquè dóna a l'exterior.

void laberint::obre_porta(paret p, const posicio &pos) throw(error) {
    if (pos.first > _nFil or pos.second > _nCol or pos.first < 1 or pos.second < 1) {  // Al començar des de 0 li hem de restar 1, per això es >=.
        throw error(PosicioInexistent);

    } else if (portaExterior(p, pos)) {
        throw error(PortaExterior);  // comprova si la paret està al perímetre
                                     // del laberint.
    } else {
        int i = pos.first - 1;
        int j = pos.second - 1;
        _lab[i][j].obre_porta(p);

        if (p == paret::NORD)
            _lab[i - 1][j].obre_porta(p.SUD);  // and p == p.NORD.
        else if (p == paret::SUD)
            _lab[i + 1][j].obre_porta(p.NORD);
        else if (p == paret::OEST)
            _lab[i][j - 1].obre_porta(p.EST);
        else if (p == paret::EST)
            _lab[i][j + 1].obre_porta(p.OEST);
    }
}

// Tanca la porta en la paret donada de la cambra que està especificada per pos.
// També tanca la porta corresponent en la cambra adjacent.
// Es produeix un error si la posició no existeix.

void laberint::tanca_porta(paret p, const posicio &pos) throw(error) {
    if (pos.first > _nFil or pos.second > _nCol or pos.first < 1 or pos.second < 1) {  // Al començar des de 0 li hem de restar 1, per això es >=.
        throw error(PosicioInexistent);
    } else {
        int i = pos.first - 1;
        int j = pos.second - 1;
        _lab[i][j].tanca_porta(p);

        if (not portaExterior(p, pos)) {
            if (p == paret::NORD)
                _lab[i - 1][j].tanca_porta(paret::SUD);  // and p == p.NORD.
            else if (p == paret::SUD)
                _lab[i + 1][j].tanca_porta(paret::NORD);
            else if (p == paret::OEST)
                _lab[i][j - 1].tanca_porta(paret::EST);
            else if (p == paret::EST)
                _lab[i][j + 1].tanca_porta(paret::OEST);
        }
    }
}

// Escriu el laberint a l'ostream (canal de sortida) os. El format per escriure
// el laberint seguirà l'exposat a l'apartat 2.3.

void laberint::print(std::ostream &os) const throw() {
    os << _nFil << " " << _nCol << std::endl;
    for (nat i = 0; i < _nFil; i++) {
        os << "*";
        for (nat j = 0; j < _nCol; j++) {  // Pintem parets verticals menys la última del sud

            if (_lab[i][j].porta_oberta(paret::NORD)) {
                os << " ";
                // os<<"nord estic oberta";
            } else
                os << "*";

            os << "*";
        }

        os << std::endl;

        for (nat j = 0; j < _nCol; j++) {  // Pintem partes horitzontals

            if (_lab[i][j].porta_oberta(paret::OEST)) {
                os << " ";
                // os<<"oest estic oberta";
            } else
                os << "*";
            os << " ";
        }
        os << "*";
        os << std::endl;

        if (i == _nFil - 1) {
            os << "*";
            for (nat j = 0; j < _nCol; j++) {  // Pintem  la darrera paret sud
                os << "*";
                os << "*";
            }
            os << std::endl;
        }
    }
}

bool laberint::portaExterior(paret p, posicio pos) {
    // Pre: p és una paret d'una cambra del laberint i pos es una posicio
    // existent del laberint. Post: Retorna true si p és una porta exterior,
    // altrament false.

    // pos.first/second -1 es provisional, cal veure q tal funciona més endavant
    if (pos.first - 1 == 0 and p == paret::NORD)
        return true;
    else if (pos.first == _nFil and p == paret::SUD)
        return true;
    else if (pos.second - 1 == 0 and p == paret::OEST)
        return true;
    else if (pos.second == _nCol and p == paret::EST)
        return true;

    return false;
}
