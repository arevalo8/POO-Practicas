#include "tarjeta.hpp"
#include <iostream>

using namespace std;

std::set<Numero> Tarjeta::tarjetas_;
bool luhn(const Cadena&);

//Clase Numero
Numero::Numero(const Cadena& numero) {
	Cadena n;
	for(auto x:numero) {
		if(!isspace(x)) {
			if(!isdigit(x)) {
				Numero::Incorrecto digito(Razon::DIGITOS);
				throw digito;
			} else {
				n+=Cadena(1,x);
			}
		}
	}
	
	if(n.length()< 13 || n.length() > 19) {
		Numero::Incorrecto longitud(Razon::LONGITUD);
		throw longitud;
	}else if(!luhn(n)) {
		Numero::Incorrecto no_valido(Razon::NO_VALIDO);
		throw no_valido;
	} else {
		numero_ = n;
	}
}

bool operator <(const Numero& n1, const Numero& n2) {
	return static_cast<Cadena>(n1) < static_cast<Cadena>(n2);
}

//Clase Tarjeta
Tarjeta::Tarjeta(const Numero& numero, Usuario& usuario, const Fecha& fecha) : numero_{numero}, titular_{&usuario}, caducidad_{fecha}, activa_{true} {
	Fecha hoy;
	if(caducidad_ < hoy) {
		Tarjeta::Caducada caducada(caducidad_);
		throw caducada;
	} else if(!tarjetas_.insert(numero).second) {
		Tarjeta::Num_duplicado duplicado(numero_);
		throw duplicado; 
	} else {
		titular_->es_titular_de(*this);
	}
}

Tarjeta::Tipo Tarjeta::tipo() const noexcept {
	Cadena primeros(2);
	primeros[0] = numero_[0];
	primeros[1] = numero_[1];
	
	switch(primeros[0]) {
		case '3':
			if(primeros == "34" || primeros == "37") {
				return Tarjeta::AmericanExpress;
			} else {
				return Tarjeta::JCB;
			}
			break;
		case '4':
			return Tarjeta::VISA;
			break;
		case '5':
			return Tarjeta::Mastercard;
			break;	
		case '6':
			return Tarjeta::Maestro;
			break;
		default:
			return Tarjeta::Otro;		
	}
}

void Tarjeta::anula_titular(){
	const_cast<Usuario*&>(titular_) = nullptr;
	activa_ = false;
}

Tarjeta::~Tarjeta() {
	if(titular_) {
		titular_->no_es_titular_de(*this);
	}
	tarjetas_.erase(numero_);
}


//enum Tipo { Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo) {
	switch(tipo) {
		case Tarjeta::Otro:
			os << "Tipo indeterminado";
			break;
		case Tarjeta::AmericanExpress:
			os << "AmericanExpress";
			break;	
		case Tarjeta::VISA:
			os << "VISA";
			break;
		case Tarjeta::JCB:
			os << "JCB";
			break;	
		case Tarjeta::Mastercard:
			os << "Mastercard";
			break;
		case Tarjeta::Maestro:
			os << "Maestro";
			break;
		default:
			os << "Error Tipo Tarjeta";
	}
	
	return os;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& t) {
	os << " " << std::setfill('-') << std::setw(30) << " " << std::endl;
	os << "/                              \\"  << std::endl;
	//tipo
	os << "| " << std::left << std::setfill(' ') << std::setw(28) << t.tipo() << " |" << std::endl;
	//numero
	os << "| " << std::left << std::setfill(' ') << std::setw(28) << t.numero() << " |" << std::endl;
	//titular
	Cadena nom = t.titular()->nombre() + " " + t.titular()->apellidos();
	for (auto& c:nom) {
		if(islower(c)) {
			c = toupper(c);
		}
	}
	
	os << "| " << std::setfill(' ') << std::setw(28) << nom << " |" << std::endl;
	//Fecha de vencimiento
	os << std::right << "| Caduca: " << std::setfill('0') << setw(2) << t.caducidad().mes() << "/" << setw(2) <<
	 t.caducidad().anno() % 100 << setfill(' ') << setw(15) << " |" << std::endl;
	os << "\\                              /"  << std::endl;
	os << " " << std::setfill('-') << std::setw(30) << " " << std::endl;
	
	return os;
}



bool operator <(const Tarjeta& t1, const Tarjeta& t2) { return t1.numero() < t2.numero(); }





