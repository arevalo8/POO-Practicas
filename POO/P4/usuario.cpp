#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <random>

#include "usuario.hpp"

using namespace std;

Clave::Clave(const char* c)
{
    if (strlen(c) < 5)
		throw Incorrecta(Razon::CORTA);

	random_device r;
	uniform_int_distribution<size_t> dist(0, 63);

	char const MD5chars[] =
        "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	char salt[2] = { MD5chars[dist(r)], MD5chars[dist(r)] };

	char* encriptado = crypt(c, salt);

	if(encriptado == nullptr)
        throw Incorrecta(Razon::ERROR_CRYPT);

	pass_ = encriptado;
}

Usuario::Usuarios Usuario::st_id;

Usuario::Usuario(const Cadena& id,const Cadena& nom,const Cadena& apel,
                 const Cadena& dir,const Clave& p)
    : u_id(id), u_nom(nom), u_apell(apel), u_dir(dir), pass(p)
{
   if (!st_id.insert(id).second)
       throw Id_duplicado(u_id);
}

void Usuario::es_titular_de(const Tarjeta& t)
{
   if(t.titular() == this)
       m_tarjetas[t.numero()] = const_cast<Tarjeta*>(&t);
}

void Usuario::no_es_titular_de(Tarjeta& t) { 
	m_tarjetas.erase(t.numero());
	t.anula_titular();
	t.activa(true);

 }



void Usuario::compra(const Articulo& a, unsigned cantidad)
{
	auto cesta = n_art.find(const_cast<Articulo*>(&a));
	if(cesta != n_art.end()) {		//Si ya se encuentra en la cesta
	    if (cantidad == 0){
	        n_art.erase(const_cast<Articulo*>(&a));		//Si la cantidad es 0 lo eliminamos
	    } else {
	        cesta->second = cantidad;	//Si ya esta lo sumamos
		}
	} else {
		
		if(cantidad > 0) {
			n_art[const_cast<Articulo*>(&a)] = cantidad;		//Articulo nuevo
		}
					
	}
}

Usuario::~Usuario()
{
    for (auto& i : m_tarjetas)
        i.second->anula_titular();

    st_id.erase(u_id);
}

ostream& operator<<(ostream& os, const Usuario& u)
{
    os << u.u_id << "[" << u.pass.clave() << "]" << u.u_nom
       << u.u_apell << endl << u.u_dir << endl << "Tarjetas:" << endl;

    for (auto& t : u.m_tarjetas)
        os << *t.second << endl;

    return os;
}

void mostrar_carro(ostream& os, const Usuario& u)
{
    os << "Carrito de compra de " << u.id() << " [Artículos: "
       << u.n_articulos() << "]" << endl;

    if (u.n_articulos() == 0)
        return;

    os << " Cant. Artículo" << endl
       << setw(65) << setfill('=') << '\n'  << setfill(' ');

    for (auto const& i : u.compra())
    {
        const Articulo& a = *i.first;
        os << setw(4) << i.second << "   "
           << "[" << a.referencia() << "] \""
           << a.titulo() << "\", " << a.f_publi().anno()
           << ". " << fixed << setprecision(2) << a.precio()
           << " €" << endl;
    }

    os << endl;
}


void Usuario::vaciar_carro() {	
		n_art.clear();
}
	
