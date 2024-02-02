#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include "cadena.hpp"
#include "usuario.hpp"
#include "fecha.hpp"

#include <string>
#include <set>
#include <cctype>
#include <iostream>
#include <iomanip>

class Usuario;


//clase Numero
class Numero {
	public:
		//constructor
		Numero(const Cadena& numero); 
		
		//operador de conversion
		operator const char* () const;
		
		//Clase Excepcion Incorrecto
		enum Razon { LONGITUD, DIGITOS, NO_VALIDO };
		class Incorrecto {
			public: 
				Incorrecto(Razon razon);
				Razon razon() const;
			private:
				Razon razon_;
		};	
		
		
	private:
		Cadena numero_;
};


//clase excepcion
inline Numero::Incorrecto::Incorrecto(Razon razon) : razon_{razon} {}
inline Numero::Razon Numero::Incorrecto::razon() const { return razon_; }

inline Numero::operator const char*() const {
	return numero_.c_str();	
}

//operador de comparacion <
bool operator <(const Numero& n1, const Numero& n2);

//clase Tarjeta
class Tarjeta {
	public:
		enum Tipo { Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
		
		
		Tarjeta(const Numero& numero, Usuario& usuario, const Fecha& fecha);
		
		//eliminamos la copia y la asignacion
		Tarjeta(const Tarjeta& t) = delete;
		Tarjeta& operator =(const Tarjeta&) = delete;
		
		//metodos observadores
		const Numero& numero() const noexcept;
		Usuario* titular() const noexcept;
		const Fecha& caducidad() const noexcept;
		bool activa() const noexcept;
		Tipo tipo() const noexcept;
		
		//activar y desactivar tarjeta
		bool activa(bool a) noexcept;
		
		
		
		
		//Destructor
		~Tarjeta();
		
		
		//Clase excepcion Caducada
		class Caducada {
			public:
				Caducada(const Fecha& cuando);
				const Fecha& cuando() const;
			private:
				Fecha cuando_;	
		};
		
		//Clase Excepcion Num_duplicado
		class Num_duplicado {
			public:	
				Num_duplicado(const Numero& numero);
				const Numero& que() const;
			private:
				Numero num_;
		};
		
		class Desactivada{};
		
		
		
	private:
		const Numero numero_;
		const Fecha caducidad_;
		bool activa_;
		Usuario* const titular_;
		//anular titular
		friend class Usuario;
		void anula_titular();
		
		
		
		static std::set<Numero> tarjetas_;
};

inline const Numero& Tarjeta::numero() const noexcept { return numero_; }
inline Usuario* Tarjeta::titular() const noexcept { return titular_; }
inline const Fecha& Tarjeta::caducidad() const noexcept { return caducidad_; }
inline bool Tarjeta::activa() const noexcept { return activa_; }




//clase excepcion tarjeta caducada
inline Tarjeta::Caducada::Caducada(const Fecha& cuando) : cuando_{cuando} {}
inline const Fecha& Tarjeta::Caducada::cuando() const { return cuando_; }

//Clase excepcion numero duplicado
inline Tarjeta::Num_duplicado::Num_duplicado(const Numero& numero) : num_{numero} {}
inline const Numero& Tarjeta::Num_duplicado::que() const { return num_; }

//activar y desactivar tarjeta
inline bool Tarjeta::activa(bool a) noexcept {
	activa_ = a;
	return a;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& t);
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo);

bool operator <(const Tarjeta& t1, const Tarjeta& t2);


#endif
