#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "calc.h"
#include "utility.h"
#include "read.h"
#include "write.h"
#include "data.h"

moneyData user = {0, 0, 0, 0};

int main()
{
    // 楽しくお金を管理してレベルアップしよう
    time_t current = time(NULL);
    struct tm *timer = localtime(&current);
    // お知らせ表示
    printf("お知らせ\n");
    read_message();
    printf("\n");
    printf("\n");

    char n[1];
    // ユーザーの選択

    int quit0 = 1;
    int quit2;
    while (quit0 == 1)
    {
        printf("1.本日の収支表示/入力\n(2.過去の履歴を編集)\n3.指定月の収支を合算表示する\n4.目標を設定する\nH.ヘルプを表示する\nQ.終了する\n");
        scanf("%s", n);
        // １なら"本日の収支表示/入力"
        // ２なら"過去の履歴を編集"
        // ３なら”今月の収支表示、計画との差を表示”
        // ４なら"今月の目標の設定"
        // Hならヘルプを表示
        // Qなら終了する
        switch (n[0])
        {
        // case 1
        case 0x31:
            init_struct(&user);

            int quit1 = 1;
            while (quit1 == 1)
            {
                put_time();
                printf("(本日)の収支について\n1.表示する 2.入力する (3.編集する) 4.戻る\n");
                scanf("%s", n);
                switch (n[0])
                {
                case 0x31:
                    read_money();
                    continue;
                case 0x32:
                    write_money(&user);
                    continue;
                case 0x33:
                    //削除予定
                    printf("編集したい行を指定して下さい\n");
                    read_all_money();
                    //編集処理を書く
                    //編集したい行番号を引数として受け取る
                    //試験的内容
                    //1.グローバル変数に値を代入するyear,month,day,filename
                    set_today();
                    sprintf(GlobalFilename, "./archives/%d/%02d/%d%02d%02d.csv", GlobalYear, GlobalMonth, GlobalYear, GlobalMonth, GlobalDay);
                    //2.ファイルオープンからクローズまでを関数化する
                    edit_money();
                    //これでは、変更した後半の収支が足されず合わない
                    continue;
                case 0x34:
                    quit1 = 0;
                    break;
                default:
                    printf("入力が不正です\n");
                    continue;
                }
            }
            continue;

        //削除予定
        case 0x32:  // case2

            quit2 = 1;
            while (quit2 == 1)
            {
                printf("編集したい日付を指定して下さい\n");
                int year;
                int month;
                int day;
                printf("年を入力して下さい\n");
                scanf("%d", &year);
                printf("月を入力して下さい\n");
                scanf("%d", &month);
                printf("日を入力して下さい\n");
                scanf("%d", &day);
                int quit2_1 = 1;
                while(quit2_1 == 1){
                    read_past_money(year, month, day);
                    printf("編集したい行を指定して下さい\n");
                // 編集したい行を指定して、その編集内容を入力する
                // 新規ファイルを生成して、元のファイルをコピーして、該当行だけ変更
                // 元のファイルを削除する
                // 新規ファイルを元のファイルと同じ名前にする

                //編集を抜けるか確認
                printf("編集を終了しますか？\n1.はい 2.いいえ\n");
                scanf("%d", &quit2_1);
                if(quit2_1 == 2){
                    continue;
                }else if(quit2_1 == 1){
                    break;
                }
                }
                if(quit2_1 == 1){
                    break;
                }
            }
            continue;

        case 0x33:
        // case3
        // ある月の日付のファイルの最後尾を読み取ってその値を合算する
        // その値とその月の目標の差を表示する
        // 達成されていると経験値がもらえる(初めて貰ったかフラグ管理)
        // 目標が設定されていなければcase4に移る
        printf("合算したい年月を指定して下さい\n");
                int year;
                int month;
                printf("年を入力して下さい\n");
                scanf("%d", &year);
                printf("月を入力して下さい\n");
                scanf("%d", &month);
                long sum = read_month_money(year, month);
                printf("合計は%ld円です\n", sum);
                continue;

        case 0x34:
        printf("目標を設定したい年月を入力して下さい\n");
            // case4
            // 目標を設定する
            // 目標は月ごとに設定できる
            // 設定したい年月を入力する
            // その月の目標(支出)を入力する
            write_plan();
            break;



        case 0x48:
        case 0x68:  
            // caseH
            // ヘルプを表示する
            printf("使い方を表示します\n");
            printf("指定された番号を入力して進んでください\n");
            printf("戻りたい時は戻る番号を入力して下さい\n");
            printf("ctrl + c で終了すると正しく保存されない恐れがあります\n");
            break;

        case 0x51:
        case 0x71:
            quit0 = 0;
            break;
            // caseQ
            // 終了する
        }
    }
    return (0);
}