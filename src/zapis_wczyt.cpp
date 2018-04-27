#include "zapis_wczyt.h"

#include "gra.h"

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>

std::string utworzZnacznik(TypZnacznika typ, void* dane)
{
	char buffer[512];
	
	std::string znacznik = "";
	znacznik.append("{");
	
	sprintf(buffer, "%x", (int)typ);
	znacznik.append(buffer);
	
	switch(typ)
	{
		case TypZnacznika::STARTUJACY:
		{
			TypDokumentu* typ_wsk = (TypDokumentu*)dane;
			sprintf(buffer, ";%x", (int)(*typ_wsk));
			
			znacznik.append(buffer);
		} break;
		case TypZnacznika::KONCZACY:
		{
			// znacznik konczący ma tylko swój typ
		} break;
		
		// F O R M A T   Z A P I S U   S P O L E K
		case TypZnacznika::SPOLKA:
		{
			Spolka* spl = (Spolka*)dane;
			sprintf(buffer, ";%x;%s;%x;%x",
				spl->typ_spolki,
				spl->nazwa.c_str(),
				spl->wartosc_akcji,
				spl->dostepne_akcje );
			
			znacznik.append(buffer);
		} break;
		
		// F O R M A T   Z A P I S U   W A L U T
		case TypZnacznika::WALUTA:
		{
			Waluta* waluta = (Waluta*)dane;
			sprintf(buffer, ";%s;%.2f", waluta->nazwa.c_str(), waluta->wartosc);
			
			znacznik.append(buffer);
		} break;
		case TypZnacznika::STAN_GRY:
		{
			Gra* gra = (Gra*)dane;
			sprintf(buffer, ";%x", gra->_tura);
			
			znacznik.append(buffer);
		} break;
	}
	
	znacznik.append("}");
	
	return znacznik;
}

void zapiszDane(const char* sciezka, TypDokumentu typ, void* dane)
{
	std::ofstream plik;
	
	plik.open(sciezka, std::ofstream::out);
	if( plik.fail() )
	{
		fprintf(stderr, "Błąd przy tworzeniu nowego pliku: %s\n", sciezka);
		return;
	}
	
	plik << utworzZnacznik(TypZnacznika::STARTUJACY, &typ) << std::endl;
	
	switch(typ)
	{
		case TypDokumentu::ZAPISU_ROZGRYWKI:
		{
			Gra* gra = (Gra*)dane;
			
			plik << utworzZnacznik(TypZnacznika::STAN_GRY, gra) << std::endl;
			
			for( unsigned int i = 0; i < gra->_spolki.size(); ++i )
			{
				plik << utworzZnacznik(TypZnacznika::SPOLKA, &(gra->_spolki[i])) << std::endl;
			}
			
			for( unsigned int i = 0; i < gra->_waluty.size(); ++i )
			{
				plik << utworzZnacznik(TypZnacznika::WALUTA, &(gra->_waluty[i])) << std::endl;
			}
			
		} break;
		case TypDokumentu::KONFIGURACYJNY:
		{
			
		} break;
		case TypDokumentu::NIEZDEFINIOWANY:
		{
		} break;
	}
	
	plik << utworzZnacznik(TypZnacznika::KONCZACY, nullptr) << std::endl;
	
	plik.close();
}

void rozdzielArgZnacznika(const char* tresc, std::vector<std::string>& docelowa_lista)
{
	if( !docelowa_lista.empty() )
	{
		docelowa_lista.clear();
	}
	
	unsigned int dlugosc_lancucha = strlen(tresc);
	
	std::string tymczasowy = "";
	bool koniec_zn = false;
	
	for( unsigned int i = 0; i <= dlugosc_lancucha || !koniec_zn; ++i )
	{
		switch(tresc[i])
		{
			case ';':
				docelowa_lista.push_back(tymczasowy);
				tymczasowy.clear();
				break;
			case '{':
				// ...
				break;
			case '}':
				koniec_zn = true;
				docelowa_lista.push_back(tymczasowy);
				tymczasowy.clear();
				break;
			default:
				tymczasowy += tresc[i];
				break;
		}
	}
}

TypZnacznika odczytajTypZnacznika(const std::vector<std::string>& argumenty)
{
	int ityp = 0;
	sscanf(argumenty[0].c_str(), "%x", &ityp);
	return ((TypZnacznika)ityp);
}

void* odczytajZnacznik(const std::vector<std::string>& argumenty, TypZnacznika typ, void* obiekt_docelowy)
{
	int iliczba = 0;
	float fliczba = 0.0f;
	
	switch(typ)
	{
		case TypZnacznika::STARTUJACY:
		{
			if( argumenty.size() == 2 )
			{
				TypDokumentu* typ_dok = (TypDokumentu*)obiekt_docelowy;
				
				sscanf(argumenty[1].c_str(), "%x", &iliczba);
				*typ_dok = (TypDokumentu)iliczba;
			}
		} break;
		case TypZnacznika::KONCZACY:
		{
		} break;
		
		case TypZnacznika::SPOLKA:
		{
			if( argumenty.size() == 5 )
			{
				Spolka* nowa_spolka = (Spolka*)(obiekt_docelowy);
				
				// typ_spolki
				sscanf(argumenty[1].c_str(), "%x", &iliczba);
				nowa_spolka->typ_spolki = (Spolka::Typ)iliczba;
				
				// nazwa
				nowa_spolka->nazwa = argumenty[2];
				
				// wartość akcji
				sscanf(argumenty[3].c_str(), "%x", &(nowa_spolka->wartosc_akcji));
				
				// dostępne akcje
				sscanf(argumenty[4].c_str(), "%x", &(nowa_spolka->dostepne_akcje));
			}
		} break;
		case TypZnacznika::WALUTA:
		{
			if( argumenty.size() == 3 )
			{
				Waluta* nowa_waluta = (Waluta*)(obiekt_docelowy);
				
				// nazwa
				nowa_waluta->nazwa = argumenty[1].c_str();
				
				// wartość
				sscanf(argumenty[2].c_str(), "%f", &(nowa_waluta->wartosc));
			}
		} break;
		case TypZnacznika::STAN_GRY:
		{
			Gra* gra = (Gra*)obiekt_docelowy;
			
			// tura
			sscanf(argumenty[1].c_str(), "%x", &(gra->_tura));
		} break;
	}
	
	return obiekt_docelowy;
}

void wczytajDane(const char* sciezka, void* obiekt_docelowy)
{
	TypDokumentu typ_dokumentu = TypDokumentu::NIEZIDENTYFIKOWANY;
	
	FILE* plik = nullptr;
	plik = fopen(sciezka, "r");
	if( !plik )
	{
		fprintf(stderr, "Nie udalo sie wczytac pliku (%s)!", sciezka);
	}
	else
	{
		TypZnacznika typ_znacznika = TypZnacznika::NIEZIDENTYFIKOWANY;
		std::string tresc_znacznika = "";
		std::vector<std::string> argumenty;
		bool znaleziono_znacznik = false;
		
		char znak = 0;
		while((znak = getc(plik)) != EOF)
		{
			if( znak == '{' )
				znaleziono_znacznik = true;
			else if( znak == '}' && znaleziono_znacznik )
			{
				znaleziono_znacznik = false;
				tresc_znacznika += znak;
				
				rozdzielArgZnacznika(tresc_znacznika.c_str(), argumenty);
				tresc_znacznika.clear();
				typ_znacznika = odczytajTypZnacznika(argumenty);
				
				if( typ_znacznika == TypZnacznika::STARTUJACY )
				{
					odczytajZnacznik(argumenty, typ_znacznika, &typ_dokumentu);
				}
				
				switch(typ_dokumentu)
				{
					case TypDokumentu::KONFIGURACYJNY:
					{
						
					} break;
					case TypDokumentu::ZAPISU_ROZGRYWKI:
					{
						Gra* gra = (Gra*)obiekt_docelowy;
						
						switch(typ_znacznika)
						{
							case TypZnacznika::KONCZACY:
								break;
							
							case TypZnacznika::SPOLKA:
							{
								Spolka wczytywana_spolka;
								odczytajZnacznik(argumenty, typ_znacznika, &wczytywana_spolka);
								gra->dodajSpolke(wczytywana_spolka);
							} break;
							case TypZnacznika::WALUTA:
							{
								Waluta wczytywana_waluta;
								odczytajZnacznik(argumenty, typ_znacznika, &wczytywana_waluta);
								gra->dodajWalute(wczytywana_waluta);
							} break;
							case TypZnacznika::STAN_GRY:
							{
								odczytajZnacznik(argumenty, typ_znacznika, gra);
							} break;
							default:
								break;
						}
					} break;
					case TypDokumentu::NIEZIDENTYFIKOWANY:
					{
						fprintf(stderr, "Błąd wczytywania pliku! Niezidentyfikowany typ pliku!\n");
						fprintf(stderr, "Scieżka do pliku: %s\n", sciezka);
						fclose(plik);
						return;
					} break;
				}
			}
			
			if( znaleziono_znacznik )
			{
				tresc_znacznika += znak;
			}
		}
	}
	
	fclose(plik);
}
