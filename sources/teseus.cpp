#include "teseus.hpp"
using namespace std;

//IMPLEMENTACIÓ DE LA CLASSE TESEUS. 

struct info{
    posicio pos;
    bool vis;
    std::list<posicio> l; //successors 
};

nat calculIndex(posicio pos, nat cols); 
//Pre:
//Post:

//void successors(std::list<info> &L, info in, const laberint & M, info arrayPos[]);
void successors(std::list<posicio> &L, info in, const laberint & M, info arrayPos[]); 
//Pre:
//Post:

  // Genera una llista de posicions que conté el camí mínim. El primer element
  // d'aquesta llista serà la posició inici, i l'última la posició final.
  // Una posició respecte a la seva anterior o posterior ha de ser consecutiva.
  // Dues posicions són consecutives si i només si la diferència de les primeres
  // components de les posicions és en valor absolut 1 i les segones components
  // són iguals, o si la diferència de les segones components és en valor
  // absolut 1 i les primeres components són iguals. Es produeix un error si no
  // hi ha cap camí que vagi des de la cambra inicial del laberint a la final,
  // o si la cambra inicial o final no són vàlides.
  void teseus::buscar(const laberint & M, const posicio & inici, const posicio & final, 
              std::list<posicio> & L) throw(error) {
                
    // Comprovem si la posició és vàlida
    if (inici.first < 1 or inici.first > M.num_files()
          or inici.second < 1 or inici.second > M.num_columnes())  
              throw error (IniciFinalNoValid); 

    if (final.first < 1 or final.first > M.num_files() 
          or final.second < 1 or final.second > M.num_columnes())
               throw error (IniciFinalNoValid);
                      
    cambra cinici = M(inici);     // Cambra inicial. 
    cambra cfi = M(final);        // Cambra destí. 
    

    // Si la posicio inicial i final son diferents, comprovarem si son accesibles.
    if (inici != final) {

        if (not cinici.porta_oberta(paret::NORD) and not cinici.porta_oberta(paret::SUD) and
            not cinici.porta_oberta(paret::EST) and not cinici.porta_oberta(paret::OEST) )
                throw error (SenseSolucio);
        
        if (not cfi.porta_oberta(paret::NORD) and not cfi.porta_oberta(paret::SUD) and
            not cfi.porta_oberta(paret::EST) and not cfi.porta_oberta(paret::OEST) )
                throw error (SenseSolucio);
    }
    
    nat files = M.num_files();
    nat cols = M.num_columnes();
    nat totalVert = files*cols;
    //nat dist[totalVert];
    //Creem la matriu d'adjacència.     
    info arrayPos[totalVert];
    posicio pred[totalVert];
    //nat inf = 999999;

    nat k = 0;
    posicio senti(0,0);  // Sentinella 
    for (nat i = 1; i <= M.num_files(); i++) {
        for (nat j = 1; j <= M.num_columnes(); j++, k++) {
            
            info in;
            posicio p(i,j);
            // Afegim els valors a l'atribut de l'struct
            in.vis = false;             // Indica si s'ha visitat o no. 
            in.pos = p;
            // Afegim la informacio a l'array.
            arrayPos[k] = in;
            pred[k] = senti; 
            //dist[k] = inf;

        }
    }
    
    // A cada posicio li posem els seus successors. 
    for (nat i = 0; i < totalVert; i++) {
        successors(arrayPos[i].l,arrayPos[i],M, arrayPos);
    }


/*    for (nat i = 0; i < totalVert; i++) {
        std::list<info> lsucc;
        successors(lsucc,arrayPos[i],M, arrayPos);

        for (list<info>::iterator it = lsucc.begin(); it != lsucc.end(); it++) {
            //std::cout<<"index: " << arrayPos[calculIndex((*it).pos, cols)].pos.first<<", "<<arrayPos[calculIndex((*it).pos, cols)].pos.second<<endl;
            arrayPos[i].l.push_back(arrayPos[calculIndex((*it).pos, cols)].pos);
        }
    } */
    std::list<info> noVist;     // Lista dels nodes no explorats

    // Posem a 0 la distancia del punt inicial cap a ell mateix i el marquem com a visitat
    nat in = calculIndex(inici, cols);
    //dist[in] = 0;              
    arrayPos[in].vis = true;
    noVist.push_back(arrayPos[in]);
               
    nat indexActual;
    nat indexSuc;
    bool cami = false;          // Booleà que ens indica si hem trobat la posicio final o no.
    //nat rep = 0;

    if (inici == final) {
        posicio res(arrayPos[calculIndex(inici,cols)].pos);
        L.push_back(res);   
    }
    else{
        while (not noVist.empty() and not cami) {
            // Explotem el node
            info actual = noVist.front();
            noVist.pop_front();
            indexActual = calculIndex(actual.pos,cols);

        /*    info test;

                test = arrayPos[indexActual];
                cout<<"pos: "<<actual.pos.first<<", "<<actual.pos.second<<" successor: ";
                for(list<posicio>::iterator it = actual.l.begin(); it != actual.l.end(); it++){
                    cout<<(*it).first<<", "<<(*it).second<<" - ";
                }
                cout<<endl; */

            // Recorrem els successors del node explotat.
            for (list<posicio>::iterator it = actual.l.begin(); it != actual.l.end() and not cami; it++){
                indexSuc = calculIndex(*it, cols);
                // Comprovem si ja haviem visitat aquesta posicio. 
                // Si no es aixi augmentem la distancia i la marquem com a explorada
                if (not (arrayPos[indexSuc].vis)) { 
                    arrayPos[indexSuc].vis = true;
                    //dist[indexSuc] = dist[indexActual]+1;
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

        // Si no hem trovat camí previament, retornem un error.
        if (not cami) throw error (SenseSolucio);

        // Prenem el camí més curt del que hem explorat.
        posicio previ = final;
        nat indexPrevi = calculIndex(previ,cols);
        L.push_back(previ);
        // Mentre la posicio previa sigui diferent a la sentinella.
        
        while (pred[indexPrevi] != senti) {
            indexPrevi = calculIndex(previ,cols);
            L.push_front(pred[indexPrevi]);
            previ = pred[indexPrevi];
        }
        //Eliminem la sentinella (0,0)
        L.pop_front();
    }              
}


//void successors(std::list<info> &L, info in, const laberint & M, info arrayPos[]) {
void successors(std::list<posicio> &L, info in, const laberint & M, info arrayPos[]) {

    cambra c = M(in.pos);
    if (c.porta_oberta(paret::NORD)) {

        posicio posNovaN(in.pos.first-1, in.pos.second);
        info infoNovaN  = arrayPos[calculIndex(posNovaN, M.num_columnes())];
    
        if (not infoNovaN.vis) {
            //L.push_back(infoNovaN);
            L.push_back(posNovaN);
            }
        }

    if (c.porta_oberta(paret::SUD)) {

        posicio posNovaS(in.pos.first+1, in.pos.second);
        info infoNovaS  = arrayPos[calculIndex(posNovaS, M.num_columnes())];

        if (not infoNovaS.vis) {
         //L.push_back(infoNovaS);
         L.push_back(posNovaS);
        }
    }
        
    if (c.porta_oberta(paret::EST)) {

        posicio posNovaE(in.pos.first, in.pos.second+1);
        info infoNovaE  = arrayPos[calculIndex(posNovaE, M.num_columnes())];
        
        if (not infoNovaE.vis) {
            //L.push_back(infoNovaE);
            L.push_back(posNovaE);
            }
        }        

    if (c.porta_oberta(paret::OEST)) {
        
        posicio posNovaO(in.pos.first, in.pos.second-1);
        info infoNovaO  = arrayPos[calculIndex(posNovaO, M.num_columnes())];

        if (not infoNovaO.vis) {
            //L.push_back(infoNovaO);
            L.push_back(posNovaO);
        }   
    }
}

//Formula per accedir a la posicio de l'array a on es troba la nostra coordenda:
// numCols*(pos.first-1)+1+(pos.second-1)
 nat calculIndex(posicio pos, nat cols) {

     nat index = cols*(pos.first-1)+(pos.second-1);
     return index;
 }
