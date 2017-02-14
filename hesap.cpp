#include <cstdlib>
#include <iostream>
#include <conio.h>
//#include <fstream>
#include <string.h>
#include <stack>
#include <cmath>
using namespace std;
const double PI=3.141593;  //p� sabitimizi tan�mlad�k
const double E=2.718281;   //e say�s� sabitimizi tan�mlad�k
struct eleman{             //eleman  ad�nda yap�m�z� tan�mlad�k
	char icerik[50];       //icerik ad�nda de�i�kenimizi tan�mlad�k
	struct eleman *ileri;  //ba�l� listemiz �ift ynl� oldugu i�in ileri 
	struct eleman *geri;   //ve geri pointer tan�mlamalar�n� yapt�k
};
typedef struct eleman Eleman;  //yap�m�z�  adland�rd�k
typedef Eleman* Elemanptr;     // adland�rd���m�z yap�ya pointer atad�k
struct liste{                
	Elemanptr bas;             //Eleman  t�r�n de listemizi olu�turduk 
	Elemanptr son;
};
typedef struct liste Liste;   //listemizi adland�rd�k
typedef Liste* Listeptr;      //listemize  pointer atad�k ca��rmam�z i�in

Listeptr yeni_liste ()       //Listeptr t�r�nde yeni liste olu�turduk
{ 
	Listeptr liste ;         //liste olarak adland�rd�k
	liste = (Listeptr)malloc(sizeof(Liste));   //listeye Listeptr t�r�ne g�re alan tahsis ettik
	liste ->bas = NULL;      //ilk olarak listenin bas�n� bos olarak tan�mlad�k
	liste ->son = NULL;      //ilk olarak listenin sonunu bos olarak tan�mlad�k
	return liste ;           //listemizi d�nd�rd�k
}

void veri_ekle(char veri[],Listeptr l) //temp->veriye ve liste->l'ye buraya atan�r
{
	if(l->bas==NULL){  //listemizin bas� bos ise
		Elemanptr yeni;  //elemanptr t�r�nde yeni tan�tacak
		yeni=(Elemanptr)malloc(sizeof(Eleman)); //yeni degiskenine elemanptr t�r�nde alan tahsisi olacak
		strcpy(yeni->icerik,veri); //veri yeninin i�eri�ine atan�r
		yeni->geri=NULL;  //yeninin gerisi bos olur
		yeni->ileri=NULL; //yeninin ilerisi bos olur
		l->bas=yeni;      //yeniyi listenin bas�na eklenilir 
		l->son=yeni;      //yeniyi listenin sonuna ekler
	}	else{     //liste bos degilse
		Elemanptr temp=(Elemanptr)malloc(sizeof(Eleman));//elemanptr t�r�nde temp'e alan tahsis edilir
		strcpy(temp->icerik,veri);//veri tempteki icerige atan�r
		temp->ileri=NULL;//temp'in ilerisi bos olarak olusturulur
		temp->geri=l->son; //listenin sonunu temp'in gerisine atar
		l->son->ileri=temp;//listenin sonunun ilerisine temp'i atar
		l->son=temp;//listenin sonu temp olur
		}
}

void denklem_ekle(char veri[],Listeptr l,int j) //temp ,liste ve j degiskeni buraya atand� diger sarrtta j+1 g�nderecek
{
	char temp[50];  //temp dizisi tan�tt�k
	for(int i=0;i<j;i++) temp[i]=veri[i]; //i ve j'ye g�re for olu�turup verideki degerleri tempe atacak
	for(int i=j;i<50;i++) temp[i]=0;   //for a g�re tempin degerlerini s�f�ra esitleyecek
	veri_ekle(temp,l);     //temp ve listeyi veri_ekle fonksiyonuna g�nderir
	
}

void listeye_ekle(Elemanptr eleman,Listeptr liste)  //temp ve yeni listeyi atad�k buraya
{
	if(liste->bas==NULL)  //listenin bas� bos ise
	{ 
		eleman->geri=NULL;    //tempin gerisine bos olsun
		liste->bas=eleman;    //listenin bas� eleman olsun
	}
	else  //degilse
	{
		liste->son->ileri=eleman; //liste sonunun ilerisine eleman� ekle
		eleman->geri=liste->son; //listenin sonunuda eleman�n gerisine ekle
	}                          //b�ylece eleman� sona eklemi� oluruz
	eleman->ileri=NULL;//eleman�n ilerisini bos olarak tan�mla
	liste->son=eleman;  //listenin sonuna eleman� ata
}

void listele(Listeptr l)   //gelen liste l  ad�ndaki listeye atan�r
{
	Elemanptr temp=l->bas;   //listenin bas� elemanptr t�r�ndeki tempe atan�r
	cout<<endl;              //yazma i�leminde g�revli olacakt�r.
	while(temp!=NULL){       //temp bos olmad�g� m�ddetce
		cout<<temp->icerik;  //tempin iceri�i yazd�r�l�r
		temp=temp->ileri;    //daha sonra tempin ilerisi tempe atan�r b�ylece hepsi yazd�r�l�r
	}
}

int krk_knt(char dizi[])   //tan�mlad���m�z fonksiyona denklemi diziye atad�k
{
	int i=0;  //i'yi tan�mlad�k
	while(i<strlen(dizi)) //dizinin karakter uzunlu�u i'den b�y�k oldugu muddetce
	{
		if(dizi[i]>=40&&dizi[i]<=57&&dizi[i]!=44) i++; //ascii karakter sorgulanmas� yap�l�yor
		else if(dizi[i]=='{'||dizi[i]=='}'||dizi[i]=='['||dizi[i]==']'||dizi[i]=='!'||dizi[i]=='%'||dizi[i]=='^') i++; //karakter sorgusuna g�re artt�rma
		else if(dizi[i]=='e'&&dizi[i+1]=='x'&&dizi[i+2]=='p') i+=3;//exp say�s�n� sorgulad�k ona g�re artt�r�m yapt�k
		else if(dizi[i]=='p'&&dizi[i+1]=='i') i+=2; //pi karakteri i�in sorgulama yapt�k
		else if(dizi[i]=='P'&&dizi[i+1]=='I') i+=2; //PI karakteri i�in sorgulama yapt�k
		else if(dizi[i]=='l'&&dizi[i+1]=='n') i+=2; //ln karakteri i�in sorgulama yapt�k
		else if(dizi[i]=='l'&&dizi[i+1]=='o'&&dizi[i+2]=='g') i+=3; //log karakteri i�in sorgulama yapt�k 
		else if(dizi[i]=='t'&&dizi[i+1]=='a'&&dizi[i+2]=='n') i+=3; //tan karakteri i�in sorgulad�k
		else if(dizi[i]=='s')//sin ve sgn karakteri i�in sorgu
		{
			if(dizi[i+1]=='i'&&dizi[i+2]=='n') i+=3; //sin i�in sorgu
			else if(dizi[i+1]=='g'&&dizi[i+2]=='n') i+=3;//sgn i�in sorgu
			else return i;
		}
		else if(dizi[i]=='c') //cos ve cot karakteri i�in sorgu
		{
			if(dizi[i+1]=='o'&&dizi[i+2]=='s') i+=3; //cos i�in sorgu
			else if(dizi[i+1]=='o'&&dizi[i+2]=='t') i+=3;//cot i�in sorgu
			else return i;//hi�biri ise i d�nd�r
		}
		else if(dizi[i]=='a')  //asin,atan,acos,acot i�in sorgu
		{
			if(dizi[i+1]=='s'&&dizi[i+2]=='i'&&dizi[i+3]=='n') i+=4; //asin icin karakter sorgusu
			else if(dizi[i+1]=='t'&&dizi[i+2]=='a'&&dizi[i+3]=='n') i+=4;//atan icin karakter sorgu
			else if(dizi[i+1]=='c')  //acos ve acot'un cos ve cot k�sm� sorgusu
			{
				if(dizi[i+2]=='o'&&dizi[i+3]=='s') i+=4; //acos karakter sorgusu
				else if(dizi[i+2]=='o'&&dizi[i+3]=='t') i+=4;//acot karakter sorgusu
				else return i;//hi�biri ise i d�nd�r
			}
			else return i;//hi�biri ise i d�nd�r
		}
		else return i;//hi�biri ise i d�nd�r
	}
return -1;	//yukar�dakiler olmaz ise -1 d�nd�r
	
}

void bagli_yapma(char denklem[],Listeptr liste) //denkelem ve liste buraya atand�
{
	
	char temp[50]; //temp tan�t�m� yap�ld�
	char bos[50]; //bosumuzun tan�t�m� yap�ld�
	int j=0;	  //j degikeni tan�t�ld�
	for(int i=0;i<strlen(denklem);i++) //i degerimizi denklemin uzunluguna kadar d�ng�y� soktuk
	{
		if(denklem[i]!='('&&denklem[i]!=')'&&denklem[i]!='{'&&denklem[i]!='}'&&denklem[i]!='['&&denklem[i]!=']'&&denklem[i]!='/'&&denklem[i]!='*'&&denklem[i]!='+'&&denklem[i]!='-'&&denklem[i]!='^'&&denklem[i]!='%'&&denklem[i]!='!')
		{ //denklemde yukar�daki semboller kullan�lmad�ysa degerleri temp dizimize atad�k 
			temp[j]=denklem[i];
			j++;    //j'yi bir artt�r�r
		}
		else //kullan�ld�ysa
		{	
			if(j!=0) //ve j s�f�rdan farkl�ysa
			{
				denklem_ekle(temp,liste,j);  //denklem_ekle fonksiyonuna temp liste ve j yi g�nderir
				j=0;  //j'yi daha sonra s�f�ra esitler
			}                                                                                                    //sinana sor bakal�m:)
			temp[j]=denklem[i]; //denklemdeki de�i�kenleri temp dizisine atacak
			denklem_ekle(temp,liste,j+1);  //burda ise j'yi 1 artt�r�p denklem_ekle fonksiyonuna g�nderecek
			j=0;
		}
	}
	if(j!=0)//j s�f�rdan farkl� olacak sekilde 
	{
		denklem_ekle(temp,liste,j);//denklem ekleye g�nderilir                                       //sinana sor bakal�m:)
		j=0;
	}
}

int hata(Listeptr liste)   //listemizi listeye atad�k
{
	int sayi=0;    //degisken tan�t�m� yap�ld�
	stack <char> s;  //char t�r�nde s ad�nda stack tan�t�m� yap�ld�
	s.push(0);       //stack e 0 degeri atand�
	Elemanptr temp=liste->bas;   //listenin bas�n� elemanptr t�r�ndeki tempe atad�k
	while(temp!=NULL)     //temp bos olmad�g� m�ddetce
	{
		if(temp->icerik[0]=='(' || temp->icerik[0]=='{' || temp->icerik[0]=='[')//tempin i�eri�ininilk karakteri (,{,[ ise
		{
			if(temp->ileri!=NULL) //tempin ilerisi bos de�ilse
			{ 
				if(temp->ileri->icerik[0]=='*' || temp->ileri->icerik[0]=='/' || temp->ileri->icerik[0]=='+' || temp->ileri->icerik[0]=='-' || temp->ileri->icerik[0]=='^' || temp->ileri->icerik[0]=='%')
				{//tempin ilerisinin iceri�inde yukar�daki sart sembollerinden birini sa�larsa
					cout<<sayi+2<<". yerde isaret hatasi var.";  //yazd�r
					return 1;  //1 degerini d�nd�r
				}
				else if(temp->ileri->icerik[0]==')' || temp->ileri->icerik[0]=='}' || temp->ileri->icerik[0]==']')
				{//degilse ve ) veya} veya ] ise
					cout<<sayi+1<<". ve "<<sayi+2<<". yerdeki parantezlerde hata var.";  //yazd�r
					return 1;	//1 degeri d�nd�r
				}
			}
			if(temp->geri!=NULL)
			{
				//if(temp->geri->icerik[0]!='*' && temp->geri->icerik[0]!='/' && temp->geri->icerik[0]!='+' && temp->geri->icerik[0]!='-' && temp->geri->icerik[0]!='^' && temp->geri->icerik[0]!='%' && temp->geri->icerik[0]!='(' && temp->geri->icerik[0]!='{' && temp->geri->icerik[0]!='[')
				if(temp->geri->icerik[0]>=48&&temp->geri->icerik[0]<=57)//asc�� kodlamaya g�re kars�last�rma sa�l�yor ise
				{
					cout<<sayi<<". yerden sonra isaret konmasi gerek.";   //yazd�r
					return 1;//1 degeri d�nd�r
				}
			}
			s.push(temp->icerik[0]);   //tempin i�eriginin ilk degerini stacke ekle
		}
		else if(temp->icerik[0]==')' || temp->icerik[0]=='}' || temp->icerik[0]==']' || temp->icerik[0]=='!')
		{  //yukar�dakiler degilse eger ) veya} veya] veya ! ise
			if(temp->geri!=NULL)  //tempin gerisi bos degilse
			{
				if(temp->geri->icerik[0]=='*' || temp->geri->icerik[0]=='/' || temp->geri->icerik[0]=='+' || temp->geri->icerik[0]=='-' || temp->geri->icerik[0]=='^' || temp->geri->icerik[0]=='%')
				{//tempin gerisinin iceriginin ilk karakteri sembollerden biri ise
					cout<<sayi<<". yerde isaret hatasi var.";   //yazd�r
					return 1; //1 degerini d�nd�r
				}
			}
			if(temp->ileri!=NULL) //tempin ilerisi bos de�ilse
			{ 
				if(temp->ileri->icerik[0]!='*' && temp->ileri->icerik[0]!='/' && temp->ileri->icerik[0]!='+' && temp->ileri->icerik[0]!='-' && temp->ileri->icerik[0]!='^' && temp->ileri->icerik[0]!='%' && temp->ileri->icerik[0]!='!' && temp->ileri->icerik[0]!=')' && temp->ileri->icerik[0]!='}' && temp->ileri->icerik[0]!=']')
				{//tempin ilerisinin i�eri�i yukar�daki verden birine e�it ise
					cout<<sayi+1<<". yerden sonra isaret konmasi gerek.";   
					return 1;
				}
			}
			if(temp->icerik[0]==')')
			{  //tempin i�eri�inin ilk karakteri ) ise
				char top=s.top(); //stack in ba��ndakini topa at
				if(s.top()!='(')  //stackin bas� ( farkl� ise
				{
					cout<<sayi+1<<". yerde parantez hatasi var."; 
					return 1;
				}
				else s.pop();   //de�ilse stackin ba�� yap			
			}
			else if(temp->icerik[0]=='}')  
			{//tempin ilk karakteri } ise
				char top=s.top();  //stackin ba��ndakini topa at
				if(s.top()!='{')   //stackin ba�� { farkl� ise
				{
					cout<<sayi+1<<". yerde parantez hatasi var."; 
					return 1;
				}
				else s.pop();  //de�ilse stackin bas�da ol			
			}
			else if(temp->icerik[0]==']')
			{ //tempin i�eri�inin ilk karakteri ] ise
				char top=s.top();//stackin bas�ndakini topa at
				if(s.top()!='[') //stackin bas� [ farkl� ise
				{
					cout<<sayi+1<<". yerde parantez hatasi var"; 
					return 1;
				}
				else s.pop();// de�ilse stackin bas�nda ol	
			}
		}
		if(temp->icerik[0]=='*' || temp->icerik[0]=='/' || temp->icerik[0]=='+' || temp->icerik[0]=='-' || temp->icerik[0]=='^' || temp->icerik[0]=='%')
		{//tempin i�eri�inin ilk karakteri yukar�daki i�aretlerden biri ise
			if(temp->ileri==NULL || temp->geri==NULL)
			{//tempin ilerisi veya gerisi bos ise
				cout<<sayi+1<<". yerde isaret hatasi var"; 
				return 1;
			}
			if(temp->ileri->icerik[0]=='*' || temp->ileri->icerik[0]=='/' || temp->ileri->icerik[0]=='+' || temp->ileri->icerik[0]=='-' || temp->ileri->icerik[0]=='^' || temp->ileri->icerik[0]=='%')
			{//tempin ilerisinin i�eri�inin ilk karakteri yukar�dakilerden herhangi biri ise
				cout<<sayi+2<<". yerde isaret hatasi var"; 
				return 1;
			}
			if(temp->geri->icerik[0]=='*' || temp->geri->icerik[0]=='/' || temp->geri->icerik[0]=='+' || temp->geri->icerik[0]=='-' || temp->geri->icerik[0]=='^' || temp->geri->icerik[0]=='%')
			{ //tempin gerisinin i�eri�i yukaridakilerden herhangi biri ise
				cout<<sayi<<". yerde isaret hatasi var"; 
				return 1;
			}
		}
		
		temp=temp->ileri; //tempin ilerisini tempe atar
		sayi++; //sayiyi yani sayaci bir att�r�r
	}
	if(s.top()!=0)  
	{//stackin bo� olup olmad���n� kontrol eder. bo� de�ilse
		cout<<"parantez kapatilmamis";
		return 1;
	}
	
}

int oncelik(char krk)  //atad���m�mz tempin i�eri�inin ilk karakteri
{
	if(krk=='a'||krk=='s'||krk=='c'||krk=='t'||krk=='l') return 5;//a,s,c,t,l ise 5 degeri d�nd�rs�n
    else if(krk=='^'||krk=='%') return 4;    //^ veya % ise 4 d�nd�rs�n
    else if(krk=='*'||krk=='/') return 3;     //* veya / ise 3 d�nd�rs�n
    else if(krk=='+'||krk=='-') return 2;    //+ veya - ise 2 d�nd�rs�n
	else if(krk=='('||krk=='['||krk=='{') return 1;  // (,[ veya { ise 1 d�nd�rs�n
	else return 0;   //hi�biri de�ilse 0 d�nd�rs�n
}

void sabit_yerlestir(Listeptr l)  //listemizi l olarak tan�mlad�k
{
	Elemanptr temp;  //elemanptr t�r�nde temp'i tan�mlad�k
	temp=l->bas;   //listenin bas�n� temp'e atad�k
	while(temp!=NULL) //temp bos ise
	{
		if(temp->icerik[0]=='P'||temp->icerik[0]=='p') sprintf(temp->icerik, "%2.6f", PI);//  tempin i�eri�indeki karakter katar�na yazar
		else if(temp->icerik[0]=='E'||temp->icerik[0]=='e') sprintf(temp->icerik, "%2.6f", E); //tempin i�eri�indeki karakter katar�na yazar
		temp=temp->ileri;  //tempin ilerisini tempe aktar�r
	}
}

Listeptr postfix(Listeptr liste)  //liste t�r�nde posfix tan�mland� ve listemizi parametreye atad�k
{
	int oncelikA,oncelikU;   //iki de�i�kenimizi tan�mlad�k
	Listeptr yeni=yeni_liste(); //liste ptr t�r�nde yeni tan�mlad�k yeni liste fonksiyonunu atad�k
	Elemanptr temp,temp1;       //elemanptr t�r�nde temp ve temp1 tan�mlad�k
	stack <Elemanptr> s;        //elemanptr t�r�nde s ad�nda stak olu�turduk
	temp=liste->bas;            //listenin bas�n� temp'e atad�k
	while(temp!=NULL)      //temp bos ise
	{
		temp1=temp->ileri;   //temp'in ilerisini tmp1 e atad�k
		if(temp->icerik[0]!='a' && temp->icerik[0]!='t' && temp->icerik[0]!='c' && temp->icerik[0]!='s' && temp->icerik[0]!='l' && temp->icerik[0]!='*' && temp->icerik[0]!='/' && temp->icerik[0]!='+' && temp->icerik[0]!='-' && temp->icerik[0]!='^' && temp->icerik[0]!='%' && temp->icerik[0]!='(' && temp->icerik[0]!='{' && temp->icerik[0]!='[' && temp->icerik[0]!=')' && temp->icerik[0]!='}' && temp->icerik[0]!=']')
		{ //tempin i�eri�indeki ilk karakter a,t,c,s,l,*/+-! gibi karakterlerden farkl� ise
			listeye_ekle(temp,yeni); //temp'i ve yeni listeyi liste_ekleye g�nderir
		}
		else if(temp->icerik[0]=='(' || temp->icerik[0]=='[' || temp->icerik[0]=='{') //tempin i�eri�inde basta ([{ varsa
		{
			s.push(temp); //bu tempi stack'e ekler
		}
		else if(temp->icerik[0]==')') //yukar�daki de�ilse eger ) ise
		{
			while(s.top()->icerik[0]!='(')  //stackteki tempin bas�n�n icerigi ( farkl� ise
			{
				listeye_ekle(s.top(),yeni);  //stackin bas�ndaki tempi ve yeni listeyi liste_ekleye g�ndderir
				s.pop();  //stackten tempi c�karacak
				
			}
			s.pop(); //stackten c�karacakt�r
		}
		else if(temp->icerik[0]==']')//yukar�dakiler de�ilse eger ] ise
		{
			while(s.top()->icerik[0]!='[')//stackteki tempin bas�n�n iceri�i [ ise
			{
				listeye_ekle(s.top(),yeni); //stackin bas�ndaki tempi ve yeni listeyi liste_ekleye g�nderir
				s.pop();				//stackten c�kar�r
			}
			s.pop();  //burda stackten c�kar�r
		}
		else if(temp->icerik[0]=='}') //yukar�dakiler de�ilse eger } ise
		{
			while(s.top()->icerik[0]!='{') //stackin bas�ndaki tempin i�erigi { farkl� olana kadar
			{
				listeye_ekle(s.top(),yeni); //listenin bas�ndaki tempi ve yeniyi lisye_ekle ye g�nder
				s.pop();   //stackten c�kar
				
			}
			s.pop();  //burda da stackten c�kar
		}
		else if(s.empty()) s.push(temp);    //yukar�dakiler degilse ve stack bos ise temp i stacke ekle
		else //yukar�dakiler de�ilse
		{
			oncelikU=oncelik(temp->icerik[0]);   //tempin i�eri�inin ilk karakterini ocelik fonk.g�nderir ve oncelikU ya atar
			oncelikA=oncelik(s.top()->icerik[0]);//stackteki bastaki tempin iceriginin ilk karakterini oncelik fonk. g�nderir ve oncelikA ya atar
			if(oncelikU>oncelikA)  //d�nen degerlere g�re kar��last�rma saglan�l�rsa
			{
				s.push(temp); //stacke temp i atas�n
			}
			else  //saglanmaz ise 
			{
				while(oncelikU<=oncelikA) //sart sagland��� m�ddetce
				{
					listeye_ekle(s.top(),yeni);   //stack'i ve yeni listeyi liste_ekleye g�nderir
					s.pop();     //stackten c�kar�r
					if(s.empty()) oncelikA=0;  //stack bos ise oncelikA ya 0 degeri atan�r
					else oncelikA=oncelik(s.top()->icerik[0]);	//bos degilse stackin bas�ndaki tempin i�eriginin 				
				}                                               //ilk karakteri oncelik den d�nen deger atan�r oncelikA'ya
				s.push(temp);    //temp stack'e atan�r
			}
		}
		temp=temp1;     //temp1 temp degiskenine atan�r
	}
	while(!s.empty())  //stack bos olmad�g� m�ddetce
	{
		listeye_ekle(s.top(),yeni);  //stackin bas�ndaki temp ve yeni liste liste_ekle fonk. g�nderilir
		s.pop();   //stackten c�kart�l�r
	}
	free(liste);   //liste icin ayr�lm�� alan bosalt�l�r yada kald�r�l�r (garbage collector)
	return yeni;   //yeni degerini d�nd�recektir.
}

void coz(Listeptr l)   //listeyi l ad�nda listeptr t�r�ndeki l ye atad�k
{
	Elemanptr temp,sayi1,sayi2;  //elemanptr t�r�nde temp,sayi1,sayi2 tan�t�ld�
	temp=l->bas;      //listenin bas�n� tempe atad�
	double sonuc;     //sonuc degiskeni tan�t�ld�
	while(l->bas!=l->son)  //listenin bas� listenin sonundan farkl� oldugu m�ddetce
	{
		if(oncelik(temp->icerik[0])<5&&oncelik(temp->icerik[0])>1) //oncelik fonk.dan gelen degerler kars�last�rmas� saglan�rsa
		{
			sayi1=temp->geri;   //sayi1 e tempin gerisi atan�r
			sayi2=sayi1->geri;  //sayi2 ye sayi1 in gerisi atan�r
			switch(temp->icerik[0])  //tempin i�eri�inin ilk karakteri;
			{
				case '+' : sonuc=atof(sayi2->icerik)+atof(sayi1->icerik); break;//icerikleri aritmetik i�lemlere al�p sonuca atar
				case '-' : sonuc=atof(sayi2->icerik)-atof(sayi1->icerik); break;
				case '*' : sonuc=atof(sayi2->icerik)*atof(sayi1->icerik); break;
				case '/' : sonuc=atof(sayi2->icerik)/atof(sayi1->icerik); break;
				case '^' : sonuc=pow(atof(sayi2->icerik),atof(sayi1->icerik)); break;  //�sl� i�erikler i�in float olarak d�n��t�r�p sonuca atar
				case '%' : sonuc=fmod(atof(sayi2->icerik),atof(sayi1->icerik)); break;  //modunu al�r
			}
			sprintf(temp->icerik, "%2.6f", sonuc);   //karakter katar�n� yazd�r�r
			if(sayi2->geri==NULL)   //sayi2 nin gerisi bos ise
			{
				temp->geri=NULL;   //tempin gerisi bos olsun
				l->bas=temp;       //listenin bas�na tempi ata
			}
			else    //bos de�ilse
			{
				temp->geri=sayi2->geri;   //sayi2nin gerisini tempin gerisine atas�n
				sayi2->geri->ileri=temp;   //sayi2 nin gerisinin ilerisine tempi atas�n
				free(sayi1);       //sayi1 ve sayi2 i�in tahsis edilen alanlar temizlenilir
				free(sayi2);                    //garbage collector
			}
		}
		else if(temp->icerik[0]=='!')   // degilse eger tempin i�eri�inin ilk karakteri ! e esitse
		{
			sayi1=temp->geri;          //tempin gerisini sayi1 e atas�n
			sonuc=1;                   //sonuca 1 degerini atas�n
			if(atoi(sayi1->icerik)!=0)  //sayi1 ini iceri�indeki int deger 0 dan farkl� ise
			{
				for(int i=atoi(sayi1->icerik);i>0;i--) //bu sarta g�re for d�ng�s� olu�turup azalt
				{
					sonuc*=i;    //sonucu i ile carp�p sonuca ekleyelim
				}	
			}
			sprintf(temp->icerik, "%2.1f", sonuc);   //tempin iceri�indeki  sonucu katara ekler
			if(sayi1->geri==NULL)    //sayi1in gerisi bos ise
			{
				temp->geri=NULL;   //tempin gerisini bos yap
				l->bas=temp;       //tempi listenin bas�na aktar
			}
			else        //bos degilse
			{
				temp->geri=sayi1->geri;     //tempin gerisine sayi1 in gerisini atas�n
				sayi1->geri->ileri=temp;    //sayi1in geisinin ilerisine tempi atas�n
				free(sayi1);         //sayi1 i�in ayr�lan alan� bo�altsin
			}
		}
		else if(oncelik(temp->icerik[0])==5)  //yukar�dak� degilse ve oncelikten d�nn deger 5 ise
		{
			sayi1=temp->geri;      //tempin gerisini sayi1 e atas�n
			switch(temp->icerik[0])   //tempin iceri�inin ilk karakteri;
			{
				case 'l' :    //l ise
				if(temp->icerik[1]=='n') sonuc=log(atof(sayi1->icerik));//ln ise sonuca ln islemini uygula
				else if(temp->icerik[2]=='g') sonuc=log10(atof(sayi1->icerik));//log ise log islemini uygula
				break;   //bitir
				case 's' :     //s ise
				if(temp->icerik[1]=='i') sonuc=sin(atof(sayi1->icerik)); //sin ise sonuca sin islemini ata
				else if(temp->icerik[1]=='g')  //degilse ve sg islemi varsa
				{
					if(atof(sayi1->icerik)>0) sonuc=1;   //islem s�f�rdan b�y�kse sonuc 1 olsun
					else if(atof(sayi1->icerik)<0) sonuc=-1;  //s�f�rdan k���k ise -1 olsun
					else sonuc=0;   //o da degilse sonuc 0 olsun
				}
				break; //bitir
				case 'c' :   //c ise
				if(temp->icerik[2]=='s') sonuc=cos(atof(sayi1->icerik));  //cos isemi yap�p sonuca atas�n
				else if(temp->icerik[2]=='t') sonuc=1/tan(atof(sayi1->icerik));   //cot islemi yap�p sonuca atas�n
				break; //bitir
				case 't' : sonuc=tan(atof(sayi1->icerik)); break;  // t ise tan islemini yap�p sonuca atas�n
				case 'a' :   //a ise
				if(temp->icerik[1]=='s') sonuc=asin(atof(sayi1->icerik));   //asin ise asin islemi yap�p sonuca atas�n
				else if(temp->icerik[1]=='t') sonuc=atan(atof(sayi1->icerik));//atan ise atan islemi yap�p sonuca atas�n
				else if(temp->icerik[1]=='c')    //sonraki c ise
				{
					if(temp->icerik[3]=='s') sonuc=acos(atof(sayi1->icerik));  //s ise acos islemi yap�p sonuca atas�n
					else if(temp->icerik[3]=='t') sonuc=1-atan(atof(sayi1->icerik));  //t ise acot islemi yap�p sonuca atas�n
				}
				break; //bitir
			}
			sprintf(temp->icerik, "%2.6f", sonuc);   //tempin i�eri�i sonucu katar� yazar
				if(sayi1->geri==NULL)        //sayi1 in gerisi bos ise
				{
					temp->geri=NULL;     //tempin gerisi bos olsun
					l->bas=temp;         //tempi listenin bas�na atas�n
				}
				else   //bos de�ilse
				{
					temp->geri=sayi1->geri;    //sayi1 in gerisini tempin gerisine atas�n
					sayi1->geri->ileri=temp;   //sayi1 in gerisinin ilerisini temp olu�tursun
					free(sayi1);     //sonra sayi1 i�in olu�turulan alan� bo�alts�n (garbage collector)
				}
		}
	temp=temp->ileri;     //tempin ilerisini tempe atas�n
	//listele(l);
	}
}

double islem(char denklem[])    //islem fonksiyonumuzu olusturduk
{	
	Listeptr liste=yeni_liste();  //liste ad�nda tan�mlamam�z� yapt�k
	int i=krk_knt(denklem);       //denklemi krk_knt fonksiyonuna g�nderip gelen degeri i degiskenine atad�k
	if(i!=-1)    //gelen deger -1'den farkl� ise
	{
		cout<<i+1<<". karakater bilinmiyor."; //iyi 1 artt�r ve yazmay� gerceklestir
		exit(0);      //c�k�sa y�nelt
	}
	bagli_yapma(denklem,liste);  //bagl�_yapma fonksiyonuna denklemi ve listeyi g�nderiyor.
	if(hata(liste)==1) exit(1);  //listeyi hata fonksiyonuna g�nderir hatadan 1 d�nerse c�k�sa git
	//listele(liste);
	sabit_yerlestir(liste);//listeyi  sabit yerlestir fonksiyonuna g�nderiyoruz pi ve exp i�in
	liste=postfix(liste);  //listeyi postfix fonksiyonuna g�nderdikten sonra listeye tekrar atar
	listele(liste);       //listeyi listele fonk. nuna g�nderir
	coz(liste);           //listeyi coz fonksiyonuna g�nderir
	listele(liste);	      //listeleme islemini tekrarlaas�n
	return atof(liste->bas->icerik);;   //listeninbas�ndaki icerigi float degerini d�nd�rs�n
	
}

int main()
{
	double sonuc;  //sonuc icin degi�ken tan�mlad�k
	char denklem[50];  //girilecek denklem i�in de�isken tan�mlamas� yapt�k
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"++      Lutfen Trigonometrik ve Logaritmik ifadeleri () icinde kullaniniz.      ++"<<endl;
	cout<<"++++                Pi Sayisi icin (pi yada PI) kullaniniz.                   ++++"<<endl;
	cout<<"++++++                Exp(e) sayisi icin:exp kullaniniz.                    ++++++"<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"++                                                                              ++"<<endl;
    cout<<"++                Ornek denklem: sin(pi/2)+ln(exp)+log(10)+(3%2)!               ++"<<endl; 
    cout<<"++                                                                              ++"<<endl;                                      
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"Denklemi Yaziniz:"<<endl;
	cin>>denklem;	//denklem girisini ald�k
	cout<<"Denklemin Postfixi ve Sonucu:";
	sonuc=islem(denklem); //denklemi islem fonksiyonuna g�nderdik
	cout<<endl;
	cout<<"Denklemin Yuvarlatilmis Sonucu : "<<endl<<round(sonuc);
}
