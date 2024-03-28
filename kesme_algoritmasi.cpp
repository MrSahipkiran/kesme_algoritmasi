#include <stdio.h>
#include <stdlib.h>

struct parcaBilgi{
	int adet;
	int boyut;
	struct parcaBilgi *sonraki;
};
struct parcaBilgi	*head =	NULL;
struct parcaBilgi 	*tail =	NULL;

struct cubukBilgi{	//bu kısımda gerekli olursa diye struct içerisinde: kacıncı çubuk oldugu-kalan çubuk boyutu-çubuktaki parça sayısı - hangi parçalar ve boyutları-- bilgisini tuttum.
	int sira;
	int artanBoyut;
	int parcaSayisi;
	int parcalar[6];
	struct cubukBilgi *sonraki;
};
struct cubukBilgi	*head2 =	NULL;
struct cubukBilgi 	*tail2 =	NULL;

void struct_Ekle(int gelenAdet,int gelenBoyut){
	struct parcaBilgi *yeni = (struct parcaBilgi*)malloc(sizeof(struct parcaBilgi));
	if(head == NULL ){
		yeni->adet	=gelenAdet;
		yeni->boyut	=gelenBoyut;
		yeni->sonraki=NULL;
		head=yeni;tail=yeni;
	}
	else{
		tail->sonraki=yeni;
		yeni->adet	=gelenAdet;
		yeni->boyut	=gelenBoyut;
		yeni->sonraki=NULL;
		tail=yeni;
	}
}

int eleman_Sayisi_Bul(){
	int diziBoyut=0;
	struct parcaBilgi *temp=head;
	while(temp!=NULL){
		diziBoyut  +=	temp->adet;
		temp		= temp->sonraki;
	}
	return diziBoyut;
}

int * siraliDiziYap(int diziBoyut){
	struct parcaBilgi *temp=head;
	static int dizi[100];				//dizi oluştur
	
	int sayac=0;
	for(int i=0;i<diziBoyut;i++){		//diziye verileri ekle
		for(int j=0;j<temp->adet;j++){
			dizi[sayac]=temp->boyut;
			sayac++;
		}
		if(temp->sonraki != NULL)temp	= temp->sonraki;		
	}
	
	int temp1=0;
	for(int i=0;i<diziBoyut-1;i++){			//diziyi sırala
		for(int j=i+1;j<diziBoyut;j++){
			if(dizi[i]>dizi[j]){
				temp1=dizi[j];
				dizi[j]=dizi[i];
				dizi[i]=temp1;
			}
		}
	}
	return dizi;
}


void minimumFireBul(int dizi[100],int cubukBoyutu,int diziBoyutu){
	int sayac=1;
	int i=diziBoyutu-1;
	
	struct cubukBilgi *yeni = (struct cubukBilgi*)malloc(sizeof(struct cubukBilgi));	//ilk çubuğu oluşturduk      
	yeni->sira	=	1;
	yeni->artanBoyut	=	cubukBoyutu;
	yeni->parcaSayisi	=	0;
	yeni->sonraki=NULL;
	head2=yeni;tail2=yeni;			
	
	struct cubukBilgi *temp2	=	head2;
	while(i>=0){																//kesme işlemlere
		for(int j=0;j<sayac;j++){												//cubuklarda gezıyoruz
			if(temp2->artanBoyut	<	dizi[i]){		//eğer bulunuduğumuz çubukta kesilecek kısım yetersizse							
				if(temp2->sonraki	!=	NULL)	temp2	=	temp2->sonraki;		//eğer kesmek istedğimiz değer kesilebilir değerden büyükse sonraki çubuğa geçiyoruz
				
				else{															//ancak sonraki çubuk yoksa yeni çubuğu oluşturuyoruz
					struct cubukBilgi *yeni = (struct cubukBilgi*)malloc(sizeof(struct cubukBilgi));	    
					tail2->sonraki=yeni;
					yeni->sira	=	tail2->sira+1;
					yeni->artanBoyut	=	cubukBoyutu;
					yeni->parcaSayisi	=	0;
					yeni->sonraki=NULL;
					tail2=yeni;
					sayac++;
					temp2=head2;
				}
			}
			else {										//eğer bulunuduğumuz çubukta kesilecek kısım yeterliyse(KESME İŞLEMİ)
				temp2->artanBoyut	-=	dizi[i];
				temp2->parcaSayisi++;
				temp2->parcalar[temp2->parcaSayisi-1]=dizi[i];
				temp2=head2;
				i--;
				break;
			}
		}
	}
}

void toplam_fire(){
	struct cubukBilgi *temp2=head2;
	int toplamFire=0;
	while(temp2	!= NULL){
		toplamFire	+=	temp2->artanBoyut;
		temp2		 =	temp2->sonraki;
	}
	printf("\nTOPLAM FIRE = %.1f metredir.",(float)toplamFire/100);
}

void kesme_Bilgi(){
	struct cubukBilgi *temp	=	head2;
	
	while(temp	!=	NULL){
		printf("\n%d. cubugu %d parcaya ayrilmistir.	",temp->sira,temp->parcaSayisi);
		printf("kalan=%d 	",temp->artanBoyut);
		for(int i=0; i<temp->parcaSayisi;i++){
			printf("%d	",temp->parcalar[i]);
		}
		temp=temp->sonraki;
	}
}

int main(int argc, char *argv[]) {
	int uzunluk;
	int adet;
	int cubukBoyu;
	printf("CUBUK BOYUTUNU CM CINSINDEN GIRINIZ	");
	scanf("%d",&cubukBoyu);
	printf("CIKMAK ICIN '-1' GIRINIZ");
	printf("\nONCE ADET SAYISINI SONRA CM CINSINDEN PARCA BOYUTUNU GIRINIZ\n");
	
	
	while(1){//değerleri al
		scanf("%d",&adet);
		scanf("%d",&uzunluk);
		if(adet==(-1)	||	uzunluk==(-1))break;
		struct_Ekle(adet,uzunluk);
	}
	
	int diziBoyut=	eleman_Sayisi_Bul();	//toplam kesilecek parça sayısını bul
	int *dizi;
	dizi	 =	siraliDiziYap(diziBoyut);	//sıralanan diziyi oluşturduğumuz değişkene ata
	
	/*for(int a=0;a<diziBoyut;a++){			//sıralı diziyi kontrol amacıyla yazdırabilirsin
		printf("%d	",dizi[a]);
	}*/
	
	minimumFireBul(dizi,cubukBoyu,diziBoyut);	//parçalara ayır
	toplam_fire();								//toplam fireyi minumum bul
	kesme_Bilgi();
}

