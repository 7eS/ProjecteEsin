#include "dedalus.hpp"
using namespace std;

struct info{
    posicio pos;
    paret par;
};

posicio seleccionaCambra(posicio arrayCambres[], nat i, nat quantes,int r);
//Pre: 
//Post:
posicio cambraAdjunta(posicio pos, paret par);
//Pre:
//Post:
info cambraAdjunta(posicio pos, int r);
//Pre:
//Post: 

bool posValida(posicio pos, nat numFiles, nat numCol);
//Pre:
//Post: Retorna true si la posició és vàlida, altrament false. 
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

    //cout<<"cambra: "<< arrayCambres[quantesCambres-1].first<<" "<<arrayCambres[quantesCambres-1].second<<endl;
   /* cout<<endl;
    cout<<"k: "<<k<<endl;
    cout<<"quantes cambres: "<<quantesCambres<<endl;
    cout<<"numElems: "<<p.num_elements()<<endl;
    cout<<"fin construc"<<endl; */

    util::Random r;     // Utilitzem la classe Random.

    posicio pos, pos2;
    cambra c, c2;
    paret par;
    info camAdj;
    nat cont = 0, repeticions;
    int ranCambra = 0, ranParet;
    bool cambraValida, cambraAdjValida, valida;

    //cout<<"cambres del vector:"<<endl;
    //cout<<"[";
    //for(int j = 0; j < quantesCambres; j++) cout<<arrayCambres[j].first<<", "<<arrayCambres[j].second<<" -- ";
    //cout<<"]"<<endl;

    while (p.size() > 1) {      // Mentre hi hagi més d'un conjunt.
        repeticions = 0;
        //cout<<"cont: "<<cont<<endl;
        cambraValida = false;
        //cout<<"pre cambraValida"<<endl;
        // Busquem una cambra aleatoria.
        while (not cambraValida and cont < quantesCambres) {
            
            // Evitem que es quedi en un bucle infinit.
            if(repeticions < 10) ranCambra = r(cont, quantesCambres-1);
            else ranCambra = r(0, quantesCambres-1);
            //pos = seleccionaCambra(arrayCambres, cont, quantesCambres, ran);
            //cout<<"pos.first: "<<pos.first<<"pos.second: "<<pos.second<<endl;
            //cout<<"ran cambra: "<<ranCambra<<endl;
            pos = arrayCambres[ranCambra];
            c = M(pos);
            //cout<<"cambra escollida: "<<pos.first<<", "<<pos.second<<endl;

            ranParet = r(4);
            //cout<<"ran paret: "<<ranParet<<endl;
            par = seleccionaParet(ranParet);
            if (not portaExt(pos,par,M.num_files(),M.num_columnes()) and not c.porta_oberta(par))
            cambraValida = true;
            
            repeticions++;
           /* if (not (c.porta_oberta(paret::NORD) or  c.porta_oberta(paret::SUD) or
                 c.porta_oberta(paret::EST) or  c.porta_oberta(paret::OEST))) */      
        }
        //cout<<"cambra valida ok"<<endl;
        /*
        cout<<"cambres que queden:"<<endl;
        cout<<"[";
        for(int j = cont; j < quantesCambres; j++) cout<<arrayCambres[j].first<<", "<<arrayCambres[j].second<<" - ";
        cout<<"]"<<endl;
        
        cout<<"pos: "<<pos.first<<", "<<pos.second<<endl;
        cout<<"par: "<<par<<endl; */

        pos2 = cambraAdjunta(pos,par);

        if (not p.mateix_grup(pos,pos2)) {
            // Intercanviem les posicions per evitar fer iteracions de més.
            cout<<"unio de: ";
            cout<<"pos: "<<pos.first<<", "<<pos.second<<" i ";
            cout<<"pos2: "<<pos2.first<<", "<<pos2.second<<endl;
            arrayCambres[ranCambra] = arrayCambres[cont];
            arrayCambres[cont] = pos;
            cont++;
            M.obre_porta(par, pos);
            cout<<"psize: "<<p.size()<<endl;
            p.unir(pos, pos2);
            cout<<"afegida"<<endl;
            cout<<"psize: "<<p.size()<<endl;
            cout<<endl;  
        }
/*
        cambraAdjValida = false;
        while (not cambraAdjValida ){
        // Busquem una cambra que no surti del rang
            valida = false;

            while (not valida){
                
                // Variant 1, amb struct
 
                //camAdj = cambraAdjunta(pos,ran);
                //cout<<endl;
                //cout<<"cont:"<<cont<<endl;
                //cout<<"posValida: "<<posValida(camAdj.pos,M.num_files(), M.num_columnes())<<endl;
                //if( posValida(camAdj.pos,M.num_files(), M.num_columnes())){
                    //cout<<"posicio rand: "<<pos2.first <<", "<<pos2.second<<endl;
                //    valida  = true;
                //}
                
                //Variant 2, sense struct

            //Variant 1, amb struct
            //pos2 = camAdj.pos;
            //par = camAdj.par;

            // Part comuna

            cout<<"pos1: "<<pos.first<<", "<<pos.second<<" - "<<"pos2: "<<pos2.first<<", "<<pos2.second<<endl;
            cout<<p.mateix_grup(pos,pos2)<<endl;
            cout<<p.size()<<endl;
            if(not p.mateix_grup(pos, pos2)){
                cout<<"not mateix grup"<<endl;
                cambraAdjValida = true;
            }
            //cout<<"mateix grup: "<<p.mateix_grup(pos,pos2)<<endl;

            //cout<<"mateix grup: "<<p.mateix_grup(pos,pos2)<<endl; 
        }
        cout<<"cambra adjunta valida ok"<<endl;
        // Si no pertany al mateix grup, obrim porta i unim
        //if (not p.mateix_grup(pos, pos2)) {
            cout<<"paret: "<<par<<endl;
            cout<<"posicio que pasem a obreporta: "<<pos.first<<", "<<pos.second<<endl;
        
        //}
            c2 = M(pos2);
            cout<<endl;
            cout<<"cambres que queden:"<<endl;
            cout<<"[";
            for(int j = cont; j < quantesCambres; j++) cout<<arrayCambres[j].first<<", "<<arrayCambres[j].second<<" - ";
            cout<<"]"<<endl;
            cout<<"p size "<<p.size()<<endl;
            cout<<"pos1: "<<pos.first<<" "<<pos.second<<endl;
            cout<<"pos2: "<<pos2.first<<" "<<pos2.second<<endl;
            cout<<"mateix grup: "<<p.mateix_grup(pos,pos2)<<endl;
            cout<<"porta nord: "<<c.porta_oberta(paret::NORD) <<"porta sud: "<< c.porta_oberta(paret::SUD) 
            << "porta est: "<<c.porta_oberta(paret::EST) << "porta oest: " << c.porta_oberta(paret::OEST)<<endl;
            cout<<"porta nord2: "<<c2.porta_oberta(paret::NORD) <<"porta sud2: "<< c2.porta_oberta(paret::SUD) 
            << "porta est2: "<<c2.porta_oberta(paret::EST) << "porta oest2: " << c2.porta_oberta(paret::OEST)<<endl; */
  }
}

posicio seleccionaCambra(posicio arrayCambres[],nat i, nat quantes, int ran) {

    posicio res;
    //cout<<"cont: "<<i<<endl;
    //cout<<"ran: "<<ran<<endl;
    //cout<<"cambres que n'hi ha:"<<endl;
    /* cout<<"[";
    for(int j = 0; j < quantes; j++) cout<<arrayCambres[j].first<<", "<<arrayCambres[j].second<<" - ";
    cout<<"]"<<endl;  */
    cout<<"ran: "<<ran<<endl;
    cout<<"cambra escollida: "<<res.first<<", "<<res.second<<endl;
    arrayCambres[ran] = arrayCambres[i]; 
    cout<<"cambres que queden:"<<endl;
    cout<<"[";
    for(int j = i+1; j < quantes; j++) cout<<arrayCambres[j].first<<", "<<arrayCambres[j].second<<" - ";
    cout<<"]"<<endl;
    
    //cout<<"i: "<<i<<" quantes: "<<quantes<<endl;
    //cout<<"res: "<<res.first<<", "<<res.second<<endl;
    return res;
}


info cambraAdjunta(posicio pos, int ran) {    

    struct info cambra;

    //cout<<"ran: "<<ran<<endl;

        if (ran == 0){                          // Nord.
            cambra.pos.first = pos.first-1;
            cambra.pos.second = pos.second;
            cambra.par = paret::NORD;
        
        } else if (ran == 1){                   // Est.
            cambra.pos.first = pos.first;
            cambra.pos.second = pos.second+1;
            cambra.par = paret::EST;
        
        } else if (ran == 2){                   // Sud.
            cambra.pos.first = pos.first+1;
            cambra.pos.second = pos.second;
            cambra.par = paret::SUD;

        } else {                                // Oest.
            cambra.pos.first = pos.first;
            cambra.pos.second = pos.second-1;
            cambra.par = paret::OEST;
        }
    
    return cambra;
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
    //cout<<"ran paret: "<<ran<<endl;

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

bool posValida(posicio pos, nat numFiles, nat numCol) {

    if (pos.first < 1 or pos.first > numFiles
    or pos.second < 1 or pos.second > numCol) return false;
    else return true;

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
