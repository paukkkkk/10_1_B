#define NOMINMAX
#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <limits>
using namespace std;

enum Speciality { Komp_Nauky, Informatyka, Matem_Econom, Phys_Inform, Trud };

struct Student
{
    string prizv;
    int kurs;
    Speciality speciality;
    int fizyka;
    int matematyka;
    union
    {
        int prohram;
        int chyselni_metody;
        int pedahoh;
    };
};

int InputInt(const string& promt, int minValue, int maxValue);
void Create(Student* p, const int N, const string specialityStr[]);
void Print(const Student* p, const int N, const string specialityStr[]);
int Third(const Student& s);
int Sum(const Student& s);
double Average(const Student& s);
int MinAverageIndex(const Student* p, const int N);
void CountSatisfactory(const Student* p, const int N, int counts[5]);

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    const string specialityStr[] = {
        "Комп'ютерні науки",
        "Інформатика",
        "Математика та економіка",
        "Фізика та інформатика",
        "Трудове навчання"
    };

    int N = InputInt("Введіть N: ", 1, 1000);

    Student* p = new Student[N];

    Create(p, N, specialityStr);
    Print(p, N, specialityStr);
    int imin = MinAverageIndex(p, N);
    cout << "Найменший середній бал (" << fixed << setprecision(2) << Average(p[imin])
        << ") у студента: " << p[imin].prizv << endl << endl;

    int counts[5];
    CountSatisfactory(p, N, counts);
    cout << "Кількість оцінок \"задовільно\" (3) з кожного предмету:" << endl;
    cout << "  Фізика          - " << counts[0] << endl;
    cout << "  Математика      - " << counts[1] << endl;
    cout << "  Програмування   - " << counts[2] << endl;
    cout << "  Чисельні методи - " << counts[3] << endl;
    cout << "  Педагогіка      - " << counts[4] << endl;

    delete[] p;
    return 0;
}

int InputInt(const string& promt, int minValue, int maxValue)
{
    int x;
    while (true)
    {
        cout << promt;
        if (cin >> x && x >= minValue && x <= maxValue)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "Помилка введіть число від " << minValue << " до " << maxValue << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Create(Student* p, const int N, const string specialityStr[])
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент N " << i + 1 << ":" << endl;

        cout << "Прізвище: ";
        getline(cin, p[i].prizv);
        p[i].kurs = InputInt(" Курс (1-6): ", 1, 6);

        cout << "Спеціальність: " << endl;
        for (int k = 0; k < 5; k++)
            cout << "    " << k << " - " << specialityStr[k] << endl;
        p[i].speciality = (Speciality)InputInt(" Ваш вибір: ", 0, 4);

        p[i].fizyka = InputInt("     Фізика (1-5): ", 1, 5);
        p[i].matematyka = InputInt("     Математика (1-5): ", 1, 5);

        switch (p[i].speciality)
        {
        case Komp_Nauky:
            p[i].prohram = InputInt("     Програмування (1-5): ", 1, 5);
            break;
        case Informatyka:
            p[i].chyselni_metody = InputInt("     Чисельні методи (1-5): ", 1, 5);
            break;
        default:
            p[i].pedahoh = InputInt("     Педагогіка (1-5): ", 1, 5);
            break;
        }
        cout << endl;
    }
}

void Print(const Student* p, const int N, const string specialityStr[])
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    const string line(124, '=');
    const string dash(124, '-');
    cout << "Таблиця успішності студентів:" << endl;
    cout << line << endl;

    cout << "| № |    Прізвище    | Курс |      Спеціальність      | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;

    cout << dash << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(1) << right << i + 1
            << " | " << setw(14) << left << p[i].prizv
            << " | " << setw(4) << right << p[i].kurs
            << " | " << setw(23) << left << specialityStr[p[i].speciality]
            << " | " << setw(6) << right << p[i].fizyka
            << " | " << setw(10) << right << p[i].matematyka;

        switch (p[i].speciality)
        {
        case Komp_Nauky:
            cout << " | " << setw(13) << right << p[i].prohram
                << " | " << setw(15) << right << ""
                << " | " << setw(10) << right << "" << " |";
            break;
        case Informatyka:
            cout << " | " << setw(13) << right << ""
                << " | " << setw(15) << right << p[i].chyselni_metody
                << " | " << setw(10) << right << "" << " |";
            break;
        default:
            cout << " | " << setw(13) << right << ""
                << " | " << setw(15) << right << ""
                << " | " << setw(10) << right << p[i].pedahoh << " |";
            break;
        }
        cout << endl;
    }
    cout << line << endl << endl;
}

int Third(const Student& s)
{
    switch (s.speciality)
    {
    case Komp_Nauky:
        return s.prohram;
    case Informatyka:
        return s.chyselni_metody;
    default:
        return s.pedahoh;
    }
}

int Sum(const Student& s)
{
    return s.fizyka + s.matematyka + Third(s);
}

double Average(const Student& s)
{
    return Sum(s) / 3.0;
}

int MinAverageIndex(const Student* p, const int N)
{
    int imin = 0;
    for (int i = 1; i < N; i++)
        if (Sum(p[i]) < Sum(p[imin]))
            imin = i;
    return imin;
}

void CountSatisfactory(const Student* p, const int N, int counts[5])
{
    for (int k = 0; k < 5; k++)
        counts[k] = 0;
    for (int i = 0; i < N; i++)
    {
        if (p[i].fizyka == 3)
            counts[0]++;
        if (p[i].matematyka == 3)
            counts[1]++;
        if (Third(p[i]) == 3)
            switch (p[i].speciality)
            {
            case Komp_Nauky:
                counts[2]++; break;
            case Informatyka:
                counts[3]++; break;
            default:
                counts[4]++; break;
            }
    }
}

