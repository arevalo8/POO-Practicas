#include <iomanip>
#include <ostream>
#include "pedido-articulo.hpp"

/********************** LINEAPEDIDO **********************/

LineaPedido::LineaPedido(double price, unsigned int n): cantidad_(n), precio_venta_(price){}

std::ostream& operator <<(std::ostream& output, const LineaPedido& lp)
{
    output << std::fixed << std::setprecision(2) << lp.precio_venta() << ' ' << "€" << '\t' << lp.cantidad() ;

    return output ;
}

/******************* PEDIDO_ARTICULO ********************/

void Pedido_Articulo::pedir(Pedido& p, Articulo& a,double price, unsigned n)
{
    Art_Ped_[&a].insert(std::make_pair(&p,LineaPedido(price,n))) ;
    Ped_Art_[&p].insert(std::make_pair(&a,LineaPedido(price,n))) ;
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p,double price, unsigned n)
{
    pedir(p,a,price,n) ;
}




Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(const Pedido& p) const{
 	//Busqueda en el diccionario
	 auto i = Ped_Art_.find((Pedido*)&p);
	 if(i != Ped_Art_.end())//Existe en el diccionario
		 //Devuelve ItemsPedido asociado
		 return i->second;
	 else
		 //Devuelve temsPedido vacio
		 return ItemsPedido{}; 
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os) const noexcept{
 //Para calcular el total ventas
	 double precio = 0.;
	 for(auto& i:Ped_Art_){
		 os << "Pedido núm. " << i.first->numero() << std::endl;
		 os << "Cliente: " << i.first->tarjeta()->titular()->nombre() << "\tFecha: " << i.first->fecha() << std::endl;
		 //Imprimimos ItemsPedido
		 os << detalle(*i.first);
		 precio = precio + i.first->total();
		 os << std::endl;
	 }
	 os << std::endl << "TOTAL VENTAS\t" << precio << " �" << std::endl; 
}






/*Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a)
{
    return Art_Ped_[&a] ;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& output)
{
    for(auto it = Art_Ped_.begin(); it != Art_Ped_.end(); it++)
    {
        output << "Ventas" << "[" << (it->first)->referencia() << "]" ;
        output << "\"" << it->first->titulo() << "\"" ;
        output << it->second << std::endl ;
    }

    return output ;
}*/


Pedido_Articulo::Pedidos Pedido_Articulo::ventas(const Articulo& art) const{
	//Busqueda en el diccionario
	auto i = Art_Ped_.find((Articulo*)&art);
	if(i != Art_Ped_.end())//Existe en el diccionario
		//Devuelve los pedidos asociados
		return i->second;
	else
		//Devuelve Pedidos vacio
		return Pedidos{};
}


void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os) const noexcept{
 for(auto& i:Art_Ped_){
 	os << "Ventas de " << "[" << i.first->referencia() << "] " << i.first->titulo() << std::endl;
	//Imprimimos Pedidos
	os << ventas(*i.first);
	
	os << endl;
	}
}




std::ostream& operator <<(std::ostream& output,const Pedido_Articulo::ItemsPedido& ip)
{

    double price = 0;


    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << "PVP \t Cant.\t Articulo\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

    for(auto it = ip.begin(); it != ip.end() ; it++)
    {

        output << (it->second).precio_venta() << "€\t" ;
        output << (it->second).cantidad() << "\t" ;
        output << "[ "<< (it->first)->referencia() << "]\t";
        output << "\"" << (it->first)->titulo() << "\"" << std::endl;

        price = price + (it->second).cantidad() * (it->second).precio_venta() ;
    }

    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << std::fixed ;
    output << std::setprecision(2) << price << " €" << std::endl ;

    return output ;
}

std::ostream& operator <<(std::ostream& output, const Pedido_Articulo::Pedidos& pa)
{

    double price = 0;
    unsigned t = 0  ;

    output << "\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << "PVP \t Cant.\t Fecha venta\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

    for(auto it = pa.begin(); it != pa.end() ; it++)
    {

        output << " " << (it->second).precio_venta() << " €\t" ;
        output << (it->second).cantidad() << "\t" ;
        output << (it->first)->fecha() << std::endl ;

        price = price + (it->second).cantidad() * (it->second).precio_venta() ;
        t += (it->second).cantidad() ;
    }


    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << std::fixed ;
    output << std::setprecision(2) << price << " €\t" << t << std::endl ;

    return output ;

}

