#include <iostream>
class Laboratorio
{
	int num;
};
class Practica
{
	int a;
	Laboratorio lab;
	
	public:
	operator Laboratorio ()  { return lab; }
	operator int () { return a; }
};
void funcion ( int a) { 
	std::cout << "funcion (int) executada"; 
}
void funcion ( Laboratorio la ) { 
	std::cout << "funcion (Laboratorio) executada"; 
}

void funcion(Practica p){
	std::cout << "funcion (Practica) executada";
}

int main()
{
	Practica p;
	funcion(p);
	return 0;
}
