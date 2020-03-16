#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <limits>

#pragma pack(1)

//100*2+13+8+4
#define MAX_BUFFER 225
#define MAX_FIELD 255


using namespace std;

class Empleado{
	private:
		void Pack();
		void UnPack();
		void GetSizeStr(int, char *);
		int Copy2Buffer(char *);
		int CopyFromBuffer(char *, char *);
    public:
	
		uint16_t SIZE;		
		char *BUFFER_REG;
        char Nombres[101];
        char Apellidos[101];
        char Cedula[14];
        double Sueldo;
		unsigned int Edad;
        Empleado();
		~Empleado();
        void Print();
		void SetBuffer(const char *, int);
		void Write();
		void GetEmpleadoByName(string);
		void crearIndice();
		void leerIndice();
		
};
