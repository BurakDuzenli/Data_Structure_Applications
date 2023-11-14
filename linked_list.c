#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct Liste{
	int numara;
	char adi[25];
	char soyadi[25];
	struct Liste *sonraki;
	int sirasi;
}BListe;

BListe *ilk = NULL, *son = NULL;
int sirasi = 1; 
void ekleme(int numara, char *adi, char *soyadi) {
	
	BListe *gecici;
	gecici = ilk;
	while(gecici != NULL) {
		if(gecici->numara == numara) {
			printf("Ayni numarali kayit eklenemez! \n");
			return;
		}
		gecici = gecici->sonraki;
	}
	BListe *kayit = (BListe*)malloc(sizeof(BListe));
	kayit->numara = numara;
	strcpy(kayit->adi, adi);
	strcpy(kayit->soyadi, soyadi);
	kayit->sirasi = sirasi++;
	kayit->sonraki = NULL;
	
	if(ilk == NULL) {
		ilk = kayit;
		son = kayit;
	} else{
		son->sonraki = kayit;
		son = kayit;
	}
}

BListe *arama(char *soyadi, char cvp, BListe *sonuc) {
	BListe *gecici;
	if(cvp == 'e'){
		gecici = ilk;
	} else {
		gecici = sonuc;
	}
	while (gecici != NULL) {
        if (strcmp(gecici->soyadi, soyadi) == 0 && cvp == 'e') {
            return gecici; 
        }
        gecici = gecici->sonraki;
        cvp = 'e';
    }	
	 
    
    return NULL;
}

void silme(int silinecek_num) {
	BListe *gecici, *bironceki, *gecici2;
	gecici = ilk;
	while(gecici != NULL) {
		if(gecici->numara == silinecek_num) {
			gecici2 = gecici;
			while(gecici2->sonraki != NULL) {
				gecici2->sonraki->sirasi--;
				gecici2 = gecici2->sonraki;
			}
			break;
		}
		bironceki = gecici;
		gecici = gecici->sonraki;
	}
	if(gecici != NULL) {
		if(gecici == ilk) {
			if(son == ilk) {
				ilk = NULL;
				son = NULL;
			} else {
				ilk = ilk->sonraki;
			}
		} else {
			if(gecici == son) {
				bironceki->sonraki = NULL;
				son = bironceki;
			} else {
				bironceki->sonraki = gecici->sonraki;
			}
		}
		free(gecici);
	} else {
		printf("Aranýlan kayýt bulunamadý");
	}
	
}

int listeleme() {
	BListe *gecici;
	gecici = ilk;
	if(gecici == NULL) return 0;
	while(gecici != NULL) {
		printf("%d. %d#%s#%s\n",gecici->sirasi, gecici->numara, gecici->adi, gecici->soyadi);
		gecici = gecici->sonraki;
	}
	return 1;
}

void tasima(int istenen_num, int n) {
	BListe *gecici, *bironceki, *gecici2, *gecici3 = ilk, *gecici4 = ilk;
	gecici = ilk;
	bironceki = ilk;
	int i;
	while(gecici != NULL) {
		if(gecici->numara == istenen_num) {
			gecici2 = gecici;
			while(gecici2->sonraki != NULL) {
				gecici2->sonraki->sirasi--;
				gecici2 = gecici2->sonraki;
			}
			break;
		}
		bironceki = gecici;
		gecici = gecici->sonraki;
	}
	if(n < 1 || n > son->sirasi){
		printf("Liste boyutunun dýþýnda bir boyut girdiniz.\n");
        return;
	}
	if(n == 1) {
		bironceki->sonraki = gecici->sonraki;
		gecici->sonraki = ilk;
		ilk = gecici;
		gecici->sirasi = 1;
		gecici2 = gecici;
		while(gecici2->sonraki != NULL) {
			gecici2->sonraki->sirasi++;
			gecici2 = gecici2->sonraki;
		}
	} else {
		if(gecici->sirasi == 1) {
			ilk = ilk->sonraki;
			gecici4 = ilk;
			gecici3 = ilk;
		}else if(gecici->sirasi == son->sirasi) {
			son = bironceki;
		}
		bironceki->sonraki = gecici->sonraki;
		if(gecici->sirasi != son->sirasi){
			while(gecici3 != NULL) {
			if(gecici3->sirasi == n) {
				break;
			}
			gecici3 = gecici3->sonraki;
		}
		gecici->sonraki = gecici3;
	}
		while(gecici4 != NULL) {
			if(gecici4->sirasi== n -1) {
				break;
			}
			gecici4 = gecici4->sonraki;
		}

		gecici4->sonraki = gecici;
		gecici->sirasi = n;
		gecici2 = gecici;
		while(gecici2->sonraki != NULL) {
			gecici2->sonraki->sirasi++;
			gecici2 = gecici2->sonraki;
		}
	}
	listeleme();
}


char* bosluk_sil(char *str)
{
  int id=0, pos=0;

  while (str[id]) {
    if(!isspace(str[id])) {
       str[pos++] = str[id];
    }
    id++;
  }
  str[pos] = '\0';

  return str;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Turkish");
	FILE* dosya = fopen("text.txt", "r");

    char satir[100];
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        int numara;
        char adi[25];
        char soyadi[25];
        char *alici;
        alici = strtok(satir, "#");
        if (alici) {
        	numara = atoi(alici);
        	alici = strtok(NULL, "#"); 
    	} 

    	if (alici) {
        	strncpy(adi, alici, sizeof(adi));
        	alici = strtok(NULL, "#"); 
    	} 

    	if (alici) {
        	strncpy(soyadi, alici, sizeof(soyadi));
			alici = strtok(NULL, "#"); 
    	} 
    	bosluk_sil(soyadi);
        ekleme(numara, adi, soyadi);
    }
    fclose(dosya);
    while(1) {
    	int kullanici_cvp;
    	char kullanici_cvp_char;
    	int kullanici_num;
    	int kullanici_num2;
    	char kullanici_ad[50];
    	char kullanici_soyad[50];
    	int kullanici_aranacak_num;
    	printf("Programima hosgeldiniz! \n");
    	printf("1. Listeleme\n");
    	printf("2. Ekleme\n");
    	printf("3. Arama\n");
    	printf("4. Silme\n");
    	printf("5. Taþýma\n");
    	printf("6. Çýkýþ\n");
    	printf("Yapmak istediðiniz iþlemi seçin: ");
    	scanf("%d", &kullanici_cvp);
    	switch(kullanici_cvp) {
    		case 1: //hallettim
    			listeleme();
    			break;
    		case 2: //hallettim
				printf("eklemek istediðiniz kaydýn numarasýný, adýný ve soyadýný aralarýnda boþluk olacak þekilde ve türkçe karakter kullanmadan giriniz: ");
				scanf("%d %s %s", &kullanici_num, kullanici_ad, kullanici_soyad);
				ekleme(kullanici_num, kullanici_ad, kullanici_soyad);
				break;
			case 3: //hallettim
                
                    printf("Soyadýný aramak istediðiniz kaydý giriniz: ");
                    char aranacak_soyadi[25];
                    kullanici_cvp_char = 'e';
                    scanf("%s", aranacak_soyadi);
                    BListe *sonuc = arama(aranacak_soyadi, kullanici_cvp_char, sonuc);
                    while (1) {
                    if (sonuc != NULL) {
                        printf("Bulunan Kayýt: %d. %d#%s#%s\n", sonuc->sirasi, sonuc->numara, sonuc->adi, sonuc->soyadi);
                        printf("Aramak istenen kayýt bulundu mu? (e/h): ");
                        scanf(" %c", &kullanici_cvp_char);
                    
                        if (kullanici_cvp_char == 'h') {
                        	sonuc = arama(aranacak_soyadi, kullanici_cvp_char, sonuc);
                        } else {
                        	break;
						}
                    } else {
                        printf("Aranan kayýt bulunamadý.\n");
                        break; 
                    }
                }
                break;
            case 4: // hallettim
				printf("Silinecek numarayý giriniz: ");
				scanf("%d", &kullanici_num);
				silme(kullanici_num);
				break;
			case 5: //hallettim
				printf("Taþýnmak istenen numarayý ve hangi sýraya taþýnmak istendiðini giriniz: ");
				scanf("%d %d", &kullanici_num, &kullanici_num2);
				tasima(kullanici_num, kullanici_num2);
				break;
			case 6:
				dosya = fopen("text.txt", "w");
                BListe *gecici = ilk;
                while (gecici != NULL) {
                    fprintf(dosya, "%d#%s#%s\n", gecici->numara, gecici->adi, gecici->soyadi);
                    gecici = gecici->sonraki;
                }
                fclose(dosya);
                return 0;
				break;
			default:
				printf("Böyle bir iþlem yok.");
				break;	
		}
	}    
	return 0;
}
