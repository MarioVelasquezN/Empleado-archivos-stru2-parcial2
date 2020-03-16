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
	bool cam=true;
	char s[2];
	uint16_t r_size;
	Empleado p;
	int cont=0;
	ifstream f;
	
	f.open("empleado.txt");
	if(!f){
		cout<<"Erro al abrir el archivo empleado.txt";
		return;
	}

	while(cam)
	{
		f.read(s,2);
		memcpy(&r_size, s,2);
		f.read(buffer,r_size);
		
		p.SetBuffer(buffer, r_size);

		if(nombre==p.Nombres){
			cout<<"aqui\n";
			
			p.Print();
			break;
		}else{
			f.tellg();
			cam=true;
		}

	}if(f.eof());
	f.close();
}

void Empleado::crearIndice(){
	fstream f;
	fstream l;
	char buffer[MAX_BUFFER];
	char* bufferindex[100];
	bufferindex[0]=0;
	uint16_t size;
	char* name;
	Empleado emple;

	f.open("indice.txt");
	l.open("empleado.txt");

	while(1){
		int offset=f.tellp();
		f.read(buffer,size);
		f.read((char*)&offset,sizeof(int));
		if(f.eof())break;
		emple.SetBuffer(buffer,size);
	}

	cout<<"\nIngrese nombre pa buscar: "<<endl;
	cin>>name;
	if(emple.Nombres==name){
		
		int offset=f.tellg();
		f.write((char*)&offset,2);
		f.write((char*)&emple.Nombres,size);

	}
	f.close();
	l.close();
}



//abrir un zip y extraer lo que tiene, metodo estandar
//leer binariamente los encabezados del zio yleer las entradas
//

int main(int argc, char **argv){
	Empleado p;
	if (strcmp(argv[1], "1") == 0) ReadAll();	
	if (strcmp(argv[1], "2") == 0) p.crearIndice();
	cout<<"\n";
		//p.GetEmpleadoByName("Daniel");
	//ReadAll();

	//p.crearIndice();	
	//p.countCharLineSpace();
}	
