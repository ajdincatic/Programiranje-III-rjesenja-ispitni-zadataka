#include<iostream>
#include<vector>
#include<regex>
#include<iterator>
#include<exception>
#include<string>
using namespace std;

class Datum {
	int *_dan, *_mjesec, *_godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum& d) {
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	Datum& operator=(const Datum& d) {
		if (this != &d) {
			delete _dan;
			delete _mjesec;
			delete _godina;
			_dan = new int(*d._dan);
			_mjesec = new int(*d._mjesec);
			_godina = new int(*d._godina);
		}
		return *this;
	}
	friend bool operator==(const Datum& d1, const Datum& d2) {
		return (*d1._dan == *d2._dan && *d1._mjesec == *d2._mjesec && *d1._godina == *d2._godina);
	}
	friend bool operator>(const Datum& d1, const Datum& d2) {
		int days = *d1._dan + *d1._mjesec * 30 + *d1._godina * 365;
		int days_d = *d2._dan + *d2._mjesec * 30 + *d2._godina * 365;
		return days > days_d;
	}
	friend ostream& operator<< (ostream &COUT,const Datum &obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};

class Izuzetak :public exception {
	Datum _datum;//KORISTITE DANASNJI DATUM
	string _funkcija;//FUNKCIJA U KOJOJ JE NASTAO IZUZETAK
	int _linija;//LINIJA CODE-A U KOJOJ JE NASTAO IZUZETAK
public:
	Izuzetak(const char* poruka, const Datum& d, string funkcija, int linija) :exception(poruka), _datum(d) {
		_funkcija = funkcija;
		_linija = linija;
	}
	friend ostream& operator<<(ostream& COUT, const Izuzetak& i) {
		COUT << i.exception::what() << " - " << i._datum << " - " << i._funkcija << " - " << i._linija << endl;
		return COUT;
	}
};

template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max];
	T2 _elementi2[max];
	int * _trenutno;
public:
	Kolekcija() {
		_trenutno = new int(0);
	}
	~Kolekcija()
	{
		delete _trenutno;
		_trenutno = nullptr;
	}
	Kolekcija(const Kolekcija& k) {
		for (size_t i = 0; i < *k._trenutno; i++)
		{
			_elementi1[i] = k._elementi1[i];
			_elementi2[i] = k._elementi2[i];
		}
		_trenutno = new int(*k._trenutno);
	}
	Kolekcija& operator=(const Kolekcija& k) {
		if (this != &k) {
			for (size_t i = 0; i < *k._trenutno; i++)
			{
				_elementi1[i] = k._elementi1[i];
				_elementi2[i] = k._elementi2[i];
			}
			delete _trenutno;
			_trenutno = new int(*k._trenutno);
		}
		return *this;
	}
	void AddElement(const T1& el1, const T2& el2) {
		if ((*_trenutno) == max) {
			throw Izuzetak("Zauzeta kolekcija", Datum(31, 12, 2018), __FUNCTION__, __LINE__);
		}
		_elementi1[(*_trenutno)] = el1;
		_elementi2[(*_trenutno)++] = el2;
	}
	int size()const { return (*_trenutno); }
	int GetTrenutno()const { return (*_trenutno); }
	void SetTrenutnoNa0() { *_trenutno = 0; }
	int GetMax()const { return max; }
	T1& GetElement1(int lokacija) 
	{
		if (lokacija < 0 || lokacija >= (*_trenutno))
		{
			throw Izuzetak("Nepostojeca lokacija", Datum(31, 12, 2018), __FUNCTION__, __LINE__);
		}
		return _elementi1[lokacija]; 
	}
	T2& GetElement2(int lokacija) 
	{
		if (lokacija < 0 || lokacija >= (*_trenutno))
		{
			throw Izuzetak("Nepostojeca lokacija", Datum(31, 12, 2018), __FUNCTION__, __LINE__);
		}
		return _elementi2[lokacija]; 
	}
	T1& operator[](int lokacija) {
		if (lokacija < 0 || lokacija >= (*_trenutno))
		{
			throw Izuzetak("Nepostojeca lokacija", Datum(31, 12, 2018), __FUNCTION__, __LINE__);
		}
		return _elementi1[lokacija];
	}
	friend ostream& operator<< (ostream& COUT, const Kolekcija& k) {
		for (size_t i = 0; i < (*k._trenutno); i++)
			COUT << k._elementi1[i] << " - " << k._elementi2[i] << endl;
		return COUT;
	}
};

enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
const char * CharKursevi[] = { "HtmlCSSJavaScript", "SoftwareEngeneeringFundamentals", "MasteringSQL", "WindowsSecurity" };

class Kurs {
	enumKursevi _kurs;
	Datum _pocetak;
	Datum _kraj;
	char * _imePredavaca;
public:
	Kurs() :_imePredavaca(nullptr) {}
	Kurs(enumKursevi kurs, const char*predavac, const Datum& pocetak, const Datum& kraj) {
		_kurs = kurs;
		_pocetak = pocetak;
		_kraj = kraj;
		int size = strlen(predavac) + 1;
		_imePredavaca = new char[size];
		strcpy_s(_imePredavaca, size, predavac);
	}
	Kurs(const Kurs& k) {
		_kurs = k._kurs;
		_pocetak = k._pocetak;
		_kraj = k._kraj;
		int size = strlen(k._imePredavaca) + 1;
		_imePredavaca = new char[size];
		strcpy_s(_imePredavaca, size, k._imePredavaca);
	}
	~Kurs()
	{
		delete[]_imePredavaca;
		_imePredavaca = nullptr;
	}
	Datum& GetPocetak() { return _pocetak; }
	Datum& GetKraj() { return _kraj; }
	Kurs& operator=(const Kurs& k) {
		if (this != &k) {
			_kurs = k._kurs;
			_pocetak = k._pocetak;
			_kraj = k._kraj;
			delete[]_imePredavaca;
			int size = strlen(k._imePredavaca) + 1;
			_imePredavaca = new char[size];
			strcpy_s(_imePredavaca, size, k._imePredavaca);
		}
		return *this;
	}
	enumKursevi GetKurs() { return _kurs; }
	char *GetImePredavaca() { return _imePredavaca; }
	friend bool operator==(const Kurs& k1, const Kurs& k2) {
		return (k1._kurs == k2._kurs && strcmp(k1._imePredavaca, k2._imePredavaca) == 0 && k1._pocetak == k2._pocetak && k1._kraj == k2._kraj);
	}
	friend ostream& operator<<(ostream& COUT, const Kurs& k) {
		cout << CharKursevi[k._kurs] << " | " << k._imePredavaca << " | " << k._pocetak << " | " << k._kurs << endl;
		return COUT;
	}
	friend ostream& operator<<(ostream& COUT, const Kurs* k) {
		cout << CharKursevi[k->_kurs] << " | " << k->_imePredavaca << " | " << k->_pocetak << " | " << k->_kurs << endl;
		return COUT;
	}
};

class Polaznik {
	static int ID;
	const int _polaznikID;
	//SVAKOM NOVOM POLAZNIKU AUTOMATSKI DODIJELITI NOVI ID (AUTOINCREMENT) POCEVSI OD BROJA 1
	char * _imePrezime;
	string _kontaktTelefon; //BROJ TELEFONA TREBA BITI U FORMATU (06X)XXX-XXX 
	Kolekcija<Kurs *, int, 10> _uspjesnoOkoncaniKursevi;
	//INT PREDSTAVLJA OSTVARENI PROCENAT NA ISPITU, A JEDAN POLAZNIK MOZE POLOZITI NAJVISE 10 KURSEVA
public:
	Polaznik(const char * imePrezime, string telefon) :_polaznikID(ID++) {
		int size = strlen(imePrezime) + 1;
		_imePrezime = new char[size];
		strcpy_s(_imePrezime, size, imePrezime);
		_kontaktTelefon = telefon;
	}
	Polaznik(const Polaznik &p) :_polaznikID(p._polaznikID), _kontaktTelefon(p._kontaktTelefon) {
		int size = strlen(p._imePrezime) + 1;
		_imePrezime = new char[size];
		strcpy_s(_imePrezime, size, p._imePrezime);
		Polaznik *pol = const_cast<Polaznik*>(&p);
		for (size_t i = 0; i < p._uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
		{
			_uspjesnoOkoncaniKursevi.AddElement(new Kurs(*pol->_uspjesnoOkoncaniKursevi.GetElement1(i)), pol->_uspjesnoOkoncaniKursevi.GetElement2(i));
		}
	}
	~Polaznik() {
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _uspjesnoOkoncaniKursevi.size(); i++)
		{
			delete _uspjesnoOkoncaniKursevi[i];
			_uspjesnoOkoncaniKursevi[i] = nullptr;
		}
	}
	bool operator == (Polaznik &p) {
		if (_uspjesnoOkoncaniKursevi.GetTrenutno() != p._uspjesnoOkoncaniKursevi.GetTrenutno() || strcmp(_imePrezime, p._imePrezime) != 0) 
			return false;
		for (size_t i = 0; i < _uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
			if (_uspjesnoOkoncaniKursevi.GetElement1(i) != p._uspjesnoOkoncaniKursevi.GetElement1(i)) 
				return false;
		return true;
	}
	Polaznik &operator = (Polaznik &p) {
		if (this != &p) {
			int size = strlen(p._imePrezime) + 1;
			_imePrezime = new char[size];
			strcpy_s(_imePrezime, size, p._imePrezime);
			_kontaktTelefon = p._kontaktTelefon;
			for (size_t i = 0; i < _uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
			{
				delete _uspjesnoOkoncaniKursevi.GetElement1(i);
			}
			_uspjesnoOkoncaniKursevi.SetTrenutnoNa0();
			for (size_t i = 0; i < p._uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
				_uspjesnoOkoncaniKursevi.AddElement(new Kurs(*p._uspjesnoOkoncaniKursevi.GetElement1(i)), p._uspjesnoOkoncaniKursevi.GetElement2(i));
		}
		return *this;
	}
	int GetID() { return _polaznikID; }
	Kolekcija<Kurs *, int, 10>& GetKolekcija() { return _uspjesnoOkoncaniKursevi; }
	friend ostream& operator<<(ostream& cout, const Polaznik& p) {
		cout << p._polaznikID << " | " << p._imePrezime << " | " << p._kontaktTelefon << endl;
		cout << p._uspjesnoOkoncaniKursevi << endl;
		return cout;
	}
	friend ostream& operator<<(ostream& cout, const Polaznik* p) {
		cout << p->_polaznikID << " | " << p->_imePrezime << " | " << p->_kontaktTelefon << endl;
		cout << p->_uspjesnoOkoncaniKursevi << endl;
		return cout;
	}
};

int Polaznik::ID = 1;

class SkillsCentar {
	string _nazivCentra;
	vector<Kurs> _kursevi;//KURSEVI KOJE NUDI ODREDJENI CENTAR
	Kolekcija<Kurs, Polaznik *, 150> _aplikanti;
public:
	SkillsCentar(string naziv) { _nazivCentra = naziv; }
	SkillsCentar(SkillsCentar & obj) :_kursevi(obj._kursevi) {
		_nazivCentra = obj._nazivCentra;
		for (size_t i = 0; i < obj._aplikanti.GetTrenutno(); i++)
		{
			_aplikanti.AddElement(obj._aplikanti.GetElement1(i), new Polaznik(*obj._aplikanti.GetElement2(i)));
		}
	}
	~SkillsCentar()
	{
		for (size_t i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			delete _aplikanti.GetElement2(i);
			_aplikanti.GetElement2(i) = nullptr;
		}
	}
	//JEDAN KURS NE SMIJE POCETI DOK DRUGI TRAJE TJ. VRIJEME ODRZAVANJA KURSA SE NE SMIJE POKLAPATI
	bool ProvjeriKoliziju(Kurs& k) {
		for (size_t i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i].GetKraj() > k.GetPocetak()) {
				return false;
			}
		}
		return true;
	}
	void AddKurs(const Kurs& k) {
		vector<Kurs>::iterator it = _kursevi.begin();
		while (it != _kursevi.end()) {
			if (*it == k) {
				throw Izuzetak("Ne mozete dodati isti kurs", Datum(31, 12, 2018), __FUNCTION__, __LINE__);
			}
			it++;
		}
		_kursevi.push_back(k);
	}

	//ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
	//ONEMOGUCITI APLICIRANJE ZA ISTI KURS. FUNKCIJA BAZA IZUZETAK
	void AddAplikaciju(const Kurs& k, Polaznik& p) {
		bool registrovanKurs = false;
		vector<Kurs>::iterator it = _kursevi.begin();
		while (it != _kursevi.end()) {
			if (*it == k) {
				registrovanKurs = true;
			}
			it++;
		}
		if (!registrovanKurs) {
			throw Izuzetak("Kurs nije registrovan u centru", Datum(31, 12, 2018), __FUNCTION__, __LINE__);
		}
		for (size_t i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			if (_aplikanti.GetElement1(i) == k && *_aplikanti.GetElement2(i) == p) {
				throw Izuzetak("Polaznik je vac aplicirao za ovaj kurs", Datum(31, 12, 2018), __FUNCTION__, __LINE__);
			}
		}
		_aplikanti.AddElement(k, new Polaznik(p));
	}
	//BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU DODA INFORMACIJU O USPJESNO POLOZENOM 
	//KURSU KOJI JE POSLAN KAO PARAMETAR. PREDUSLOV ZA DODAVANJE JE DA JE POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%
	void DodajUspjesnoOkoncanKurs(int ID, const Kurs& k, float bodovi) {
		if (bodovi < 55)
			throw Izuzetak("Student je imao manje od 55 bodova", Datum(31, 12, 2018), __FUNCTION__, __LINE__);
		bool aplicirao = false;
		for (size_t i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			if (_aplikanti.GetElement2(i)->GetID() == ID) {
				aplicirao = true;
				_aplikanti.GetElement2(i)->GetKolekcija().AddElement(new Kurs(k), bodovi);
				return;
			}
		}
		if(!aplicirao)
			throw Izuzetak("Student nije aplicirao za kurs", Datum(31, 12, 2018), __FUNCTION__, __LINE__);
	}

	//VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS

	vector<Polaznik> GetPolazniciByPredavac(string p, enumKursevi kurs) {
		vector<Polaznik> polaznici;
		for (size_t i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			for (size_t j = 0; j < _aplikanti.GetElement2(i)->GetKolekcija().GetTrenutno(); j++)
			{
				if (p == _aplikanti.GetElement2(i)->GetKolekcija().GetElement1(j)->GetImePredavaca() &&
					_aplikanti.GetElement2(i)->GetKolekcija().GetElement1(j)->GetKurs() == kurs) {
					polaznici.push_back(*_aplikanti.GetElement2(i));
				}
			}
		}
		return polaznici;
	}

	friend ostream& operator<<(ostream& cout, SkillsCentar& s) {
		cout << s._nazivCentra << endl;
		ostream_iterator<Kurs> out(cout, "\n");
		copy(s._kursevi.begin(), s._kursevi.end(), out);
		for (size_t i = 0; i < s._aplikanti.GetTrenutno(); i++)
		{
			cout << s._aplikanti.GetElement1(i) << " | " << s._aplikanti.GetElement2(i) << endl;
		}
		return cout;
	}
	//ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
	bool RemoveKurs(Kurs& k) {
		for (size_t i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			if (_aplikanti.GetElement1(i) == k)
				return false;
		}
		for (size_t i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i] == k) {
				_kursevi.erase(_kursevi.begin() + i);
				return true;
			}
		}
		return false;
	}
};

const char *crt = "\n---------------------------------------\n";

bool ProvjeriFormatTelefona(string telefon) {
	//(061)111-111
	string pravilo = "(\\()([0-9]{3})(\\))([0-9]{3})(\\-)([0-9]{3})";
	return regex_match(telefon, regex(pravilo));
}

void main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
	Kolekcija<int, int, 10> kolekcija1;
	try
	{
		for (size_t i = 0; i < kolekcija1.GetMax(); i++)
			kolekcija1.AddElement(i, i + 2);
		//FUNKCIJA TREBA BACITI IZUZETAK U SLUCAJ DA NEMA VISE PROSTORA ZA DODAVANJE NOVIH ELEMENATA
		cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
		cout << kolekcija1.GetElement1(20) << " " << kolekcija1.GetElement2(20) << endl;
		//FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO ELEMENT NA ZAHTIJEVANOJ LOKACIJI NE POSTOJI
	}
	catch (Izuzetak & err)
	{
		cout << "Greska -> " << err << endl;
	}

	cout << kolekcija1 << endl;
	Kolekcija<int, int, 10> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int, 10> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion
#pragma region TestiranjeKursa
	Kurs sef(SoftwareEngeneeringFundamentals, "Jasmin Azemovic", Datum(28, 1, 2016), Datum(15, 2, 2016));
	Kurs msql(MasteringSQL, "Adel Handzic", Datum(28, 2, 2016), Datum(15, 3, 2016));
	sef = msql;
	cout << sef << endl;
	cout << msql << endl;
	if (sef == msql)//KURSEVI SU ISTI AKO POSJEDUJU IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA
		cout << "ISTI SU KURSEVI" << endl;
	Kurs msql2(msql);
	cout << msql2 << endl;
#pragma endregion
#pragma region TestiranjePolaznika
	string telefon1 = "(061)111-111";
	string telefon2 = "(061)111222";
	string telefon3 = "(061)111-333";

	if (!ProvjeriFormatTelefona(telefon1))
		cout << "Broj " << telefon1 << " nije validan1" << endl;
	if (!ProvjeriFormatTelefona(telefon2))
		cout << "Broj " << telefon2 << " nije validan2" << endl;
	if (!ProvjeriFormatTelefona(telefon3))
		cout << "Broj " << telefon3 << " nije validan3" << endl;


	Polaznik denis("Denis Music", telefon1);
	Polaznik denis2("Denis2 Music2", telefon3);

#pragma endregion

#pragma region TestiranjeCentra
	try {
		SkillsCentar mostar("Skills Center Mostar");
		if (mostar.ProvjeriKoliziju(sef))
			//JEDAN KURS NE SMIJE POCETI DOK DRUGI TRAJE TJ. VRIJEME ODRZAVANJA KURSA SE NE SMIJE POKLAPATI
			mostar.AddKurs(sef);
		if (mostar.ProvjeriKoliziju(msql))
			mostar.AddKurs(msql);
		if (mostar.ProvjeriKoliziju(msql2))
			mostar.AddKurs(msql2);
		//ONEMOGUCITI DODAVANJE IDENTICNIH KURSEVA. FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO SE POKUSA DODATI IDENTICAN KURS
		mostar.AddAplikaciju(sef, denis);
		//ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
		try
		{		// dodajemo try catch jer ovaj poziv funkkcije prekida izvrsavanje svega ispod u try bloku
			mostar.AddAplikaciju(msql, denis);
		}
		catch (Izuzetak & err)
		{
			cout << err << endl;
		}
		try
		{
			mostar.AddAplikaciju(msql, denis);
		}
		catch (Izuzetak & err)
		{
			cout << err << endl;
		}
		//ONEMOGUCITI APLICIRANJE ZA ISTI KURS. FUNKCIJA BAZA IZUZETAK
		cout << denis2 << endl;
		denis2 = denis;
		if (denis == denis2)
			//POLAZNICI SU ISTI AKO POSJEDUJU ISTO IME I AKO SU POHADJALI ISTE KURSEVE
			cout << "ISTI SU" << endl;

		mostar.DodajUspjesnoOkoncanKurs(1, sef, 60);//BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU DODA INFORMACIJU O USPJESNO POLOZENOM KURSU KOJI JE POSLAN KAO PARAMETAR. PREDUSLOV ZA DODAVANJE JE DA JE POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%
		mostar.DodajUspjesnoOkoncanKurs(1, msql, 83);
		vector<Polaznik> listaPolaznika = mostar.GetPolazniciByPredavac("Jasmin Azemovic", SoftwareEngeneeringFundamentals);//VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS

		if (mostar.RemoveKurs(sef))//ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
			cout << "Kurs " << sef << " uspjesno uklonjen iz centra " << mostar << endl;

		SkillsCentar sarajevo = mostar;
		cout << sarajevo << endl;
	}
	catch (Izuzetak & err) {
		cout << err << endl;
	}
#pragma endregion

	system("pause");
}