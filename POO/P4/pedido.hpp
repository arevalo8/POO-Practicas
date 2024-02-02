#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iomanip>

#include "usuario.hpp"
#include "articulo.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido
{
public:

    class Vacio
    {
    public:
        Vacio(Usuario const* u) : u_us(u) {}
        Usuario const& usuario() const noexcept { return *u_us; }
    private:
        const Usuario* u_us;
    };

    class Impostor
    {
    public:
        Impostor(Usuario const* u) : u_us(u) {}
        Usuario const& usuario() const noexcept { return *u_us; }
    private:
        const Usuario* u_us;
    };

    class SinStock
    {
    public:
        SinStock(Articulo const* a) : a_art(a) {}
        Articulo const& articulo() const noexcept { return *a_art; }
    private:
        const Articulo* a_art;
    };
    
    class Desactivada {};

    Pedido(Usuario_Pedido& us_ped, Pedido_Articulo& ped_art, Usuario& u,
           Tarjeta const& t, Fecha const& f = Fecha());

    int numero() const noexcept { return num_; }
    Tarjeta const* tarjeta() const noexcept{ return tarjeta_; }
    Fecha fecha() const noexcept { return fecha_; }
    double total() const noexcept { return total_; }

    static int n_total_pedidos() noexcept { return N_pedidos; }

private:
    int num_; //nº ultimo pedido
    Tarjeta const* tarjeta_;
    Fecha fecha_;
    double total_; //importe total
    static int N_pedidos; //nº correlativo

    void vaciarCarrito(Usuario& u);
};

ostream& operator<<(ostream& os, const Pedido& p);

#endif //PEDIDO_HPP
