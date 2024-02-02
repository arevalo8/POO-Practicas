#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <unistd.h>
#include <ctime>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <map>
#include <set>

#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"


class Numero;
class Tarjeta;


using namespace std;

class Clave
{
public:
    enum Razon{CORTA, ERROR_CRYPT};

    Clave(const char* cl);

    const Cadena& clave() const noexcept { return pass_; }

    bool verifica(const char* cl) const noexcept
    { return strcmp(crypt(cl, pass_.c_str()), pass_.c_str()) == 0; }

    class Incorrecta
    {
    public:
        Incorrecta(Razon r) : r_(r) {}
        Razon razon() const { return r_; }
    private:
        Razon r_;
    };

private:
    Cadena pass_;
};

class Usuario
{
public:
    typedef map<Numero, Tarjeta*> Tarjetas;
    //localizo tarjeta a traves de la clave numero

    typedef unordered_map<Articulo*, unsigned int> Articulos;
    //unsigned añade info extra

    typedef std::unordered_set<Cadena> Usuarios;

    Usuario(const Cadena& id,const Cadena& nom,const Cadena& apel,
            const Cadena& dir,const Clave& p);

    Usuario(const Usuario&) = delete;
    Usuario& operator=(const Usuario&) = delete;

    ~Usuario();

    const Cadena& id() const noexcept { return u_id; }
    const Cadena& nombre() const noexcept { return u_nom; }
    const Cadena& apellidos() const noexcept { return u_apell; }
    const Cadena& direccion() const noexcept { return u_dir; }
    const Tarjetas& tarjetas() const noexcept { return m_tarjetas; }

    void es_titular_de(const Tarjeta& t);
    void no_es_titular_de(Tarjeta& t);

    void compra(const Articulo& a, unsigned cantidad = 1);

    const Articulos& compra() const { return n_art; }

    size_t n_articulos() const { return n_art.size(); }

    friend ostream& operator<<(ostream& os, const Usuario& u);
    
    
	void vaciar_carro();
	

    class Id_duplicado
    {
    public:
        Id_duplicado(const Cadena& idd) : u_idd(idd) {}
        const Cadena& idd() const { return u_idd; }
    private:
        Cadena u_idd;
    };

private:
    Cadena u_id, u_nom, u_apell, u_dir;

    Clave pass;

    Tarjetas m_tarjetas;
    Articulos n_art;
    

    static Usuarios st_id;
};

void mostrar_carro(ostream& os, const Usuario& u);

#endif
