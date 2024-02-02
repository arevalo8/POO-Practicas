#include "pedido.hpp"

#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include <locale>

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& us_ped, Pedido_Articulo& ped_art,
               Usuario& u, Tarjeta const& t, Fecha const& f)
    : num_(N_pedidos+1), tarjeta_(&t), fecha_(f), total_(0)

{
    if(u.n_articulos() == 0)
        throw Vacio(&u);

    if(t.titular() != &u)
        throw Impostor(&u);
        
    if(!t.activa()) 
    	throw Tarjeta::Desactivada{};

    if(f > t.caducidad())
        throw Tarjeta::Caducada(t.caducidad());

    set<Articulo*> expirados;

    for (const auto& it : u.compra())
    {
        Articulo* art = it.first;

        if (auto* libroDig = dynamic_cast<LibroDigital*>(art)) {
            if (libroDig->f_expir() < Fecha())
                expirados.insert(art);

        } else if (auto* artAlm = dynamic_cast<ArticuloAlmacenable*>(art))
            if(artAlm->stock() < it.second)
            {
                vaciarCarrito(u);
                throw SinStock(art);
            }
    }

    for (auto art : expirados)
        u.compra(*art, 0);

    if (u.compra().size() == 0)
        throw Vacio(&u);


    for (auto& par : u.compra())
    {
        Articulo& art = *par.first;
        unsigned cant = par.second;

        ped_art.pedir(*this, art, art.precio(), cant);
        ped_art.pedir(art, *this, art.precio(), cant);

        total_ += art.precio() * cant;

        if(auto* Artalm = dynamic_cast<ArticuloAlmacenable*>(&art))
            Artalm->stock() -= cant;
    }

    us_ped.asocia(u, *this);
    us_ped.asocia(*this, u);

    vaciarCarrito(u);
    ++N_pedidos;
}

ostream& operator<<(ostream& os, const Pedido& p)
{
	os << left;
	os << "NÃºm. pedido: " << p.numero() << endl;
	os << setw(13) << "Fecha: " << p.fecha() << endl;
	os << setw(13) << "Pagado con: " << p.tarjeta()->tipo() << " n.º: " << p.tarjeta()->numero() << endl;
	os << setw(13) << "Importe: " << fixed << setprecision(2) << p.total() << " \u20AC" << endl;
		
	return os;
}


void Pedido::vaciarCarrito(Usuario& u)
{
    auto compra = u.compra();

    for (auto& par : compra)
        u.compra(*par.first, 0);
}
