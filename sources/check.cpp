#include "laberint.hpp"
#include <esin/util>

using util::nat;
using namespace std;

namespace check {
  
  bool comprova_cami_minim(const posicio& ini, 
			     const posicio& final,
			     const laberint& L,
			     const list<posicio>& cami_candidat) 
    throw(error) {
      posicio posI = ini;
      posicio posF = final;
      laberint l = L;
      list<posicio> cami1 = cami_candidat;
      posI = posF;
    
    return true;
  }
  
  bool comprova_perfecte(const laberint& L) {
    laberint l = L;
    return true;
  }
};
