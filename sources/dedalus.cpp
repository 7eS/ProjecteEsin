#include "dedalus.hpp"

//IMPLEMENTACIÓ DE LA CLASSE DEDALUS. 

  // Excava el laberint, fent un laberint perfecte. Un laberint està excavat
  // si i només si alguna de les seves cambres té alguna porta oberta.
  // Es produeix un error si el laberint ja està excavat.
  void dedalus::construir(laberint & M) throw(error) {

    bool trobat = false;
    int i = 0;
    int j = 0;

    // Comprovem si hi ha alguna porta oberta a alguna de les cambres del laberint M. 
    while (i < M.num_files() and not trobat) {
      while (j < M.num_columnes() and not trobat) {
        posicio pos(i,j);
        cambra c = M(pos);
        if (c.porta_oberta(paret::NORD) or c.porta_oberta(paret::SUD) or c.porta_oberta(paret::EST) or c.porta_oberta(paret::OEST)) {
            throw error (EstaExcavat);
        }
        else j++;
      }
      i++;
    }
    
    nat quantesCambres = (M.num_files()*M.num_columnes());    // comprovar si es -1 o no. 
    particio<cambra> p(quantesCambres);

    for(int i = 0; i <M.num_files(); i++){
      for(int j = 0; j<M.num_columnes(); j++){
        posicio pos(i,j);
        cambra c = M(pos);
        p.afegir(c);
      }
    }
    int i = 0;

    util::Random ran;

    while (i < quantesCambres) {

    int fil = ran(M.num_files());
    int col = ran(M.num_columnes());

      posicio pos(fil,col);
      cambra c = M(pos);

      if(fil == 0)
      int ran = c2(4);
      if (fil == 0) posicio pos2(fil-1,col); //N
      if (fil == 1) posicio pos2(fil+1,col); //S
      if (fil == 2) posicio pos2(fil,col+1); //E
      if (fil == 3) posicio pos2(fil,col-1); //O



        if (not c.porta_oberta(paret::NORD) and not c.porta_oberta(paret::SUD) 
        and not c.porta_oberta(paret::EST) and not c.porta_oberta(paret::OEST)) 


      posicio pos(a,b);

      obrir_porta()

    }



    
  }