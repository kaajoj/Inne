#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <string>

using namespace std;

void obliczanie (int &crc32, char znak){
	int CRC32 = 0x04c11db7;
    bool flaga = 0;
    char znakpom = 0;
    int tym = 0;

    for (int i=0; i<8;i++){
        if (crc32 & 0x80000000)   // 0x80000000(16) = 10000000000000000000000000000000(2)
			flaga = 1;
        else
			flaga = 0;
        crc32 = crc32 << 1;            // przesuniêcie o jeden
        crc32 = crc32 & 0xfffffffe;   // 0xfffffffe(16) = 11111111111111111111111111111110(2)                                    
        znakpom = znak >> (7-i);   
        znakpom = znakpom & 0x01;
        tym = (int)znakpom;
        crc32 = crc32 | tym;   //dopisanie bitu na koniec
        if (flaga!=0) crc32 = crc32^CRC32;
    }
}


int zapisywanie (string nazwa_pliku_wejsciowego, ofstream &plik_zapis, int crc32){
	string nazwa_pliku_crc32;
	bool flaga;

	nazwa_pliku_crc32 = nazwa_pliku_wejsciowego.substr(0, nazwa_pliku_wejsciowego.find_last_of(".")) + ".crc32";
	plik_zapis.open(nazwa_pliku_crc32.c_str());

	flaga=plik_zapis.is_open();
	if (!flaga){
		cout << "Blad otwierania pliku do zapisu sumy kontrolnej!" << endl;
		return -1;
	}
    cout << endl << "Wyznaczone wartosci CRC-32 dla pliku wejsciowego: " << endl; 

	int pom = crc32;
	unsigned char znakpom = 0;
	int temp = 0;
	int i;
	int j;

	for (i=0, j=0; i<32; i++, j++){
        temp = pom >> (31-i);
        temp = temp & 0x00000001;
        znakpom = znakpom + temp*pow(2,(7-j));
        if (j == 7){
        	j = -1;
        	plik_zapis << znakpom;
        	cout << znakpom;
        	znakpom = 0;
		}
    }
    
	plik_zapis << endl;
    cout << endl;
    cout << "bin: ";
	for (i=0; i<32; i++){
        int temp = pom >> (31-i);
        temp = temp & 0x00000001;

        if (temp==1){
        	plik_zapis <<dec<< 1;
        	cout << 1;
		}
		else {
			plik_zapis <<dec<< 0;
			cout << 0;
		}
    }
	plik_zapis << endl;

	plik_zapis << hex << crc32 << endl;
	plik_zapis << dec << crc32 << endl;

    cout << endl << hex << "hex: " << crc32 << endl;
    cout << dec << "dec: " << crc32 << endl;
    cout << endl << "Zapisywanie wyznaczonych powyzej wartosci CRC-32 do pliku." << endl << endl;
	plik_zapis.close();
}

int main(int argc, char *argv[]) {
    system("cls");
	string nazwa_pliku_wejsciowego;

	ifstream plik_odczyt;
	ofstream plik_zapis;

	int crc32 = 0;
	char znak = 0;
	int RetCode;
    bool wynik;

	if (argc<2){
		cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
		return -1;
	}
    
	nazwa_pliku_wejsciowego = argv[1];
	cout << "Plik: " << nazwa_pliku_wejsciowego << endl;
	
	cout << endl << "Obliczanie..." << endl;

	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);

	wynik = plik_odczyt.is_open();
	if (!wynik){
		cout << "Blad otwierania pliku odczytywanego!" << endl;
		return -1;
	}

	while (true){
		znak = plik_odczyt.get();
		obliczanie(crc32, znak);
		wynik = plik_odczyt.good();
		if (!wynik) break;
	}
	plik_odczyt.close();

	for (int i=0;i<4;i++){
		obliczanie(crc32,0);
	}
	zapisywanie (nazwa_pliku_wejsciowego, plik_zapis, crc32);
	return 0;
}
