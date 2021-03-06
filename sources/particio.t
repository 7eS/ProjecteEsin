#include <cstddef>
#include <iomanip>

#include "particio.hpp"


// Construeix una particio amb n elements com a màxim.
// Cost en temps: Θ(1). Cost en espai: Θ(1)
template <typename T>
particio<T>::particio(nat n) throw(error) {
 
    _arrel = NULL;
    _quantsGrups = 0;
    _lim = n;
    _quantsElements = 0;
}

// Constructora per còpia, assignació i destructora.
// Cost en temps: Θ(n). Cost en espai: (n)
template <typename T>
particio<T>::particio(const particio &p) throw(error) {

    _quantsGrups = p._quantsGrups;
    _lim = p._lim;
    _quantsElements = p._quantsElements;

    _arrel = copia_nodes(p._arrel);

    copia_repres(_arrel,p._arrel);
}

// Cost en temps: Θ(n). Cost en espai: Θ(n)
template <typename T>
particio<T> &particio<T>::operator=(const particio &p) throw(error) {

    if (this != &p) {

        particio pAux(p);

        esborra_nodes(_arrel);

        _lim = pAux._lim;
        _quantsGrups = pAux._quantsGrups;
        _quantsElements = pAux._quantsElements;
        _arrel = pAux._arrel;

        pAux._arrel = NULL;
       
    }
    return (*this);
}

// Cost en temps: Θ(n). Cost en espai: -
template <typename T>
particio<T>::~particio() throw() {
    esborra_nodes(_arrel);
}

// Afegeix un nou element a la particio. Aquest nou element formarà ell sol
// un nou grup. En cas que l'element ja estigués present a la partició llavors
// no es modifica la partició. Es produeix un error si la particio ja té el
// número màxim d'elements abans d'afegir aquest nou.
// Cost en temps: Θ(log(n)). Cost en espai: Θ(1)
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
// Cost en temps: Θ(log(n)). Cost en espai: -
template <typename T>
void particio<T>::unir(const T &x, const T &y) throw(error) {

    node *px = hi_es(x), *py = hi_es(y);
     
    if (px == NULL or py == NULL) throw error(ElemInexistent);
    
    node *pRepreX = find_repre(px);
    node *pRepreY = find_repre(py);

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
}

// Retorna si els elements x i y pertanyen al mateix grup.
// Es produeix un error si algun dels dos elements no pertany a la partició.
// Cost en temps: Θ(log(n)). Cost en espai: -
template <typename T>
bool particio<T>::mateix_grup(const T &x, const T &y) const throw(error) {

    node *posX = hi_es(x), *posY = hi_es(y);

    if (posX == NULL or posY == NULL) throw error(ElemInexistent);

    node *pRepreX = find_repre(posX);
    node *pRepreY = find_repre(posY);
    if (pRepreX->_clau == pRepreY->_clau)
        return true;
    else
        return false;
}

// Retorna el número de grups que té la particio.
// Cost en temps: Θ(1). Cost en espai: -
template <typename T>
nat particio<T>::size() const throw() {
    return _quantsGrups;
}

// Retorna el número d'elements que té la particio.
// Cost en temps: Θ(1). Cost en espai: -
template <typename T>
nat particio<T>::num_elements() const throw() {
    return _quantsElements;
}

// Retorna el número màxim d'elements que pot tenir la particio.
// Cost en temps: Θ(1). Cost en espai: -
template <typename T>
nat particio<T>::num_maxim() const throw() {
    return _lim;
}

// Cost en temps: O(n_i). Cost en espai: - . On n_i = num elements d'un subconjunt de la particio.
// El considerem cost O(n_i) perquè en el pitjor dels casos, per trobar el representant d'un element,
// haurem de recórrer tots els elements d'un subconjunt, i aquest pot arribar a ser de tamany n. 
// Altrament, en el millor dels casos el cost serà constant, doncs l'element buscat és el seu
// propi representant.
template <typename T>
typename particio<T>::node *particio<T>::find_repre(const node *p) const {

    while (p->_clau != p->_repre->_clau) {
        p = p->_repre;
        
    }
    return p->_repre;
}

// Cost en temps: Θ(log(n)). Cost en espai: Θ(1)
template <typename T>
typename particio<T>::node *particio<T>::afegir(node *p, const T &x) throw(error) {

    if (p == NULL){
        _quantsGrups++;
        _quantsElements++;
        return (nouNode(x));
        }

    if (x < p->_clau  ) p->_fesq = afegir(p->_fesq, x);

    else if (x > p->_clau) p->_fdret = afegir(p->_fdret, x);
    // Si l'element ja es troba no fem res.
    else p->_clau = x;

    // Podem afegir nou node
    p->_altura = 1 + maxim(altura(p->_fesq), altura(p->_fdret));

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

// Cost en temps: Θ(n). Cost en espai: Θ(n)
template <typename T>
typename particio<T>::node *particio<T>::copia_nodes(node *m) {

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

        } catch (...) {
            delete p;
            throw;
        }
    }
    return p;
}

// Cost en temps: Θ(n). Cost en espai: -
template <typename T>
void particio<T>::esborra_nodes(node *m) {
   
    if (m != NULL) {
        esborra_nodes(m->_fesq);
        esborra_nodes(m->_fdret);

        delete m;
    }
}

// Cost en temps: Θ(log(n)). Cost en espai: -
template <typename T>
typename particio<T>::node *particio<T>::hi_es(const T &x) const throw(error) {

    node *p = _arrel;
    bool trobat = false;
        while (p != NULL and not trobat) {
            if (x < p->_clau)
                p = p->_fesq;

            else if (x > p->_clau)
                p = p->_fdret;

            else {
                
                trobat = true;
            } 
        }

    if (trobat) return p;
    else return NULL;
}

// Cost en temps: Θ(n). Cost en espai: -
template <typename T>
void particio<T>::print(node *p, int prof) {

    if (p != NULL) {
        print(p->_fdret, prof + 1);

        std::cout << std::setw(5 * (prof + 1));
        std::cout << " clau: " << p->_clau;
        std::cout << " altura: " << p->_altura;
        std::cout << " elemConjunts: " << p->_numElemConjunt;
        std::cout << " repre: " << find_repre(p)->_clau;
        std::cout << " _quantsGrups: " <<_quantsGrups<<std::endl;

        print(p->_fesq, prof + 1);
    }
}

// Cost en temps: Θ(1). Cost en espai: Θ(1)
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

// Cost en temps: Θ(1). Cost en espai: -
template <typename T>
nat particio<T>::altura(node *p) {

    if (p == NULL) return 0;
    return p->_altura;
}

// Cost en temps: Θ(1). Cost en espai: -
template <typename T>
nat particio<T>::maxim(nat a, nat b) {
    
    if (a > b)
        return a;
    else
        return b;
} 

// Cost en temps: Θ(1). Cost en espai: -
template <typename T>
typename particio<T>::node *particio<T>::rotaDreta(node *pesq) {

    node *prot = pesq->_fesq;
    node *praux = prot->_fdret;

    prot->_fdret = pesq;
    pesq->_fesq = praux;

    pesq->_altura = maxim(altura(pesq->_fesq), altura(pesq->_fdret)) + 1;
    prot->_altura = maxim(altura(prot->_fesq), altura(prot->_fdret)) + 1;

    // Retorna la nova arrel.
    return prot;
}

// Cost en temps: Θ(1). Cost en espai: -
template <typename T>
typename particio<T>::node *particio<T>::rotaEsquerra(node *pdreta) {

    node *prot = pdreta->_fdret;
    node *paux = prot->_fesq;

    prot->_fesq = pdreta;
    pdreta->_fdret = paux;

    pdreta->_altura = maxim(altura(pdreta->_fesq), altura(pdreta->_fdret)) + 1;
    prot->_altura = maxim(altura(prot->_fesq), altura(prot->_fdret)) + 1;

    // Retorna la nova arrel.
    return prot;
}

// Cost en temps: Θ(1). Cost en espai: -
template <typename T>
int particio<T>::obteEquilibri(node *p) {

    if (p == NULL) return 0;
    return altura(p->_fesq) - altura(p->_fdret);
}

// Cost en temps: Θ(n). Cost en espai: -
template <typename T>
void particio<T>::copia_repres(node *n,node *m) {

    if (m != NULL) {

        node *repren = (hi_es(m->_repre->_clau));

        n->_repre = repren;

        copia_repres(n->_fesq, m->_fesq);
        copia_repres(n->_fdret, m->_fdret);

        }
}
