#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include "write.h"
#include "data.h"
#include "utility.h"

int GlobalYear = 0;
int GlobalMonth = 0;
int GlobalDay = 0;
char GlobalFilename[200] = "./plan/0000/00/00000000.csv";

void write_money(moneyData *a)
{
	// プログラムを起動してから日付を跨ぐとyear,month,dayが更新されない
	// 毎回更新するために関数の中にtimeを入れる必要がある
	time_t current = time(NULL);
	struct tm *timer = localtime(&current);
	int year = timer->tm_year + 1900;
	int month = timer->tm_mon + 1;
	int day = timer->tm_mday;
	FILE *fp;
	char filename[200];
	printf("./archives/%d/%02d/%d%02d%02d.csv", year, month, year, month, day);
	sprintf(filename, "./archives/%d/%02d/%d%02d%02d.csv", year, month, year, month, day);
	switch (file_exists(filename))
	{
	case 0: // ファイルが存在しない場合(初期化をしてbreakしずに次のcaseに移る)
		fp = fopen(filename, "w");
		if (fp == NULL)
		{
			printf("ファイルをオープンできません。\n");
			fprintf(fp, "0,0,0,0\n");
		}
		else
		{
			fprintf(fp, "0,0,0,0\n");
		}
		fclose(fp);
	case 1: // ファイルが存在する場合
		fp = fopen(filename, "a");
		if (fp == NULL)
			printf("ファイルをオープンできません。\n");
		else
		{
			printf("編集項目を選んで下さい\n1.収入 2.支出");
			int x;
			scanf("%d", &x);
			switch (x)
			{
			case 1:
				printf("収入を入力して下さい");
				long inc;
				scanf("%ld", &inc);
				a->No++;
				a->incomes += inc;
				fprintf(fp, "%d,%ld,%ld,0\n", a->No, a->incomes, a->expenses);
				break;
			case 2:
				printf("支出を入力して下さい");
				long exp;
				scanf("%ld", &exp);
				a->No++;
				a->expenses += exp;
				fprintf(fp, "%d,%ld,%ld,0\n", a->No, a->incomes, a->expenses);
				break;
			}

			fclose(fp);
		}
	}
}

void write_plan(void)
{
	int year;
	int month;
	printf("年を入力して下さい\n");
	scanf("%d", &year);
	printf("月を入力して下さい\n");
	scanf("%d", &month);
	FILE *fp;
	char filename[200];
	printf("./plan/%d/%02d/%d%02d.csv", year, month, year, month);
	sprintf(filename, "./plan/%d/%02d/%d%02d.csv", year, month, year, month);
	switch (file_exists(filename))
	{
	case 0: // ファイルが存在しない場合(初期化をしてbreakしずに次のcaseに移る)
		printf("ファイルをオープンできません。\n");
		int n = 0;
		while (n <= 4)
		{
			sprintf(filename, "./plan/%d/%02d", year, month);
			if (mkdir(filename, 0777) == -1)
			{
				printf("ファイルをオープンできません。\n");
				sprintf(filename, "./plan/%d", year);
				if (mkdir(filename, 0777) == -1)
				{
					printf("ファイルをオープンできません。\n");
					sprintf(filename, "./plan");
					if (mkdir(filename, 0777) == -1)
					{
						printf("ディレクトリを作成できませんでした\n");
					}
					n++;
					continue;
				}
				n += 2;
				continue;
			}
			n += 4;
		}

		printf("ディレクトリを作成しました\n");
		sprintf(filename, "./plan/%d/%02d/%d%02d.csv", year, month, year, month);
		fp = fopen(filename, "w");
		fprintf(fp, "0\n");
		fclose(fp);
	case 1: // ファイルが存在する場合
		fp = fopen(filename, "a");
		printf("設定する目標を選んで下さい\n1.差額");
		int x;
		scanf("%d", &x);
		switch (x)
		{
		case 1:
			printf("目標を入力して下さい\n");
			long tmp;
			scanf("%ld", &tmp);
			fprintf(fp, "%ld\n", tmp);
			break;
		case 2:
			break;
		default:
			break;
		}
		fclose(fp);
	}
}

//編集したい行番号を引数として受け取る関数
//extern宣言を使ってグローバル変数を使えるようにすれば、ほしい処理だけを関数にまとめられる
//ファイルを読み込んだ時の処理
//編集したい行の内容を入力する
//編集したい行までの内容を新規ファイルにコピーする
//編集したい行の内容を新規ファイルに書き込む
//編集したい行以降の内容を新規ファイルにコピーする
//元のファイルを削除する
//新規ファイルを元のファイルと同じ名前にする
void edit_money()
{
	int lineNo;
	FILE *file;
	file = fopen(GlobalFilename, "r");
	char line[256];
	if (file == NULL)
	{
		printf("ファイルを開けませんでした。\n");
	}
	printf("編集したい行を入力して下さい\n");
	scanf("%d", &lineNo);

	//新規ファイルを生成する
	FILE *newfile;
	char newFilename[200];
	sprintf(newFilename,"./archives/%d/%02d/0000%d%02d%02d.csv", GlobalYear, GlobalMonth, GlobalYear, GlobalMonth, GlobalDay);
	newfile = fopen(newFilename, "w");
	if (newfile == NULL)
	{
		printf("ファイルを開けませんでした。\n");
	}

	//編集したい行までの内容を新規ファイルにコピーする
	for (int i = 0; i < lineNo-1; i++)
	{
		fgets(line, sizeof(line), file);
		fprintf(newfile, "%s", line);
	}
	int prelineNo;
	long preincomes;
	long preexpenses;
	char prestr[256];
	fgets(line, sizeof(line), file);
	sscanf(line,"%d,%ld,%ld,%s",&prelineNo,&preincomes,&preexpenses,prestr);
	fprintf(newfile, "%d,%ld,%ld,%s\n", prelineNo, preincomes, preexpenses, prestr);
	//構造体のNoと同じ行を追加する
	long incomes_tmp;
	long expenses_tmp;
	char str_tmp[256];
	int tmp;
	long incomes;
	long expenses;
	printf("収入を入力して下さい\n");
	scanf("%ld", &incomes_tmp);
	printf("支出を入力して下さい\n");
	scanf("%ld", &expenses_tmp);
	printf("タグを入力して下さい\n");
	scanf("%s", str_tmp);
	fprintf(newfile, "%d,%ld,%ld,%s\n", lineNo, preincomes + incomes_tmp, preexpenses + expenses_tmp, str_tmp);
	//編集したい行以降の内容を新規ファイルにコピーする
	fgets(line, sizeof(line), file);
	int difflineNo;
	long diffincomes;
	long diffexpenses;
	char diffstr[256];
	sscanf(line,"%d,%ld,%ld,%s",&difflineNo,&diffincomes,&diffexpenses,diffstr);
	diffincomes = preincomes + incomes_tmp - diffincomes;
	diffexpenses = preexpenses + expenses_tmp - diffexpenses;

	char s[256];

	while (fgets(line, sizeof(line), file) != NULL) {
	if(sscanf(line,"%d,%ld,%ld,%s",&lineNo,&incomes,&expenses,s) == 4){
		fprintf(newfile, "%d,%ld,%ld,%s\n", lineNo , incomes + diffincomes, expenses + diffexpenses, s);
		
	}
	}

// 編集したい行の値を求めることが難しい
// 差を取る必要がある
// 表示系の修正
// for (i = 0; i < n; i++){printf(i+1 - i)}
// 1行めは1-0 タグなどもそのまま書ける



	// fgets(line, sizeof(line), file);
	// for (int i = lineNo + 1; fgets(line, sizeof(line), file) != NULL; i++){
	// 	fprintf(newfile, "%s", line);
	// }
	fclose(file);
	remove(GlobalFilename);
	fclose(newfile);
	rename(newFilename, GlobalFilename);
}