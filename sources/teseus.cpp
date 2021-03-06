#include "teseus.hpp"
using namespace std;

//IMPLEMENTACIÓ DE LA CLASSE TESEUS. 
/*

Per implementar la classe Teseus, ens hem basat en l'algorisme de recorregut d'amplada d'un graf (BFS).
Per fer-ho, hem creat un struct que té com a atributs una posició pos i un booleà vis. El primer indica
la posició de la cambra que estem tractant; el segon si ja ha sigut visitada prèviament. Aquest struct
és un dels eixos principals de la classe, doncs ens permet mantenir gran part de la informació recollida 
en un mateix array. Aquest array és el que anomenem arrayPos[] i on juntament amb l'array pred[], 
de predecessors, desenvoluparem l'algorisme. A més, cada vegada que volguem obtenir les cambres successores
d'una altra cambra, crearem una llista local que les emmagatzemarà, serà recorreguda i posteriorment destruïda.
Aquesta llista de successors tindrà sempre una mida màxima de 4, una per paret. Cada vegada que una cambra
sigui explorada, aquesta serà marcada com a visitada, i posarem el seu booleà de info a true. Un cop
trobada la posició destí, si és que és accessible, només haurem de recórrer l'array pred[] cap a enrrere,
fins arribar a la posició sentinella, la (0,0).

Vam decidir fer servir un struct perquè és una estructura que ens permetria accedir a la informació amb 
un cost molt petit, doncs tenint la posició guardada podríem calcular la seva ubicació dins de l'arrayPos[]
amb un senzill càlcul, implementat al mètode calculIndex(posicio pos, nat cols). D'aquesta manera,
obtenir la ubicació de cada cambra tindria un cost constant, només requerim d'accedir a l'atribut pos.
A més, la creació de la llista de successors dintre del while ens permet estalviar costos en memòria que 
d'una altra manera tindriem si l'haguèssim afegit dins de l'struct info, tenint una llista per cada cambra
del laberint, com teníem inicialment. Aquesta optimització ens ha permés reduïr notablement els temps en 
els diferents jocs de prova tant públics com propis. 

L'ús de les dues arrays, arrayPos[] i pred[], fan de matriu d'adjacència, per tant, ens fa tenir un cost
Θ(n²) on n és el número de posicions o total de cambres que tenim. Sent una mica més pesat que una simple
llista d'adjacència, que seria Θ(n+a). Ens vam decidir a fer servir la matriu per raons de senzillesa
en el codi i per temps, doncs implementar la llista ens portava a fer servir cues de prioritat i no 
estàvem segurs de si ens donaria temps a fer-les bé en el temps que quedava.

*/

struct info{
    posicio pos;
    bool vis;
};


nat calculIndex(posicio pos, nat cols); 
//Pre: pos es una posició dintre de laberint, cols és el número de columnes del laberint. 
//Post: Retorna l'index en què es troba la cambra de posició pos.


void successors(std::list<posicio> &lsucc, info &in, const laberint & M, info arrayPos[]); 
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
// Cost en temps: Θ((numFiles*numColumes)²).  Cost en espai: Θ((numFiles*numColumes)²)
void teseus::buscar(const laberint & M, const posicio & inici, const posicio & final, 
              std::list<posicio> & L) throw(error) {
                
    // Comprovem si la posició és vàlida.
    if (inici.first < 1 or inici.first > M.num_files()
          or inici.second < 1 or inici.second > M.num_columnes())  
              throw error (IniciFinalNoValid); 

    if (final.first < 1 or final.first > M.num_files() 
          or final.second < 1 or final.second > M.num_columnes())
               throw error (IniciFinalNoValid);
                      
    
    cambra cinici = M(inici),cfi = M(final);        
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
            in.vis = false;             
            in.pos = p;

            arrayPos[k] = in;
            pred[k] = senti; 
        }
    }
    if (inici == final) {
        posicio res(arrayPos[calculIndex(inici,cols)].pos);
        L.push_back(res);   
    }
    else{

        std::list<info> noVist;     // Lista dels nodes no explorats.

        // Marquem com a visitat el punt inicial.
        nat in = calculIndex(inici, cols);
        arrayPos[in].vis = true;
        noVist.push_back(arrayPos[in]);
                
        nat indexActual, indexSuc;
        bool cami = false;     

        while (not noVist.empty() and not cami) {
            // Explotem el node.

            std::list<posicio> lsucc; //successors.
            successors(lsucc,noVist.front(),M, arrayPos);

            info actual =  noVist.front();
            noVist.pop_front();

            // Recorrem els successors del node explotat. Seran com a màxim 4 iteracions.
            for (list<posicio>::iterator it = lsucc.begin(); it != lsucc.end() and not cami; it++){
                indexSuc = calculIndex(*it, cols);

                if (not (arrayPos[indexSuc].vis)) { 
                    indexActual = calculIndex(actual.pos,cols);
                    arrayPos[indexSuc].vis = true;
                    pred[indexSuc] = arrayPos[indexActual].pos;
                    noVist.push_back(arrayPos[indexSuc]);
                    
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


// Cost en temps: Θ(1).  Cost en espai: Θ(1)
// El cost temporal és Θ(1) ja que només es faran quatre consultes, en el millor dels casos, i no 
// afegim cap node. En el pitjor dels casos, només afegim quatre posicions a la llista de 
// successors. 
void successors(std::list<posicio> &lsucc, info &in, const laberint & M, info arrayPos[]) {

    cambra c = M(in.pos);
    if (c.porta_oberta(paret::NORD)) {

        posicio posNovaN(in.pos.first-1, in.pos.second);
        info infoNovaN  = arrayPos[calculIndex(posNovaN, M.num_columnes())];
    
        if (not infoNovaN.vis) {
            lsucc.push_back(posNovaN);
        }
    }

    if (c.porta_oberta(paret::SUD)) {

        posicio posNovaS(in.pos.first+1, in.pos.second);
        info infoNovaS  = arrayPos[calculIndex(posNovaS, M.num_columnes())];

        if (not infoNovaS.vis) {
            lsucc.push_back(posNovaS);
        }
    }
        
    if (c.porta_oberta(paret::EST)) {

        posicio posNovaE(in.pos.first, in.pos.second+1);
        info infoNovaE  = arrayPos[calculIndex(posNovaE, M.num_columnes())];
        
        if (not infoNovaE.vis) {
            lsucc.push_back(posNovaE);
        }
    }        

    if (c.porta_oberta(paret::OEST)) {
        
        posicio posNovaO(in.pos.first, in.pos.second-1);
        info infoNovaO  = arrayPos[calculIndex(posNovaO, M.num_columnes())];

        if (not infoNovaO.vis) {
            lsucc.push_back(posNovaO);
        }   
    }
}

// Cost en temps: Θ(1). Cost en espai: -
 nat calculIndex(posicio pos, nat cols) {

     nat index = cols*(pos.first-1)+(pos.second-1);
     return index;
 }
