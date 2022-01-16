
#ifndef _PARET_HPP
#define _PARET_HPP

#include <string>

class paret {
public:
  enum {NORD, EST, SUD, OEST, NO_DIR};
  // Cost en temps: Θ(1) 
  paret(int p = NO_DIR) throw() : _p(p) {}

  //Cost en temps: Θ(1)
  paret(const std::string& s) throw() {
    _p = NO_DIR;
    if (s == "nord" || s == "NORD" || s == "N") _p = NORD;
    if (s == "est" || s == "EST" || s == "E") _p = EST;
    if (s == "sud" || s == "SUD" || s == "S") _p = SUD;
    if (s == "oest" || s == "OEST" || s == "O") _p = OEST;
  }

  //Cost en temps: Θ(1)
  paret& operator++() throw() {
    _p = (_p == NO_DIR) ? NO_DIR : _p + 1;
    return *this;
  }

  //Cost en temps: Θ(1)
  operator int() const throw() {
    return _p;
  }

private:
  int _p;  
};
#endif
