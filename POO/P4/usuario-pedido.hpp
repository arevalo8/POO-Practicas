#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <iostream>
#include <iterator>

#include "pedido.hpp"

class Usuario_Pedido
{
public:
    typedef set<Pedido*> Pedidos;

    void asocia(Usuario& u, Pedido& p); 
    void asocia(Pedido& p, Usuario& u); 

    const Pedidos& pedidos(Usuario& u);
    const Usuario* cliente(Pedido& p);

private:
    map<Usuario*, Pedidos> m_usuario_pedido;
    map<Pedido*, Usuario*> m_pedido_usuario;
};

#endif //USUARIO_PEDIDO_HPP
