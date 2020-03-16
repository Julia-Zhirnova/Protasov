#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;

int main() 
{
	// ������������ ������� ������ ��� �������
	setlocale(LC_ALL, "Russian");
	
	int M = 11; // ���������� �������
	float beta = 0.0; // ��������� ������
	int ITs = 100; // ����� ��������
	int N = 100; // ����� �������� �������� 
	float Teta[N*M] = {0.0}; // ��������� ��������
	float GR = 0.0; // ����������� ����������� ������� ������ ��������
	float GN = 0.0; // ����������� ������������� ������� ������ ��������
	float GS = 0.0; // ����������� ������� ������ ������ ��������
    float TGR=0.0; // �������� ��������
    float DR=2.0; // ������ - ������ ��������
	float TGS=DR+TGR; // �������� ��������
	float TER=2.0; // ��������� ��������
	float DE=2.0; // ������ - ������ ��������
	float QR = 0.0, QN = 0.0, Qo=0.0; // ������� ������
	float sumR = 0.0, sumS = 0.0, sumN = 0.0; // ����� ���� ������������
		
	ofstream out; // ����� ��� ������
    out.open("test.txt"); // ������� ���� "img.txt"
    if (!out.is_open()) cout << "������ �������� �����" << endl;
	
	
	for (beta = -5; beta < 8; beta++) 
	  {
	   cout << endl;  
	   out << endl;
	   cout << "beta = " << beta << endl;
	   out << "beta = " << beta << endl;
	   cout << endl;  
	   out << endl;
	   for (int IT=0; IT<ITs; IT++)
	     {
	      for (int IN=0; IN<N; IN++)
	        {
	     	 for (int j=0; j<M; j++)
	           {
	           	GR = 1/(1 + exp(beta - TGR)); // ����������� ����������� ������� ������ �������� �������������� �� ������ ����
	     	    // cout << j << ": ����������� ����������� ������� ������ = " << GR << endl;
	     	    sumR += GR; // ����� ���� ������������ ����������� �������
	     	    GS = 1/(1 + exp(beta - (TGR+DR))); // ����������� ������� ������ ����� ��������� �������������� �� ������ ����
	     	    // cout << j << ": ����������� ������� ������ = " << GS << endl;
	     	    sumS += GS; // ����� ���� ������������
	     	    GN = 1/(1 + exp(beta - TGS)) - 1/(1 + exp(beta - TGR)); // ����������� ������������� ������� ������ ����� ��������� �������������� �� ������ ����
	     	    // cout << j << ": ����������� ������������� ������� ������ = " << GN << endl;
	     	    sumN += GN; // ����� ���� ������������ ������������� �������
	     	    
				float r = 0.01*(rand() % 101); // ��������� ����� �� 0 �� 1
	     	    if (r<GR) Teta[j+IN*M] = 1; // ������ ������ ���������
	     	    if ((r<GS) && (r>GR)) Teta[j+IN*M] = -1; // ������ ������ �����������
	     	    if (r>GS) Teta[j+IN*M] = 0;  // ����� "�� ����"
	     	    // cout << Teta[j+IN*M]; // ������� ������� ������
	     	    // out << Teta[j+IN*M];
	     	    if (Teta[j+IN*M] == 1) QR++; // ������� ���������� �������
	     	    if (Teta[j+IN*M] == -1) QN++; // ������� ������������ �������
	     	    if (Teta[j+IN*M] == 0) Qo++; // ������� �� ������ �������
	     	   }
		    // cout << endl;   
		    // out << endl;
		    }	
		    
		 }
		// cout << "QR = " << QR << ";   QN = " << QN << ";   Qo = " << Qo << endl;
		// out << "QR = " << QR << ";   QN = " << QN << ";   Qo = " << Qo << endl;
		// cout << "������� ����������� ����������� ������� ������ = " << sumR/(ITs*N*M) <<endl;
		// cout << "������� ����������� ������� ������ = " << sumS/(ITs*N*M) <<endl; 
		// out << sumR/(ITs*N*M) <<endl;
		// out << sumS/(ITs*N*M) <<endl;
		// out << sumN/(ITs*N*M) <<endl;
		sumR = 0.0; sumS = 0.0; sumN = 0.0;
		QR = QR/(ITs*N*M);
	  	QN = QN/(ITs*N*M);
	  	cout << "������� ���������� ������� ������ ������� = " << QR << ";   ������� ������������ ������� ������ ������� = " << QN << endl;
	  	out << "������� ���������� ������� ������ ������� = " << QR << ";   ������� ������������ ������� ������ ������� = " << QN << endl;
		QR = 0.0; QN = 0.0;	Qo = 0.0;
	  }
	out.close();
}
