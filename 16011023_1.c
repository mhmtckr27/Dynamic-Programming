#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


void printMatrix(double** probabilityMatrix, int N)
{
    int i;//dongu degiskeni
    int j;//dongu degiskeni
    printf("________________________________________________________________________\n");
    //matrisi yazdirma islemi
    for (i = 0; i < N + 1; i++)
    {
        printf("|");
        for (j = 0; j < N + 1; j++)
        {
            printf("%lf|", probabilityMatrix[i][j]);
        }
        printf("\n");
    }
    printf("========================================================================\n");
}

double sumProbabilities(double** probabilityMatrix, int N)
{
    int i;//dongu degiskeni
    double result = 0.0;//A takiminin seriyi kazanma ihtimali
    //A takiminin seriyi kazanmasi icin en az oynanan mac sayisinin yarisindan bir fazla kadar mac kazanmasi gerekir. ornegin 7 macin 4 u.
    //i degiskenini bu sayidan baslatarak toplam mac sayisina kadar ilerler ve
    //A takiminin seriyi kazanmasi ihtimalini hesaplariz.
    //ornegin A takiminin 7 macin 4'unu(i = 4), 5'ini (i=5), 6'sini, 7'sini kazanmasi ihtimallerini toplayarak sonuca ulasiriz.
    for (i = (N + 1) / 2; i < N + 1; i++)
    {
        result += probabilityMatrix[N][i];
    }
    return result;
}

double P(double p, int N)
{
    int i;//dongu degiskeni
    int j;//dongu degiskeni
    double** probabilityMatrix = (double**)calloc(N + 1, sizeof(double*));//olasiliklar matrisi
    //matrisin satir indeksi oynanan mac sayisini, sutun indeksi de A takiminin kazandigi mac sayisini belirtiyor. 
    //ornegin probabilityMatrix[1][1] = 1 mac oynanip o maci da A takiminin kazanmasi ihtimalidir.
    //ornek 2: probabilityMatrix[7][4] = oynanan 7 macin 4 unu A takimi, 3 unu B takimi kazanmistir.
    //bu sebeple; hesaplamalarimiz bittikten sonra probabilityMatrix[N][(n+1)/2 + 1] den baslayarak probabilityMatrix[n][n] e kadar
    //olan degerleri toplayarak A takiminin seriyi kazanma olasiligini hesaplamis oluruz.
    //matrisin sag ust tarafini (sutun indeksinin satir indeksinden fazla oldugu durum) 0 ile doldurdum A takiminin kazandigi mac sayisi
    //toplam mac sayisindan fazla olamaz.

    for (i = 0; i < N + 1; i++)
    {
        probabilityMatrix[i] = (double*)calloc(N + 1, sizeof(double));
    }
    probabilityMatrix[0][0] = 1.0;

    //i her adimda degiserek toplam oynanan mac sayisini temsil ediyor.
    for (i = 1; i < N + 1; i++)
    {
        //j A takiminin kazandigi mac sayisini temsil ediyor.
        for (j = 0; j < i + 1; j++)
        {
            //A takimi i kadar macta hic mac kazanamamasi durumunda bu if'e girilir.
            //ayni kolonda ust satirdaki degeri tasiyip B takiminin kazanmasi ihtimaliyle carpariz.
            if (j == 0)
            {
                probabilityMatrix[i][j] = probabilityMatrix[i - 1][j] * (1.0 - p);
            }
            else
            {
                probabilityMatrix[i][j] = probabilityMatrix[i - 1][j] * (1.0 - p) + probabilityMatrix[i - 1][j - 1] * p;
            }
        }
    }
    printMatrix(probabilityMatrix, N);
    return sumProbabilities(probabilityMatrix, N);
}

int main()
{
    // A takiminin bir maci kazanma olasiligi
    double p;
    //toplam mac sayisi
    int n;

    printf("A takiminin kazanma olasiligini giriniz (ornek 0.4): ");
    scanf("%lf", &p);
    printf("Toplam oynanacak mac sayisini giriniz (ornek 7): ");
    scanf("%d", &n);

    printf("%f\n", P(p, n));
    return 0;
}
