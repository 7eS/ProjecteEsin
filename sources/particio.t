  #include "particio.hpp"

  // Construeix una particio amb n elements com a màxim.
  template <typename T>
  particio<T>::particio(nat n) throw(error){}

  // Constructora per còpia, assignació i destructora.
  template <typename T>
  particio<T>::particio(const particio & p) throw(error){}
  
  template <typename T>
  particio<T> & particio<T>::operator=(const particio & p) throw(error){}
  
  template <typename T>
  particio<T>::~particio() throw(){}

  // Afegeix un nou element a la particio. Aquest nou element formarà ell sol
  // un nou grup. En cas que l'element ja estigués present a la partició llavors
  // no es modifica la partició. Es produeix un error si la particio ja té el
  // número màxim d'elements abans d'afegir aquest nou.

  template <typename T>
  void particio<T>::afegir(const T &x) throw(error){}

  // Uneix els dos grups als quals pertanyen aquests dos elements. Si tots dos
  // elements ja pertanyien al mateix grup no fa res.
  // Es produeix un error si algun dels elements no pertany a la partició.
  
  template <typename T>
  void particio<T>::unir(const T & x, const T & y) throw(error){}

  // Retorna si els elements x i y pertanyen al mateix grup.
  // Es produeix un error si algun dels dos elements no pertany a la partició.
  template <typename T>
  bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error){}

  // Retorna el número de grups que té la particio.
  template <typename T>
  nat particio<T>::size() const throw(){}

  // Retorna el número d'elements que té la particio.
  template <typename T>
  nat particio<T>::num_elements() const throw(){}

  // Retorna el número màxim d'elements que pot tenir la particio.
  template <typename T>

  nat particio<T>::num_maxim() const throw(){}