#include"walmart.h"

char* liveTime(){
    time_t rawtime;
    struct tm *timeinfo;
    char* date_string = (char*)malloc(11 * sizeof(char)); // Allocate memory for the date string

    if (date_string == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(date_string, 11, "%d-%m-%Y", timeinfo); // Format the date

    return date_string;
}

int dateToInt(const char* date){
    char temp[11];
    strcpy(temp, date);
    temp[2] = temp[5] = '\0'; // Null terminate after day and month
    return atoi(&temp[6]) * 10000 + atoi(&temp[3]) * 100 + atoi(&temp[0]);
}



int compareDates(const char* t1, const char* t2) {
    int date1 = dateToInt(t1);
    int date2 = dateToInt(t2);

    if (date1 < date2) {
        return -1;
    } else if (date1 > date2) {
        return 1;
    } else {
        return 0;
    }
}
