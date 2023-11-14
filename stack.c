#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct Node {
    char data;
    struct Node* prev;
    struct Node* next;
}BListe;
BListe *top = NULL;
int sesliHarf(char c) {
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}
int sessizHarf(char c) {
    return !sesliHarf(c);
}
void pop()
{
    BListe *n;
    n = top;
    top = n->prev;
    free(n);
}
void yazdir()
{
        BListe *gecici = top;
        printf("Stack:  \n");
        while (gecici != NULL) {
            printf("%c\n", gecici->data);
            gecici = gecici->prev;
        }
        printf("\n");
}
int push(char n) {
	static int adim_sayisi = 1;
	printf("gelen eleman: %c \n", n);
	static int i = 0;
	
	BListe *yeni_kayit=(BListe*)malloc(sizeof(BListe));
	yeni_kayit->data=n;
	if(top == NULL) {
		yeni_kayit->prev = NULL;
        yeni_kayit->next = NULL;
        top = yeni_kayit;
	} else {
		top->next = yeni_kayit;
        yeni_kayit->next = NULL;
        yeni_kayit->prev = top;
        top = yeni_kayit;
	}
	printf("eklenen eleman: %c \n", top->data);
	printf("adim sayisi: %d \n", adim_sayisi);
	adim_sayisi++;
	yazdir();
	while (i > 0 && top->prev != NULL && ((sesliHarf(n) && sesliHarf(top->prev->data)) || (sessizHarf(n) && sessizHarf(top->prev->data)))) {
        printf("cikarilan eleman: %c \n", top->data);
        pop();
        i--;
        printf("adim sayisi: %d \n", adim_sayisi);
        adim_sayisi++;
        yazdir();
    }
    i++;
    printf("\n");
	return i;
}


void randomDizi() {
	int i = 0;
    char dizi[10];
    srand(time(NULL));
    for (i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            dizi[i] = "AEIOU"[rand() % 5];
        } else {
            dizi[i] = "BCDFGJKLMNPQSTVXZHRWY"[rand() % 21];
        }
    }
    for (i = 9; i > 0; i--) {
        int j = rand() % (i + 1);
        char gecici = dizi[i];
        dizi[i] = dizi[j];
        dizi[j] = gecici;
    }
	for (i = 0; i < 10; i++) {
        printf("%c", dizi[i]);
    }
    printf("\n");
    int sonuc = 0;
	while(1) {
		sonuc = push(dizi[rand() % 10]);
		if(sonuc == 6) {
			break;
		}
	}
}

int main(int argc, char *argv[]) {
	randomDizi();
	yazdir();
	return 0;
}
