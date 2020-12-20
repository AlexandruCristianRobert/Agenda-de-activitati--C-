#define _CRT_SECURE_NO_WARNINGS
#include <algorithm> // o folosim la operatia for_each care schimba caracterele in caractere mici
#include <vector>// folosim un vector dinamic si e mai usor de lucrat asa
#include <string> //  folosim comanda getline pentru a citi o linie intreaga ca denumire
#include <iostream> // o folosim cand citim din si in fisier pentru a seta nr de caractere citite cant folosim setw
#include <iomanip>// pentru 
#include <time.h>// o folosim pentru a seta un timp default
#include <fstream>// o folosim pentru a citi in si din fisier
using namespace std;

class Activitate // ai doua clase, Activitate si Agenda
{
private: // atribute private ( pot fi si functii private, dar noi folosim doar atribute aici) ele pot fi folosite doar in interiorul clasei, in cazul nostru doar in Activitate, daca vrem sa le folosim in Agenda sau in int main nu putem
	time_t theTime = time(NULL); 
	struct tm* aTime = localtime(&theTime); // le folosim pentru a putea accesa cateva comenzi ce folosesc zilele anului
	int cod; //  cod-ul produsului, este unic pentru fiecare
	string denumire;
	int durata;// durata activitatii
	bool status;// daca e planificat =false, daca e realizat =true;
	int zi; // ziua in care programam activitatea
public://  tot ce e mai jos poate fi folosit oriunde in cod.
	static int nextcod;// o variabila static pe care o folosim pentru a incrementa cod-ul activitatii
	// o variabila static e o variabila ce apartine clasei nu obiectului

	Activitate()// constructorul clasei Activitate, tehnic aici se creaza obiectul cand il declaram
	{
		zi = aTime->tm_yday;// am stetat sa ca ziua in care e declarat obiectul sa se dea automat
		// cum ar fi azi 20 dec = ziua 364 din an
		cod = nextcod++;
		/*
		cod e o variabila a obiectului,
		nextcod e o variabila a clasei
		Daca e sa crestem cod-ul creste codul obiectului, de ex de la 0 la 1
		facem alt obiect, noul obiect o sa aiba valoarea 0 din nou
		Dar putem folosi o variabila a clasei
		o incrementam si asa ramane, nu se reseteaza cand cream alt obiect
		Noi o incrementam de fiecare data cand apelam constructorul(adica de fiecare data cand cream un obiect), deci se va incrementa de fiecare data
		*/
		denumire = "Nespecificat";
		durata = 1;
		status = false; // false=planificat, true=realizat
	}

	void setStatus()// pentru a accesa variabile private am creat o functie publica. Ele mai sunt numite ca functii de access ( functiile set si get, e o conventie de nume)
		// cerinta spune sa putem seta ca realizata o activitate, deci cand apelam functia asta trecem activitatea ca realizata(true)
	{
		status = true;
	}
	void setStatus(bool status)// o suprascriere de functie pentru citirea din fisier
	{
		this-> status=status;// chit  ca au un nume identic, calculatorul stie pe care sa o apeleze cand vede ce primeste, una nu primeste nimic, iar alta primeste un parametru bool.
	}
	void setCod(int cod)// setam codul si crestem si variabila statitca  de fiecare data cand setam un cod
	{// folosim acest setter cand citim dintr-un fisier, sa zicem ca citim 5 , vrem ca nextcod sa aiba urmatoarea valoare dupa codul ultimului produs
		this->cod = cod;// this-> se refera la atributul obiectului, aici atributul cod specificat mai sus in private. Normal this-> e implicit, il citeste calculatorul fara a fi nevoie sa-l scrii tu
		// dar aici avem un atribut cod al obiectului si o variabila cod parametru al functiei, si cu this-> facem deosebirea intre ele.
		nextcod=cod+1; //  nextcod++ nu ar merge. Noi  putem avea produse cu coduri de forma 1 2 3 5 7 9 10, daca am face cu nextcod++ ar veni 1 2 3 4 5 6 7  si ar crea inca o activitate cu codul 7. Cazul asta se aplica cand stergem produse, noi am sters produsele 6 si 8 ca sa rezulte cazul asta
	}
	void setZi(int zi)
	{
		this->zi = zi;
	}
	void setDenumire(string denumire)
	{
		this->denumire = denumire;
	}

	void setDurata(int durata)
	{
		this->durata = durata;
	}
	string getDenumire() // functie ce returneaza denumirea produsului
	{
		return denumire;
	}

	bool getStatus()//  functie ce returneaza statusul
	{
		return status;
	}
	int getCod()// functie ce returneaza cod-ul
	{
		return cod;
	}
	int getZi()// functie ce returneaza ziua
	{
		return zi;
	}
	int getDurata()
	{
		return durata;
	}

	bool operator ==(Activitate& a) //  suprascrierea operatorului de egalitate. Adica noi spunem ca doua sunt obiecte(Activitati) sunt egale cand au ce am specificat mai jos egale
		// daca au cod, zi, denumire,durata si status egale atunci returneaza true, daca cel putin una difera returneaza fals.
	{
		return this->cod == a.cod && this->zi == a.zi && this->denumire == a.denumire && this->durata == a.durata && this->status == a.status;
	}
	friend ostream& operator <<(ostream& os, const Activitate& a) //  suprascrierea operatorului de afisare <<
		// normal cout<< nu stie sa afiseze un obiect asa ca noi trebuie sa ii spunem cum sa il afiseze
		/*
		sunt mai multe lucruri de spus aici:
		friend = o functie friend e o functie ce ii permite altei clase sa acceseze functiile din alta clasa 
		in cazul nostru avem clasa ostream(clasa pentru afisare) si clasa Activitate
		& inseamna referinta
		folosim & pentru a ne referi la un obiect deja existent, daca nu l-am folosi ar face o copie dupa elementul ala si ar lucra cu copia si ar fi mult mai costisitor de memorie progoramul
		const  folosim  pentru ca avem o referinta la un obiect si nu dorim sa-l schimbam
		*/
	{
		os << "Cod activitate: " << a.cod << endl;
		os << "Zi: " << a.zi << endl;
		os << "Denumire: " << a.denumire << endl;
		os << "Durata: " << a.durata << " ore" << endl;
		if (a.status)
			os << "Status: realizat" << endl;
		else
			os << "status: planificat" << endl;
		os << "------------------------------------------------------------" << endl;
		return os;
	}
	friend istream& operator >>(istream& is, Activitate& a)//  suprascrierea functiei de citire de la tastatura
	{
		cout << "Denumire: ";
		cin.ignore(); // o folosim pentru a ignora ultima linie introdusa de la tastatura
		getline(is, a.denumire);// citim o linie introdusa de la tastatura, daca nu era cin.ignore() el citea ultima linie introdusa;
		// la cum am scris codul , introducem un nume si dupa citim denumirea, daca nu era cin.iignore atunci getline citea numele introdus mai devreme.
		do//  functie do while sa  ne asiguram ca ziua introdusa e intre 1-365
		{
			cout << "Zi(1-365): ";
			is >> a.zi;
		} while (a.zi < 1 || a.zi>365);

		do//  la fel pentru durata 1-24
		{
			cout << "Durata: ";
			is >> a.durata;
		} while (a.durata < 1 || a.durata>24);
		cout << "Status activitate (planificat sau realizat): "; 
		string raspuns;
		is >> raspuns;
		for_each(raspuns.begin(), raspuns.end(), [](char& c)// e o functie in plus, in cazul in care scrii ReAliZat sau orice in afara de realizat, el schimba toate caracterele, una cate una, in caractere mici
			{
				c = ::tolower(c); //  pentru asta avem nevoie de #include< algorithm>
			});
		if (raspuns == "realizat")
			a.status = true;
		else
			a.status = false;
		return is;
	}
};
int Activitate::nextcod = 0;// aici initializam variabila statica

template <typename T> class Agenda // template  t e un mod frumos de ai arata profului ca stii sa lucrezi si cu ce s-a facut in ultimele 2-3 saptamani.
	//template e o chestie pe care o folosim cand vrem sa lucram cu mai multe tipuri de variabile, in aceleasi functii( in cazul nostru avem un vector).
	// Cu template el poate alege ce fel de vector sa fie , vector de Activitati, sau vector de inturi sau vector de strings sau vector de chars, etc.
{
private:
	vector<T> lista_activitati; // vector dinamic(adica cu marime ce fluctueaza, poate avea cate elemete vrei tu sa aiba) de T obiecte( noi o sa folosim Activitati)
public:
	string nume;// numele proprietarului agendei.

	void Adauga_Activitate(T activitate)// primeste un obiect
	{
		lista_activitati.push_back(activitate);// functia .push_back adauga elementul la capatul vectorului, ex daca vectorul are 5 elemente cu functia pushback devine vector de 6 elemente
	}

	void Sterge_Activitate(int cod) // stergem o activitate dupa codul ei
	{
		int incr = 0;// tinem minte al catelea element este, pornind de la primul
		for (auto i = lista_activitati.begin();i != lista_activitati.end();++i)// auto e un tip de variabila, auto ii permite sistemului sa gaseasca el ce fel de tip de variabila e i, in cazul nostru e un pointer la o activitate(adica tine minte pozitia la care se gaseste activitatea) si parcurge tot vectorul de la inceput (begin()) pana la final ( end())
		{
			if ((*i).getCod() == cod)// cand am gasit elementul cu codul respectiv
			{
				lista_activitati.erase(lista_activitati.begin() + incr);// stergem elementul de la pozitia (inceputul vectorului + nr de elemente)
				cout << "Activitatea a fost stearsa cu succes!";
				cout << "-------------------------------------" << endl;
				break;//  pentru ca am gasit si l-am sters nu mai are rost sa parcurgem vectorul asa ca folosim break pentru a intrerupe for-ul
			}
			incr++;
		}
	}
	void Afisare_pe_zi(int zi)// afisam toate activitatile dintr-o zi
	{
		for (auto i = lista_activitati.begin();i != lista_activitati.end();++i)
		{
			if ((*i).getZi() == zi)// daca activitatea are ziua egala cu zi atunci o afisam
				cout << *i;// pentru ca am suprascris << atunci cout<<*i o sa afiseze ce i-am spus noi sa afiseze
		}
	}
	void setStatus(int cod) // setam statusul ca realizat pentru o activitate
	{
		for (auto i = lista_activitati.begin();i != lista_activitati.end();++i)
		{
			if ((*i).getCod() == cod)//  cauta activitatea cu cod-ul respectiv in vector si ii seteaza statusul
			{
				(*i).setStatus();
				cout << "Status setat cu succes!";
				cout << "-----------------------" << endl;
				break;
			}
		}
	}
	friend istream& operator >>(istream& is, Agenda& a)// diferenta intre asta si cea de dedesupt e f in nume, istream e folosit pentru cin>>
	{
		is >> a.nume;
		return is;
	}
	friend ifstream& operator >> (ifstream& ifs, Agenda& a)// ifstream e folosit cand citim dintr-un fisier, la fel si pentru ostream si ofstream
	{
		ifs.open(a.nume+".txt");// deschide fisierul cu numele+terminatia .txt : ex ana.txt
		if (!ifs)// daca fisierul nu exista nu citim nimic
		{
			return ifs;
		}
		int cod, zi, durata;
		bool status;
		string denumire;
		while (ifs >> cod >> zi >> denumire >> durata >> status) // cat timp citeste un rand cu 5 variabile in forma aia 
		{
			Activitate activ;// cream o activitate cu setarile default
			activ.setCod(cod);// ii setam codul, nextcod
			activ.setZi(zi);//ziua
			activ.setDenumire(denumire);// si tot asa
			activ.setStatus(status);
			a.Adauga_Activitate(activ);// dupa o adaugam la vectorul de activitati al agendei
		}
		ifs.close();//inchidem fisierul
		return ifs;

	}
	friend ofstream& operator << (ofstream& ofs, Agenda& a)
	{
		ofs.open(a.nume+".txt",ios::app); // ios::app e functia append adica adauga la terminatia fisierului. 
		for (auto i = a.lista_activitati.begin();i != a.lista_activitati.end();++i)
		{
			ofs << setw(4)<<(*i).getCod()<<setw(4)<< (*i).getZi() <<setw(20)<< (*i).getDenumire() <<setw(5)<< (*i).getDurata() <<setw(6)<< (*i).getStatus()<<endl;// functia setw zice pe cate caractere sa se afiseze ce ai introdus, cum am pus acolo afiseaza cod-ul pe 4 caractere, daca ai codul 1 iti afiseaza spatiuspatiuspatiu1
		}
		ofs.close();
		return ofs;
	}
};


int main()
{
	Agenda<Activitate> agenda; // definim agenda ce contine un vector cu elemente de tip Activitate
	string nume;
	int alegere;
	cout << "Introduceti numele: ";
	cin >> agenda;
	ifstream ifs; // aici se creeaza un stream, o cale prin care citim in fisier
	ifs >> agenda;//citim agenda, daca exista se citeste, daca nu exista nu se face nimic
	do// functie do while ce se repeta cat timp alegere e diferit de 5
	{
		cout << "------------------------" << endl;
		cout << nume << "----Agenda" << endl;
		cout << "1. Adaugare activitate" << endl;
		cout << "2. Stergere activitatate" << endl;
		cout << "3. Afisare activitati dupa zi" << endl;
		cout << "4. Setare status activitate" << endl;
		cout << "5. Iesire" << endl;
		cin >> alegere;
		switch (alegere)// functie switch, in functie de ce valoare are variabila el executa un cod
		{
		case 1://  in cazul in care alegere are valoarea 1
		{
			Activitate a;// creem o activitate
			cin >> a;// o citim
			agenda.Adauga_Activitate(a); //  o adaugam la vector/ in agenda
			break;// intrerupem cazul. Daca nu ai pune break el ar intra si ar executa si ce scrie in cazul 2, daca nici acolo nu ar gasi break ar continua si la 3 si tot asa.
		}
		case 2:
		{
			int cod;
			cout << "Introduceti codul activitatii: ";
			cin >> cod;
			agenda.Sterge_Activitate(cod);// stergere in functie de cod-ul introdus
			break;
		}
		case 3:
		{
			int zi;
			cout << "Introduceti ziua(1-365): ";
			cin >> zi;
			agenda.Afisare_pe_zi(zi);// afisare in functie de ziua introdusa
			break;
		}
		case 4:
		{
			int cod;
			cout << "Introduceti codul activitatii: ";
			cin >> cod;
			agenda.setStatus(cod);// setam statusul realizat in functie de codul introdus
			break;
		}
		case 5:
		{
			cout << "O zi buna!"; // mesaj de iesire, optional
			break;
		}
		}


	} while (alegere != 5);
	ofstream of;// stream de scriere
	of << agenda;// scriem agenda daca nu exista, daca exista adaugam la final.
	return 0;
}
