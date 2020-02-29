#include <iostream>

using namespace std;

struct Matric
{
	//Размер
	int N;
	//Кол-во ненулевых элементов
	int NZ;
	//Диагональ
	int *AD;
	//Строки Верхнего триугольника
	int *AU;
	//Столбцы нижнего триугольника
	int *AL; 
	//Номера позиции в столбце
	int *LJ;
	//Номера позиции в строке
	int *LI;
};

//Функция доступа к элементу Матрицы
//Принимает указатель на структуру матрицы и индексы элемента
//Возвращает элемент в несжатой матрицы из сжатой
int Element(Matric temp, int i, int j)
{
	//Верхний триугольник
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
	//Нижний триугольник
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
	//Главная диагональ
	else if (i == j)
	{
		return temp.AD[i];
	}
		return 0;
}

//Функция Инициализации Матрицы
//Принимает указатель на структуру матрицы
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

//Функция суммирования всех элементов матрицы
//Принимает указатель на структуру матрицы
//Возвращает сумму всех элементов
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

//Функция печати
//Принимает структуру матрицы
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
	cout << "Sum: " << Sum(temp) << endl;	//Сумируем элементы
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

//Функция ввода матрицы
//Принимает указатель на структуру матрицы
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
				//Главная диагональ
				if (i == j)
				{
					system("cls");
					Print(*temp);
					cout << "Input A(" << i + 1 << "," << j + 1 << "): " << endl;
					scanf_s("%d", &temp->AD[i]);
				}
				//Верхний триугольник
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
						//Сохраняем сумму координат, для проверки симметрии в дальнейшем
						protect[counterProtect++] = i + j;
						//Уменьшаем кол-во оставшихся ненулевых знач.
						counterNZ--;
					}
					//Если первый ненулевой элемент ещё не найден
					//А строка кончилась
					if (flag == 1 && j + 1 > temp->N)
					{
						temp->LI[counterLI++] = temp->LI[counterLI + 1];
						flag--;
					}
				}
				//Нижний триугольник
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
								//Изменяем позицию в массиве
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

//Функция освобождения памяти
//Принимает указатель на структуру матрицы
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
	//Создаем матрицу
	Matric matric;
	//Заполняем её
	Input(&matric);
	//Выводим матрицу и сумму
	Print(matric);
	//Очищаем память
	Delete(&matric);
	system("pause");
	return 0;
}