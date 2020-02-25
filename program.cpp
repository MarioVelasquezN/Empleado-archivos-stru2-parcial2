#include <limits>
#include <fstream>
#include <inttypes.h>

#include "Empleado.h"

using namespace std;

void ReadAll(){
	char buffer[MAX_BUFFER];
	char s[2];
	uint16_t r_size;
	Empleado p;
	ifstream f;
	cout<< "Nombres  Apellidos  Cedula Sueldo Edad"<< endl;
	
	f.open("empleado.txt");

	while(1)
	{
		f.read(s,2);
		memcpy(&r_size, s,2);
		f.read(buffer, r_size);
		if(f.eof()) break;

		p.SetBuffer(buffer, r_size);
		p.Print();
	}
	f.close();
}

int WriteAll(){
	char c[100];
	c[0] = 0;
	Empleado p;
	
	ofstream f;
	f.open("empleado.txt", ios::binary | ios::app	);
	while(1)
	{
		p.Write();
		f.seekp(0, ios::end);
		f.write(p.BUFFER_REG, p.SIZE);

		cout << "Desea Continuar? (S/N): "<<flush; cin.getline(c, 100);
		if (strcmp(c,"N") == 0) break;
	}
	f.close();
    return 1;
}

void Empleado::GetEmpleadoByName(string nombre){
	char buffer[MAX_BUFFER];
	Empleado p;
	int cont=0;
	ifstream f;
	//cout<< "Nombres  Apellidos  Cedula Sueldo Edad"<< endl;
	
	f.open("empleado.txt");
	
	while(1)
	{
		f.read(0,ios::beg);
		
		if(strcmp(nombre,Nombres)==0){
			
			p.Print();
		}
		if(f.eof()); break;

	}
	f.close();

}



int main(int argc, char **argv){
	Empleado p;
	if (strcmp(argv[1], "1") == 0) ReadAll();	
	if (strcmp(argv[1], "2") == 0) WriteAll();

	if(strcmp(argv[1],"3")==0){
		p.GetEmpleadoByName("Daniel");
	}
	
}	

