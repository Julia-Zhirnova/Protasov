#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;

int main() 
{
	// ������������ ������� ������ ��� �������
	setlocale(LC_ALL, "Russian");
	
	int n = 10, Lx = 200, Ly = 200; // n - ����� ���, Lx � Ly - �������� ���������
	float F[Lx*Ly] = {0}, Falfa[Lx*Ly] = {0}; // F[Lx*Ly] - �������� �-��, Falfa[Lx*Ly] - �������� �-�� ��� ���������� ������
	float J[Lx*Ly] = {0}; // ������������
	float a[n]={0}, px[n]={0}, py[n]={0}, tx[n]={0}, ty[n]={0}, alfa[n]={0}, x[n] ={0}, y[n] = {0};
	// a[n] - ��������� (������ ����), px[n] � py[n] - ������� �����, tx[n]={0} � ty[n]={0} - ����� ��������� �����, 
	// alfa[n] - ���� �������� �����, x[n] � y[n] - ����� ���������� ��� ������� ����������� �����;
	float Pl[11]={}; // ���������
	float L_len = 0, Pl_len = 0; // ����� ��������
	float z1, z2, z3; // ��������� �����
	float Npl_x, Npl_y, Npl_z; // ���������� �������� ������ ����������������
	
	float Li_x=153, Li_y=115, Li_z=423; // ���������� �������� ������ �����
	float L[]={Li_x, Li_y, Li_z}; // ������ �����
	float cosfi; // ���� ������ �����
	
	char color[] = {' ', '.', ',', '-', '^', '+', 'o', '*', '{', 'T', 'N', 'B', '%', '�', '&', 'W'}; // ����
	int m; // ������������ �����
		
	for (int k = 0; k < n; k++)
	{
		a[k] = 100 + 900*0.01*(rand() % 101); // ��������� �� 100 �� 1000
		px[k] = 3 + 27*0.01*(rand() % 101); // ������� � �� 3 �� 30
		py[k] = 3 + 27*0.01*(rand() % 101); // ������� � �� 3 �� 30
		tx[k] = 20 + 160*0.01*(rand() % 101); // ����� ����� �� ��� � �� 20 �� 180
		ty[k] = 20 + 160*0.01*(rand() % 101); // ����� ����� �� ��� � �� 20 �� 180
		alfa[k] = -90 + 180*0.01*(rand() % 101); // ���� �� -90 �� 90
		//cout<<"a: "<<a[k]<<"; px: "<<px[k]<<"; py: "<<py[k]<<"; tx: "<<tx[k]<<"; ty: "<<ty[k]<<"; alfa[k]: "<<alfa[k] <<endl;
	}
	
	ofstream out; // ����� ��� ������
    out.open("img.txt"); // ������� ���� "img.txt"
    if (!out.is_open()) cout << "������ �������� �����" << endl;
    
    ofstream out_alfa; // ����� ��� ������
    out_alfa.open("img_alfa.txt"); // ������� ���� "img_alfa.txt"
    if (!out_alfa.is_open()) cout << "������ �������� �����" << endl;
    
	 	for (int k = 0; k < n; k++)
		{
			for (int j = 0; j < Ly; j++)
			{
				for(int i = 0; i < Lx; i++)
				{
					// ������ ��� ������ ������
					F[i+j*Lx] += a[k]*exp(-((i-tx[k])/px[k])*((i-tx[k])/px[k]))*exp(-((j-ty[k])/py[k])*((j-ty[k])/py[k]));
					
					int P;
					P = F[i+j*Lx]/100;
					if (P > 14) P = 14;
					
					//out << color[P];
					
					// ������ ��� ������ ����������� ��� ����� �����
					x[k] = (((i-tx[k])*cos(alfa[k])+(j-ty[k])*sin(alfa[k]))/px[k])*(((i-tx[k])*cos(alfa[k])+(j-ty[k])*sin(alfa[k]))/px[k]);
					y[k]  = ((-(i-tx[k])*sin(alfa[k])+(j-ty[k])*cos(alfa[k]))/py[k])*((-(i-tx[k])*sin(alfa[k])+(j-ty[k])*cos(alfa[k]))/py[k]);
					Falfa[i+j*Lx] += a[k]*exp(-(x[k]))*exp(-(y[k]));
					
					int P_alfa;
					P_alfa = Falfa[i+j*Lx]/100;
					if (P_alfa > 14) P_alfa = 14;
										
					out_alfa << color[P_alfa];
				}
			//out << endl;
			out_alfa << endl;
			}
		}
	/*	// ����� ��������� ����������� � �������
		int P = 0;
		cout << " ������ �����: " << endl;
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
		cout << " ����� ��� ��������: " << endl;*/
		for (int jk = 0; jk < Ly; jk++)
		{
			for(int ik = 0; ik < Lx; ik++)
			{
				//��������� ����� ������� ���������
				z1 = Falfa[ik+jk*Lx];
				z2 = Falfa[1+ik+jk*Lx];
				z3 = Falfa[ik+(1+jk)*Lx];
			//	cout << " z1: " << z1 << " z2: " << z2<< " z3: " << z3 << endl;
			    // ������� ������ �������
				Npl_x = z1-z2;
				Npl_y = z1-z3;
				Npl_z = 1;
			//  cout << " pl_x: " << pl_x << " pl_y: " << pl_y<< " pl_z: " << pl_z << endl;
				Pl_len = sqrt(Npl_x*Npl_x + Npl_y*Npl_y + Npl_z*Npl_z); // ����� ������� ������� � ���������
				L_len = sqrt(Li_x*Li_x + Li_y*Li_y + Li_z*Li_z); // ����� ������� �����
			//	cout << " L_len: " << L_len << " Pl_len: " << Pl_len << endl;
				cosfi = (abs(Li_x*Npl_x + Li_y*Npl_y + Li_z*Npl_z))/(L_len*Pl_len); // ���� ����� �������� ������� � ���������
				// � �������� ������� �����
			//	cout << " ����: " << cosfi << endl;	
			if (cosfi <= 0)  m =14;
			if (cosfi > 0 && cosfi <= 0.0714287) m = 13;
 			if (cosfi > 0.0714287 && cosfi <= 0.142857) m = 12;
 			if (cosfi > 0.142857 && cosfi <= 0.214286) m = 11;
 			if (cosfi > 0.214286 && cosfi <= 0.285714) m = 10;
 			if (cosfi > 0.285714 && cosfi <= 0.357143) m = 9 ;
 			if (cosfi > 0.357143 && cosfi <= 0.428571) m = 8;
 			if (cosfi > 0.428571 && cosfi <= 0.5) m = 7;
 			if (cosfi > 0.5 && cosfi <= 0.571429) m = 6;
 			if (cosfi > 0.571429 && cosfi <= 0.642857) m = 5;
 			if (cosfi > 0.642857 && cosfi <= 0.714286) m = 4;
 			if (cosfi > 0.714286 && cosfi <= 0.785715) m = 3;
 			if (cosfi > 0.785715 && cosfi <= 0.857143) m = 2;
 			if (cosfi > 0.857143 && cosfi < 1) m = 1;
 			if (cosfi == 1) m = 0;
 			
 			cout << color[m];
 			out << color[m];
			}
		 cout<<endl;
		 out<<endl;
		}	
		/*for (float col = -1.0; col <=1.0 ; col = col + (2.0/28.0))
		{
			cout << " col: " << col << endl;
			out << " col: " << col << endl;
		}*/
	
	out.close();
	out_alfa.close();
}
