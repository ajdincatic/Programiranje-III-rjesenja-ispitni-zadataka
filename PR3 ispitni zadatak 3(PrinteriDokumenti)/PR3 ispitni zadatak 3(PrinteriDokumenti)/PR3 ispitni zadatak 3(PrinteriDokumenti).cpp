#include<iostream>
#include<vector>
#include<string>
#include<thread>
#include<algorithm>
#include<functional>
#include<regex>
#include<mutex>
#include<exception>
#include<iterator>
using namespace std;
const char *crt = "\n---------------------------------------\n";
mutex m;

class DatumVrijeme {
	int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);

	}
	DatumVrijeme(const DatumVrijeme& d) {
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
		_sati = new int(*d._sati);
		_minuti = new int(*d._minuti);
	}
	DatumVrijeme& operator=(const DatumVrijeme& d) {
		if (this != &d) {
			delete _dan;
			delete _mjesec;
			delete _godina;
			delete _sati;
			delete _minuti;
			_dan = new int(*d._dan);
			_mjesec = new int(*d._mjesec);
			_godina = new int(*d._godina);
			_sati = new int(*d._sati);
			_minuti = new int(*d._minuti);
		}
		return *this;
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	bool JesuLiIstiDatumi(const DatumVrijeme& d1)const {
		return (*d1._dan == *_dan && *d1._mjesec == *_mjesec && *d1._godina == *_godina && *d1._sati == *_sati);
	}
	friend ostream& operator<< (ostream &COUT, DatumVrijeme &obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
};

template<class T1, class T2 = int>
class FITKolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutno;
public:
	FITKolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	FITKolekcija(const FITKolekcija &f) {
		_trenutno = f._trenutno;
		_elementi1 = new T1[f._trenutno];
		_elementi2 = new T2[f._trenutno];
		for (size_t i = 0; i < f._trenutno; i++)
		{
			_elementi1[i] = f._elementi1[i];
			_elementi2[i] = f._elementi2[i];
		}
	}
	~FITKolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}
	void Dodaj(const T1& el1, const T2& el2) {
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[]_elementi1;
		delete[]_elementi2;
		temp1[_trenutno] = el1;
		temp2[_trenutno++] = el2;
		_elementi1 = temp1;
		_elementi2 = temp2;
	}
	void Sortiraj() {
		for (size_t i = 0; i < _trenutno - 1; i++)
		{
			for (size_t j = i + 1; j < _trenutno; j++)
			{
				if (_elementi1[i] > _elementi1[j]) {
					swap(_elementi1[i], _elementi1[j]);
					swap(_elementi2[i], _elementi2[j]);
				}
			}
		}
	}
	void DodajNaLokaciju(const T1& el1, const T2& el2, int lokacija) {
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (i == lokacija) {
				_elementi1[i] = el1;
				_elementi2[i] = el2;
			}
		}
	}

	/*METODA GetJedinstveni VRAĆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE
	SADRŽE DUPLIKATE (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2).
	ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/

	FITKolekcija *GetJedinstveni() {
		FITKolekcija *k = new FITKolekcija;
		bool imaDupli = false;
		for (size_t i = 0; i < _trenutno; i++)
		{
			for (size_t j = 0; j < k->GetTrenutno(); j++)
			{
				if (k->GetT1()[j] == _elementi1[i] && k->GetT2()[j] == _elementi2[i]) {
					imaDupli = true;
					break;
				}
			}
			if (!imaDupli) {
				k->Dodaj(_elementi1[i], _elementi2[i]);
			}
			imaDupli = false;
		}
		return k;
	}
	FITKolekcija& operator=(const FITKolekcija& k) {
		if (this != &k) {
			_trenutno = k._trenutno;
			delete[]_elementi1;
			delete[]_elementi2;
			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];
			for (size_t i = 0; i < k._trenutno; i++)
			{
				_elementi1[i] = k._elementi1[i];
				_elementi2[i] = k._elementi2[i];
			}
		}
		return *this;
	}
	T1 * GetT1() { return _elementi1; }
	T2 * GetT2() { return _elementi2; }
	int GetTrenutno() { return _trenutno; }

	friend ostream& operator<<(ostream &COUT,const FITKolekcija &obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};

enum vrstaDokumenta { PDF, DOC, TXT, HTML };
const char *CharVrstaDokumenta[] = { "PDF","DOC","TXT","HTML" };

class Dokument {
	vrstaDokumenta _vrsta;
	string _naziv;
	string _sadrzaj;
	int _brojStranica;

public:
	Dokument() { _brojStranica = 0; }
	Dokument(vrstaDokumenta vrsta, string naziv) {
		_naziv = naziv; _vrsta = vrsta; _brojStranica = 0;
	}

	string GetNaziv()const { return _naziv; };
	string GetSadrzaj()const { return _sadrzaj; };
	vrstaDokumenta GetVrsta() { return _vrsta; };
	void UvecajBrojStranica() { _brojStranica++; }
	int GetBrojStranica() { return _brojStranica; }
	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREĐUJE PRILIKOM DODAVANJA SADRŽAJA. 
	//ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUČUJUĆI I RAZMAKE
	void DodajSadrzaj(string sadrzaj) {
		_sadrzaj += " " + sadrzaj;
		_brojStranica = _sadrzaj.length() / 30 + (int)(_sadrzaj.length() % 30 != 0);
	}
	friend ostream & operator<<(ostream&COUT, Dokument & obj) {
		COUT << obj._naziv << "." << CharVrstaDokumenta[obj._vrsta] << " (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
		return COUT;
	}
};

class Uredjaj {
protected:
	char * _proizvodjac;
	char * _model;
public:
	Uredjaj(const char * proizvodjac,const char * model) {
		int vel = strlen(proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, proizvodjac);
		vel = strlen(model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, model);
	}
	Uredjaj(const Uredjaj &u) {
		int vel = strlen(u._proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, u._proizvodjac);
		vel = strlen(u._model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, u._model);
	}
	~Uredjaj() {
		delete[] _proizvodjac; _proizvodjac = nullptr;
		delete[] _model; _model = nullptr;
	}
	friend ostream & operator<<(ostream&COUT, Uredjaj & obj) {
		COUT << obj._proizvodjac << "." << obj._model << endl;
		return COUT;
	}
};

class Printer : public Uredjaj {
	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
	vector<string> _zabranjeneRijeci;

	void Print(string sadrzaj) {
		m.lock();
		cout << sadrzaj << endl;
		m.unlock();
	}

public:
	Printer(const char *proizvodjac, const char * model) :Uredjaj(proizvodjac, model)
	{}
	//Printer(const Printer &p) :Uredjaj(p), _printaniDokumenti(p._printaniDokumenti), _zabranjeneRijeci(p._zabranjeneRijeci) {}
	FITKolekcija<DatumVrijeme, Dokument> & GetPrintaniDokumenti() { return _printaniDokumenti; };
	vector<string> & GetZabranjeneRijeci() { return _zabranjeneRijeci; };
	// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
	void DodajZabranjenuRijec(string zabranjenaRijec) {
		for (vector<string>::iterator it = _zabranjeneRijeci.begin(); it != _zabranjeneRijeci.end(); it++)
		{
			if (*it == zabranjenaRijec)
				return;
		}
		_zabranjeneRijeci.push_back(zabranjenaRijec);
	}
	/*
		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEĆA PRAVILA:
		1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr: ispitPRIII.doc
		NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
		2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
		ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
		SADRŽAJ DOKUMENTA KOJI SE PRINTA
	*/
	void Printaj(const DatumVrijeme& datum, const Dokument& doc) {

		_printaniDokumenti.Dodaj(datum, doc);

		string pravilo = "([A-Za-z]{5,15})(\\.)(doc|txt|pdf|html)";
		
		if (!regex_match(doc.GetNaziv(), regex(pravilo)))
			throw exception("Naziv nije u adekvatnom formatu");

		pravilo = "(";
		for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
		{
			pravilo += _zabranjeneRijeci[i];
			if (i < _zabranjeneRijeci.size() - 1)
				pravilo += "|";
		}
		pravilo += ")";
		if (regex_search(doc.GetSadrzaj(), regex(pravilo)))
			throw exception("Sadrzaj posjeduje nedozvoljenu rijec");

		thread t(&Printer::Print, this, doc.GetSadrzaj());
		t.join();
	}
	//KOD POREĐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	float GetProsjecanBrojStranicaPoDatumu(const DatumVrijeme& d) {
		int brojStranicaNaDatum = 0;
		int ukupanBrojStranica = 0;
		for (size_t i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			if (d.JesuLiIstiDatumi(_printaniDokumenti.GetT1()[i]))
			{
				brojStranicaNaDatum += _printaniDokumenti.GetT2()[i].GetBrojStranica();
			}
			ukupanBrojStranica += _printaniDokumenti.GetT2()[i].GetBrojStranica();
		}
		return (float)ukupanBrojStranica / brojStranicaNaDatum;
	}

	string GetTopZabranjenuRijec() {
		int b = 0;
		int naj = 0;
		string topRijec = "";
		for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
		{
			for (size_t j = 0; j < _printaniDokumenti.GetTrenutno(); j++)
			{
				if (strstr(_printaniDokumenti.GetT2()[j].GetSadrzaj().c_str(), _zabranjeneRijeci[i].c_str()) != nullptr)
					b++;
			}
			if (b > naj) {
				naj = b;
				topRijec = _zabranjeneRijeci[i];
			}
		}
		return topRijec;
	}
	//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	void UkloniDokumente() {
		bool ukloni = false;
		FITKolekcija<DatumVrijeme, Dokument> kol;
		for (size_t i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			string pravilo = "([:alpha:]{5,15})(\\.)(doc|txt|pdf|html)";

			if (!regex_match(_printaniDokumenti.GetT2()[i].GetNaziv(), regex(pravilo)))
				ukloni = true;

			pravilo = "(";
			for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
			{
				pravilo += _zabranjeneRijeci[i];
				if (i < _zabranjeneRijeci.size() - 1)
					pravilo += "|";
			}
			pravilo += ")";
			if (regex_search(_printaniDokumenti.GetT2()[i].GetSadrzaj(), regex(pravilo)))
				ukloni = true;

			if (!ukloni) {
				kol.Dodaj(_printaniDokumenti.GetT1()[i], _printaniDokumenti.GetT2()[i]);
			}
		}
		_printaniDokumenti = kol;
	}
};


void main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/

#pragma region TestiranjeDatumVrijeme
	DatumVrijeme danas(1, 2, 2017, 10, 15);
	DatumVrijeme sutra(danas);
	DatumVrijeme prekosutra(4, 5, 2018, 10, 15);
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region FITKolekcija
	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);

	cout << brojevi << crt;
	//SORTIRANJE ČLANOVA KOLEKCIJE SE VRŠI U RASTUĆEM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	brojevi.Sortiraj();
	cout << brojevi << crt;
	//BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
	brojevi.DodajNaLokaciju(v109, v6, 2);
	cout << brojevi << crt;
	brojevi.Sortiraj();
	cout << brojevi << crt;
	/*METODA GetJedinstveni VRAĆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE 
	SADRŽE DUPLIKATE (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2). 
	ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/
	FITKolekcija<int, int> * jedinstveni = brojevi.GetJedinstveni();
	cout << *jedinstveni << crt;
	*jedinstveni = brojevi;
	cout << *jedinstveni << crt;
	delete jedinstveni;

	Dokument ispitPRIII(DOC, "ispitPRIII.doc");
	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREĐUJE PRILIKOM DODAVANJA SADRŽAJA. 
	//ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUČUJUĆI I RAZMAKE
	ispitPRIII.DodajSadrzaj("NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO RE");
	cout << "Broj stranica -> " << ispitPRIII.GetBrojStranica() << endl;
	Dokument ispitBaze(DOC, "ispitBaze.doc");
	ispitBaze.DodajSadrzaj("PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT");
	cout << ispitBaze << endl;//ISPISUJE SVE DOSTUPNE PODATKE O DOKUMENTU

	Printer hp3200("HP", "3200");
	//PRINTER NEĆE DOZVOLITI PRINTANJE DOKUMENATA U ČIJEM SADRŽAJU SE NALAZI NEKA OD ZABRANJENIH RIJEČI
	hp3200.DodajZabranjenuRijec("RE");// :)
	hp3200.DodajZabranjenuRijec("RAT");
	hp3200.DodajZabranjenuRijec("UBITI");
	hp3200.DodajZabranjenuRijec("RE");// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
	hp3200.DodajZabranjenuRijec("MRZITI");
	try
	{
		/*
		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEĆA PRAVILA:
		1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr: ispitPRIII.doc
		NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
		2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
		ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
		SADRŽAJ DOKUMENTA KOJI SE PRINTA
		*/
		hp3200.Printaj(danas, ispitBaze);
		hp3200.Printaj(prekosutra, ispitPRIII);

		/*
		IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORIŠTENJE sleep_for FUNKCIJE
		VODITI RAČUNA O DIJELJENJU ZAJEDNIČKIH RESURSA
		*/

	}
	catch (exception& err)
	{
		cout << err.what() << endl;
	}

	//KOD POREĐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;

	Printer hp4000(hp3200);
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
	hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	cout << hp4000 << crt;

#pragma endregion

	system("pause");
}