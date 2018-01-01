// Karol Nowak 
// Grupa: I6X1N1 
// Nr albumu: 67471

#include <iostream>
#include <fstream>

using namespace std;

int funkcja_ile(string nazwa_pliku_wejsciowego,ifstream &plik_odczyt,ofstream &plik_zapis);               // .ile
int funkcja_licz_msort(string nazwa_pliku_wejsciowego,ifstream &plik_odczyt,ofstream &plik_zapis);        // .licz, .msort

int main(int argc, char *argv[]) {   
    system("cls");
    cout << "ZADANIE 1" << endl;
    cout << "Program wyznaczajacy model zrodla informacji dla dowolnego pliku." << endl << endl;
    
    string test, nazwa_pliku_wejsciowego;
    ifstream plik_odczyt,plik_odczyt1,plik_odczyt2;
    ofstream plik_zapis;
    int RetCode;

    	if (argc!=2) {
    		cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
    		return -1;
    	}
        else {
		nazwa_pliku_wejsciowego = argv[1];
        cout << "Wczytany plik: " << nazwa_pliku_wejsciowego << endl << endl;
        }

	cout << "Obliczanie calkowitej liczby symboli(bajtow) wystepujacych w pliku wejsciowym." << endl;
	RetCode = funkcja_ile(nazwa_pliku_wejsciowego,plik_odczyt1,plik_zapis);
	if(RetCode==-1) return -1;
    
	cout << "Wyznaczenie tabeli symboli z liczba wystapien oraz sortowanie." << endl << endl;
	RetCode = funkcja_licz_msort(nazwa_pliku_wejsciowego,plik_odczyt2,plik_zapis);
    if(RetCode==-1) return -1;
    
    cout << endl << "Pliki z rozszerzeniami .ile, .licz, .msort zotaly zapisane." << endl;
}

int funkcja_ile(string nazwa_pliku_wejsciowego,ifstream &plik_odczyt,ofstream &plik_zapis) {
    int n=0;
	string nowa_nazwa_pliku;
	bool wynik;
	unsigned char bajt_8b;

	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(),ios::binary);
	wynik=plik_odczyt.is_open();
    	if (!wynik){
    		cout << "Blad otwierania pliku odczytywanego w trybie binarnym!" << endl;
    		return -1;
    	}
    	
    nowa_nazwa_pliku = nazwa_pliku_wejsciowego.substr(0,nazwa_pliku_wejsciowego.find_last_of("."))+".ile";
    plik_zapis.open(nowa_nazwa_pliku.c_str(),ios::binary);
	wynik=plik_zapis.is_open();
    	if (!wynik){
    		cout << "Blad otwierania pliku do zapisu w trybie binarnym!" << endl;
    		return -1;
    	}
// .ile
	while(true){
		bajt_8b=plik_odczyt.get();
		wynik=plik_odczyt.good();
		if(!wynik) break;
        n++;
	}

	cout << endl << "Liczba wszystkich symboli: " << n << endl << endl;
	plik_zapis <<"Liczba wszystkich symboli: "<< n << endl;

	plik_odczyt.close();
	plik_zapis.close();

	return 0;
}

int funkcja_licz_msort(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis) {
	string nowa_nazwa_pliku;
	string nowa_nazwa_pliku2;
	bool wynik;
    int j,i;
    int pom;                                                    // zmienna pomocniczna do sortowania
    char c;
	unsigned char bajt_8b;

	struct symbole {
        int symbol;
        int licznik;
	};
	
    symbole tab[256];

	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);
	wynik=plik_odczyt.is_open();
    	if (!wynik){
    		cout << "Blad otwierania pliku odczytywanego do tablicy!" << endl;
    		return -1;
    	}

     for (i=0;i<256;i++){
         tab[i].licznik=0;          
         tab[i].symbol=i;                                 
     }
// .licz
   while(bajt_8b=plik_odczyt.get()) {
		wynik=plik_odczyt.good();
		if (!wynik) break;
        c=int(bajt_8b);
        for(j=0;j<256;j++){
            if (tab[j].symbol==c) tab[j].licznik++;
        }
	}
	plik_odczyt.close();

	nowa_nazwa_pliku=nazwa_pliku_wejsciowego.substr(0,nazwa_pliku_wejsciowego.find_last_of("."))+".licz";
	plik_zapis.open(nowa_nazwa_pliku.c_str());
	wynik=plik_zapis.is_open();
	if (!wynik){
		cout << "Blad otwierania pliku do zapisu tablicy!" << endl;
		return -1;
	}
    cout <<"TABELA SYMBOLI" << endl;
	for (int i=0;i<256;i++) {
        if (tab[i].licznik!= 0) {
		plik_zapis << tab[i].symbol <<  " " << tab[i].licznik <<endl;
        cout << tab[i].symbol <<  " " << tab[i].licznik <<endl;
        }
	}
    cout << endl;
	plik_zapis.close();

	nowa_nazwa_pliku2=nazwa_pliku_wejsciowego.substr(0, nazwa_pliku_wejsciowego.find_last_of("."))+".msort";
	plik_zapis.open(nowa_nazwa_pliku2.c_str());
    wynik=plik_zapis.is_open();
    	if (!wynik){
    		cout << "Blad otwierania pliku do zapisu tablicy!" << endl;
    		return -1;
    	}	  
// sortowanie, .msort                     
    for (i=255;i>0;i--) {
        for (j=1;j<=i;j++){
            if (tab[j-1].licznik<tab[j].licznik){
                pom=tab[j-1].licznik, tab[j-1].licznik=tab[j].licznik, tab[j].licznik=pom;
                pom=tab[j-1].symbol, tab[j-1].symbol=tab[j].symbol, tab[j].symbol=pom; 
            }
        }
    }
    
    cout << endl << "POSORTOWANA TABELA SYMBOLI" <<endl;
        for (int i=0;i<256;i++){
            if (tab[i].licznik!= 0) {
                cout << tab[i].symbol << " " << tab[i].licznik <<endl;
                plik_zapis << tab[i].symbol << " " << tab[i].licznik <<endl;
            }
        }

return 0;
}
