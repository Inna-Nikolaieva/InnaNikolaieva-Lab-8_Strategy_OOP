/* Патерн «Стратегія»
17. Створити базовий клас КВИТОК НА ПОЇЗД (задаються дані про пасажира, номер вагона).
Створити похідні класи КУПЕЙНИЙ КВИТОК (задаються номер місця в межах від 1 до 36, вартість)
та КВИТОК-ЛЮКС (задаються номер місця в межах від 1 до 18, вартість). Для заданих прикладів квитків перевірити правильність введених даних
(коректність номера місця), визначити тип місця в залежності від номера (верхнє або нижнє, ліве або праве) відсортувати за зростанням вартості і
обчислити їх сумарну вартість. Для перевірки використати масив вказівників на об’єкти базового класу, яким присвоїти адреси об’єктів похідних класів.*/

#include <iostream>
#include <string>

using namespace std;

class Train_Ticket					//базовий клас
{
public:
	virtual string get_data() = 0;
	virtual int get_number() = 0;
	virtual int get_place() = 0;
	virtual void SetData() = 0;
	virtual double get_price() = 0;
	virtual void Typeofplace() = 0;
};

class Compartment_Ticket : public Train_Ticket
{
private:
	string data;					//дані про пасажира
	int number;						//номер вагона
	int place;						//місце у вагоні
	double price;					//вартість квитка
public:
	Compartment_Ticket() :data(""), number(0), place(0), price(0) { }
	Compartment_Ticket(string str, int n, int p, double c) :data(str), number(n), place(p), price(c) {}
	~Compartment_Ticket() {}

	string get_data() { return data; }
	int get_number() { return number; }
	int get_place() { return place; }
	double get_price() { return price; }

	void SetData()
	{
		if (place < 1 || place > 36)
		{
			cout << "Incorrectly entered data!!!" << endl;
			system("pause");
			return;
		}
	}

	void Typeofplace()
	{
		if (place % 2 == 0)
			cout << "Top shelf.";
		else
			cout << "Bottom shelf.";
	}
};

class Luxury_Ticket : public Train_Ticket
{
private:
	string data;					//дані про пасажира
	int number;						//номер вагона
	int place;						//місце у вагоні
	double price;					//вартість квитка
public:
	Luxury_Ticket() :data(""), number(0), place(0), price(0) {}
	Luxury_Ticket(string str, int n, int p, double c) :data(str), number(n), place(p), price(c) {}
	~Luxury_Ticket() {}

	string get_data() { return data; }
	int get_number() { return number; }
	int get_place() { return place; }
	double get_price() { return price; }

	void SetData()
	{
		if (place < 1 || place > 18)
		{
			cout << "Incorrectly entered data!!!" << endl;
			system("pause");
			return;
		}
	}

	void Typeofplace()
	{
		if (place % 2 == 0)
			cout << "Right place.";
		else
			cout << "Left place.";
	}
};

class Tickets {
private:
	Train_Ticket* p;
public:
	Tickets() { p = NULL; }
	Tickets(Train_Ticket* tt) :p(tt) {  }
	~Tickets() { delete p; }
	void Set(Train_Ticket* tt)
	{
		delete p;
		p = tt;
	}
	string get_data() { return p->get_data(); }
	int get_number() { return p->get_number(); }
	int get_place() { return p->get_place(); }
	void SetData() { return p->SetData(); }
	double get_price() { return p->get_price(); }
	void Typeofplace() { return p->Typeofplace(); }
};

void input_data(Tickets* p, int kst);
void sort(Tickets* p, int k);
void print(Tickets* p, int k);
double total_cost(Tickets* p, int k);

int main(void)
{
	Tickets* p;
	int kst = 0;
	cout << "Enter the number of tickets: ";
	cin >> kst;
	p = new Tickets[kst];
	input_data(p,kst);
	sort(p, kst);
	print(p, kst);
	double sum = total_cost(p, kst);
	cout << endl << "Total cost: " << sum << endl;
	delete[] p;
	system("pause");
	return 0;
}

void input_data(Tickets* p, int kst)
{
	for (int i = 0; i < kst; i++)
	{
		string n;
		int num = 0, pl = 0;
		double pr = 0;
		cout << endl << "Enter passenger data: ";
		cin >> n;
		cout << "Enter the train number: ";
		cin >> num;
		cout << "Enter the ticket type (c-Compartment Ticket, l-Luxury Ticket): ";
		char type;
		cin >> type;
		if (type == 'c')
		{
			cout << "Enter a place: ";
			cin >> pl;
			cout << "Enter the price: ";
			cin >> pr;
			p[i].Set(new Compartment_Ticket(n, num, pl, pr));
			p[i].SetData();
		}
		if (type == 'l')
		{
			cout << "Enter a place: ";
			cin >> pl;
			cout << "Enter the price: ";
			cin >> pr;
			p[i].Set(new Luxury_Ticket(n, num, pl, pr));
			p[i].SetData();
		}
	}
}

void sort(Tickets* p, int k)
{
	Tickets* pt;
	Tickets temp;
	int i, t = 0;
	for (i = 1; i < k; i++) {
		if (p[i].get_price() > p[i - 1].get_price())
			continue;
		swap(temp, p[i]);
		pt = p + i - 1;
		while (temp.get_price() < (*pt).get_price()) {
			swap(*(pt + 1), *pt);
			if (--pt < p) break;
		}
		swap(*(pt + 1), temp);
	}
}

void print(Tickets* p, int k)
{
	cout << endl;
	for (int i = 0; i < k; i++) {
		cout << i + 1 << ". " << "Passenger data: " << p[i].get_data() << "        ";
		cout << "Train number: " << p[i].get_number() << "        ";
		cout << "Place: " << p[i].get_place() << "        ";
		p[i].Typeofplace(); cout << "        ";
		cout << "Price: " << p[i].get_price() << endl;
	}
}

double total_cost(Tickets* p, int k)
{
	double sum = 0;
	for (int i = 0; i < k; i++)
		sum += p[i].get_price();
	return sum;
}

/*
6
Adams_Henry
96
l
12
225.46
Bright_Richard
145
c
26
128.95
Woods_James
23
c
14
135.25
Cooper_Alan
89
l
5
189.3
Penney_Steve
56
c
29
136.75
Mills_Hannah
179
c
17
118.5
*/