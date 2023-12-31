#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include "utility.h"
#include "data.h"

/*--- 現在の年月日を表示する ---*/
void put_time(void)
{
	time_t current = time(NULL);
	struct tm *timer = localtime(&current);

	printf("%d年%d月%d日", timer->tm_year + 1900, timer->tm_mon + 1, timer->tm_mday);
}

// 指定されたパスのファイルが存在するかどうかを確認する関数
// 存在する場合は1を返す
// 存在しない場合は0を返す
int file_exists(const char *path)
{
	FILE *fp;
	fp = fopen(path, "r");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		fclose(fp);
		return 1;
	}
}

// 構造体の実体のメンバをcsvファイルの最終行を読み込んでその値で初期化する関数
// 初期化するのはNoとincomesとexpensesだけ
// その日の値で初期化されるので、使うタイミングに注意
void init_struct(moneyData *a)
{
	time_t current = time(NULL);
	struct tm *timer = localtime(&current);
	int year = timer->tm_year + 1900;
	int month = timer->tm_mon + 1;
	int day = timer->tm_mday;
	FILE *fp;
	char filename[200];
	// make_dir();
	// printf("./.archives/%d/%02d/%d%02d%02d.csv", year, month, year, month, day);
	sprintf(filename, "./.archives/%d/%02d/%d%02d%02d.csv", year, month, year, month, day);
	switch (file_exists(filename))
	{
	case 0: // ファイルが存在しない場合(初期化をしてbreakしずに次のcaseに移る)
		make_dir();
		fp = fopen(filename, "w");
		fprintf(fp, "0,0,0,0\n");
		fclose(fp);
	case 1: // ファイルが存在する場合
		fp = fopen(filename, "r");
		char line[256];
		for (int i = 1; i < count_lines(filename); i++)
		{
			fgets(line, sizeof(line), fp); // 指定した行番号までファイルポインタを移動
		}
		fscanf(fp, "%d,%ld,%ld,%s", &a->No, &a->incomes, &a->expenses, a->tagline);
		fclose(fp);
	}
}

// ディレクトリを作成する関数
void make_dir(void)
{
	time_t current = time(NULL);
	struct tm *timer = localtime(&current);
	int year = timer->tm_year + 1900;
	int month = timer->tm_mon + 1;
	char dir[200];
	printf("0\n");
	sprintf(dir, "./.archives/%d", year);
	if (mkdir(dir, 0777) == 0)
	{
		printf("1\n");
		sprintf(dir, "./.archives/%d/%02d", year, month);
		if (mkdir(dir, 0777) == 0)
		{
			printf("2\n");
		}
	}
	else
	{
		sprintf(dir, "./.archives/%d/%02d", year, month);
		if (mkdir(dir, 0777) == 0)
		{
			printf("3\n");
		}
		else if (mkdir(dir, 0777) == -1 && file_exists(dir) == 0)
		{
			printf("4\n");
			printf("ErrorCode:NotFound'./.archives'folder\n");
		}
	}
}

// ファイルの行数を返す関数
int count_lines(const char *path)
{
	FILE *fp;
	int count = 0;
	char c;

	fp = fopen(path, "r");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		while ((c = fgetc(fp)) != EOF)
		{
			if (c == '\n')
			{
				count++;
			}
		}
		fclose(fp);
		return count;
	}
}

// グローバル変数に今日の日付を代入する関数
void set_today(void)
{
	time_t current = time(NULL);
	struct tm *timer = localtime(&current);
	GlobalYear = timer->tm_year + 1900;
	GlobalMonth = timer->tm_mon + 1;
	GlobalDay = timer->tm_mday;
}
// グローバル変数に指定された日付を代入する関数
void set_day(int year, int month, int day)
{
	GlobalYear = year;
	GlobalMonth = month;
	GlobalDay = day;
}