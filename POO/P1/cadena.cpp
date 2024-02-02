#include "cadena.hpp"
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <stdexcept>


using namespace std;

Cadena::Cadena(size_t tam, char c) :  s_{new char[tam+1]}, tam_{tam} {
	for(size_t i = 0; i< tam_; i++){
		s_[i] = c;
	}
	s_[tam_] = '\0';
}


Cadena::Cadena(const Cadena& c) : tam_{c.tam_} {
	s_ = new char[c.tam_ + 1];
	strcpy(s_, c.s_);
}

Cadena::Cadena(const char* c) : s_{new char[strlen(c)+1]}, tam_{strlen(c)}{
	strcpy(s_, c);
}

Cadena::Cadena(Cadena&& c) : s_{c.s_}, tam_{c.tam_} {
	c.tam_ = 0;
	c.s_=new char[1];
	c.s_[0]  = '\0';
}

Cadena& Cadena::operator =(const Cadena& c) {
	if(this!=&c){
		delete[] s_;
		tam_ = c.tam_;
		s_ = new char[c.tam_+1];
		strcpy(s_, c.s_);
	}
	
	return *this;
}

Cadena& Cadena::operator =(Cadena&& c){
	if(this != &c){
		tam_ = c.tam_;
		delete[] s_;
		s_ = c.s_;
		c.s_ = new char[1];
		c.s_[0] = '\0';
		c.tam_ = 0;
	}
	return *this;
}


Cadena& Cadena::operator +=(const Cadena& c){
	char *aux = new char[tam_ + 1];
	strcpy(aux, s_);
	
	tam_ += c.tam_;
	
	delete[] s_;
	s_ = new char[tam_ + 1];
	strcpy(s_ , aux);
	
	strcat(s_, c.s_);
	
	delete[] aux;
	
	return *this;
}

Cadena operator +(const Cadena& c1, const Cadena& c2){
	Cadena aux(c1);
	return aux+=c2;
}

bool operator ==(const Cadena& c1, const Cadena& c2){
	return !strcmp(c1.c_str(), c2.c_str());
}

bool operator !=(const Cadena& c1, const Cadena& c2){
	return strcmp(c1.c_str(), c2.c_str());
}

bool operator <(const Cadena& c1, const Cadena& c2){
	return (strcmp(c1.c_str(), c2.c_str()) < 0);
}

bool operator >(const Cadena& c1, const Cadena& c2){
	return (c2 < c1);
}

bool operator <=(const Cadena& c1, const Cadena& c2){
	return !(c1 > c2);
}

bool operator >=(const Cadena& c1, const Cadena& c2){
	return !(c1 < c2);
}


char& Cadena::at(size_t i){
	if(i >= tam_){
		throw std::out_of_range("Error. Fuera de rango");
	}else{
		return s_[i];
	}
}

const char& Cadena::at(size_t i) const {
	if(i >= tam_){
		throw std::out_of_range("Error. Fuera de rango");
	}else{
		return s_[i];
	}
}

Cadena Cadena::substr(size_t i, size_t tam) const{
	if(i+tam > tam_ || tam > tam_ || i > tam_ ){
		throw std::out_of_range("Error. Fuera de rango");
	}else{
		Cadena aux(tam);
		strncpy(aux.s_, s_ + i, tam);
		aux.s_[tam] = '\0';
		
		return aux;
	}
}

std::ostream& operator << (std::ostream& os, const Cadena& c){
	os << c.c_str();
	return os;
}

std::istream& operator >> (std::istream& is, Cadena& c){
  /*
  size_t i = 0;
  char* s = new char[32];
  char a;

  while(isspace(is.get() != 0 && i < 32)){
      i++;
    }
    is.unget();

    i=0;
    while(!isspace(is.peek() && i < 32 && is.good())){
	a = is.get();
	s[i] = a;
	i++;
      }

      c = Cadena(s);

      delete[] s;
  */

  char linea[33] = "";
  is.width(33);
  is >> linea;
  c = linea;
      return is;
}


Cadena::~Cadena(){
	delete[] s_;
	tam_=0;
}






