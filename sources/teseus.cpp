#include "teseus.hpp"
using namespace std;

//IMPLEMENTACIÓ DE LA CLASSE TESEUS. 

//typedef vector<vector<int> > arestes; //Llista d'adjacencia de integers
nat calculIndex(posicio pos, nat cols);
//Pre:
//Post:

nat distMinima(nat dist[], bool adj[], std::list<posicio> & L, nat quants);
//Pre:
//Post:

void hi_ha_cami(const posicio &inici, const posicio & final, bool mAdj[], bool &cami);
//Pre:
//Post: 
void successors(std::list<posicio> &L, posicio pos, const laberint & M);
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
    
    if (not cinici.porta_oberta(paret::NORD) and not cinici.porta_oberta(paret::SUD) and
          not cinici.porta_oberta(paret::EST) and not cinici.porta_oberta(paret::OEST) )
              throw error (SenseSolucio);
    
    if (not cfi.porta_oberta(paret::NORD) and not cfi.porta_oberta(paret::SUD) and
          not cfi.porta_oberta(paret::EST) and not cfi.porta_oberta(paret::OEST) )
              throw error (SenseSolucio);
    

    //Creem la matriu d'adjacència.     
    nat files = M.num_files();
    nat cols = M.num_columnes();
    nat totalVert = files*cols;
    bool mAdj[totalVert];
    nat dist[cols];
    posicio arrayPos[totalVert];
    nat inf = 999999;

    //std::iterator it = L.begin();
    // Potser nomes hauriem d'aprofitar la part superior de la matriu. j = i
    nat k = 0;
    for(nat i = 1; i <= M.num_files(); i++){
        for(nat j = 1; j <= M.num_columnes(); j++, k++){
            posicio pos(i,j);
            mAdj[k] = false;
            dist[k] = inf;
            arrayPos[k] = pos;
        }
    }
    //Formula per accedir a la posicio de l'array a on es troba la nostra coordenda:
    // numCols*(pos.first-1)+1+(pos.second-1)

    // Posem a 0 la distancia del punt inicial cap a ell mateix
    dist[calculIndex(inici,cols)] = 0;


    //posicio::iterator itCam = L.begin();

    //list<posicio>::iterator it = L.begin();

    bool cami = false; 
    posicio aux = inici;
    nat indexMin;
    //bool nomPerDeterminar = false;

    // Obtenim el vertex més proper
    L.push_back(inici);
    // Farem un recorregut per tots els nodes excepte per l'inicial.
    for(nat contVert = 0; contVert < totalVert and not cami; contVert++){

        if(aux == final){
            cami = true;
        }

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

            cout<<"posMinim: "<<posMin.first<<" ,"<<posMin.second<<endl;

            for(std::list<posicio>::iterator i = lSucc.begin(); i != lSucc.end(); ++i) {
                posicio p = *i;
                cout<<"lSucc: "<<p.first<<", "<<p.second<<endl; 

            }
            
            //Actualitzem les distàncies a les cambres adjacents
            //for (nat i2 = 1; i2 <= totalVert; i2++){
                for (std::list<posicio>::iterator it = lSucc.begin(); it != lSucc.end(); ++it) { 
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
    if(L.empty()) throw error(SenseSolucio);
}



    
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


void successors(std::list<posicio> &L, posicio pos, const laberint & M) {

    cambra c = M(pos);
    if (c.porta_oberta(paret::NORD)){
        posicio posNovaN(pos.first-1, pos.second);
        L.push_back(posNovaN);
        }
    if (c.porta_oberta(paret::SUD)){
        posicio posNovaS(pos.first+1, pos.second);
        L.push_back(posNovaS);
        }
    if (c.porta_oberta(paret::EST)){
        posicio posNovaE(pos.first, pos.second-1);
        L.push_back(posNovaE); 
    }
    if (c.porta_oberta(paret::OEST)){
        posicio posNovaO(pos.first, pos.second+1);
        L.push_back(posNovaO);
    } 
}

    

 nat calculIndex(posicio pos, nat cols) {

     nat index = cols*(pos.first-1)+1+(pos.second-1);
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

  