  #include "particio.hpp"

  // Construeix una particio amb n elements com a màxim.
  template <typename T>
  particio<T>::particio(nat n) throw(error) {
    // Num nodes màxim que pot tenir
    _arrel = NULL;
    _quantsGrups = 0;
    _lim = n;
  }

  // Constructora per còpia, assignació i destructora.
  template <typename T>
  particio<T>::particio(const particio & p) throw(error) {
    //Mirar apunts
    _quantsGrups = p._quantsGrups;
    _lim = p._lim;
    _arrel = copia_nodes(p._arrel);
    }
    
  
  template <typename T>
  particio<T> & particio<T>::operator=(const particio & p) throw(error) {
    
    if(this != &p){
      particio pAux(p);
      pAux._arrel = copia_nodes(p._arrel);
      esborra_nodes(_arrel);
      _arrel = pAux._arrel;
      _lim = pAux._lim;
      _quantsGrups = pAux._quantsGrups; 
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

  }

  // Uneix els dos grups als quals pertanyen aquests dos elements. Si tots dos
  // elements ja pertanyien al mateix grup no fa res.
  // Es produeix un error si algun dels elements no pertany a la partició.
  
  template <typename T>
  void particio<T>::unir(const T & x, const T & y) throw(error) {

  }

  // Retorna si els elements x i y pertanyen al mateix grup.
  // Es produeix un error si algun dels dos elements no pertany a la partició.
  template <typename T>
  bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error) {

    /*if(hi_es(_arrel, x) == NULL or hi_es(_arrel, y) == NULL) throw error(ElemInexistent);
    
    T repreX = find_repre(x);
    T repreY = find_repre(y);

    if(repreX == repreY) return true;
    else return false; */

  }

  // Retorna el número de grups que té la particio.
  template <typename T>
  nat particio<T>::size() const throw() {
    return _quantsGrups;
  }

  // Retorna el número d'elements que té la particio.
  template <typename T>
  nat particio<T>::num_elements() const throw() {
      
      return _arrel->_quantsFills;
  }

  // Retorna el número màxim d'elements que pot tenir la particio.
  template <typename T>
  nat particio<T>::num_maxim() const throw() {

      return _lim;
  }

  template <typename T>
  T particio<T>::find_repre(const T & x) {
//Pre: x és un element que pertany a un grup de la partició. 
//Post: retorna l'element representant del grup al qual pertany x.
  
  node *p = x->_repre;
  
  while(p->_clau != p->_repre){
    p = p->_repre;
  }

  return p->_clau;
  }

  template <typename T>
  typename particio<T>::node* particio<T>::afegir(node *p, const T &x) throw(error) {

    //Comprovem si encara queda espai a la partició.
    if (_quantsGrups >= _lim) throw error(ParticioPlena);

    else {
      //afegim l'element x a la partició

      if (p == NULL){
        node *p = new node;
        p->_clau = x;
        p->_fdret = NULL;
        p->_fesq = NULL;
        p->_quantsFills = 0;
        p->_repre = p;

        if (_arrel == NULL) _arrel = p;
        
        _quantsGrups++;
        return p;
      }

      else {
        if (p->_clau < x){
          p->_quantsFills+=1;
          p->_fesq = afegir(p->_fesq, x);
          
          }
        else if (p->_clau > x){
          p->_quantsFills+=1;
          p->_fdret = afegir(p->_fdret, x);
        }
        // Si l'element ja es troba no fem res. Pot ser cal afegir l'else
        else p->_clau = x;
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
  else{
    p = new node;
    try
    {
      p->_clau = m->_clau;
      p->_fesq = m->_fesq;
      p->_fdret = m->_fdret;
      p->_repre = m->_repre;
      p->_quantsFills = m->_quantsFills;
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
  typename particio<T>::node* particio<T>::esborra_nodes(node *m){
    //Pre: Cert
    //Post: Elimina tots els nodes de la partició
    if(m!= NULL){
      esborra_nodes(m->_fesq);
      esborra_nodes(m->_fdret);
      delete m;
    }
  }

  template <typename T>
  typename particio<T>::node* particio<T>::hi_es(node *p, const T &x){
    
    if(p == NULL) return NULL;

    else{
      if(p->_clau < x) hi_es(p->_fesq, x);
      else if (p->_clau > x) hi_es(p->_fdret, x);
      else p->_clau = x;
    }
    return p;
  }



