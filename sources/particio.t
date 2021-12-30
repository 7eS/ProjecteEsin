  #include "particio.hpp"

  // Construeix una particio amb n elements com a màxim.
  template <typename T>
  particio<T>::particio(nat n) throw(error) {
    // Num nodes màxim que pot tenir
    _arrel = new node;
    _arrel -> _fesq = NULL;
    _arrel -> _fdret = NULL;
    _arrel -> _repre = _arrel;
    _arrel -> _numElemConjunt = 0;

    //_arrel = NULL;
    _quantsGrups = 0;
    _lim = n;
    _quantsElements = 0;
  }

  // Constructora per còpia, assignació i destructora.
  template <typename T>
  particio<T>::particio(const particio & p) throw(error) {
    //Mirar apunts
    _arrel = new node;
    _arrel = copia_nodes(p._arrel);
    _quantsGrups = p._quantsGrups;
    _lim = p._lim;
    _quantsElements = p._quantsElements;
    //fer print de la copia
    std::cout<<"arrel: "<<_arrel->_clau<<std::endl;


    print(_arrel);
    //std::cout<<"arrel: "<<_arrel<<std::endl;
    }
    
  
  template <typename T>
  particio<T> & particio<T>::operator=(const particio & p) throw(error) {
    
    if (this != &p) {
      particio pAux(p);

      pAux._arrel = copia_nodes(p._arrel);

      esborra_nodes(_arrel);
      _lim = pAux._lim;
      _quantsGrups = pAux._quantsGrups;
      _quantsElements = pAux._quantsElements;
      _arrel = pAux._arrel;
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

    afegir(_arrel, x);
    print(_arrel);

  }

  // Uneix els dos grups als quals pertanyen aquests dos elements. Si tots dos
  // elements ja pertanyien al mateix grup no fa res.
  // Es produeix un error si algun dels elements no pertany a la partició.
  
  template <typename T>
  void particio<T>::unir(const T & x, const T & y) throw(error) {

    node *px = hi_es(x), *py = hi_es(y);
    //std::cout<<"repreX: "<<px<<" "<<"repreY: "<<py<<std::endl;

    if(px == NULL or py == NULL) throw error(ElemInexistent);
    //std::cout<<"prueba "<<std::endl;

    node *pRepreX = find_repre(px);
    node *pRepreY = find_repre(py);
    //std::cout<<"prueba2"<<std::endl;

    if(pRepreX != pRepreY){
      if (pRepreX->_numElemConjunt > pRepreY->_numElemConjunt){
          pRepreY->_repre = pRepreX->_repre;
          pRepreX->_numElemConjunt+=pRepreY->_numElemConjunt;  

      } else {
        pRepreX->_repre = pRepreY->_repre;
        pRepreY->_numElemConjunt+=pRepreX->_numElemConjunt;
        
      }
      _quantsGrups--;
    }
  }

  // Retorna si els elements x i y pertanyen al mateix grup.
  // Es produeix un error si algun dels dos elements no pertany a la partició.
  template <typename T>
  bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error) {

    node *posX = hi_es(x), *posY = hi_es(y);
    //std::cout<<"posX: "<<posX<<" "<<"posY: "<<posY<<std::endl;

    //if(not hi_es(x) or not hi_es(y)) throw error(ElemInexistent);
    if(posX == NULL or posY == NULL) throw error(ElemInexistent);

    //std::cout<<"repre: "<<x._repre->_clau<<std::endl;

    //T repreX = find_repre(posX);
    //T repreY = find_repre(posY);
    
    node *pRepreX = find_repre(posX);
    node *pRepreY = find_repre(posY);

    //std::cout<<"repreX: "<<pRepreX->_clau<<" "<<"repreY: "<<pRepreY->_clau<<std::endl;


    if(pRepreX->_clau == pRepreY->_clau) return true;
    else return false;

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
typename particio<T>::node* particio<T>::find_repre(const node *p)const {
//Pre: x és un element que pertany a un grup de la partició. 
//Post: retorna l'element representant del grup al qual pertany x.
  
  while (p->_clau != p->_repre->_clau) {

    p = p->_repre;
        //std::cout<<"p->_clau: "<<p->_clau<<" "<<"repre->_clau: "<<p->_repre->_clau<<std::endl;

  }

  return p->_repre;
}

  template <typename T>
  typename particio<T>::node* particio<T>::afegir(node *p, const T &x) throw(error) {

      if(p != NULL){
          if (p->_clau < x) p->_fesq = afegir(p->_fesq, x);
            
          else if (p->_clau > x) p->_fdret = afegir(p->_fdret, x);
          
          // Si l'element ja es troba no fem res. Pot ser cal afegir l'else
          else{
            return p;
            //p->_clau = x;
          }
      }
      else {
        //Comprovem si encara queda espai a la partició.
          if (_quantsGrups >= _lim) throw error(ParticioPlena);

            
            p = new node;
            p->_clau = x;
            p->_fdret = NULL;
            p->_fesq = NULL;
            p->_numElemConjunt = 1;
            p->_repre = p;

            if (_quantsGrups == 0) _arrel = p;

              _quantsGrups++;
              _quantsElements++;

              p->_numElemConjunt = 1+maxim(pes(p->_fesq), pes(p->_fdret));

              int equil = obteEquilibri(p);

              if (equil > 1 and x < p->_fesq->_clau) return rotaDreta(p);

              if (equil < -1 and x > p->_fdret->_clau) return rotaEsquerra(p);

              if (equil > 1 and x > p->_fesq->_clau) {
                p->_fesq = rotaEsquerra(p->_fesq);
                return rotaDreta(p);
              }

              if (equil < -1 and x < p->_fdret->_clau) {
                p->_fdret  =rotaDreta(p->_fdret);
                return rotaEsquerra(p);
              }
            }
    return p;
  }

  template <typename T>
  typename particio<T>::node* particio<T>::copia_nodes(node *m){
  //Pre: Cert
  //Post: Retorna una particio amb els nodes copiats de m

  node *p;
  if (m == NULL) p = NULL;
  else {
    p = new node;
    try 
    {
      p->_clau = m->_clau;
      p->_fesq = copia_nodes (m->_fesq);
      p->_fdret = copia_nodes(m->_fdret);
      //Probablement l'error estigui a l'hora de copiar p->_repre
      p->_repre = m->_repre;
      p->_numElemConjunt = m->_numElemConjunt;
      
    }
    catch(...)
    {
      delete p;
      throw;
    }
  }
  return p;
  }


  template <typename T>
  void particio<T>::esborra_nodes(node *m){
  //Pre: Cert
  //Post: Elimina tots els nodes de la partició
    
    if (m!= NULL) {
      esborra_nodes(m->_fesq);
      esborra_nodes(m->_fdret);
      delete m;
    }
  }

  template <typename T>
  typename particio<T>::node* particio<T>::hi_es(const T &x)const throw(error){
//Pre: x és l'element a cercar a la partició, p és el punter de node que recorre la partició. 
//Post: Retorna true si l'element x es troba a la partició, altrament false.
    
  bool trobat = false;
  node *p = _arrel;
  //std::cout<<"quantsGrups: "<<_quantsGrups<<" lim: "<<_lim<<std::endl;
  if(_quantsGrups > 0){
    //std::cout<<"entro"<<std::endl;
    while (p!=NULL and not trobat) {

      if (p->_clau < x) p = p->_fesq;
      
      else if (p->_clau > x) p = p->_fdret;
      
      else{
        trobat = true;
      }
    }
  }
  
  //std::cout<<"salgo p: "<<p<<std::endl;
  if(trobat) return p;
  else return NULL;
}

template <typename T>
void  particio<T>::print(node *p){

  if(p != NULL){
    std::cout<<p->_clau<<" ";
    print(p->_fesq);
    print(p->_fdret);
  }

}

/*  template <typename T>
  typename particio<T>::node* particio<T>::node( const T &clau, node *esq,
  node *dret, nat numElem): _clau(clau), _fesq(esq), _fdret(dret), _repre(&this), 
  _numElemConjunt(numElem); */

template <typename T>
int particio<T>::pes(node *p) {
    if (p == NULL) return 0;
    return p->_numElemConjunt;
}
 
// A utility function to get maximum of two integers
template <typename T>
nat particio<T>::maxim(nat a, nat b) {
  if( a > b) return a;
  else return b;

}


template <typename T>
typename particio<T>::node* particio<T>::rotaDreta(node *pesq) {

    node *prot = pesq->_fesq;
    node *praux = prot->_fdret;
 
    // Fem la rotació. 
    prot->_fdret = pesq;
    pesq->_fesq = praux;
 
    // Actualitzem les alçades. 
    pesq->_numElemConjunt = maxim(pes(pesq->_fesq), pes(pesq->_fdret)) + 1;
    prot->_numElemConjunt = maxim(pes(prot->_fesq), pes(prot->_fdret)) + 1;
 
    // Retorna la nova arrel. 
    return prot;
}
 
template <typename T>
typename particio<T>::node* particio<T>::rotaEsquerra(node *pdreta) {

    node *prot = pdreta->_fdret;
    node *paux = prot->_fesq;
 
    // Fem la rotació. 
    prot->_fesq = pdreta;
    pdreta->_fdret = paux;
 
    // Actualitzem les alçades. 
    pdreta->_numElemConjunt = maxim(pes(pdreta->_fesq),   
                    pes(pdreta->_fdret)) + 1;
    prot->_numElemConjunt = maxim(pes(prot->_fesq),
                    pes(prot->_fdret)) + 1;
 
    // Retorna la nova arrel. 
    return prot;
}
 
// Get Balance factor of node N
template <typename T>
int particio<T>::obteEquilibri(node *p) {

    if (p == NULL)
        return 0;
    return pes(p->_fesq) - pes(p->_fdret);
}
