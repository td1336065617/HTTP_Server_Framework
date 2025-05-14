//
// Created by fspst on 23-6-14.
//

#include <ctime>
#include "time_cl.h"
#include "../Time_data/Time_data.h"
std::string time_cl::get_time(time_t now,Time_data &timeData) {
    std::string tm;
    std::tm* local_time = std::localtime(&now);
    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;
    int second = local_time->tm_sec;
    timeData.year=year;
    timeData.month=month;
    timeData.day=day;
    timeData.hour=hour;
    timeData.minute=minute;
    timeData.second=second;
    tm+= std::to_string(year)+"-";
    tm+= std::to_string(month)+"-";
    tm+= std::to_string(day)+" ";
    tm+= std::to_string(hour)+":";
    tm+= std::to_string(minute);
    char tm2[100];
    sprintf(tm2,"%04d-%02d-%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
    tm=tm2;
    return tm;
}


std::string time_cl::get_time2(time_t now,Time_data &timeData) {
    std::string tm;
    std::tm* local_time = std::localtime(&now);
    int year = local_time->tm_year-70;
    int month = local_time->tm_mon;
    int day = local_time->tm_mday;
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;
    int second = local_time->tm_sec;
    timeData.year=year;
    timeData.month=month;
    timeData.day=day;
    timeData.hour=hour;
    timeData.minute=minute;
    timeData.second=second;
    tm+= std::to_string(year)+"年";
    tm+= std::to_string(month)+"月";
    tm+= std::to_string(day)+"日 ";
    tm+= std::to_string(hour)+":";
    tm+= std::to_string(minute);
    char tm2[100];
    sprintf(tm2,"%02d月%02d日 %02d:%02d",month,day,hour,minute);
    tm=tm2;
    return tm;
}
