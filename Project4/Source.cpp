#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <fstream>

using namespace std;

enum Spec { KN = 0, IT, M_end_E, Ph_end_I, L_E };

string specStr[] = { "��", "��","�_�_����", "�_�_���", "����" };

struct Student
{
    char Prizv[60];
    int Kurs;
    Spec spec;
    double Math;
    double Phisic;
    union
    {
        double Inform;
        double Pedagogic;
        double Metod;
    };
};

void Create(string filename)
{
    ofstream f(filename, ios::binary);
    Student s;
    char ch;
    int spec, i = 0;

    do
    {
        i++;
        cin.get();
        cout << "������� �" << i << ":" << endl;
        cout << "�������: "; cin.getline(s.Prizv, 60);
        cout << "����: "; cin >> s.Kurs;
        cout << "������������ (0 - ��, 1 - ��, 2 - �_�_����, 3 - �_�_���, 4 - ����): "; cin >> spec;
        s.spec = (Spec)spec;
        cout << "����������: "; cin >> s.Math;
        cout << "Գ����: "; cin >> s.Phisic;
        switch (s.spec)
        {
        case KN:
            cout << "��i��� � ������������� - "; cin >> s.Inform;
            break;
        case IT:
            cout << "��i��� � ��������� ������ - "; cin >> s.Metod;
            break;
        case M_end_E:
        case Ph_end_I:
        case L_E:
            cout << "��i��� � �������i�� - "; cin >> s.Pedagogic;
            break;
        }
        cin.get();

        f.write((char*)&s, sizeof(Student));

        cout << "���������� �������? (Y/N): "; cin >> ch; cout << endl;
    } while (ch == 'Y' || ch == 'y');
    f.close();
    cout << endl;
}

void Print(string filename)
{
    ifstream f(filename, ios::binary);
    Student s;
    int i = 0;

    cout << "==============================================================================================================" << endl;
    cout << "| � |  �������  | ���� | ������������ | ���������� | Գ���� | ������������� | ��������� | ������� ������ |" << endl;
    cout << "==============================================================================================================" << endl;

    while (f.read((char*)&s, sizeof(Student)))
    {
        i++;
        cout << "| " << i << " | " << setw(10) << left << s.Prizv
            << " | " << setw(4) << left << s.Kurs 
            << " | " << setw(13) << left << specStr[s.spec];
        cout << " | " << setw(10) << left << s.Math
            << " | " << setw(6) << left << s.Phisic;
        switch (s.spec)
        {
        case KN:
            cout << " | " << setw(13) << left << s.Inform << 
                " | " << setw(10) << left << "" <<
                " | " << setw(15) << left << "" << " |";
            break;
        case IT:
            cout << " | " << setw(13) << left << "" <<
                " | " << setw(10) << left << "" <<
                " | " << setw(15) << left << s.Metod << " |";
            break;
        default:
            cout << " | " << setw(13) << left << "" <<
                " | " << setw(10) << left << s.Pedagogic <<
                " | " << setw(15) << left << "" << " |";
            break;
        }
        cout << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    }
    cout << "==============================================================================================================" << endl;

    f.close();
}

void ExcellentStudentsPercent(string filename)
{
    ifstream f(filename, ios_base::binary);
    Student s;
    int excellentCount = 0, totalStudents = 0;

    while (f.read((char*)&s, sizeof(Student)))
    {
        totalStudents++;
        if (s.Math == 5 && s.Phisic == 5 && (s.Inform == 5 || s.Pedagogic == 5 || s.Metod == 5))
            excellentCount++;
    }
    f.close();

    double percentage = (double)excellentCount / totalStudents * 100;

    cout << "������� ��������, �� ������� �� �������: " << percentage << "%" << endl;
}

void PhysicsGrade5Students(string filename)
{
    ifstream f(filename, ios_base::binary);
    Student s;

    cout << "������� ��������, �� �������� � ������ ������ �5�:" << endl;

    while (f.read((char*)&s, sizeof(Student)))
    {
        if (s.Phisic == 5)
            cout << s.Prizv << endl;
    }

    f.close();
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filename;
    cout << "������ ����� �����: "; cin >> filename;
    int menuItem;
    do {
        cout << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ��������� ����� �� �����" << endl;
        cout << " [3] - ³�������" << endl;
        cout << " [4] - ������ � ������ = 5" << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
        cout << "������ ��������: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            Create(filename);
            break;
        case 2:
            Print(filename);
            break;
        case 3:
            ExcellentStudentsPercent(filename);
            break;
        case 4:
            PhysicsGrade5Students(filename);
            break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! ��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);
}