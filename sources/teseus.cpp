#include "teseus.hpp"
using namespace std;

//IMPLEMENTACIÓ DE LA CLASSE TESEUS. 
/*

to do. 


*/
struct info{
    posicio pos;
    bool vis;
    //std::list<posicio> l; //successors 
};


nat calculIndex(posicio pos, nat cols); 
//Pre: pos es una posició dintre de laberint, cols és el número de columnes del laberint. 
//Post: Retorna l'index en què es troba la cambra de posició pos.


void successors(std::list<posicio> &l, info &in, const laberint & M, info arrayPos[]); 
//void successors(info &in, const laberint & M, info arrayPos[]); 
//Pre: in conté informació sobre la cambra escollida, M és el laberint, arrayPos[] és no buit. 
//Post: Adjunta a in els seus corresponents successors.


// Genera una llista de posicions que conté el camí mínim. El primer element
// d'aquesta llista serà la posició inici, i l'última la posició final.
// Una posició respecte a la seva anterior o posterior ha de ser consecutiva.
// Dues posicions són consecutives si i només si la diferència de les primeres
// components de les posicions és en valor absolut 1 i les segones components
// són iguals, o si la diferència de les segones components és en valor
// absolut 1 i les primeres components són iguals. Es produeix un error si no
// hi ha cap camí que vagi des de la cambra inicial del laberint a la final,
// o si la cambra inicial o final no són vàlides.
// Cost en temps: Θ(1)  Cost en espai: -
void teseus::buscar(const laberint & M, const posicio & inici, const posicio & final, 
              std::list<posicio> & L) throw(error) {
                
    // Comprovem si la posició és vàlida
    if (inici.first < 1 or inici.first > M.num_files()
          or inici.second < 1 or inici.second > M.num_columnes())  
              throw error (IniciFinalNoValid); 

    if (final.first < 1 or final.first > M.num_files() 
          or final.second < 1 or final.second > M.num_columnes())
               throw error (IniciFinalNoValid);
                      
    
    cambra cinici = M(inici),cfi = M(final);        
    // Si la posicio inicial i final son diferents, comprovarem si son accesibles.
    if (inici != final) {

        if (not cinici.porta_oberta(paret::NORD) and not cinici.porta_oberta(paret::SUD) and
            not cinici.porta_oberta(paret::EST) and not cinici.porta_oberta(paret::OEST) )
                throw error (SenseSolucio);
        
        if (not cfi.porta_oberta(paret::NORD) and not cfi.porta_oberta(paret::SUD) and
            not cfi.porta_oberta(paret::EST) and not cfi.porta_oberta(paret::OEST) )
                throw error (SenseSolucio);
    }
    
    nat files = M.num_files(), cols = M.num_columnes(), totalVert = files*cols;
    //Creem la matriu d'adjacència.     
    info arrayPos[totalVert];
    posicio pred[totalVert];

    nat k = 0;
    posicio senti(0,0);  // Sentinella 
    for (nat i = 1; i <= M.num_files(); i++) {
        for (nat j = 1; j <= M.num_columnes(); j++, k++) {
            
            info in;
            posicio p(i,j);
            // Afegim els valors a l'atribut de l'struct
            in.vis = false;             
            in.pos = p;
            // Afegim la informacio a l'array.
            arrayPos[k] = in;
            pred[k] = senti; 
        }
    }
    if (inici == final) {
        posicio res(arrayPos[calculIndex(inici,cols)].pos);
        L.push_back(res);   
    }
    else{

        std::list<info> noVist;     // Lista dels nodes no explorats

        // Marquem com a visitat el punt inicial
        nat in = calculIndex(inici, cols);
        //successors(arrayPos[in].l,arrayPos[in],M, arrayPos);
        arrayPos[in].vis = true;
        noVist.push_back(arrayPos[in]);
                
        nat indexActual, indexSuc;
        bool cami = false;  // Booleà que ens indica si hem trobat la posicio final o no.
        //bool primer = true;   

        while (not noVist.empty() and not cami) {
            // Explotem el node
            //indexActual = calculIndex(noVist.front().pos,cols);

            std::list<posicio> l; //successors 
            successors(l,noVist.front(),M, arrayPos);
            //successors(noVist.front(),M, arrayPos);

            info actual =  noVist.front();
            noVist.pop_front();


        /*    info test;

                test = arrayPos[indexActual];
                cout<<"pos: "<<actual.pos.first<<", "<<actual.pos.second<<" successor: ";
                for(list<posicio>::iterator it = actual.l.begin(); it != actual.l.end(); it++){
                    cout<<(*it).first<<", "<<(*it).second<<" - ";
                }
                cout<<endl; */

            // Recorrem els successors del node explotat. Seran com a màxim 4 iteracions.
            //for (list<posicio>::iterator it = actual.l.begin(); it != actual.l.end() and not cami; it++){
            for (list<posicio>::iterator it = l.begin(); it != l.end() and not cami; it++){
                indexSuc = calculIndex(*it, cols);
                // Comprovem si ja haviem visitat aquesta posicio. 
                // Si no es aixi augmentem la distancia i la marquem com a explorada
                if (not (arrayPos[indexSuc].vis)) { 
                    indexActual = calculIndex(actual.pos,cols);
                    arrayPos[indexSuc].vis = true;
                    pred[indexSuc] = arrayPos[indexActual].pos;
                    // Afegim el node a la llista de pendents per explorar.
                    noVist.push_back(arrayPos[indexSuc]);
                    //rep++;
                    if (arrayPos[indexSuc].pos == final) {
                        cami =  true;
                    }
                }
            }
        } 

        if (not cami) throw error (SenseSolucio);

        // Prenem el camí més curt del que hem explorat.
        posicio previ = final;
        nat indexPrevi = calculIndex(previ,cols);
        L.push_back(previ);
        
        while (pred[indexPrevi] != senti) {
            indexPrevi = calculIndex(previ,cols);
            L.push_front(pred[indexPrevi]);
            previ = pred[indexPrevi];
        }
        //Eliminem la sentinella (0,0)
        L.pop_front();
    }              
}



// Cost en temps: Θ()  Cost en espai:
//void successors( info & in, const laberint & M, info arrayPos[]) {
void successors(std::list<posicio> &L, info &in, const laberint & M, info arrayPos[]) {

    cambra c = M(in.pos);
    if (c.porta_oberta(paret::NORD)) {

        posicio posNovaN(in.pos.first-1, in.pos.second);
        info infoNovaN  = arrayPos[calculIndex(posNovaN, M.num_columnes())];
    
        if (not infoNovaN.vis) {
            L.push_back(posNovaN);
            //in.l.push_back(posNovaN);
            }
        }

    if (c.porta_oberta(paret::SUD)) {

        posicio posNovaS(in.pos.first+1, in.pos.second);
        info infoNovaS  = arrayPos[calculIndex(posNovaS, M.num_columnes())];

        if (not infoNovaS.vis) {
         L.push_back(posNovaS);
         //in.l.push_back(posNovaS);
        }
    }
        
    if (c.porta_oberta(paret::EST)) {

        posicio posNovaE(in.pos.first, in.pos.second+1);
        info infoNovaE  = arrayPos[calculIndex(posNovaE, M.num_columnes())];
        
        if (not infoNovaE.vis) {
            L.push_back(posNovaE);
            //in.l.push_back(posNovaE);
            }
        }        

    if (c.porta_oberta(paret::OEST)) {
        
        posicio posNovaO(in.pos.first, in.pos.second-1);
        info infoNovaO  = arrayPos[calculIndex(posNovaO, M.num_columnes())];

        if (not infoNovaO.vis) {
            L.push_back(posNovaO);
            //in.l.push_back(posNovaO);
        }   
    }
}

// Cost en temps: Θ(1)  Cost en espai: -
 nat calculIndex(posicio pos, nat cols) {

     nat index = cols*(pos.first-1)+(pos.second-1);
     return index;
 }
