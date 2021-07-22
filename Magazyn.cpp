#include <iostream>
#include <fstream>
#include <string>

using namespace std;

fstream baza_danych;

int ilosclini;  // ilosc rekordow w bazie danych
string* nazwa;  // tablica nazw
int* ilosc;     // tablica ilosc
double* cena;   // tablica cen
double cena_szt;// cena za 1szt


void separator() // ------
{
    cout << "\n----------------\n" << endl;
}
void wielkosc_bazy() // dynamicznie zmienia wielkosc bazy danych
{
    nazwa = new string[ilosclini];
    ilosc = new int[ilosclini];
    cena = new double[ilosclini];
}
void sprawdzenie_pliku() // sprawdza i tworzy plik bazy danych
{
    baza_danych.open("magazyn.txtmag", ios::in | ios::out);

    if (baza_danych.is_open())
    {
        cout << "Uzyskalem dostep do pliku";
        separator();
    }
    else
    {
        cout << "Nie moge uzyskac dostepu do pliku";
        baza_danych.open("magazyn.txtmag", ios::out);
        baza_danych.close();
        baza_danych.open("magazyn.txtmag", ios::in | ios::out);
        baza_danych << "nowy" << "\t" << 1 << "\t" << 1;
        separator();
        sprawdzenie_pliku();
    }
    baza_danych.close();
}
void ilosc_lini() // sprawadza dlugosc bazy danych
{
    string linia;
    baza_danych.open("magazyn.txtmag", ios::in | ios::out);
    while (getline(baza_danych, linia))
    {
        ilosclini++;
    }
    baza_danych.close();
    wielkosc_bazy();
}
void wczytywanie_pliku() // wczytuje baze danych do tablicy
{
    baza_danych.open("magazyn.txtmag", ios::in | ios::out);

    while (!baza_danych.eof())
    {
        for (int i = 0; i <= ilosclini - 1; i++)
        {
            baza_danych >> nazwa[i];
            baza_danych >> ilosc[i];
            baza_danych >> cena[i];
        }
    }
    baza_danych.close();
}
void wypisywanie(bool wyswietl_nazwa = false, bool wyswietl_ilosc = false, bool wyswietl_cena = false) // wypisuje baze danych
{
    for (int i = 0; i <= ilosclini - 1; i++)
    {
        if (wyswietl_nazwa == true)
        {
            cout << i + 1 << ") " << nazwa[i] << endl;
        }
        if (wyswietl_ilosc == true)
        {
            cout << ilosc[i] << " szt" << endl;
        }
        if (wyswietl_cena == true)
        {
            cout << cena[i] << " zl" << endl;
            cout << "Cena za szt: ";
            cena_szt = cena[i] / ilosc[i];
            cout.precision(3);
            cout << cena_szt << " zl" << endl << endl;
            cout.precision(10);
        }
    }
}
void menu() // menu i glowna czesc programu
{
    int opcja = 0;
    int ktory = -1;
    int ile = 0;
    string produkt = "";
    double wartosc = 0;


    cout << "1) Pokaz magazyn" << endl;
    cout << "2) Dodaj ilosc" << endl;
    cout << "3) Odejmij ilosc" << endl;
    cout << "4) Dodaj nowy przedmiot" << endl << endl;
    cout << "Wybierz odpowiednia opcje (1-4): ";
    cin >> opcja;
    separator();

    while (opcja > 4)
    {
        cout << "Bledna opcja, podaj jeszcze raz:";
        cin >> opcja;
    }

    switch (opcja)
    {
    case 1:

        system("cls");
        wypisywanie(true, true, true);
        separator();
        system("PAUSE");
        system("cls");
        menu();

        break;
    case 2:
        system("cls");
        wypisywanie(true);
        separator();
        cout << "Do ktorej pozycji dodac dostawe?" << endl;
        cin >> ktory;
        ktory -= 1;
        cout << "Ile szt dodac?" << endl;
        cin >> ile;
        ilosc[ktory] += ile;
        cout << "Cena dostawy:" << endl;
        cin >> wartosc;
        cena[ktory] += wartosc;

        baza_danych.open("magazyn.txtmag", ios::in | ios::out);
        for (int i = 0; i <= ilosclini - 1; i++)
        {
            baza_danych << nazwa[i] << "\t" << ilosc[i] << "\t" << cena[i] << "\n";
        }
        baza_danych.close();
        system("cls");
        menu();
        break;
    case 3:
        system("cls");
        wypisywanie(true);
        separator();
        cout << "Od ktorej pozycji odjac dostawe?" << endl;
        cin >> ktory;
        ktory -= 1;
        cout << "Ile szt odjac?" << endl;
        cin >> ile;
        ilosc[ktory] -= ile;
        cena[ktory] -= cena_szt * ile;

        baza_danych.open("magazyn.txtmag", ios::in | ios::out);
        for (int i = 0; i <= ilosclini - 1; i++)
        {
            baza_danych << nazwa[i] << "\t" << ilosc[i] << "\t" << cena[i] << "\n";
        }
        baza_danych.close();
        system("cls");
        menu();
        break;

    case 4:
        system("cls");
        cout << "Podaj nazwe nowego przedmiotu: ";
        ilosclini++;
        delete[] nazwa;
        delete[] ilosc;
        delete[] cena;
        wielkosc_bazy();
        wczytywanie_pliku();
        cout << ilosclini << ") ";
        cin >> produkt;
        nazwa[ilosclini - 1] = produkt;
        ilosc[ilosclini - 1] = 0;
        cena[ilosclini - 1] = 0;
        baza_danych.open("magazyn.txtmag", ios::in | ios::out);

        for (int i = 0; i <= ilosclini - 1; i++)
        {
            baza_danych << nazwa[i] << "\t" << ilosc[i] << "\t" << cena[i] << "\n";
        }

        baza_danych.close();
        system("cls");
        menu();
        break;
    }
}
int main() // wywolanie menu
{
    cout << "Witamy w magazynie v0.1";
    separator();
    sprawdzenie_pliku();
    ilosc_lini();
    wczytywanie_pliku();
    menu();
    return 0;
}