#ifndef ARTICULOS_HPP
#define ARTICULOS_HPP

#include <iostream>
#include <set>

#include "cadena.hpp"
#include "fecha.hpp"

using namespace std;

class Autor{
public:
    Autor(const Cadena& nombre, const Cadena& apell, const Cadena& dir) noexcept
    : nom_(nombre), apell_(apell), dir_(dir) {}

    const Cadena& nombre() const noexcept { return nom_; }
    const Cadena& apellidos() const noexcept { return apell_; }
    const Cadena& direccion() const noexcept { return dir_; }

private:
    Cadena nom_;
    Cadena apell_;
    Cadena dir_;
};

class Articulo{
public:

    typedef set<Autor*> Autores;

    class Autores_vacios {};

	Articulo(const Autores& a, const Cadena& c, const Cadena& t,
             const Fecha& f, double p);

	const Cadena& referencia() const noexcept { return cod_; }
	const Cadena& titulo() const noexcept { return titulo_; }
	const Fecha& f_publi() const noexcept { return fecha_; }

	double precio() const noexcept { return precio_; }
	double& precio() noexcept { return precio_; }

	void crea_autores(Autor& au) { au_.insert(&au); }
    const Autores& autores() const noexcept { return au_; }

    virtual ~Articulo() {}
    virtual void impresion_especifica(ostream& os) const noexcept = 0;

protected:
    Autores au_;
	Cadena cod_;
	Cadena titulo_;
	Fecha fecha_;
	double precio_;
};

class ArticuloAlmacenable : public Articulo{
public:

    ArticuloAlmacenable(const Autores& a, const Cadena& c,
                        const Cadena& t, const Fecha& f, double p,
                        unsigned stock)
        : Articulo(a, c, t, f, p), stock_(stock) {}

    unsigned stock() const noexcept { return stock_; }
	unsigned& stock() noexcept { return stock_;}

protected:
    unsigned stock_;
};

class Libro : public ArticuloAlmacenable{
public:
    Libro(const Autores& a, const Cadena& c, const Cadena& t,
          const Fecha& f, double p, unsigned nPag, unsigned stock = 0)
        : ArticuloAlmacenable(a, c, t, f, p, stock), n_pag_(nPag) {}

    unsigned n_pag() const noexcept { return n_pag_; }
    void impresion_especifica(ostream& os) const noexcept;

private:
    const unsigned n_pag_;

   
};

class Revista : public ArticuloAlmacenable{
public:
  Revista(const Autores& a, const Cadena& c, const Cadena& t,
	   const Fecha& f, double p, int num, int periodicidad, unsigned stock = 0)
    : ArticuloAlmacenable(a, c, t, f, p, stock), numero_(num), periodicidad_{periodicidad} {}
  
  int numero() const noexcept { return numero_; }
  int periodicidad() const noexcept { return periodicidad_; }
  void impresion_especifica(ostream& os) const noexcept;
  
private:
  const int numero_;
  const int periodicidad_;
  
  
};

class LibroDigital : public Articulo{
public:
    LibroDigital(const Autores& a, const Cadena& c, const Cadena& t,
                 const Fecha& fComp, double p, const Fecha& fExp)
        : Articulo(a, c, t, fComp, p), f_expir_(fExp) {}

    const Fecha& f_expir() const noexcept { return f_expir_; }
    void impresion_especifica(ostream& os) const noexcept;

private:
    const Fecha f_expir_;

    
};

ostream& operator<<(ostream& os, const Articulo& a) noexcept;

inline void Libro::impresion_especifica(ostream& os) const noexcept
{
    os << n_pag_ << " págs., " << stock_ << " unidades.";
}

inline void Revista::impresion_especifica(ostream& os) const noexcept
{
    os << "Número: "  << numero_ << ", Periodicidad: " << periodicidad_ << " días." << endl;
    os << "\tPróximo número a partir de: " <<  fecha_ + periodicidad_ << ".";
}

inline void LibroDigital::impresion_especifica(ostream& os) const
    noexcept
{
    os << "A la venta hasta el " << f_expir_ << '.';
}


#endif
