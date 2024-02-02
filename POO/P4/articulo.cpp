#include "articulo.hpp"
#include <iomanip>
#include <iostream>

Articulo::Articulo(const Autores& a, const Cadena& c, const Cadena& t,
                   const Fecha& f, double p) : au_(a), cod_(c),
                                               titulo_(t), fecha_(f),
                                               precio_(p)

{
    if(au_.empty())
        throw Autores_vacios();
}

ostream& operator<<(ostream& os, const Articulo& a) noexcept
{
	os << "[" << setw(3) << setfill('0') << a.referencia() << "] \"" << a.titulo()
       << "\", de ";

    auto autor = a.autores().begin();

    os << (*autor)->apellidos();

    for(++autor; autor != a.autores().end(); ++autor)
        os << ", " << (*autor)->apellidos();

    os << ". ";

    int anio = a.f_publi().anno();

    os << anio << ". " << fixed << setprecision(2)
       << a.precio() << " €\n\t";

	a.impresion_especifica(os);

    return os;
}


