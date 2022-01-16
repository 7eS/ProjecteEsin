#include "dedalus.hpp"

/*

Per fer aquesta classe ens vam basar en l'algorisme indicat a l'enunciat del projecte.
Fem servir la partició creada a la classe anterior per emmagatzemar totes les posicions del laberint.
Alhora, guardem les posicions també en un array que ens servirà per evitar iteracions en el moment 
d'escollir la posició aleatòria.

Crearem un comptador de cambres escollides i un comptador de repeticions, ambdós inicialitzats a 0 i un
objecte Random que farem servir per escollir la posició que, si és possible, obrirà la porta i la seva
orientació. És a dir, sempre que totes les cambres no formin part d'un sol conjunt, el Random ens generarà 
un número aleatori d'entre comptador i numeroTotalCambres-1. Seguidament, s'escollirà una orientació sobre 
la que obrir una porta, si aquesta no està oberta ni la cambra adjunta triada forma part del mateix conjunt, 
aquesta serà vàlida.

Llavors, per cada vegada que la cambra escollida obri la porta, a l'ArrayPosicions la posició escollida 
s'intercanviarà amb la posició que tingui el valor del comptador. Seguidament, el comptador s'incrementarà 
en 1. Amb aquest mètode, aconseguim que el número aleatori no esculli dues vegades la mateixa cambra. 

Ara bé, pot donar-se el cas que, per aleatorietat o haver-ne obert una prèviament, les darreres cambres
que es troben a l'ArrayPosicions formin part del mateix conjunt. És en aquest moment quan el comptador de 
repeticions entra en joc. Per evitar entrar en un bucle infinit, cada vegada que s'escolleix una cambra
aquest s'incrementa en 1. Si la cambra escollida és vàlida i se li obre la porta, aquest es reinicia.
Altrament, si aquest comptador arriba a 10, l'interval de números aleatoris del Random passa de ser d'entre
(comptador, numeroTotalCambres-1) a (0, numeroTotalCambres-1), eliminant d'aquesta manera el delimitador
del comptador de posicions. Això ens permet evitar bucles infinits i reduïr el número d'iteracions innecessàries.

Com a mètodes extra, hem afegit seleccionaParet(..), que indica a quina paret obrir la porta segons el 
número aleatori, que va del 0 al 3. També hem afegit cambraAdjunta(..), que segons la posició i la
paret triades, retorna la cambra que també obrirà porta i comprovarà si formen part del mateix conjunt o no.
Finalment, hem afegit també portaExt(..) que indica si la paret escollida dona a l'exterior o no.

Les raons per fer servir el vector en comptes de la total aleatorietat han sigut simplement pel temps.
Volíem evitar que fes iteracions innecessàries i, sobretot, volíem estalviar temps en les darreres 
iteracions, on ja pràcticament totes les cambres formen part del mateix grup. Creiem que és una mesura
útil i eficient i que compleix amb la seva finalitat.

*/

posicio cambraAdjunta(posicio pos, paret par);
//Pre: pos és la posició de la cambra a comprovar, par és la paret escollida.
//Post: Retorna la posició de la cambra adjunta a la paret par. 

bool portaExt(posicio pos, paret par, nat numFiles, nat numCol);
//Pre: pos és una posició de la cambra a comprovar, par és la paret, 
// numFiles i numCol són les mides del laberint.  
//Post: Retorna true si la porta és una porta exterior, altrament false. 

paret seleccionaParet(nat r);
//Pre: r és un natural entre 0 i 3. 
//Post: Retorna la paret seleccionada. 



// IMPLEMENTACIÓ DE LA CLASSE DEDALUS.

// Excava el laberint, fent un laberint perfecte. Un laberint està excavat
// si i només si alguna de les seves cambres té alguna porta oberta.
// Es produeix un error si el laberint ja està excavat.

// Cost en temps: Ω(numFiles*numColumnes). Cost en espai: Θ(numFiles*numColumnes).
// El cost temporal és Ω(numFiles*numColumnes) ja que a l'estar basada en gran part en 
// la tria de números aleatoris, no podem aproximar un cost exacte ni màxim. Però sí que
// podem saber que el número mínim d'iteracions serà n*m, doncs en el millor dels casos,
// mai escollirà una cambra dues vegades i, per tant, només es farà un recorregut lineal al
// laberint.
void dedalus::construir(laberint& M) throw(error) {

    nat quantesCambres = (M.num_files() * M.num_columnes());
    particio<posicio> p(quantesCambres);

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

    util::Random r;
    posicio pos, pos2;
    cambra c, c2;
    paret par;
    nat cont = 0, repeticions, ranCambra = 0, ranParet;
    bool cambraValida;

    // Mentre hi hagi més d'un conjunt.
    while (p.size() > 1) { 
        repeticions = 0;
        cambraValida = false;

        while (not cambraValida and cont < quantesCambres) {
            
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
}

// Cost en temps: Θ(1)  Cost en espai: -
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

// Cost en temps: Θ(1). Cost en espai: -
paret seleccionaParet(nat ran) {
    
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

// Cost en temps: Θ(1). Cost en espai: -
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
