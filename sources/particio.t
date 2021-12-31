#include <cstddef>
#include <iomanip>

#include "particio.hpp"

using namespace std;
// Construeix una particio amb n elements com a màxim.
template <typename T>
particio<T>::particio(nat n) throw(error) {
    // Num nodes màxim que pot tenir
    /* _arrel -> _fesq = NULL;
     _arrel -> _fdret = NULL;
     _arrel -> _repre = _arrel;
     _arrel -> _numElemConjunt = 0;
     _arrel -> _altura = 1; */

    _arrel = NULL;
    _quantsGrups = 0;
    _lim = n;
    _quantsElements = 0;
}

// Constructora per còpia, assignació i destructora.
template <typename T>
particio<T>::particio(const particio &p) throw(error) {
    //cout<< "impresion dentro de asignacion "<< endl;
    _quantsGrups = p._quantsGrups;
    _lim = p._lim;
    _quantsElements = p._quantsElements;

    //std::cout<<"lim3 "<<_lim<<std::endl;
    //std::cout<<"quants grups3 "<<_quantsGrups<<std::endl;
    //std::cout<<"quants elems3 "<<_quantsElements<<std::endl;
    _arrel = copia_nodes(p._arrel);
     //std::cout<<"lim4 "<<_lim<<std::endl;

//  std::cout<<"clau arrel "<<p._arrel->_clau<<std::endl;
    //std::cout<<"post copia nodes "<<std::endl;
    copia_repres(_arrel,p._arrel);

    //std::cout<<"post copia repres "<<std::endl;

    // fer print de la copia
    //std::cout << "arrel: " << _arrel->_clau << std::endl;

    //print(_arrel, 0);
    // std::cout<<"arrel: "<<_arrel<<std::endl;
    //print(p._arrel,0);
}

template <typename T>
particio<T> &particio<T>::operator=(const particio &p) throw(error) {
    if (this != &p) {

        particio pAux(p);

        //node* aux = _arrel;
        esborra_nodes(_arrel);

        _lim = pAux._lim;
        _quantsGrups = pAux._quantsGrups;
        _quantsElements = pAux._quantsElements;
        _arrel = pAux._arrel;

        pAux._arrel = NULL;
       /* std::cout<<"lim2 "<<_lim<<std::endl;
        std::cout<<"quants grups2 "<<_quantsGrups<<std::endl;
        std::cout<<"quants elems2 "<<_quantsElements<<std::endl; */
    }
    return (*this);
}

template <typename T>
particio<T>::~particio() throw() {
    esborra_nodes(_arrel);
}

// Afegeix un nou element a la particio. Aquest nou element formarà ell sol
// un nou grup. En cas que l'element ja estigués present a la partició llavors
// no es modifica la partició. Es produeix un error si la particio ja té el
// número màxim d'elements abans d'afegir aquest nou.

template <typename T>
void particio<T>::afegir(const T &x) throw(error) {
    node *p = hi_es(x);
    if (p == NULL){
      if (_quantsGrups >= _lim) throw error(ParticioPlena);
      _arrel = afegir(_arrel, x);
    }
}

// Uneix els dos grups als quals pertanyen aquests dos elements. Si tots dos
// elements ja pertanyien al mateix grup no fa res.
// Es produeix un error si algun dels elements no pertany a la partició.

template <typename T>
void particio<T>::unir(const T &x, const T &y) throw(error) {
    node *px = hi_es(x), *py = hi_es(y);
     //std::cout<<"repreX: "<<px<<" "<<"repreY: "<<py<<std::endl;

    if (px == NULL or py == NULL) throw error(ElemInexistent);
    // std::cout<<"prueba "<<std::endl;

    node *pRepreX = find_repre(px);
    node *pRepreY = find_repre(py);
    // std::cout<<"prueba2"<<std::endl;

    if (pRepreX != pRepreY) {
        if (pRepreX->_numElemConjunt > pRepreY->_numElemConjunt) {
            pRepreY->_repre = pRepreX->_repre;
            pRepreX->_numElemConjunt += pRepreY->_numElemConjunt;

        } else {
            pRepreX->_repre = pRepreY->_repre;
            pRepreY->_numElemConjunt += pRepreX->_numElemConjunt;
        }
        _quantsGrups--;
    }
        print(_arrel, 0);

}

// Retorna si els elements x i y pertanyen al mateix grup.
// Es produeix un error si algun dels dos elements no pertany a la partició.
template <typename T>
bool particio<T>::mateix_grup(const T &x, const T &y) const throw(error) {
    node *posX = hi_es(x), *posY = hi_es(y);
    // std::cout<<"posX: "<<posX<<" "<<"posY: "<<posY<<std::endl;

    // if(not hi_es(x) or not hi_es(y)) throw error(ElemInexistent);
    if (posX == NULL or posY == NULL) throw error(ElemInexistent);

    // std::cout<<"repre: "<<x._repre->_clau<<std::endl;

    // T repreX = find_repre(posX);
    // T repreY = find_repre(posY);

    node *pRepreX = find_repre(posX);
    node *pRepreY = find_repre(posY);

    // std::cout<<"repreX: "<<pRepreX->_clau<<" "<<"repreY:
    // "<<pRepreY->_clau<<std::endl;

    if (pRepreX->_clau == pRepreY->_clau)
        return true;
    else
        return false;
}

// Retorna el número de grups que té la particio.
template <typename T>
nat particio<T>::size() const throw() {
    return _quantsGrups;
}

// Retorna el número d'elements que té la particio.
template <typename T>
nat particio<T>::num_elements() const throw() {
    return _quantsElements;
}

// Retorna el número màxim d'elements que pot tenir la particio.
template <typename T>
nat particio<T>::num_maxim() const throw() {
    return _lim;
}

template <typename T>
typename particio<T>::node *particio<T>::find_repre(const node *p) const {
    // Pre: x és un element que pertany a un grup de la partició.
    // Post: retorna l'element representant del grup al qual pertany x.

    while (p->_clau != p->_repre->_clau) {
        p = p->_repre;
        // std::cout<<"p->_clau: "<<p->_clau<<" "<<"repre->_clau:
        // "<<p->_repre->_clau<<std::endl;
    }
    return p->_repre;
}

template <typename T>
typename particio<T>::node *particio<T>::afegir(node *p, const T &x) throw(error) {

    if (p == NULL){
        _quantsGrups++;
        _quantsElements++;
        return (nouNode(x));
        }

    if (x < p->_clau  ) p->_fesq = afegir(p->_fesq, x);

    else if (x > p->_clau) p->_fdret = afegir(p->_fdret, x);
    // Si l'element ja es troba no fem res. Pot ser cal afegir l'else
    else p->_clau = x;

    // Podem afegir nou node
    p->_altura = 1 + maxim(altura(p->_fesq), altura(p->_fdret));

    //if (_quantsGrups == 1) _arrel = p;

    int equil = obteEquilibri(p);

    // Cas esq-esq
    if (equil > 1 and x < p->_fesq->_clau) return rotaDreta(p);

    // Cas dreta-dreta
    if (equil < -1 and x > p->_fdret->_clau) return rotaEsquerra(p);

    // Cas esq-dreta
    if (equil > 1 and x > p->_fesq->_clau) {
        p->_fesq = rotaEsquerra(p->_fesq);
        return rotaDreta(p);
    }

    // Cas dreta-esq
    if (equil < -1 and x < p->_fdret->_clau) {
        p->_fdret = rotaDreta(p->_fdret);
        return rotaEsquerra(p);
    }
return p;
}

template <typename T>
typename particio<T>::node *particio<T>::copia_nodes(node *m) {
    // Pre: Cert
    // Post: Retorna una particio amb els nodes copiats de m

    node *p = NULL;

    if (m != NULL){
        p = nouNode(m->_clau);
        try {
            p->_clau = m->_clau;
            p->_repre = NULL;
            p->_numElemConjunt = m->_numElemConjunt;
            p->_altura = m->_altura;

            p->_fesq = copia_nodes(m->_fesq);
            p->_fdret = copia_nodes(m->_fdret);
            // Probablement l'error estigui a l'hora de copiar p->_repre

        } catch (...) {
            delete p;
            throw;
        }
    }
    return p;
}

template <typename T>
void particio<T>::esborra_nodes(node *m) {
    // Pre: Cert
    // Post: Elimina tots els nodes de la partició
    if (m != NULL) {
        esborra_nodes(m->_fesq);
        esborra_nodes(m->_fdret);

        delete m;
    }
}

template <typename T>
typename particio<T>::node *particio<T>::hi_es(const T &x) const throw(error) {
    // Pre: x és l'element a cercar a la partició, p és el punter de node que
    // recorre la partició. Post: Retorna true si l'element x es troba a la
    // partició, altrament false.


/*    if(a != NULL){

        if(a->_clau == x) return a;
        else if(a->_clau < x) hi_es(x);
        else hi_es(x);
    }
    return a;

*/
    //if( p == NULL) std::cout<<"soy nulo"<<std::endl;
    //else  std::cout<<"nose donde apunto"<<std::endl;
    //std::cout<<"p: "<<p->_clau<<std::endl;

    // std::cout<<"quantsGrups: "<<_quantsGrups<<" lim: "<<_lim<<std::endl;
    //std::cout<<"hi es"<<std::endl;

    // El fallo se refleja aqui, de alguna forma no detecta la clau de p.
    node *p = _arrel;
    bool trobat = false;
        while (p != NULL and not trobat) {
            if (x < p->_clau)
                p = p->_fesq;

            else if (x > p->_clau)
                p = p->_fdret;

            else {
                //std::cout<<"x: "<<x<<std::endl;
                //std::cout<<"clau: "<<p->_clau<<std::endl;
                trobat = true;
            }
                //std::cout<<"x2: "<<x<<std::endl;
                //std::cout<<"clau2: "<<p->_clau<<std::endl; 
        //std::cout<<"hola4"<<std::endl;
        //std::cout<<"es arrel: "<< (p ==_arrel) <<std::endl;
        }
    // std::cout<<"salgo p: "<<p<<std::endl;
    if (trobat){
        //std::cout<<"trobat"<<std::endl;
        return p;
    }
    else{
        //std::cout<<" no trobat"<<std::endl;
        return NULL;
    }
}

template <typename T>
void particio<T>::print(node *p, int prof) {
    if (p != NULL) {
        print(p->_fdret, prof + 1);

        std::cout << std::setw(5 * (prof + 1));
        std::cout <<" clau: " << p->_clau;
        cout << " altura: " << p->_altura;
        cout << " elemConjunts: " << p->_numElemConjunt;
        cout << " repre: " << find_repre(p)->_clau;
        cout << " _quantsGrups: " <<_quantsGrups<<endl;


        print(p->_fesq, prof + 1);
    }
}

template <typename T>
typename particio<T>::node *particio<T>::nouNode(const T &x) {

    node *p = new node;
    p->_clau = x;
    p->_fesq = NULL;
    p->_fdret = NULL;
    p->_altura = 1;
    p->_numElemConjunt = 1;
    p->_repre = p;

    return p;
}

template <typename T>
nat particio<T>::altura(node *p) {
    if (p == NULL) return 0;
    return p->_altura;
}

// ens retoorna el màxi, entre dos enters
template <typename T>
nat particio<T>::maxim(nat a, nat b) {
    if (a > b)
        return a;
    else
        return b;
}

template <typename T>
typename particio<T>::node *particio<T>::rotaDreta(node *pesq) {
    node *prot = pesq->_fesq;
    node *praux = prot->_fdret;

    // Fem la rotació.
    prot->_fdret = pesq;
    pesq->_fesq = praux;

    // Actualitzem les alçades.
    pesq->_altura = maxim(altura(pesq->_fesq), altura(pesq->_fdret)) + 1;
    prot->_altura = maxim(altura(prot->_fesq), altura(prot->_fdret)) + 1;

    // Retorna la nova arrel.
    return prot;
}

template <typename T>
typename particio<T>::node *particio<T>::rotaEsquerra(node *pdreta) {
    node *prot = pdreta->_fdret;
    node *paux = prot->_fesq;

    // Fem la rotació.
    prot->_fesq = pdreta;
    pdreta->_fdret = paux;

    // Actualitzem les alçades.
    pdreta->_altura = maxim(altura(pdreta->_fesq), altura(pdreta->_fdret)) + 1;
    prot->_altura = maxim(altura(prot->_fesq), altura(prot->_fdret)) + 1;

    // Retorna la nova arrel.
    return prot;
}

// Obté el factor equilibri del node p
template <typename T>
int particio<T>::obteEquilibri(node *p) {
    if (p == NULL) return 0;
    return altura(p->_fesq) - altura(p->_fdret);
}

// copiem el representant del node
template <typename T>
void particio<T>::copia_repres(node *n,node *m) {

 if (m != NULL) {

    node *repren = (hi_es(m->_repre->_clau));
    //std::cout<<"repren"<<repren<<std::endl;
    //std::cout<<"hola3"<<std::endl;

    n->_repre = repren;

    copia_repres(n->_fesq, m->_fesq);
    copia_repres(n->_fdret, m->_fdret);

    }
}




