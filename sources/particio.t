  #include "particio.hpp"

  // Construeix una particio amb n elements com a màxim.
  template <typename T>
  particio<T>::particio(nat n) throw(error) {
    // Num nodes màxim que pot tenir
    _arrel = NULL;
    _quantsGrups = 0;
    _lim = n;
    _quantsElements = 0;
  }

  // Constructora per còpia, assignació i destructora.
  template <typename T>
  particio<T>::particio(const particio & p) throw(error) {
    //Mirar apunts
    _quantsGrups = p._quantsGrups;
    _lim = p._lim;
    _quantsElements = p._quantsElements;
    _arrel = copia_nodes(p._arrel);
    }
    
  
  template <typename T>
  particio<T> & particio<T>::operator=(const particio & p) throw(error) {
    
    if (this != &p) {
      particio pAux(p);
      pAux._arrel = copia_nodes(p._arrel);
      esborra_nodes(_arrel);
      _arrel = pAux._arrel;
      _lim = pAux._lim;
      _quantsGrups = pAux._quantsGrups; 
      _quantsElements = pAux._quantsElements;
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

    node *repreX = hi_es(x), *repreY = hi_es(y);

    if(repreX == NULL or repreY == NULL) throw error(ElemInexistent);

    else if(repreX != repreY){
      if (repreX->_numElemConjunt > repreY->_numElemConjunt){
          repreY->_repre = repreX->_repre;
          repreX->_numElemConjunt+=repreY->_numElemConjunt;  

      } else {
        repreX->_repre = repreY->_repre;
        repreY->_numElemConjunt+=repreX->_numElemConjunt;
        
      }
      _quantsGrups--;
    }
  }

  // Retorna si els elements x i y pertanyen al mateix grup.
  // Es produeix un error si algun dels dos elements no pertany a la partició.
  template <typename T>
  bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error) {

    node *posX = hi_es(x), *posY = hi_es(y);
    //if(not hi_es(x) or not hi_es(y)) throw error(ElemInexistent);
    if(posX == NULL or posY == NULL) throw error(ElemInexistent);

    //std::cout<<"repre: "<<x._repre->_clau<<std::endl;

    T repreX = find_repre(posX);
    T repreY = find_repre(posY);

    //std::cout<<"repreX: "<<repreX<<" "<<"repreY: "<<repreY<<std::endl;

    if(repreX == repreY) return true;
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
T particio<T>::find_repre(const node *p)const {
//Pre: x és un element que pertany a un grup de la partició. 
//Post: retorna l'element representant del grup al qual pertany x.
  
  while (p->_clau != p->_repre->_clau) {

    p = p->_repre;
        //std::cout<<"p->_clau: "<<p->_clau<<" "<<"repre->_clau: "<<p->_repre->_clau<<std::endl;

  }

  return p->_repre->_clau;
}

  template <typename T>
  typename particio<T>::node* particio<T>::afegir(node *p, const T &x) throw(error) {

    //Comprovem si encara queda espai a la partició.
    if (_quantsGrups >= _lim) throw error(ParticioPlena);

    else {
      //afegim l'element x a la partició

      if (p == NULL) {
        node *p = new node;
        p->_clau = x;
        p->_fdret = NULL;
        p->_fesq = NULL;
        p->_numElemConjunt = 1;
        p->_repre = p;

        if (_arrel == NULL) _arrel = p;
        
        _quantsGrups++;
        _quantsElements++;
        return p;
      }

      else {
        if (p->_clau < x) p->_fesq = afegir(p->_fesq, x);
          
        else if (p->_clau > x) p->_fdret = afegir(p->_fdret, x);
        
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
  else {
    p = new node;
    try 
    {
      p->_clau = m->_clau;
      p->_fesq = m->_fesq;
      p->_fdret = m->_fdret;
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
  typename particio<T>::node* particio<T>::esborra_nodes(node *m){
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
  
  while (p!=NULL and not trobat) {

    if (p->_clau < x) p = p->_fesq;
    
    else if (p->_clau > x) p = p->_fdret;
    
    else{
      trobat = true;
    }
  }
  if(trobat) return p;
  else return NULL;
  //return trobat;
}



