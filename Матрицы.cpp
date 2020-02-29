#include <iostream>

using namespace std;

struct Matric
{
	//������
	int N;
	//���-�� ��������� ���������
	int NZ;
	//���������
	int *AD;
	//������ �������� ������������
	int *AU;
	//������� ������� ������������
	int *AL; 
	//������ ������� � �������
	int *LJ;
	//������ ������� � ������
	int *LI;
};

//������� ������� � �������� �������
//��������� ��������� �� ��������� ������� � ������� ��������
//���������� ������� � �������� ������� �� ������
int Element(Matric temp, int i, int j)
{
	//������� �����������
	if (i < j)
	{
		int N1 = temp.LI[i];
		int N2 = temp.LI[i + 1];
		for (int k = N1; k < N2; k++)
		{
			if (temp.LJ[k] == j)
			{
				return temp.AU[k];
			}
		}
	}
	//������ �����������
	else if (i > j)
	{
		int N1 = temp.LI[j];
		int N2 = temp.LI[j + 1];
		for (int k = N1; k < N2; k++)
		{
			if (temp.LJ[k] == i)
			{
				return temp.AL[k];
			}
		}
	}
	//������� ���������
	else if (i == j)
	{
		return temp.AD[i];
	}
		return 0;
}

//������� ������������� �������
//��������� ��������� �� ��������� �������
void Init(Matric *temp)
{
	temp->AD = new int[temp->N];
	temp->AU = new int[temp->NZ];
	temp->AL = new int[temp->NZ];
	temp->LJ = new int[temp->NZ];
	temp->LI = new int[temp->N];
	for (int i(0); i < temp->N; i++)
	{
		temp->AD[i] = 0;
	}
	for (int i(0); i < temp->NZ; i++)
	{
		temp->AU[i] = 0;
	}
	for (int i(0); i < temp->NZ; i++)
	{
		temp->AL[i] = 0;
	}
	for (int i(0); i < temp->N; i++)
	{
		temp->LI[i] = 0;
	}
	for (int i(0); i < temp->NZ; i++)
	{
		temp->LJ[i] = 0;
	}
}

//������� ������������ ���� ��������� �������
//��������� ��������� �� ��������� �������
//���������� ����� ���� ���������
int Sum(Matric temp)
{
	int TempSum = 0;
	for (int i(0); i < temp.N; i++)
		TempSum += temp.AD[i];
	for (int i(0); i < temp.NZ; i++)
		TempSum += temp.AU[i];
	for (int i(0); i < temp.NZ; i++)
		TempSum += temp.AL[i];
	return TempSum;
}

//������� ������
//��������� ��������� �������
void Print(Matric temp)
{
	cout << " ";
	for (int i(0); i < temp.N; i++)
	{
		cout << "|-" << i + 1 << "-|";
	}
	cout << endl;
	for (int i(0); i < temp.N; i++)
	{
		cout << i + 1;
		for (int j(0); j < temp.N; j++)
		{
			cout << "|-" << Element(temp, i, j) << "-|";
		}
		cout << endl;
	}
	cout << "Sum: " << Sum(temp) << endl;	//�������� ��������
	for (int i(0); i < temp.N; i++)
	{
		cout << temp.AD[i];
	}
	cout << endl;
	for (int i(0); i < temp.NZ; i++)
	{
		cout << temp.AU[i];
	}
	cout << endl;
	for (int i(0); i < temp.NZ; i++)
	{
		cout << temp.AL[i];
	}
	cout << endl;
	for (int i(0); i < temp.N; i++)
	{
		cout << temp.LI[i];
	}
	cout << endl;
	for (int i(0); i < temp.NZ; i++)
	{
		cout << temp.LJ[i];
	}
}

//������� ����� �������
//��������� ��������� �� ��������� �������
void Input(Matric *temp)
{
		//----------------------------------------------------
		int t, counterAU, counterAL, counterNZ, counterProtect, counterLI, counterLJ, flag;
		counterProtect = 0;
		counterAL = 0;
		counterAU = 0;
		counterNZ = 0;
		counterLI = 0;
		counterLJ = 0;
		flag = 0;
		temp->N = 0;
		temp->NZ = 0;
		//----------------------------------------------------
		cout << "Input size of Matric: ";
		scanf_s("%d", &temp->N);
		cout << "Input the number non-zero value of Matric: ";
		scanf_s("%d", &temp->NZ);
		temp->NZ /= 2;
		counterNZ = temp->NZ;
		int *protect = new int[temp->NZ];
		Init(temp);
		//----------------------------------------------------
		for (int i(0); i < temp->N; i++)
		{
			flag++;
			for (int j(0); j < temp->N; j++)
			{
				//������� ���������
				if (i == j)
				{
					system("cls");
					Print(*temp);
					cout << "Input A(" << i + 1 << "," << j + 1 << "): " << endl;
					scanf_s("%d", &temp->AD[i]);
				}
				//������� �����������
				else if (i < j)
				{
					system("cls");
					Print(*temp);
					cout << "Input A(" << i + 1 << "," << j + 1 << "): " << endl;
					scanf_s("%d", &t);
					if (t != 0 && counterNZ > 0)
					{
						temp->AU[counterAU++] = t;
						temp->LJ[counterLJ++] = j;
						if (flag == 1)
						{
							temp->LI[counterLI++] = i;
							flag--;
						}
						//��������� ����� ���������, ��� �������� ��������� � ����������
						protect[counterProtect++] = i + j;
						//��������� ���-�� ���������� ��������� ����.
						counterNZ--;
					}
					//���� ������ ��������� ������� ��� �� ������
					//� ������ ���������
					if (flag == 1 && j + 1 > temp->N)
					{
						temp->LI[counterLI++] = temp->LI[counterLI + 1];
						flag--;
					}
				}
				//������ �����������
				else if (i > j)
				{
					for (int k(0); k < counterProtect; k++)
					{
						if (protect[k] == (i + j))
						{
							system("cls");
							Print(*temp);
							cout << "Input A(" << i + 1 << "," << j + 1 << "): " << endl;
							scanf_s("%d", &t);
							if (t != 0)
							{
								temp->AL[counterAL] = t;
								//�������� ������� � �������
								counterAL++;
							}
						}
					}
				}
			}
			temp->LI[counterLI] = counterLI;
		}
		delete[] protect;
}

//������� ������������ ������
//��������� ��������� �� ��������� �������
void Delete(Matric *temp)
{
	delete[] temp->AD;
	delete[] temp->AU;
	delete[] temp->AL;
	delete[] temp->LJ;
	delete[] temp->LI;
	temp->N = 0;
	temp->NZ = 0;
}

int main()
{
	//������� �������
	Matric matric;
	//��������� �
	Input(&matric);
	//������� ������� � �����
	Print(matric);
	//������� ������
	Delete(&matric);
	system("pause");
	return 0;
}