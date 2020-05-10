#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<iterator>
using namespace std;

enum Predmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski, Muzicko, Fizicko };
enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
const char * ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };
const char * ispisPredmeti[] = { "Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
const char *crt = "\n-------------------------------------------\n";

template<class T1, class T2>
class Kolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutno;
public:
	Kolekcija()
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	Kolekcija(const Kolekcija& k) {
		_elementi1 = new T1[k._trenutno];
		_elementi2 = new T2[k._trenutno];
		for (size_t i = 0; i < k._trenutno; i++)
		{
			_elementi1[i] = k._elementi1[i];
			_elementi2[i] = k._elementi2[i];
		}
		_trenutno = k._trenutno;
	}
	~Kolekcija()
	{
		delete[]_elementi1;
		_elementi1 = nullptr;
		delete[]_elementi2;
		_elementi2 = nullptr;
	}
	Kolekcija operator=(const Kolekcija& k) {
		if (this != &k) {
			delete[]_elementi1;
			delete[]_elementi2;
			_elementi1 = new T1[k._trenutno];
			_elementi2 = new T2[k._trenutno];
			for (size_t i = 0; i < k._trenutno; i++)
			{
				_elementi1[i] = k._elementi1[i];
				_elementi2[i] = k._elementi2[i];
			}
			_trenutno = k._trenutno;
		}
		return *this;
	}
	void AddElement(const T1& el1, const T2& el2) {
		T1 *temp1 = new T1[_trenutno + 1];
		T2 *temp2 = new T2[_trenutno + 1];
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

	void RemoveElement(int lokacija) {
		T1 *temp1 = new T1[_trenutno - 1];
		T2 *temp2 = new T2[_trenutno - 1];
		int j = 0;
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (i != lokacija) {
				temp1[j] = _elementi1[i];
				temp2[j++] = _elementi2[i];
			}
		}
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = temp1;
		_elementi2 = temp2;
		_trenutno--;
	}
	int GetTrenutno() { return _trenutno; }
	T1& GetElement1(int lokacija) {
		if (lokacija < 0 || lokacija >= _trenutno)
			throw exception("Nepostojeci index");
		return _elementi1[lokacija];
	}
	T2& GetElement2(int lokacija) {
		if (lokacija < 0 || lokacija >= _trenutno)
			throw exception("Nepostojeci index");
		return _elementi2[lokacija];
	}

	friend ostream& operator<<(ostream& cout, const Kolekcija& k) {
		for (size_t i = 0; i < k._trenutno; i++)
		{
			cout << k._elementi1[i] << " | " << k._elementi2[i] << endl;
		}
		return cout;
	}
};
class Datum {
	int *_dan, *_mjesec, *_godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}

	Datum(const Datum&obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}
	Datum& operator=(const Datum& obj) {
		if (this != &obj) {
			*_dan = *obj._dan;
			*_mjesec = *obj._mjesec;
			*_godina = *obj._godina;
		}	
		return *this;
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}

	friend ostream& operator<< (ostream &COUT, const Datum &obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};
bool ProvjeriValidnostBrojaTelefona(string telefon) {//globalna funkcija
	/*
	broj telefona treba biti u formatu: +387(61)-222-333
	*/
	string pravilo = "(\\+)(\\d{3})(\\()(\\d{2})(\\))([-]{1})(\\d{3})(\\-)(\\d{3})";
	return regex_match(telefon, regex(pravilo));
}
class Osoba {
protected:
	char * _imePrezime;
	Datum * _datumRodjenja;
	string _brojTelefona;
public:
	Osoba(const char * imePrezime, Datum datum) {
		_imePrezime = new char[strlen(imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
		_datumRodjenja = new Datum(datum);
		_brojTelefona = "";

	}
	Osoba(const Osoba & obj) :_brojTelefona(obj._brojTelefona) {
		_imePrezime = new char[strlen(obj._imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
		_datumRodjenja = new Datum(*obj._datumRodjenja);
	}
	Osoba& operator=(const Osoba& o) {
		if (this != &o) {
			delete[]_imePrezime; 
			_imePrezime = new char[strlen(o._imePrezime) + 1];
			strcpy_s(_imePrezime, strlen(o._imePrezime) + 1, o._imePrezime);
			_brojTelefona = o._brojTelefona;
			delete _datumRodjenja;
			_datumRodjenja = new Datum(*o._datumRodjenja);
		}
		return *this;
	}
	~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }
	char *GatImePrezime() { return _imePrezime; }
	bool setBrojTelefona(string brojTelefona) {
		if (ProvjeriValidnostBrojaTelefona(brojTelefona)) {
			_brojTelefona = brojTelefona;
			return true;
		}
		return false;
	}

};

class Nastavnik :public Osoba {
	Kolekcija<Predmeti, Razredi> * _predmetiRazredi;
public:
	Nastavnik(const char * imePrezime,const Datum datum) :Osoba(imePrezime, datum) {
		_predmetiRazredi = nullptr;
	}
	Nastavnik(const Nastavnik& n) : Osoba(n) {
		if (n._predmetiRazredi != nullptr) {
			_predmetiRazredi = new Kolekcija<Predmeti, Razredi>(*n._predmetiRazredi);
		}
		else
			_predmetiRazredi = nullptr;
	}
	~Nastavnik()
	{
		delete _predmetiRazredi;
		_predmetiRazredi = nullptr;
	}
	Nastavnik& operator=(const Nastavnik& n) {
		if (this != &n) {
			delete _predmetiRazredi;
			Osoba::operator=(n);
			if (n._predmetiRazredi != nullptr)
				_predmetiRazredi = new Kolekcija<Predmeti, Razredi>(*n._predmetiRazredi);
			else
				_predmetiRazredi = nullptr;
		}
		return *this;
	}
	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/
	bool AddPredmetRazred(Predmeti p, Razredi r) {
		if (_predmetiRazredi == nullptr)
			_predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
		int brojac = 0;
		for (size_t i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
		{
			if (_predmetiRazredi->GetElement1(i) == p && _predmetiRazredi->GetElement2(i) == r)
				return false;
			if (_predmetiRazredi->GetElement1(i) == p && _predmetiRazredi->GetElement2(i) != r)
				brojac++;
		}
		if (brojac > 2)
			return false;
		_predmetiRazredi->AddElement(p, r);
		return true;
	}

	bool RemovePredmetRazred(Predmeti p) {
		for (size_t i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
		{
			if (_predmetiRazredi->GetElement1(i) == p) {
				_predmetiRazredi->RemoveElement(i);
				return true;
			}
		}
		return false;
	}
	friend bool operator==(const Nastavnik& l, const Nastavnik& r) {
		return (strcmp(l._imePrezime, r._imePrezime) == 0 && l._brojTelefona == r._brojTelefona);
	}
	Kolekcija<Predmeti, Razredi>& getPredmetiRazredi() { return *_predmetiRazredi; }
};
class Ucenik : public Osoba {
	int _brojUDnevniku;
	Razredi _razred;
	vector<Nastavnik *> _nastavnici;
	Kolekcija<Predmeti, int> _predmetiOcjene;
public:
	Ucenik(const char * imePrezime, const Datum datum, int brojUDnevniku, Razredi r) :Osoba(imePrezime, datum) {
		_brojUDnevniku = brojUDnevniku;
		_razred = r;
	}
	Ucenik(const Ucenik& u) :Osoba(u), _razred(u._razred) {
		_nastavnici = u._nastavnici;
		_brojUDnevniku = u._brojUDnevniku;
		_predmetiOcjene = u._predmetiOcjene;
	}
	vector<Nastavnik *>& getNastavnici() { return _nastavnici; }
	Kolekcija<Predmeti, int>& getPredmetiOcjene() { return _predmetiOcjene; }
	/*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
	/*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
	/*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/

	bool AddNastavnik(Nastavnik& n) {
		bool predaje = false;
		for (size_t j = 0; j < n.getPredmetiRazredi().GetTrenutno(); j++)
		{
			if (n.getPredmetiRazredi().GetElement2(j) == _razred)
				predaje = true;
		}
		for (size_t i = 0; i < _nastavnici.size(); i++)
		{
			if (*_nastavnici[i] == n) {
				return false;
			}
		}
		if (!predaje)
			return false;
		_nastavnici.push_back(&n);
		return true;
	}

	/*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/

	bool AddPredmetOcjenu(Predmeti p, int ocjena) {
		bool postoji = false;
		for (size_t i = 0; i < _nastavnici.size(); i++)
		{
			for (size_t j = 0; j < _nastavnici[i]->getPredmetiRazredi().GetTrenutno(); j++)
			{
				if (_nastavnici[i]->getPredmetiRazredi().GetElement1(j) == p) {
					postoji = true;
				}
			}
		}
		if (!postoji)
			return false;
		_predmetiOcjene.AddElement(p, ocjena);
		return true;
	}

	float GetProsjekByNastavnik(string nastavnik) {
		float pr = 0;
		for (size_t i = 0; i < _nastavnici.size(); i++)
		{
			if (nastavnik == _nastavnici[i]->GatImePrezime()) {
				for (size_t j = 0; j < _predmetiOcjene.GetTrenutno(); j++)
				{
					pr += _predmetiOcjene.GetElement2(j);
				}
				return pr / _predmetiOcjene.GetTrenutno();
			}
		}
		return pr;
	}

	friend ostream& operator<<(ostream&, const Ucenik&);
};

ostream& operator<<(ostream& cout, const Ucenik& u) {
	cout << u._imePrezime << endl;
	cout << *u._datumRodjenja << endl;
	cout << u._brojUDnevniku << endl;
	cout << u._brojTelefona << endl;
	cout << u._predmetiOcjene << endl;
	ostream_iterator<Nastavnik*> out(cout, "\n");
	copy(u._nastavnici.begin(), u._nastavnici.end(), out);

	return cout;
}

void main() {

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
	5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
	6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
	Kolekcija<int, int> kolekcija1;
	int brojElemenata = 15;
	for (size_t i = 0; i < brojElemenata; i++)
		kolekcija1.AddElement(i, i);
	kolekcija1.RemoveElement(0);//uklanja element na osnovu lokacije
	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
	cout << kolekcija1 << endl;
	Kolekcija<int, int> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion
#pragma region TestiranjeNastavnika
	Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
	Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));
	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/
	if (jasmin.AddPredmetRazred(Matematika, I1))
		cout << "Predmeti dodan" << endl;
	if (jasmin.AddPredmetRazred(Historija, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I2))
		cout << "Predmeti dodan" << endl;

	if (adel.AddPredmetRazred(Historija, III1))
		cout << "Predmeti dodan" << endl;

	if (adel.RemovePredmetRazred(Historija))
		cout << "Predmet uklonjen!" << endl;

	Nastavnik goran(adel);
	if (goran == adel)
		cout << "Nastavnici identicni" << endl;
	goran = jasmin;
	if (goran == jasmin)
		cout << "Nastavnici identicni" << endl;

	Kolekcija<Predmeti, Razredi> & predmetiRazredi = jasmin.getPredmetiRazredi();

	if (!jasmin.setBrojTelefona("+38761111222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (!jasmin.setBrojTelefona("+387-61-111-222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (jasmin.setBrojTelefona("+387(61)-111-222"))
		cout << "Broj telefona uspjesno dodan!" << endl;
#pragma endregion

#pragma region TestiranjeUcenika
	Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, III1);
	Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
	Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
	/*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
	/*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
	if (denis.AddNastavnik(jasmin))
		cout << "Nastavnik uspjesno dodan" << endl;
	/*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
	if (denis.AddNastavnik(adel))
		cout << "Nastavnik uspjesno dodan" << endl;
	/*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
	if (denis.AddPredmetOcjenu(Matematika, 3))
		cout << "Ocjena uspjesno dodana" << endl;
	if (denis.AddPredmetOcjenu(Historija, 4))
		cout << "Ocjena uspjesno dodana" << endl;

	vector<Nastavnik*> & nastavnici = denis.getNastavnici();
	cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;

	Kolekcija<Predmeti, int> & uspjeh = denis.getPredmetiOcjene();
	cout << "Denis ima " << uspjeh.GetTrenutno() << " polozenih predmeta" << endl;
	cout << "Prosjecna ocjena kod nastavnika Jasmin Azemovic je " << denis.GetProsjekByNastavnik("Jasmin Azemovic") << endl;

	Ucenik denis2(denis);
	cout << denis2 << endl;

#pragma endregion
	system("pause");
}