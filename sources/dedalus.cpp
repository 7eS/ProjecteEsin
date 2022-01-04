#include "dedalus.hpp"
using namespace std;

struct info{
    posicio pos;
    paret par;
};

posicio seleccionaCambra(posicio arrayCambres[], nat i, nat quantes);
info cambraAdjunta(posicio pos);
bool posValida(posicio pos, nat numFiles, nat numCol);

// IMPLEMENTACIÓ DE LA CLASSE DEDALUS.

// Excava el laberint, fent un laberint perfecte. Un laberint està excavat
// si i només si alguna de les seves cambres té alguna porta oberta.
// Es produeix un error si el laberint ja està excavat.
void dedalus::construir(laberint& M) throw(error) {

    nat quantesCambres = (M.num_files() * M.num_columnes());  // comprovar si es -1 o no.
    particio<posicio> p(quantesCambres);

    // Comprovem si hi ha alguna porta oberta a alguna de les cambres del
    // laberint M i afegim les cambres a la particio
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
    cout<<"cambra:"<< arrayCambres[quantesCambres-1].first<<" "<<arrayCambres[quantesCambres-1].second<<endl;
   /* cout<<endl;
    cout<<"k: "<<k<<endl;
    cout<<"quantes cambres: "<<quantesCambres<<endl;
    cout<<"numElems: "<<p.num_elements()<<endl;
    cout<<"fin construc"<<endl; */
    util::Random ran;  // Utilitzem la classe Random.

    posicio pos;
    posicio pos2;
    cambra c;
    cambra c2;
    paret par;
    info camAdj;

    nat cont = 0;
    bool cambraValida, cambraAdjValida;

    while (p.size() > 1) {

        cambraValida = false;
        //cout<<"pre cambraValida"<<endl;
        // Busquem una cambra aleatoria.
        /* while ( not cambraValida ){
            pos.first = ran(1, M.num_files());
            pos.second = ran(1, M.num_columnes());
            c = M(pos);
            cout<<"pos.first: "<<pos.first<<"pos.second: "<<pos.second<<endl;
            // Comprovem que la cambra no hagi sigut oberta encara
            if (not (c.porta_oberta(paret::NORD) or c.porta_oberta(paret::SUD) or
                c.porta_oberta(paret::EST) or c.porta_oberta(paret::OEST)))
                cambraValida = true;
        } */

        while (not cambraValida){

            pos = seleccionaCambra(arrayCambres, cont, quantesCambres);
            //cout<<"pos.first: "<<pos.first<<"pos.second: "<<pos.second<<endl;

            c = M(pos);

            if (not c.porta_oberta(paret::NORD) and not c.porta_oberta(paret::SUD) and
                not c.porta_oberta(paret::EST) and not c.porta_oberta(paret::OEST))
                cambraValida = true;

            if(cont < quantesCambres-2) cont++;

        }
        //cout<<"cambra valida ok"<<endl;

        cambraAdjValida = false;
        while (not cambraAdjValida ){
        // Busquem una cambra que no surti del rang

            camAdj = cambraAdjunta(pos);

            pos2 = camAdj.pos;
            par = camAdj.par;
            
            if (posValida(pos2, M.num_files(), M.num_columnes())) cambraAdjValida = true;   
        }
        cout<<"cambra adjunta valida ok"<<endl;
        // Si no pertany al mateix grup, obrim porta i unim
        if(not p.mateix_grup(pos, pos2)){
            M.obre_porta(par, pos);
            p.unir(pos, pos2);
        }
    }
}


/* bool portaExterior(paret p, posicio pos) {
    // Pre: p és una paret d'una cambra del laberint i pos es una posicio
    // existent del laberint. 
    //Post: Retorna true si p és una porta exterior, altrament false.


    if (pos.first - 1 == 0 and p == paret::NORD)
        return true;
    else if (pos.first ==  and p == paret::SUD)
        return true;
    else if (pos.second - 1 == 0 and p == paret::OEST)
        return true;
    else if (pos.second == _nCol and p == paret::EST)
        return true;

    return false;
} */

posicio seleccionaCambra(posicio arrayCambres[], nat i, nat quantes){

    util::Random r;
    posicio res;
    //cout<<"cont: "<<i<<endl;
    int ran = r(i, quantes-1);
//    cout<<"diferencia: "<<(quantes-1) - i<<endl;
//    nat diferencia = (quantes-1) - i; 

//    if(diferencia == 1) res = arrayCambres[quantes-1];

//    else{
         res = arrayCambres[ran];
         arrayCambres[ran] = arrayCambres[i];
//    }

    return res;
}

info cambraAdjunta(posicio pos){
    util::Random r;

    struct info cambra;
    int ran = r(0,4); 

    if(ran == 0){ //nord
        cambra.pos.first = pos.first-1;
        cambra.pos.second = pos.second;
        cambra.par = paret::NORD;
    
    } else if(ran == 1){ //est
        cambra.pos.first = pos.first;
        cambra.pos.second = pos.second+1;
        cambra.par = paret::EST;
    
    } else if (ran == 2){ //sud
        cambra.pos.first = pos.first+1;
        cambra.pos.second = pos.second;
        cambra.par = paret::SUD;

   } else{ //oest
        cambra.pos.first = pos.first;
        cambra.pos.second = pos.second-1;
        cambra.par = paret::OEST;
    }
    return cambra;
}

bool posValida(posicio pos, nat numFiles, nat numCol){
    if (pos.first < 1 or pos.first > numFiles
    or pos.second < 1 or pos.second > numCol) return false;
    else return true;

}

/*while(not es_dins){ 


            if(pos2.first >= 1 and pos2.first <= M.num_files()
            and pos2.first >= 1 and pos2.second <= M.num_columnes() and not portaExt) es_dins = true;

    }  */

/* 
        if (pos.first == 1) {  // Paret Nord

            if (pos.second == 1) {
                porta = ran(2);
                if (porta == 0){
                    par = paret::SUD;
                    //cout<<"par sud: "<<par<<endl;
                    }
                else{
                    //cout<<"par est: "<<par<<endl;
                    par = paret::EST;
                }

            } else if (pos.second == M.num_files()) {
                porta = ran(2);
                if (porta == 0){
                    par = paret::NORD;
                    //cout<<"par nord: "<<par<<endl;
                    }
                else{
                    par = paret::EST;
                    //cout<<"par nord: "<<par<<endl;
                    }
            } else {
                porta = ran(3);
                if (porta == 0)
                    par = paret::SUD;
                else if (porta == 1)
                    par = paret::EST;
                else
                    par = paret::OEST;
            }
        }
        else if (pos.first == M.num_files()) {  // Paret Sud

            if (pos.second == 1) {  // sud-oest
                porta = ran(2);
                if (porta == 0)
                    par = paret::NORD;
                else
                    par = paret::EST;

            } else if (pos.second == M.num_columnes()) {  // sud-est
                porta = ran(2);
                if (porta == 0)
                    par = paret::NORD;
                else
                    par = paret::OEST;

            } else {  // enmig del sud
                porta = ran(3);
                if (porta == 0)
                    par = paret::NORD;
                else if (porta == 1)
                    par = paret::EST;
                else
                    par = paret::OEST;
            }
        } else if (pos.second == M.num_columnes()) {  // Paret Est.

            if (pos.first == 1) {  // nord-est
                porta = ran(2);
                if (porta == 0)
                    par = paret::SUD;
                else
                    par = paret::OEST;

            } else if (pos.first == M.num_files()) {  // sud-est
                porta = ran(2);
                if (porta == 0)
                    par = paret::NORD;
                else
                    par = paret::OEST;

            } else {  // enmig del est
                porta = ran(3);
                if (porta == 0)
                    par = paret::NORD;
                else if (porta == 1)
                    par = paret::SUD;
                else
                    par = paret::OEST;
            }
        }
        else if (pos.second == 1) {  // Paret Oest.

            if (pos.first == 1) {  // nord-oest
                porta = ran(2);
                if (porta == 0)
                    par = paret::SUD;
                else
                    par = paret::EST;

            } else if (pos.first == M.num_files()) {  // sud-oest
                porta = ran(2);
                if (porta == 0)
                    par = paret::NORD;
                else
                    par = paret::EST;

            } else {  // enmig del oest
                porta = ran(3);
                if (porta == 0)
                    par = paret::NORD;
                else if (porta == 1)
                    par = paret::SUD;
                else
                    par = paret::EST;
            }
        }
        else{
            porta = ran(4);
            if (porta == 0)
                par = paret::NORD;
            else if (porta == 1)
                par = paret::SUD;
            else if( porta == 2)
                par = paret::EST;
            else if (porta == 3)
                par = paret::OEST;
        }

        cout<<"pos i: "<<pos.first<<" pos j: "<<pos.second<<endl;
        cout<<"pos2 i: "<<pos2.first<<" pos2 j: "<<pos2.second<<endl;
        if ((pos.first - 1 == 0 and par == paret::NORD) or (pos.first == M.num_files() and par == paret::SUD)
         or (pos.second - 1 == 0 and par == paret::OEST) or (pos.second == M.num_columnes() and par == paret::EST)){
             portaExt = true;
         }
                
        if (not portaExt){
            if (par == paret::NORD){
                cout << "paret nord: " << par << endl;
                pos2.first = pos.first - 1;
                pos2.second = pos.second;
                //cout<<"hola1"<<endl;
            }else if (par == paret::SUD){
                            cout << "paret sud: " << par << endl;
                //cout << "nova pos i2: " << pos.first+1 << " nova pos j2: " << pos.second << endl;
                pos2.first = pos.first + 1;
                pos2.second = pos.second;
                //cout<<"hola2"<<endl;
            }else if (par == paret::EST){
                            cout << "paret est: " << par << endl;
                //cout << "nova pos i2: " << pos.first << "nova  pos j2: " << pos.second +1<< endl;
                pos2.first = pos.first; 
                pos2.second = pos.second +1;
                //cout<<"hola3"<<endl;
            }else{
                            cout << "paret oest: " << par << endl;
                //cout << "nova pos i2: " << pos.first -1 << " nova pos j2: " << pos.second << endl;
                pos2.first = pos.first;
                pos2.second = pos.second -1;

                //cout<<"hola4"<<endl;
                }
            //cout<<"paret: "<<par<<endl;
        }
        */