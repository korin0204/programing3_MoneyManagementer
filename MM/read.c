#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "read.h"
#include "data.h"
#include "utility.h"

//csvファイルの最終行から収支の合計を表示する
void read_money(void){
	time_t current = time(NULL);
    struct tm *timer = localtime(&current);
	int year = timer->tm_year + 1900;
	int month = timer->tm_mon + 1;
	int day = timer->tm_mday;
	        FILE *fp;
			char line[256];
			char filename[200];
			sprintf(filename,"./archives/%d/%02d/%d%02d%02d.csv",year,month,year,month,day);
			int lineNumber = count_lines(filename);
			printf("./archives/%d/%02d/%d%02d%02d.csv",year,month,year,month,day);
            fp = fopen(filename,"r");
            if(fp == NULL)
		    printf("ファイルをオープンできません。\n");
	        else{
                printf("ファイルをオープン。\n");
				for (int i = 0; i < lineNumber; i++) {
                fgets(line, sizeof(line), fp);
				}
				fgets(line, sizeof(line), fp); // 指定した行を読み込む
                printf("読み込んだ行: %s", line);
            fclose(fp);
            }
}

//csvファイルの中身を全て表示する関数
void read_all_money(void){
	time_t current = time(NULL);
    struct tm *timer = localtime(&current);
	int year = timer->tm_year + 1900;
	int month = timer->tm_mon + 1;
	int day = timer->tm_mday;
	FILE *file;
	char filename[200];
	printf("./archives/%d/%02d/%d%02d%02d.csv",year,month,year,month,day);
	sprintf(filename,"./archives/%d/%02d/%d%02d%02d.csv",year,month,year,month,day);
    file = fopen(filename,"r");
	char line[256];
	if (file == NULL) {
		printf("ファイルを開けませんでした。\n");
	}
	printf("読み込んだ行\n");
	int lineNo1;
	long incomes1;
	long expenses1;
	char str1[256];
	int lineNo2;
	long incomes2;
	long expenses2;
	char str2[256];
	fgets(line, sizeof(line), file);
	sscanf(line,"%d,%ld,%ld,%s",&lineNo1,&incomes1,&expenses1,str1);
	while (fgets(line, sizeof(line), file) != NULL) {
		sscanf(line,"%d,%ld,%ld,%s",&lineNo2,&incomes2,&expenses2,str2);
		printf("%d,%ld,%ld,%s\n", lineNo2, incomes2 - incomes1, expenses2 - expenses1, str2);
		lineNo1 = lineNo2;
		incomes1 = incomes2;
		expenses1 = expenses2;
		strcpy(str1,str2);
	}	
	fclose(file);
}

//csvファイルの過去の履歴を表示する関数
//引数には表示したいyyyy/mm/ddを指定する
void read_past_money(int year,int month,int day){
	FILE *file;
	char filename[200];
	printf("./archives/%d/%02d/%d%02d%02d.csv",year,month,year,month,day);
	sprintf(filename,"./archives/%d/%02d/%d%02d%02d.csv",year,month,year,month,day);
	file = fopen(filename,"r");
	char line[256];
	if (file == NULL) {
		printf("ファイルを開けませんでした。\n");
	}else{
		printf("読み込んだ行\n");
	    while (fgets(line, sizeof(line), file) != NULL) {
		printf("%s", line);
	    }
	    fclose(file);
	}
	
}
//テキストファイルの中身を表示する関数
//テキストファイルは./data/message.txt
void read_message(void){
	FILE *file;
	char filename[200];
	printf("./data/message.txt");
	sprintf(filename,"./data/message.txt");
	file = fopen(filename,"r");
	char line[256];
	if (file == NULL) {
		printf("ファイルを開けませんでした。\n");
	}
	printf("読み込んだ行\n");
	while (fgets(line, sizeof(line), file) != NULL) {
		printf("%s", line);
	}
	fclose(file);
}

//yyyy/mm/yyyymmdd.csvという階層構造になっているディレクトリのcsvファイルに対して、各日にちの最終行の値を読み取って合算する関数
//引数には表示したいyyyy/mmを指定する
long read_month_money(int year,int month){
	int tmp1 = 0;
	long MonthIncome = 0;
	long MonthExpense = 0;
	char tmp[256];
	long tmp2;
	long tmp3;
	FILE *file;
	char filename[200];
	int maxday = 30;
	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 ||month == 12){
		maxday = 31;
	}
	for(int day = 1; day<=maxday; day++){
		sprintf(filename,"./archives/%d/%d/%d%02d%02d.csv",year,month,year,month,day);
		file = fopen(filename,"r");
	char line[256];
	if (file == NULL) {
		printf("その日付のファイルを開けませんでした。\n");
	}else{
		char line[256];
		for (int i = 1; i < count_lines(filename); i++)
		{
			fgets(line, sizeof(line), file); // 指定した行番号までファイルポインタを移動
		}
		fscanf(file, "%d,%ld,%ld,%s", &tmp1, &tmp2, &tmp3, tmp);
		MonthIncome += tmp2;
		MonthExpense += tmp3;
	}
	fclose(file);
	}
	return MonthIncome - MonthExpense;
}

// //テキストファイルの中身を表示する関数
// //xは引数に指定した二つの数字の範囲内の数字からランダムに決定する
// //テキストファイルは./data/assistant/hello/x.txt
// void read_yuuka_message(int a, int b){
// 	FILE *file;
// 	char filename[200];
// 	int x = rand()%(b-a+1)+a;
// 	printf("./data/assistant/hello/%d.txt",x);
// 	sprintf(filename,"./data/assistant/hello/%d.txt",x);
// 	file = fopen(filename,"r");
// 	char line[256];
// 	if (file == NULL) {
// 		printf("ファイルを開けませんでした。\n");
// 	}
// 	printf("読み込んだ行\n");
// 	while (fgets(line, sizeof(line), file) != NULL) {
// 		printf("%s", line);
// 	}
// 	fclose(file);
// }

//指定した月のディレクトリーにある各日付ごとのcsvファイルの末行の値を読み取って、収支を合算して表示関数
//引数には表示したいyyyy/mmを指定する


// void read_curent_money(void){
//     FILE *file;
//     char line[256];
//     char keyword[256];
//     printf("キーワードを入力してください: ");
//     fgets(keyword, sizeof(keyword), stdin);
//     keyword[strcspn(keyword, "\n")] = '\0'; // 改行文字を削除
//     file = fopen("data.csv", "r");
//     if (file == NULL) {
//         printf("ファイルを開けませんでした。\n");
//         return 1;
//     }
//     while (fgets(line, sizeof(line), file) != NULL) {
//         if (strstr(line, keyword) != NULL) { // キーワードが含まれる行のみを読み込む
//             printf("読み込んだ行: %s", line);
//         }
//     }
//     fclose(file);
// }
// void read_curent_money2(void){
//     FILE *file;
//     char line[256];
//     int lineNumber;
//     printf("読み込む行番号を入力してください: ");
//     scanf("%d", &lineNumber);
//     file = fopen("data.csv", "r");
//     if (file == NULL) {
//         printf("ファイルを開けませんでした。\n");
//         return 1;
//     }
//     for (int i = 1; i < lineNumber; i++) {
//         fgets(line, sizeof(line), file); // 指定した行番号までファイルポインタを移動
//     }
//     fgets(line, sizeof(line), file); // 指定した行を読み込む
//     printf("読み込んだ行: %s", line);
//     fclose(file);
// }
