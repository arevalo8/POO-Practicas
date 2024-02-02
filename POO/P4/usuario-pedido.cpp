#include "usuario-pedido.hpp"
#include <iterator>


using namespace std;

void Usuario_Pedido::asocia(Usuario& u, Pedido& p) {
	m_usuario_pedido[&u].insert((Pedido*)&p); 
	m_pedido_usuario[&p] = (Usuario*)&u;
}

void Usuario_Pedido::asocia(Pedido& p, Usuario& u) { 
	asocia(u, p);
}

const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& u) { 
	auto it = m_usuario_pedido.find((Usuario*)&u);
	if(it != m_usuario_pedido.end()) {
		return it->second;
	} else {
		return Usuario_Pedido::Pedidos{};	
	}	
	
}

const Usuario* Usuario_Pedido::cliente(Pedido& p) { 
	auto it = m_pedido_usuario.find((Pedido*)&p);
	
	if(it != m_pedido_usuario.end()) {
		return it->second;
	} else {
		return nullptr;
	}		
}
