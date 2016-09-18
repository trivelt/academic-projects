#include <iostream>
#include <cstring>
using namespace std;

class Przestepca
	{
	private:
	float pieniadze;
	string tajemnica;
	friend class Prokurator;
	friend void ukradnij(float, Przestepca&);

	public:
	void kasa(int a) { pieniadze=(float)a; }
	void jakatajemnica(string b) { tajemnica=b; }
	int ilekasy() {return pieniadze;}
	};

class Prokurator
	{
	public:
	void przesluchanie(Przestepca jaki)
		{
		cout << "- Jaka jest Twoja tajemnica?"<<endl<<"- "<<jaki.tajemnica<<endl;
		}
	};

void ukradnij(float ile, Przestepca& kto)
	{
	kto.pieniadze+=ile;
	cout << "Ukradlem "<<ile<<" zlotych"<<endl;
	}

int main()
{
Przestepca zlodziej;
zlodziej.kasa(15000);
zlodziej.jakatajemnica("zabilem policjanta");
Prokurator sledczy;
sledczy.przesluchanie(zlodziej);
ukradnij(900, zlodziej);
cout << "Mam teraz "<<zlodziej.ilekasy() <<" zlotych"<<endl;
}
