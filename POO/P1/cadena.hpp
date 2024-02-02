#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <cstring>

class Cadena{
	public:
		explicit Cadena(size_t tam = 0, char c = ' ');  //constructor
		Cadena(const Cadena& c);    //constructor de copia 
		Cadena(const char* c);		//constructor de conversion
		Cadena(Cadena&& c);			//constructor de movimiento
		
		//operadores
		Cadena& operator =(const Cadena& c);  //operador de asignacion
		Cadena& operator =(Cadena&& c);
		Cadena& operator +=(const Cadena& c);
		char& operator [](size_t i);
		const char& operator [](size_t i) const;
		char& at(size_t i);
		const char& at(size_t i) const;
		Cadena substr(size_t i, size_t tam) const;
		
		const char* c_str() const;  //operador de conversion a const char*
                explicit operator const char*() const;
		
		size_t length() const;
		
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		
		
		iterator begin(); 
		const_iterator begin() const; 
		iterator end(); 
		const_iterator end() const; 
		reverse_iterator rbegin(); 
		const_reverse_iterator rbegin() const;
		const_iterator cbegin() const; 
		const_reverse_iterator crbegin() const; 
		reverse_iterator rend(); 
		const_reverse_iterator rend() const; 
		const_iterator cend() const; 
		const_reverse_iterator crend() const;
		
		
		~Cadena();
		
		void mostrar();
		
		
	private:
		char* s_;
		size_t tam_;	
};


std::ostream& operator << (std::ostream& os, const Cadena& c); 
std::istream& operator >> (std::istream& is, Cadena& c);

Cadena operator +(const Cadena& c1, const Cadena& c2);

bool operator ==(const Cadena& c1, const Cadena& c2);
bool operator !=(const Cadena& c1, const Cadena& c2);
bool operator <(const Cadena& c1, const Cadena& c2);
bool operator >(const Cadena& c1, const Cadena& c2);
bool operator <=(const Cadena& c1, const Cadena& c2);
bool operator >=(const Cadena& c1, const Cadena& c2);




inline Cadena::operator const char*() const { return s_; }

inline size_t Cadena::length() const { return tam_; }

inline char& Cadena::operator [](size_t i) { return s_[i]; } 
inline const char& Cadena::operator [](size_t i) const { return s_[i]; } 

inline const char* Cadena::c_str() const { return s_; }

inline Cadena::iterator Cadena::begin() { return s_; }
inline Cadena::const_iterator Cadena::begin() const { return const_iterator(s_); }
inline Cadena::iterator Cadena::end() { return s_+tam_; }
inline Cadena::const_iterator Cadena::end() const { return const_iterator(s_+tam_); }
inline Cadena::reverse_iterator Cadena::rbegin() { return reverse_iterator(end()); }
inline Cadena::const_reverse_iterator Cadena::rbegin() const { return const_reverse_iterator(end()); }
inline Cadena::const_iterator Cadena::cbegin() const { return const_iterator(s_); }
inline Cadena::const_reverse_iterator Cadena::crbegin() const { return const_reverse_iterator(end()); }
inline Cadena::reverse_iterator Cadena::rend() { return reverse_iterator(begin()); }
inline Cadena::const_reverse_iterator Cadena::rend() const { return const_reverse_iterator(begin()); }
inline Cadena::const_iterator Cadena::cend() const { return const_iterator(s_+tam_); }
inline Cadena::const_reverse_iterator Cadena::crend() const { return const_reverse_iterator(begin()); }

// Para P2 y ss .
//  Especializaci ón de la   plantilla td :: hash<Key> para definir la función hash a usar
// en contenedores desordenados de Cadena, unordered_[set|map|multiset|multimap].
namespace std{  // Estaremos dentro del espacio de nombres  std.
  template <>    // Es una  especializaci ón de una  plantilla  para Cadena    .
    struct hash<Cadena>
    {// Es una clase  con solo  un operador público.
      size_t operator() (const Cadena& cad) const// El  operador función.
	{
	  hash<string> hs;// Creamos un objeto hash de string.
	  auto p{(const char*)(cad)};// Convertimos Cadena a cadena de bajo nivel.
	  string  s{p};// Creamos un string desde la cadena de b.          nivel .
	  size_t  res{hs(s)};// El  hash del  string .  Como hs.operator()(s);
	  return  res;//evolvemos el hash del string .// En forma abreviada:// return  hash<string>{}((const char*)(cad));
	}
    };
}

#endif
