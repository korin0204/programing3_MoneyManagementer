#include <stdio.h>
#include <time.h>
#include "calc.h"
#include "utility.h"
#include "read.h"
#include "write.h"

void put_time(void)
{
	time_t current = time(NULL);
	struct tm *timer = localtime(&current);

	printf("%d年%d月%d日\n",timer->tm_year + 1900, timer->tm_mon +1, timer->tm_mday);
}
  
int main(){
    time_t current = time(NULL);
    struct tm *timer = localtime(&current);
    //お知らせ表示
    char n[1];
    //ユーザーの入力待機
    //１なら"本日の収支表示/入力"
    //２なら"過去の履歴を編集"
    //３なら”今月の収支表示、計画との差を表示”
    //４なら"今月の目標の設定"
    //Hならヘルプを表示
    //Qなら終了する
    scanf("%s", n);
    printf("%s\n",n);
    switch(n[0]){
        //case 1
        case 0x31 : 
        put_time();
        printf("%d年%d月%d日(本日)の収支について\n1.表示する 2.編集する 3.戻る\n",timer->tm_year +1900,timer->tm_mon + 1,timer->tm_mday);
        scanf("%s", n);
        switch (n[0]){
            case 1 :
            //FILE *fp;
            //fp = fopen("../archives%d%02d%02d",local->tm_year + 1900,local->tm_mon + 1,local->tm_mday);
            break;
        }
        break;
        case 0x32 : break;
        case 0x33 : break;
        case 0x34 : break;

        case 0x48 : break;
        case 0x68 : break;

        case 0x51 : break;
        case 0x71 : break;
    }

    //1-1 収入の入力
    //1-2 支出の入力
    //1-1-1 (収入源,金額,配分先の設定)
    //1-1-2
    return(0);
}