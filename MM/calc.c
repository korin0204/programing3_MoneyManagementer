#include <stdio.h>
#include "calc.h"
 
//現在の収支を計算する関数
//収入
long add_money(long current_money,long add){
    current_money = current_money + add;
    return current_money;
}
//支出
long sub_money(long current_money,long sub){
    current_money = current_money - sub;
    return current_money;
}


long avg(long l,long m){
    //  引数l,mの平均値を求め、rに代入する。
    long r = (l + m) / 2.0;
    return r;
}