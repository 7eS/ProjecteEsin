  #include "particio.hpp"

  // Construeix una particio amb n elements com a màxim.
  template <typename T>
  particio<T>::particio(nat n) throw(error) {
      

      // falta crear el arbol a null
      
      _Part = new nat[n]; //demanem espai per n elements de tipus nat. 
      //num = n;
      // Pregunta Jordi, s'inicialitza a 0 o a n? Per què?
      _cont = 0; 
      for (nat i=0; i<n; i++) {
        _Part[i] = i; //Cada element és el seu propi representant. 
      }
  }

  // Constructora per còpia, assignació i destructora.
  template <typename T>
  particio<T>::particio(const particio & p) throw(error) {

    n = p._num; 

    _Part = new nat *[n];

    for (int i = 0; i < n; i++) {
        _Part[i] = new nat[n];
    }

    for (int i = 0; i < _nFil; i++) { 
            _Part[i] = p._Part[i];
        }
    }
    
  
  template <typename T>
  particio<T> & particio<T>::operator=(const particio & p) throw(error) {

  }
  
  template <typename T>
  particio<T>::~particio() throw() {

    for (int i = 0; i < n; i++)
        delete[] _Part[i];        // Eliminem les caselles del vector. 
        
    delete[] _Part;               // Eliminem el punter.
}
  

  // Afegeix un nou element a la particio. Aquest nou element formarà ell sol
  // un nou grup. En cas que l'element ja estigués present a la partició llavors
  // no es modifica la partició. Es produeix un error si la particio ja té el
  // número màxim d'elements abans d'afegir aquest nou.

  template <typename T>
  void particio<T>::afegir(const T &x) throw(error) {

    if (/*comprovar que la part esta plena*/) throw error(ParticioPlena);
    else {
      //afegir element x al vector

    }


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

  }

  // Retorna el número de grups que té la particio.
  template <typename T>
  nat particio<T>::size() const throw() {

  }

  // Retorna el número d'elements que té la particio.
  template <typename T>
  nat particio<T>::num_elements() const throw() {

      return _cont; 
  }

  // Retorna el número màxim d'elements que pot tenir la particio.
  template <typename T>
  nat particio<T>::num_maxim() const throw() {

      return _Part.size();
  }

  int find_repre(const T & x) {
//Pre: x és un element que pertany a un grup de la partició. 
//Post: retorna l'element representant del grup al qual pertany x.  




  }

