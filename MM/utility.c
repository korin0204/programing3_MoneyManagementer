#include <stdio.h>
#include <time.h>
#include "utility.h"

/*--- 現在の年月日と午前か午後かを表示する ---*/
void put_time(void)
{
	time_t current = time(NULL);
	struct tm *timer = localtime(&current);

	printf("%d年%d月%d日\n",timer->tm_year + 1900, timer->tm_mon +1, timer->tm_mday);
}