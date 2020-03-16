#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;

int main() 
{
	// устанвливаем русскую локаль для консоли
	setlocale(LC_ALL, "Russian");
	
	int n = 10, Lx = 200, Ly = 200; // n - число гор, Lx х Ly - заданная плоскость
	float F[Lx*Ly] = {0}, Falfa[Lx*Ly] = {0}; // F[Lx*Ly] - значение ф-ии, Falfa[Lx*Ly] - значение ф-ии при повернутых овалах
	float a[n]={0}, px[n]={0}, py[n]={0}, tx[n]={0}, ty[n]={0}, alfa[n]={0}, x[n] ={0}, y[n] = {0};
	// a[n] - амплитуда (высота горы), px[n] и py[n] - полуоси овала, tx[n]={0} и ty[n]={0} - центр координат овала, 
	// alfa[n] - угол поворота овала, x[n] и y[n] - новые координаты для расчета повернутого овала;
	
	char color[] = {' ', '.', ',', '-', '^', '+', 'o', '*', '{', 'T', 'N', 'B', '%', '№', '&', 'W'}; // цвет
	//for(int i=0;i<8;i++){
	//cout<<R[i]<<endl;}
	
	for (int k = 0; k < n; k++)
	{
		a[k] = 100 + 900*0.01*(rand() % 101); // амплитуда от 100 до 1000
		px[k] = 3 + 27*0.01*(rand() % 101); // полуось х от 3 до 30
		py[k] = 3 + 27*0.01*(rand() % 101); // полуось у от 3 до 30
		tx[k] = 20 + 160*0.01*(rand() % 101); // центр овала по оси х от 20 до 180
		ty[k] = 20 + 160*0.01*(rand() % 101); // центр овала по оси у от 20 до 180
		alfa[k] = -90 + 180*0.01*(rand() % 101); // угол от -90 до 90
		cout<<"a: "<<a[k]<<"; px: "<<px[k]<<"; py: "<<py[k]<<"; tx: "<<tx[k]<<"; ty: "<<ty[k]<<"; alfa[k]: "<<alfa[k] <<endl;
	}
	
	ofstream out; // поток для записи
    out.open("img.txt"); // создаем файл "img.txt"
    if (!out.is_open()) cout << "Ошибка открытия файла" << endl;
    
    ofstream out_alfa; // поток для записи
    out_alfa.open("img_alfa.txt"); // создаем файл "img_alfa.txt"
    if (!out_alfa.is_open()) cout << "Ошибка открытия файла" << endl;
    
	 	for (int k = 0; k < n; k++)
		{
			for (int j = 0; j < Ly; j++)
			{
				for(int i = 0; i < Lx; i++)
				{
					// расчет для ровных овалов
					F[i+j*Lx] += a[k]*exp(-((i-tx[k])/px[k])*((i-tx[k])/px[k]))*exp(-((j-ty[k])/py[k])*((j-ty[k])/py[k]));
					
					int P;
					P = F[i+j*Lx]/100;
					if (P > 14) P = 14;
					
					out << color[P];
					
					// расчет для овалов наклоненных под углом альфа
					x[k] = (((i-tx[k])*cos(alfa[k])+(j-ty[k])*sin(alfa[k]))/px[k])*(((i-tx[k])*cos(alfa[k])+(j-ty[k])*sin(alfa[k]))/px[k]);
					y[k]  = ((-(i-tx[k])*sin(alfa[k])+(j-ty[k])*cos(alfa[k]))/py[k])*((-(i-tx[k])*sin(alfa[k])+(j-ty[k])*cos(alfa[k]))/py[k]);
					Falfa[i+j*Lx] += a[k]*exp(-(x[k]))*exp(-(y[k]));
					
					int P_alfa;
					P_alfa = Falfa[i+j*Lx]/100;
					if (P_alfa > 14) P_alfa = 14;
					
					out_alfa << color[P_alfa];
				}
			out << endl;
			out_alfa << endl;
			}
		}
		// вывод конечного изображения в консоль
		int P = 0;
		cout << " Ровные овалы: " << endl;
		for (int js = 0; js < Ly; js++)
		{
			for(int is = 0; is < Lx; is++)
			{
				P = F[is+js*Lx]/100;
				if (P > 14) P = 14;		
				cout << color[P];
			}
			cout<<endl;
		}	
		int P_alfa = 0;
		cout << " Овалы под наклоном: " << endl;
		for (int jk = 0; jk < Ly; jk++)
		{
			for(int ik = 0; ik < Lx; ik++)
			{
				P_alfa = Falfa[ik+jk*Lx]/100;
				if (P_alfa > 14) P_alfa = 14;
				cout << color[P_alfa];		
			}
			cout<<endl;
		}	
	out.close();
	out_alfa.close();
}
