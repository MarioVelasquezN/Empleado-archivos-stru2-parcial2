#include "Empleado.h"

using namespace std;

void Empleado::Print(){
    cout 	<< Nombres << "  "
    		<< Apellidos << " "
    		<< Cedula << "  "
    		<< Sueldo << "  "
    		<< Edad << "\n"
    		<< flush;
}

Empleado::Empleado(){
	BUFFER_REG = new char[MAX_BUFFER];
    Nombres[0]=0;
    Apellidos[0]=0;
    Cedula[0]=0;
	Sueldo=0;
	Edad=0;
	BUFFER_REG[0] = 0;
	SIZE = 0;
}


void Empleado::SetBuffer(const char * buffer, int s){
	SIZE = s;
	memcpy(BUFFER_REG, buffer, SIZE);
	UnPack();
}

int Empleado::CopyFromBuffer(char *source, char *target){
	unsigned char s = 0;
	memcpy(&s, source, 1);
	memcpy(target,++source, s);
	target[s] = 0;
	return s;
}


void Empleado::UnPack(){
	unsigned char l_size = 0;
	
	char *c = BUFFER_REG; 
	l_size = CopyFromBuffer(c, Nombres); 
	c+=(l_size+1);

	l_size = CopyFromBuffer(c, Apellidos);
	c+=(l_size+1);

	memcpy(&Cedula,c, sizeof(Cedula)-1);	
	c+= (sizeof(Cedula)-1);
	Cedula[sizeof(Cedula)-1] = 0;

	memcpy(&Sueldo,c, sizeof(Sueldo));
	c+=sizeof(Sueldo);

	memcpy(&Edad,c, sizeof(Edad));
	c+=sizeof(Edad);
}

int Empleado::Copy2Buffer(char *v){
	unsigned char l_size = 0;
	l_size = strlen(v);	
	
	memcpy(&BUFFER_REG[SIZE], &l_size, 1);
	memcpy(&BUFFER_REG[++SIZE], v, l_size);
	SIZE+=l_size;
	return l_size;
}


void Empleado::Pack(){
	unsigned char l_size = 0;
	SIZE = 2;
	Copy2Buffer(Nombres);
	Copy2Buffer(Apellidos);

	memcpy(&BUFFER_REG[SIZE], &Cedula, sizeof(Cedula)-1);
	SIZE+=(sizeof(Cedula)-1);
	
	memcpy(&BUFFER_REG[SIZE], &Sueldo, sizeof(Sueldo));
	SIZE+=sizeof(Sueldo);

	memcpy(&BUFFER_REG[SIZE], &Edad, sizeof(Edad));
	SIZE+=sizeof(Edad);

	SIZE-=2;
	memcpy(&BUFFER_REG[0], &SIZE, sizeof(SIZE));
	SIZE+=2;
}

void Empleado::Write(){
	cout << "Nombres: "<<flush; cin.getline(Nombres, sizeof(Nombres)-1);
	cout << "Apellidos: "<<flush; cin.getline(Apellidos, sizeof(Nombres)-1);
	cout << "Cedula: "<<flush; cin.getline(Cedula, sizeof(Cedula)-1);
	cout << "Sueldo: "<<flush; cin >> Sueldo;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	cout << "Edad: "<<flush; cin >> Edad;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	Pack();
}


Empleado::~Empleado(){
    delete [] BUFFER_REG;
	
}
