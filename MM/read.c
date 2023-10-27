#include <stdio.h>
#include "read.h"

double read_money(void){
    int fgetc(FILE * fp);
	FILE * fp = NULL;
    char	name[32] = { 0 };	//	氏名
	int		age = 0;			//	年齢
	double	height = 0;			//	身長
	char	blood = 0;			//	血液型

	//	読み込みモードでファイルを開く
	fopen_s(&fp, "archives/sample.txt", "r");

	while (fscanf(fp, "%s %d歳 %lfcm %c型", name, &age, &height, &blood) != EOF)
	{
		//	取り出した情報を画面に表示
		printf("%s %d %3.2lf %c\n", name, age, height, blood);
	}


	fclose(fp);

	return 0;
}