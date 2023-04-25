#include <iostream>
#include <iomanip>

#include<fstream>
#include<sstream>


using namespace std;
//Estructuras

typedef struct Producto{
	
	char lado;
	char piso;
	int columna;
	int peso;
	
	int ganancia;
		
}Prod;
//Lectura de datos

bool Lectura(Prod*& productos,int& N,int& P)
{
	string archivo="datos1_0.txt";
	ifstream file(archivo);
	int i=0;
	int k=0;
	if(file.is_open())
	{
		string line;
		
		while(getline(file,line))
		{
			istringstream ss(line);
						
			if(i==0)
			{
				ss>>N;
				if(N>4)
				{
					cout<<"El N debe ser menor o igual que 4.\n";
					return false;
				} 
				productos=new Prod[4*N];
			}else if(i==1){
				ss>>P;
			
			}else{
				for(int j=0;j<N;j++)
				{
					ss>>productos[k].peso;
										
						if(i==2 || i==3) 	productos[k].lado='I';
						if(i==4 || i==5) 	productos[k].lado='D';						
						if(i%2==0) productos[k].piso='A';
						if(i%2!=0) productos[k].piso='B';
						productos[k].columna=j+1;				
					
					k++;
				}
				
				
			}			
			
			i++;
		}
		file.close();
		return true;
	}else{
		
		return false;
	}	
}

bool LecturaGanancia(Prod* productos,int n)
{
	string archivo="datos1_1.txt";
	ifstream file(archivo);
	
	int i=0;
	if(file.is_open())
	{
		string line;
		
		while(getline(file,line))
		{
			istringstream ss(line);
			
			for(int j=0;j<n;j++)
			{
				ss>>productos[i].ganancia;
				i++;
			}			
			
		}
		file.close();
		return true;
	}else{
		
		return false;
	}
	
	
}

void mostrarProductos(Prod* productos,int n)
{
	for (int i = 0; i < n; i++)
	{
    cout << "\n[+]Producto " <<setw(3)<< i +1 <<setw(6)<< " -> " ;
    cout <<setw(8)<< "Lado:" <<setw(5) <<productos[i].lado ;
    cout <<setw(12)<< "Piso:" <<setw(5) <<productos[i].piso ;
    cout <<setw(12)<< "Columna:" <<setw(5) <<productos[i].columna ;
    cout <<setw(12)<< "Peso:" <<setw(5) <<productos[i].peso ;
	}
	cout<<endl;
}

void mostrarGanancias(Prod* productos,int n)
{
	for (int i = 0; i < n; i++)
	{
    cout << "\n[+]Producto " <<setw(3)<< i +1 <<setw(6)<< " -> " ;
    cout <<setw(10)<< "Ganancia:" <<setw(5)<<productos[i].ganancia;
    
	}
	cout<<endl;
}

void imprimirSolucion(Prod* productos,int N,int i,int cant,int vS[])
{
	cout<<setw(15)<<"Resultado: ";	
	for(int j=0;j<cant;j++)
	{	
	    int ind=vS[j];	   				
		cout<<"\t"<<productos[ind].peso<<"K - ";
	}
		
	cout<<"\n"<<setw(15)<<"Ubicaciones: ";
	for(int j=0;j<cant;j++)
	{
		int ind=vS[j];
		cout<<"\t"<<productos[ind].lado
			<<productos[ind].piso
			<<productos[ind].columna<<"  ";
	}
	cout<<"\n-----------------------------------------------------"<<endl;
}


void BusquedaSolucion(Prod* productos,int N,int P)
{
	int SumP=0;
	int ind_Solucion; 
	int cant=0;
	
	
	for(int i=0;i<(1<<N);i++)
	{
		SumP=0;
		cant=0;
		int VecSolucion[N]{};
		for(int j=0;j<N;j++)
		{
			if( i & (1<<j) )
			{
				SumP += productos[j].peso;
				VecSolucion[cant]=j;				
				cant++;
			}
		}
		
		//Luego del for se ha sumado los pesos
		
		if(SumP==P)
		{
			ind_Solucion=i;
			imprimirSolucion(productos,N,i,cant,VecSolucion); 
		}	
	}
}


void imprimirSol_GM(Prod* productos,int N,int i,int cant,int vS[],int G)
{
	cout<<setw(15)<<"Resultado: ";	
	for(int j=0;j<cant;j++)
	{	
	    int ind=vS[j];	   				
		cout<<"\t"<<productos[ind].peso<<"K - ";
	}
		
	cout<<"\n"<<setw(15)<<"Ubicaciones: ";
	for(int j=0;j<cant;j++)
	{
		int ind=vS[j];
		cout<<"\t"<<productos[ind].lado
			<<productos[ind].piso
			<<productos[ind].columna<<"  ";
	}
	
	cout<<"\n\t[+] Ganancia : "<<G<<endl;
	cout<<"\n-----------------------------------------------------"<<endl;
}

void BusquedaMax_Ganancia(Prod* productos,int N,int P)
{
	int sumG=0;
	int SumP=0;
	int ind_Solucion; 	
	int G_Max=-1;
	int cant=0;
	
	
	int VecSolucion[N]{};
	int c=0;
	
	for(int i=0;i<(1<<N);i++)
	{
		sumG=0;	
		SumP=0;
		cant=0;
			
		for(int j=0;j<N;j++)
		{
			if( i & (1<<j) )
			{
				sumG += productos[j].ganancia;
				SumP += productos[j].peso;
				
				VecSolucion[cant]=j;				
				cant++;				
			}
		}
		
		//Luego del for se ha sumado los pesos
		
		if( SumP==P && sumG>G_Max) // sumG=>G_Max Mayores soluciones
		{
			G_Max=sumG;
			ind_Solucion=i;
			c=cant;
			
		}		
			
	}
	
	cout<<"\n \t[+] Mejor solucion "<<endl;
	imprimirSol_GM(productos,N,ind_Solucion,c,VecSolucion,G_Max);
	
	
	
}



int main(){
	//a)
	int N;	
	int P;
	Prod* productos;
    if(Lectura(productos,N,P))
    {
    	
    	mostrarProductos(productos,4*N);    
    	cout<<endl;
    	//b)
    	BusquedaSolucion(productos,4*N,P);
    	
    	//c)
    	if(LecturaGanancia(productos,N))
    	{
    		mostrarGanancias(productos,4*N);
    		BusquedaMax_Ganancia(productos,4*N,P);
		}else{
			cout<<"\t[-]No se pudo leer las ganancias."<<endl;
		}
    	
	}else{
		
	}
    
    
    return 0;
}