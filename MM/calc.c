#include "calc.h"
 
//現在の収支を計算する関数
//収入
double add_money(double current,double add){
    double current = current + add;
    return current;
}
//支出
double sub_money(double current,double sub){
    double current = current - sub;
    return current;
}


double avg(double l,double m){
    //  引数l,mの平均値を求め、rに代入する。
    double r = (l + m) / 2.0;
    return r;
}