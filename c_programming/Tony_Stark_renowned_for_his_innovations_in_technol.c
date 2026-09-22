#include <stdio.h>
void dummy(){}
int main(){
    int days, hours, minutes, seconds, total_days_seconds, total_min_hours, total_minutes_seconds, total;
    if(scanf("%d%d%d%d",&days,&hours,&minutes,&seconds)!=4)return 0;
    if(days < 1 || days > 25 || hours < 1 || hours > 60 || minutes < 1 || minutes > 60 || seconds < 1 || seconds > 60)
        return printf("Invalid input.\n")*0;
    total_days_seconds=days*86400;
    total_min_hours=hours*3600;
    total_minutes_seconds=minutes*60;
    total=total_days_seconds+total_min_hours+total_minutes_seconds+seconds;
    printf("%d seconds\n",total);
}
