#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct Trubba//Труба
{
	string idif; // Идентификатор
	double dlin; // Длина
	int diamet; // Диаметр
	bool sostoi; // Состояние в ремонте или нет

};
struct KompressStan // Компрессорная станция
{
	string name; // Имя
	string idif; // Идентификатор
	int Cexi; // Количество цехов
	int WCexi; // Количсевто цехов в работе
	int effectiv; // Эффективность
};
template <typename T>
T getint(string text, T border1, T border2 = 10000)
{
	T value;
	while (1)
	{
		cout << text << endl;
		cin >> value;
		if (cin.fail() || value < border1 || value >border2)
		{
			cin.clear();
			//cin.ignore(32767, '\n');
			cout << "Введённые данные не корректны. Попробуй ещё раз.\n";
		}
		else
		{
			return value;
		}
	}

}
Trubba creatTrubba() // Создание трубы
{
	Trubba t;
	t.idif = "1";
	t.dlin = getint("Введи длину трубы (Еденица измерения: м)", 1.0);
	t.diamet = getint("Введи диаметр трубы(Еденица измерения : мм)", 1);
	t.sostoi = false;
	return t;
}
KompressStan creatKompressStan() // Создание компрессорной станции
{
	KompressStan kss;
	cout << "Введи имя компрессорной станции\n";
	cin.get();
	getline(cin, kss.name);
	kss.Cexi = getint("Введи количество цехов", 1);
	kss.WCexi = getint("Введи количество цехов в работе", 0, kss.Cexi);
	kss.effectiv = getint("Введи эффективность компрессорной станцции (Эффективность измеряется по 10-ти бальной шкале)", 0);
	return kss;
}
void printTrubba(const Trubba& t) // Вывод информации о трубе
{
	cout << "Данные о трубе:\n";
	cout << "Длина трубы: " << t.dlin << " (м)" << endl;
	cout << "Диаметр турбы: " << t.diamet << " (мм)" << endl;
	cout << "Состояние трубы: " << (t.sostoi ? "В ремонте\n" : "Не в ремонте\n");
}
void printKompressStan(const KompressStan& kss) // Вывод информации о компрессорной станции
{
	cout << "Данные о компрессорной станции:\n";
	cout << "Имя компрессорной станции: " << kss.name << endl;
	cout << "Количество цехов на компрессорной станции: " << kss.Cexi << endl;
	cout << "Количество цехов в работе: " << kss.WCexi << endl;
	cout << "Эффективность компрессорной станции: " << kss.effectiv << endl;
}
void editTrubba(Trubba& t) // Отправить трубу в ремонт
{
	t.sostoi = !t.sostoi;
}
void editKompressStan(KompressStan& kss) // Изменение цехов в работе
{
	kss.WCexi = getint("Введи количество цехов в работе", 0, kss.Cexi);
}
void savefileTrubba(ofstream& fout, const Trubba& t) // Сохранение информации о трубе
{
	fout << t.idif << endl;
	fout << t.dlin << endl;
	fout << t.diamet << endl;
	fout << t.sostoi << endl;
}
Trubba inputfileTrubba(ifstream& fin) // Считывание информации о трубе
{
	Trubba t;
	fin >> t.idif;
	fin >> t.dlin;
	fin >> t.diamet;
	fin >> t.sostoi;
	return t;
}
void savefileKompressStan(ofstream& fout, const KompressStan& kss) // Сохранение информации о компрессорной станции
{
	fout << kss.name << endl;
	fout << kss.Cexi << endl;
	fout << kss.WCexi << endl;
	fout << kss.effectiv << endl;
}
KompressStan inputfileKompressStan(ifstream& fin) // Считывание информации о компрессорной станции
{
	KompressStan kss;
	fin >> kss.name;
	fin >> kss.Cexi;
	fin >> kss.WCexi;
	fin >> kss.effectiv;
	return kss;
}
Trubba& selectTrubba(vector<Trubba>& Truboprovod)
{
	unsigned int index = getint("Введите номер трубы", 1u, Truboprovod.size());
	return Truboprovod[index - 1];
}
KompressStan& selectKompressStan(vector<KompressStan>& Zavod)
{
	unsigned int index = getint("Введи номер компрессорной станции", 1u, Zavod.size());
	return Zavod[index - 1];
}
void pechatmenu()
{
	cout << "1-Добавить трубу\n";
	cout << "2-Добавить компрессорную станцию\n";
	cout << "3-Вывести информацию о трубе и компрессорной станции\n";
	cout << "4-Редактировать состояние трубы\n";
	cout << "5-Редактировать колличество цехов в работе компрессорной станции\n";
	cout << "6-Сохранить данные файл\n";
	cout << "7-Считать данные из файла\n";
	cout << "0-Выход\n";
}
int main()
{
	setlocale(LC_ALL, "Russian");
	vector <Trubba> Truboprovod;
	vector <KompressStan> Zavod;
	while (1)
	{
		pechatmenu();
		int i;
		i = getint("Введи номер действия", 0);
		switch (i)
		{
		case 1:
		{
			Truboprovod.push_back(creatTrubba());
			break;
		}
		case 2:
		{
			Zavod.push_back(creatKompressStan());
			break;
		}
		case 3:
		{
			if (Truboprovod.size() > 0 || Zavod.size() > 0)
			{
				if (Truboprovod.size() > 0)
				{
					printTrubba(selectTrubba(Truboprovod));
				}
				else
				{
					cout << "Труба не создана.\n";
				}
				if (Zavod.size() > 0)
				{
					printKompressStan(selectKompressStan(Zavod));
				}
				else
				{
					cout << "Компрессорная станция не создана.\n";
				}
				break;

			}
			else
			{
				cout << "Труба или Компрессорная станция не создана. Попробуй ещё раз.\n";
				break;
			}
		}
		case 4:
		{
			if (Truboprovod.size() > 0)
			{
				editTrubba(selectTrubba(Truboprovod));
				break;
			}
			else
			{
				cout << "Труба не создана. Попробуй ещё раз.\n";
				break;
			}
		}
		case 5:
		{
			if (Zavod.size() > 0)
			{
				editKompressStan(selectKompressStan(Zavod));
				break;
			}
			else
			{
				cout << "Компрессорная станция не создана. Попробуй ещё раз.\n";
				break;
			}
		}
		case 6:
		{
			if (Truboprovod.size() > 0 || Zavod.size() > 0)
			{
				ofstream fout;
				fout.open("info.txt", ios::out);
				if (fout.is_open())
				{
					fout << Truboprovod.size() << endl;
					fout << Zavod.size() << endl;
					if (Truboprovod.size() > 0)
					{
						for (Trubba infotrubba : Truboprovod)
						{
							savefileTrubba(fout, infotrubba);
						}
					}
					if (Zavod.size() > 0)
					{
						for (KompressStan infoKompressStan : Zavod)
						{
							savefileKompressStan(fout, infoKompressStan);
						}
					}
					fout.close();
				}
				break;
			}
			else
			{
				cout << "Труба или Компрессорная станция не создана. Попробуй ещё раз.\n";
				break;
			}
		}
		case 7:
		{
			ifstream fin;
			fin.open("info.txt", ios::in);
			if (fin.is_open())
			{
				int countt;
				int countks;
				fin >> countt;
				fin >> countks;
				Trubba infotrubba;
				KompressStan infoKompressStan;
				if (countt > 0)
				{
					while (countt--)
					{
						infotrubba = inputfileTrubba(fin);
						Truboprovod.push_back(infotrubba);
					}
				}
				if (countks)
				{
					while (countks--)
					{
						infoKompressStan = inputfileKompressStan(fin);
						Zavod.push_back(infoKompressStan);
					}
				}
			}
			break;
		}
		case 0:
		{
			return 0;
		}
		default:
		{
			cout << "Данные введены не корректно. Попробуй ещё раз.";
		}
		}
	}
}