#ifndef _DATA_H_
#define _DATA_H_

extern int GlobalYear;
extern int GlobalMonth;
extern int GlobalDay;
extern char GlobalFilename[200];

typedef struct{
    char userName[100];
    int No;
    long incomes;
    long expenses;
    char tagline[200];
}moneyData;

#endif