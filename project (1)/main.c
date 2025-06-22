
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
#define NAMESIZE 50
void displayMainMenu();
void addBook (char [][NAMESIZE] ,int [],double [],int *);
void removeBook (char [][NAMESIZE] ,int [], double [], int *);
void searchForBook(char [][NAMESIZE] ,int [], double [], int *);
void uploadDataFile (char [][NAMESIZE] ,int[], double[], int *);
void updateDataFile(char [][NAMESIZE] ,int [], double [], int *);
void printBooks (char [][NAMESIZE] ,int [], double [],int *);
int InArray (int,int[],int);
int main()
{
    char names [MAXSIZE][NAMESIZE];
    int BinNum[MAXSIZE];
    double prices[MAXSIZE];
    int size=0,operation;
    printf ("Welcome to my bookStore management system :\n");
    printf ("uploading data file ...\n");
    uploadDataFile (names,BinNum,prices,&size);
    printf ("data file uploaded\n");
    printf ("\n");
    do
    {
        displayMainMenu();
        scanf ("%d",&operation);
         switch (operation)
        {
        case 1:
            addBook (names,BinNum,prices,&size);
            break;
        case 2:
            removeBook (names,BinNum,prices,&size);
            break ;
        case 3:
            searchForBook (names,BinNum,prices,&size);
            break ;
        case 4:
            printBooks (names,BinNum,prices,&size);
            break;
        case 5:
            printf ("updating data file ...\n");
            updateDataFile (names,BinNum,prices,&size);
            printf ("data file updated\n");
            break ;
        default :
            printf ("invalid input please try again\n");
        }
    }while (operation != 5);
    printf ("\n");
    printf ("thank your for using my bookstore management system. Goodbye\n");
    return 0;
}
void displayMainMenu()
{
    printf ("please select an operation (1-5)\n1-add a book:\n2- remove a book:\n3- search for a book:\n4- print book list:\n5- exit system:\n");
        printf ("\n");
}

void addBook (char names[][NAMESIZE],int BinNum[],double prices[],int *s)
{
    int bin,shift=*s;
    double price;
    char name [NAMESIZE];
    if (*s == MAXSIZE)
    {
        printf ("the list is full\n");
        printf("\n");
        return ;
    }
     printf("enter bin number for book\n");
            scanf ("%d",&bin);
        if (InArray(bin,BinNum,*s)==1)
         {
            printf ("this bin number already exist.\n");
            printf("\n");
            return;
            }
    printf ("enter name of the book\n");
    scanf ("%s",name);
    printf ("enter price of book\n");
    scanf ("%lf",&price);
    for (int k=0;k<*s;k++)
    {
        if (BinNum[k]>bin)
        {
            shift = k;
            break ;
        }
    }
    for (int j=*s;j>= shift;j--)
    {
        strcpy (names[j],names[j-1]);
        BinNum [j] = BinNum [j-1];
        prices [j]= prices [j-1];
    }
    strcpy (names[shift],name);
    BinNum [shift]= bin ;
    prices[shift]= price;
    (*s) ++;
    printf ("book with bin %d has been added\n",bin);
    printf ("\n");
}

void removeBook (char names[][NAMESIZE],int BinNum[], double prices[], int *s)
{
    int bin;
    int i;
    if (*s == 0)
    {
        printf ("the list is empty\n");
        printf ("\n");
        return;
    }
    printf ("enter bin number for book to remove\n");
            scanf ("%d",&bin);
    if (InArray (bin,BinNum,*s)==0)
    {
        printf ("book with bin %d does no exist\n",bin);
        printf("\n");
        return;
    }
    for (i=0 ; i<*s;i++)
    {
        if (BinNum[i]== bin)
        {
            for (int j=i;j<*s-1;j++)
               {
                BinNum[j]=BinNum[j+1];
                prices[j] = prices[j + 1];
                strcpy (names[j],names[j+1]);
               }
        }
    }
    (*s)--;
    printf ("book with bin %d has been removed\n",bin);
    printf("\n");
}

int InArray (int bin,int BinNum[],int s)
{
    for (int i=0;i<s;i++)
    {
        if (bin == BinNum[i])
            return 1;
    }
    return 0;
}

void searchForBook(char names[][NAMESIZE],int BinNum[], double prices[], int *s)
{
    int binSearch;
    if (*s == 0)
    {
        printf ("the list is empty\n");
        printf("\n");
        return;
    }
    printf ("enter bin number for book to search for. \n");
    scanf ("%d",&binSearch);
    if (InArray (binSearch,BinNum,*s)==0)
    {
        printf ("the bin number does not exist in the list\n");
        printf("\n");
        return ;
    }
    for (int i=0;i<*s;i++)
    {
        if (binSearch == BinNum[i])
            printf("name = %-40s      bin# = %d     price = %.2f\n",names[i],binSearch,prices[i]);
    }

    printf("\n");

}
void printBooks (char names[][NAMESIZE],int BinNum[],double prices[],int *s)
{
    double avg;
    double sum=0;
    for (int i=0;i<*s;i++)
    {
        printf ("name = %-40s     bin# = %d     price = %.2f\n",names[i],BinNum[i],prices[i]);
    }
     for (int i=0;i<*s;i++)
        sum += prices[i];
    avg = sum/(*s);
    printf ("avg = %.2f",avg);
    printf("\n");
}
void uploadDataFile (char names[][NAMESIZE],int BinNum[], double prices[], int *size )
{
    int i=0;
    FILE *in;
    in = fopen("books.txt","r");
    for (i=0;i<=MAXSIZE&& fscanf(in,"%s %d %lf",names[i],&BinNum[i],&prices[i])!= EOF;i++);
    *size = i;
    fclose (in);
}
void updateDataFile(char names[][NAMESIZE],int BinNum[], double prices[], int *size)
{
    int i =0;
    FILE *out;
    out = fopen("books.txt","w");
    for (i;i<*size;i++)
    {
        fprintf (out,"%s %d %f\n",names[i],BinNum[i],prices[i]);
    }
    fclose (out);
}
