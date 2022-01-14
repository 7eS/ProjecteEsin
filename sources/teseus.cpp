#include "teseus.hpp"
using namespace std;

//IMPLEMENTACIÓ DE LA CLASSE TESEUS. 


// Potser es necessita.
struct info{
    posicio pos;
    bool vis;
    std::list<posicio> l; //successors 
};

//typedef vector<vector<int> > arestes; //Llista d'adjacencia de integers
void afegirCamins(posicio adjacents[], posicio inici, posicio final);
//Pre:
//Post:

nat calculIndex(posicio pos, nat cols);
//Pre:
//Post:

nat distMinima(nat dist[], bool adj[], std::list<posicio> & L, nat quants);
//Pre:
//Post:

void hi_ha_cami(const posicio &inici, const posicio & final, bool mAdj[], bool &cami);
//Pre:
//Post: 
void successors(std::list<info> &L, info in, const laberint & M, info arrayPos[]);
//Pre:
//Post:

void rec_amplada(info &in, const laberint & M, std::list<posicio> & L);
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
    
    // Mirem si les posicions donades són accesibles.
    
    if(inici != final){
        if (not cinici.porta_oberta(paret::NORD) and not cinici.porta_oberta(paret::SUD) and
            not cinici.porta_oberta(paret::EST) and not cinici.porta_oberta(paret::OEST) )
                throw error (SenseSolucio);
        
        if (not cfi.porta_oberta(paret::NORD) and not cfi.porta_oberta(paret::SUD) and
            not cfi.porta_oberta(paret::EST) and not cfi.porta_oberta(paret::OEST) )
                throw error (SenseSolucio);
    }
    

    //Creem la matriu d'adjacència.     
    nat files = M.num_files();
    nat cols = M.num_columnes();
    nat totalVert = files*cols;
    //bool mAdj[totalVert];
    nat dist[totalVert];
    //posicio arrayPos[totalVert];
    info arrayPos[totalVert];
    posicio pred[totalVert];
    nat inf = 999999;

    // Potser nomes hauriem d'aprofitar la part superior de la matriu. j = i
    nat k = 0;
    posicio senti(0,0); //sentinella 
    for (nat i = 1; i <= M.num_files(); i++) {
        for (nat j = 1; j <= M.num_columnes(); j++, k++) {
            info in;
            posicio p(i,j);
            in.vis = false;             // Indica si s'ha visitat o no. 
            in.pos = p;
            arrayPos[k] = in;
            pred[k] = senti; 
            //mAdj[k] = false;
            dist[k] = inf;
            //arrayPos[k] = p;
        }
    }

    // A cada posicio li posem els seus successors. 
    for( nat i = 0; i < totalVert; i++){
        std::list<info> lsucc;
        successors(lsucc,arrayPos[i],M, arrayPos);

        for(list<info>::iterator it = lsucc.begin(); it != lsucc.end(); it++){
            //std::cout<<"index: " << arrayPos[calculIndex((*it).pos, cols)].pos.first<<", "<<arrayPos[calculIndex((*it).pos, cols)].pos.second<<endl;
            arrayPos[i].l.push_back(arrayPos[calculIndex((*it).pos, cols)].pos);
        }
    }
    std::list<info> noVist; //Lista dels nodes no explorats

    nat in = calculIndex(inici, cols);
    dist[in] = 0; // El node inicial està a distància zero
    arrayPos[in].vis = true;
    noVist.push_back(arrayPos[in]);
    // Potse cal afegir el predecors del source.
    //pre[]


    //funcio print per veure si funciona
/*  info test;
    while(not noVist.empty()){
        test = noVist.front();
        noVist.pop_front();
        cout<<"pos: "<<test.pos.first<<", "<<test.pos.second<<" successor: ";
        for(list<posicio>::iterator it = test.l.begin(); it != test.l.end(); it++){
            cout<<(*it).first<<", "<<(*it).second<<" - ";
        }
        cout<<endl;
    } 
*/
    //funcio print per veure si funciona

/*    cout<<"test, arraypos0:abans canvi "<<arrayPos[0].pos.first<<" ,"<<arrayPos[0].pos.second<<" vist: "<<arrayPos[0].vis<<endl;
    arrayPos[0].vis = true;
    cout<<"test, arraypos0 despres canvi: "<<arrayPos[0].pos.first<<" ,"<<arrayPos[0].pos.second<<" vist: "<<arrayPos[0].vis<<endl;
   //funcio print per veure si funciona
    noVist.push_back(arrayPos[0]);
    info test = noVist.front();
    cout<<"test, arraypos0: "<<test.pos.first<<" ,"<<test.pos.second<<" vist: "<<test.vis<<endl;
*/
/*
    info test;
    for( nat i = 0; i < totalVert; i++){
        test = arrayPos[i];
        std::cout<<"pos: "<<test.pos.first<<", "<<test.pos.second<<" successor: ";
        for(list<posicio>::iterator it = test.l.begin(); it != test.l.end(); it++){
            std::cout<<(*it).first<<", "<<(*it).second<<" - ";
        }
        std::cout<<endl;
    } 
      */        
               
    nat indexActual;
    nat indexSuc;
    bool cami = false; // booleà que ens indica si hem trobat la posicio final o no
    //nat rep = 0;

    if(inici == final){
        posicio res(arrayPos[calculIndex(inici,cols)].pos);
        L.push_back(res);   
    }
    else{
        while (not noVist.empty() and not cami) {
            // Explotem el node
            info actual = noVist.front();
            noVist.pop_front();
            indexActual = calculIndex(actual.pos,cols);
            //std::cout<<"indexActual:"<<indexActual<<std::endl;
            // Recorrem els successors del node explotat.

        /*    info test;

                test = arrayPos[indexActual];
                cout<<"pos: "<<actual.pos.first<<", "<<actual.pos.second<<" successor: ";
                for(list<posicio>::iterator it = actual.l.begin(); it != actual.l.end(); it++){
                    cout<<(*it).first<<", "<<(*it).second<<" - ";
                }
                cout<<endl; */


            for (list<posicio>::iterator it = actual.l.begin(); it != actual.l.end() and not cami; it++){
                indexSuc = calculIndex(*it, cols);
                // Comprovem si ja haviem visitat aquesta posicio. 
                // Si no es aixi augmentem la distancia i la marquem com a explorada
                if (not (arrayPos[indexSuc].vis)) { 
                    arrayPos[indexSuc].vis = true;
                    // Aquesta linea de distancia potser falla
                    dist[indexSuc] = dist[indexActual]+1;
                    pred[indexSuc] = arrayPos[indexActual].pos;
                    // Afegim el node a la llista de pendents per explorar.
                    noVist.push_back(arrayPos[indexSuc]);
                    //rep++;
                    // Parem el recorregut si ens trobem amb la posicio final
                    if (arrayPos[indexSuc].pos == final) {
                        cami =  true;
                    }
                }
            }
        } 

        //std::cout<<"explorats: "<<rep<<endl;
        // Si no hem trovat camí previament, retornem un error.
        if(not cami) throw error (SenseSolucio);

        // Prenem el camí més curt del que hem explorat.
        posicio previ = final;
        nat indexPrevi = calculIndex(previ,cols);
        L.push_back(previ);
        // Mentre la posicio previa sigui diferent a la sentinella.
        
        while (pred[indexPrevi] != senti){
            indexPrevi = calculIndex(previ,cols);
            L.push_front(pred[indexPrevi]);
            previ = pred[indexPrevi];
        }
        //Eliminem la sentinella (0,0)
        L.pop_front();
    }              
}




    //Formula per accedir a la posicio de l'array a on es troba la nostra coordenda:
    // numCols*(pos.first-1)+1+(pos.second-1)
    // Posem a 0 la distancia del punt inicial cap a ell mateix
    //dist[calculIndex(inici,cols)] = 0;
    //mAdj[calculIndex(inici,cols)] = true;




/*
    bool cami = false; 
    //posicio aux = inici;
    //nat indexMin;
    // Farem un recorregut per tots els nodes excepte per l'inicial.
    info infoActual, infoSucc;
    nat indexSucc;

    for (nat i = 0; i < totalVert and not cami; i++) {
    cout<<"entro en el for grande"<<endl;
        if (not arrayPos[i].vis) {

            infoActual = arrayPos[i];
            if (infoActual.pos == final) cami = true;
            
            else {
                std::list<info> lInfo;
                lInfo.push_back(infoActual);
                infoActual.vis = true;
                cout<<"infoActual: "<<infoActual.pos.first<<" ,"<<infoActual.pos.second<<endl;

                while(not lInfo.empty()){
                    cout<<"entro en el while de dentro del for"<<endl;
                    info infoNou = lInfo.front();
                    cout<<"infoNou: "<<infoNou.pos.first<<" ,"<<infoNou.pos.second<<endl;
                    lInfo.pop_front();
                    list<info>lSucc;
                    successors(lSucc,infoNou, M, arrayPos);

                    for (list<info>::iterator it = lSucc.begin(); it != lSucc.end(); it++){
                        cout<<"entra en el for interno"<<endl;
                        cout<<(*it).pos.first<<", "<<(*it).pos.second<<" "<<(*it).vis<<endl;
                        indexSucc = calculIndex((*it).pos, M.num_columnes());
                        infoSucc = arrayPos[indexSucc];
                        cout<<"infoSucc: "<<infoSucc.pos.first<<" ,"<<infoSucc.pos.second<<endl; 
                         if (not infoSucc.vis) {
                            cout<<"entro al if"<<endl,
                            lInfo.push_back(infoSucc);
                            L.push_back(infoSucc.pos);
                            infoSucc.vis = true; 
                        }
                    cout<<"post ultim for"<<endl;
                    }
                }

                //cout<<"pre rec_amplada"<<endl;
               // rec_amplada(arrayPos[i], M, L, arrayPos); 
            }      
        }
    } 
}  */
/*
void rec_amplada(info &in, const laberint & M, std::list<posicio> & L){

    std::list<info> lInfo;
    lInfo.push_back(in);
    //L.push_back(in);
    in.vis = true;
    cout<<"pre while"<<endl;
    while (not lInfo.empty()) {
    cout<<"entra en el while"<<endl;
        info infoNou = lInfo.front(); 
        cout<<"lInfo.front() pos "<<lInfo.front().pos.first<<", "<<lInfo.front().pos.second<<" visitat: "
        <<lInfo.front().vis<<endl;
        lInfo.pop_front();
        //L.prop_front();
        //Tractar
        cout<<"element info actual: "<<in.pos.first<<", "<<in.pos.second<<" - visitat: "<<in.vis<<endl;
        list<info>lSucc;
        successors(lSucc, infoNou, M);

        cout<<"pre ultim for"<<endl;            
        cout<<"elements llista: "<<endl;
        for (list<info>::iterator it = lSucc.begin(); it != lSucc.end(); it++){
            cout<<(*it).pos.first<<", "<<(*it).pos.second<<" ";
            if (not arrayPos[calculIndex((*it).pos, M.num_columnes())].vis) {
                cout<<"entro al if"<<endl,
                lInfo.push_back(*it);
                L.push_back((*it).pos);
                (*it).vis = true; 
            }
            cout<<"post ultim for"<<endl;
        }
    }
    cout<<"post while"<<endl; 
} */
        

    //bool nomPerDeterminar = false;

    // Obtenim el vertex més proper







        /*
        else{
            nat distMin = inf;
            posicio posMin;
            
            for (nat i = 0; i < totalVert; i++) {
                
                if (not mAdj[i] and dist[i] <= distMin) {

                    distMin = dist[i];
                    indexMin = i;
                    posMin = arrayPos[i];
                }
            }
            
            // Marquem el vertex com a què ja hem passat per aquí.
            mAdj[indexMin] = true;
            posicio posNova;
            //Afegim els succesors de posMin a la llista L.
            std::list<posicio> lSucc;
            successors(lSucc, posMin, M);
            //L.push_back(posMin);
            //cout<<"posMinim: "<<posMin.first<<" ,"<<posMin.second<<endl; */

/*
            for(std::list<posicio>::iterator i = lSucc.begin(); i != lSucc.end(); ++i) {
                posicio p = *i;
                //cout<<"lSucc: "<<p.first<<", "<<p.second<<endl; 

            } */
            
            //Actualitzem les distàncies a les cambres adjacents
            //for (nat i2 = 1; i2 <= totalVert; i2++){
/*                for (std::list<posicio>::iterator it = lSucc.begin(); it != lSucc.end(); ++it) { 
                //posNova = arrayPos[i2];
                // cal fer la funcio esAdjacent()
                nat index = calculIndex(*it, cols);
                if (not mAdj[index] and dist[index] > dist[indexMin]) {
                    dist[index] = dist[indexMin];
                    L.push_back(arrayPos[indexMin]); 

                }
                aux = *it;
            }
        }
    }
    if (L.empty()) throw error(SenseSolucio);
} */



    
 /*   for (int i = 0; i < cols and not cami; i++) {
        if (aux == final) {
            cami = true;
            //return res;
        }
        else {
            if (not mAdj[a[aux.first][i]]) {

                mAdj[aux.first][i] = true;
            }
        }
    }


  for (nat i = 1; i <= cols and not cami; i++){
    
      if(aux == final) cami = true;

      else{
            cambra cNova;
            cNova = M(posNova);
            if (cNova.porta_oberta(paret::NORD) and not mAdj[aux.first-1][i]) {
              
                aux.first = aux.first-1;
                mAdj[aux.first][i] = true;
            }
            else if (cNova.porta_oberta(paret::EST) and not mAdj[aux.first][i+1]) { 
                mAdj[aux.first][i] = true;

            }
            else if (cNova.porta_oberta(paret::SUD) and not mAdj[aux.first-1][i]) {
                mAdj[aux.first][i] = true;

            }
            else if (cNova.porta_oberta(paret::OEST) and not mAdj[aux.first][i-1]){
                mAdj[aux.first][i] = true;
            }     
        }
    } */


void successors(std::list<info> &L, info in, const laberint & M, info arrayPos[]) {

    cambra c = M(in.pos);
    if (c.porta_oberta(paret::NORD)){
        //cout<<"entro en el primer if"<<endl;

        posicio posNovaN(in.pos.first-1, in.pos.second);
        //cout<<"posNovaN: "<<posNovaN.first<<", "<<posNovaN.second<<endl;
        info infoNovaN  = arrayPos[calculIndex(posNovaN, M.num_columnes())];
        //cout<<"infoNovaN: "<<infoNovaN.pos.first<<", "<<infoNovaN.pos.second<<" - vis: "<<infoNovaN.vis<<endl;
        if(not infoNovaN.vis){
            L.push_back(infoNovaN);
        //cout<<"if del if nord"<<endl;
            }
        }

    if (c.porta_oberta(paret::SUD)){
        //cout<<"entro en el 2ndo if"<<endl; 

        posicio posNovaS(in.pos.first+1, in.pos.second);
        //cout<<"posNovaS"<<posNovaS.first<<", "<<posNovaS.second<<endl;
        info infoNovaS  = arrayPos[calculIndex(posNovaS, M.num_columnes())];
        //cout<<"infoNovaS"<<infoNovaS.pos.first<<", "<<infoNovaS.pos.second<<" - vis:"<<infoNovaS.vis<<endl;

        if(not infoNovaS.vis) {
         L.push_back(infoNovaS);
         //cout<<"if del if sud"<<endl;
        }
    }
        
        /*info infoNovaS;
        posicio posNovaS(in.pos.first+1, in.pos.second);
        infoNovaS.pos = posNovaS;
        infoNovaS.vis = false;
        L.push_back(infoNovaS);*/
        

    if (c.porta_oberta(paret::EST)){

        posicio posNovaE(in.pos.first, in.pos.second+1);
        //cout<<"posNovaE: "<<posNovaE.first<<", "<<posNovaE.second<<endl;

        info infoNovaE  = arrayPos[calculIndex(posNovaE, M.num_columnes())];
        //cout<<"calcul index: "<<calculIndex(posNovaE, M.num_columnes())<<endl;
        //cout<<"infoNovaE"<<infoNovaE.pos.first<<", "<<infoNovaE.pos.second<<"- vis"<<infoNovaE.vis<<endl;

        if(not infoNovaE.vis){
            //cout<<"if del if est "<<endl;
            L.push_back(infoNovaE);
            }
        }

        /*info infoNovaE;
        posicio posNovaE(in.pos.first, in.pos.second+1);
        infoNovaE.pos = posNovaE;
        infoNovaE.vis = false;
        L.push_back(infoNovaE);*/
        

    if (c.porta_oberta(paret::OEST)){
        //cout<<"if oest"<<endl;
       /*  info infoNovaO;
        posicio posNovaO(in.pos.first, in.pos.second-1);
        infoNovaO.pos = posNovaO;
        infoNovaO.vis = false; 
        L.push_back(infoNovaO); */
        posicio posNovaO(in.pos.first, in.pos.second-1);
        //cout<<"posNovaO: "<<posNovaO.first<<", "<<posNovaO.second<<endl;
        info infoNovaO  = arrayPos[calculIndex(posNovaO, M.num_columnes())];
        //cout<<"infoNovaO: "<<infoNovaO.pos.first<<", "<<infoNovaO.pos.second<<" - vis: "<<infoNovaO.vis<<endl;

        if(not infoNovaO.vis){
            //cout<<"if del if oest "<<endl;
            L.push_back(infoNovaO);
            }
        
    }
}

    

 nat calculIndex(posicio pos, nat cols) {

     nat index = cols*(pos.first-1)+(pos.second-1);
     return index;

 }





/*
bool cami(const arestes &a, vector<bool> &vis, int ini, int dest){
    
    bool res = false;
    if (ini == dest){
        res = true;
        return res;
    }
    vis[ini] = true;
    for(int i = 0; i < a[ini].size() and not res; i++){
        if(not vis[a[ini][i]]){
            res = cami(a,vis,a[ini][i],dest);                
        }
    }
    return res;
    } 




// DIJKSTRA

// this method returns a minimum distance for the 
// vertex which is not included in Tset.
int minimumDist(int dist[], bool Tset[]) {
	int min=INT_MAX,index;
              
	for(int i=0;i<6;i++) {
		if(Tset[i]==false && dist[i]<=min) {
			min=dist[i];
			index=i;
		}
	}
	return index;
}

void Dijkstra(int graph[6][6],int src) {  // adjacency matrix used is 6x6

	int dist[6]; // integer array to calculate minimum distance for each node.                            
	bool Tset[6];// boolean array to mark visted/unvisted for each node.
	
	// set the nodes with infinity distance
	// except for the initial node and mark
	// them unvisited.  
	for(int i = 0; i<6; i++) {
		dist[i] = INT_MAX;
		Tset[i] = false;	
	}
	
	dist[src] = 0;   // Source vertex distance is set to zero.             
	
	for(int i = 0; i<6; i++) {
		int m=minimumDist(dist,Tset); // vertex not yet included.
		Tset[m]=true;// m with minimum distance included in Tset.
		for(int i = 0; i<6; i++) {
			// Updating the minimum distance for the particular node.
			if(!Tset[i] && graph[m][i] && dist[m]!=INT_MAX && dist[m]+graph[m][i]<dist[i])
				dist[i]=dist[m]+graph[m][i];
		}
	}
	cout<<"Vertex\t\tDistance from source"<<endl;
	for(int i = 0; i<6; i++) { //Printing
		char str=65+i; // Ascii values for pritning A,B,C..
		cout<<str<<"\t\t\t"<<dist[i]<<endl;
	}
}

int main() {
	int graph[6][6]={
		{0, 10, 20, 0, 0, 0},
		{10, 0, 0, 50, 10, 0},
		{20, 0, 0, 20, 33, 0},
		{0, 50, 20, 0, 20, 2},
		{0, 10, 33, 20, 0, 1},
		{0, 0, 0, 2, 1, 0}};
	Dijkstra(graph,0);
	return 0;	                        
} */

  