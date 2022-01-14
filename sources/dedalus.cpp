#include "dedalus.hpp"

/*

Per a fer aquesta classe ens vam basar en l'algorisme indicat en l'enunciat del projecte.
Fem servir la partició creada a la classe anterior per enmagatzemar totes les posicions del laberint.
Alhora, guardem les posicions també en una array que ens servirà per evitar iteracions en el moment 
d'escollir la possició aleatoria.

Crearem un contador de cambres escollides i un contador de repeticions, ambdós inicialitzats a 0 i un
objecte Random que farem servir per escollir la posició que, si és possible, obrirà la porta i quina
orientació tindrà.

Mentre que totes les cambres no formin part d'un sol conjunt, el Random ens generarà un numero aleatori
d'entre contador i numeroTotalCambres - 1. Seguidament, s'escolllirà una orientació sobre la que obrir una
porta, si aquesta no està oberta ni la cambra adjunta triada forma part del mateix conjunt, aquesta serà
valida.

Llavors, per cada vegada que la cambra escollida obri la porta, en l'ArrayPosicions la posició escollida 
s'intercanviarà amb la posició que tingui el valor del contador. Seguidament, el contador s'incrementarà 
en 1. Amb aquest mètode, aconseguim que el número aleatori no escolleixi dues vegades la mateixa cambra. 

Ara bé, pot donar-se el cas que, per aleatorietat o haver-ne obert una prèviament, les darreres cambres
que es troben en l'ArrayPosicions formin part del mateix conjunt. És en aquest moment quan el contador de 
repeticions entra en joc. Per evitar entrar en un bucle infinit, a cada vegada que s'escolleix una cambra
aquest s'incrementa en 1. Si la cambra escollida és vàlida i se li obre la porta, aquest es reinicia.
Altrament, si aquest contador arriba a 10, l'interval de números aleatoris del Random pasa de ser d'entre
( contador, numeroTotalCambres -1) a ( 0, numeroTotalCambres -1), eliminant d'aquesta manera el delimitador
del contador de posicions. Això ens permet evitar bucles infinits i reduir el número d'iteracions innecesaries.

Com a mètodes extra, hem afegit seleccionaParet(..), que com diu el nom, indica a quina paret obrir la porta
segons el número aleatori, que va del 0 al 3. També hem afegit cambraAdjunta(..), que segons la posicio i la
paret triades, retorna la cambra que també obrirà porta i comprovarà si formen part del mateix conjunt o no.
Finalment, hem afegit també portaExt(..) que com diu el nom, indica si la paret escollida dona a l'exterior.

Les raons per fer servir el vector en comptes de la total aleatorietat, han sigut simplement pel temps.
Voliem evitar que fes iteracions innecesaries i, sobretot, voliem estalvia temps en les darreres 
iteracions, on ja pràcticament totes les cambres formen part del mateix grup. Creiem que és una mesura
útil i eficient i que compleix amb la seva finalitat.

*/



posicio seleccionaCambra(posicio arrayCambres[], nat i, nat quantes,nat r);
//Pre: 
//Post: 
posicio cambraAdjunta(posicio pos, paret par);
//Pre:
//Post:

bool portaExt(posicio pos, paret par, nat numFiles, nat numCol);
//Pre:
//Post: Retorna true si la porta és una porta exterior, altrament false. 
paret seleccionaParet(nat r);
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
    nat ranCambra = 0, ranParet;
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
