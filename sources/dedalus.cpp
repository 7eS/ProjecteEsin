#include "dedalus.hpp"

posicio seleccionaCambra(posicio arrayCambres[], nat i, nat quantes,int r);
//Pre: 
//Post: 
posicio cambraAdjunta(posicio pos, paret par);
//Pre:
//Post:

bool portaExt(posicio pos, paret par, nat numFiles, nat numCol);
//Pre:
//Post: Retorna true si la porta és una porta exterior, altrament false. 
paret seleccionaParet(int r);
//Pre:
//Post: Retorna la paret seleccionada. 


// IMPLEMENTACIÓ DE LA CLASSE DEDALUS.

// Excava el laberint, fent un laberint perfecte. Un laberint està excavat
// si i només si alguna de les seves cambres té alguna porta oberta.
// Es produeix un error si el laberint ja està excavat.
void dedalus::construir(laberint& M) throw(error) {

    nat quantesCambres = (M.num_files() * M.num_columnes());    // Comprovem si es -1 o no.
    particio<posicio> p(quantesCambres);

    // Comprovem si hi ha alguna porta oberta a alguna de les cambres del
    // laberint M i afegim les cambres a la partició. 
    nat k = 0;
    posicio arrayCambres [quantesCambres];

    for (nat i = 1; i <= M.num_files(); i++) {
        for (nat j = 1; j <= M.num_columnes(); j++,k++) {
            posicio pos(i, j);
            cambra c = M(pos);
            if (c.porta_oberta(paret::NORD) or c.porta_oberta(paret::SUD) or
                c.porta_oberta(paret::EST) or c.porta_oberta(paret::OEST))
                throw error(EstaExcavat);

            p.afegir(pos);
            arrayCambres[k] = pos;
        }
    }

    util::Random r;     // Utilitzem la classe Random.

    posicio pos, pos2;
    cambra c, c2;
    paret par;
    nat cont = 0, repeticions;
    //nat iteracions = 0;
    int ranCambra = 0, ranParet;
    bool cambraValida;

    while (p.size() > 1) {      // Mentre hi hagi més d'un conjunt.
        repeticions = 0;
        cambraValida = false;
        //iteracions++;
        // Busquem una cambra aleatoria.
        while (not cambraValida and cont < quantesCambres) {
            
            // Evitem que es quedi en un bucle infinit.
            if (repeticions < 10) ranCambra = r(cont, quantesCambres-1);
            else ranCambra = r(0, quantesCambres-1);

            pos = arrayCambres[ranCambra];
            c = M(pos);

            ranParet = r(4);

            par = seleccionaParet(ranParet);
            if (not portaExt(pos,par,M.num_files(),M.num_columnes()) and not c.porta_oberta(par))
            cambraValida = true;
            
            repeticions++;
        }
        pos2 = cambraAdjunta(pos,par);
        if (not p.mateix_grup(pos,pos2)) {
            // Intercanviem les posicions per evitar fer iteracions de més.
            arrayCambres[ranCambra] = arrayCambres[cont];
            arrayCambres[cont] = pos;
            cont++;
            M.obre_porta(par, pos);
            p.unir(pos, pos2);
        }
  }
  //std::cout<<"iteracions: "<<iteracions<<std::endl;
}

posicio cambraAdjunta(posicio pos, paret par) {

        posicio res;
        if (par == paret::NORD) {           // Nord.
            res.first = pos.first-1;
            res.second = pos.second;
        
        } else if (par == paret::EST) {     // Est.
            res.first = pos.first;
            res.second = pos.second+1;

        } else if (par == paret::SUD) {     // Sud.
            res.first = pos.first+1;
            res.second = pos.second;

        } else {                            // Oest.
            res.first = pos.first;
            res.second = pos.second-1;
        }
        return res;
}

paret seleccionaParet(int ran) {
    
    paret res; 


        if (ran == 0) {             // Nord.
            res= paret::NORD;
        
        } else if (ran == 1) {      // Est.
            res = paret::EST;

        } else if (ran == 2) {      // Sud.
            res = paret::SUD;

        } else {                    // Oest. 
            res = paret::OEST;
        }    
    return res;
}

bool portaExt(posicio pos, paret par, nat numFiles, nat numCol ) {

    if (pos.first - 1 == 0 and par == paret::NORD)
        return true;
    else if (pos.first == numFiles and par == paret::SUD)
        return true;
    else if (pos.second - 1 == 0 and par == paret::OEST)
        return true;
    else if (pos.second == numCol and par == paret::EST)
        return true;

    return false;
}
