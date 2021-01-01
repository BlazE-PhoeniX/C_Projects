#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//necessary functions
int checkIfLeapYear(int year);
int getNoOfDaysInMonth(int month, int year);
char* getMonthName(int monthNumber);
char* getDayFull(int day);
char* getDayHalf(int day);
int validateDate(int dateArr[]);
int getNextLeapYear(int year);
void parseDateStr(char dateStr[], int date[]);

//date Operations menu
void dateOperations();

//date difference
int findRemainingDays(int from[], int to[]);
void findDateDifference();

//date sum
void addDayToDate(int date[], int resultDate[], int days);
void findDateSum();

//day with date
void printDay(int remainingDays);
void findDay();

//view calendar
void printCalendar(int date[], int dayNumber);
void getCustomMonth(int date[]);
void displayCalendar(char dateStr[]);


int main() {
    int choice, flag=1;
    
    while(flag) {
        int inputFlag=1;
        system("clear");
        printf("\nW O R T H L E S S   C A L E N D A R\n\n");

        printf("Menu:\n\n");
        printf("1) View Calendar\n\n2) Perform Date Operations\n\n3) Exit\n");

        while(inputFlag) {
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
            getchar();

            switch(choice) {
                case 1: 
                    displayCalendar("01/12/2020");
                    inputFlag=0;
                    break;
                case 2: 
                    dateOperations();
                    inputFlag=0;
                    break;
                case 3:
                    flag=0;
                    inputFlag=0;
                    printf("\n");
                    break;
                default:
                    printf("Invalid Input. Try Again.\n");
            }
        }
    }

    return 0;

}

int checkIfLeapYear(int year) {
    if( (year%4==0 && year%100!=0) || year%400==0) {
        return 1;
    }
    return 0;
}

int getNoOfDaysInMonth(int month, int year) {
    switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return checkIfLeapYear(year)? 29: 28;
    }
}

char* getMonthName(int monthNumber) {
    switch(monthNumber) {
        case 1: return "January";
        case 2: return "February";
        case 3: return "March";
        case 4: return "April";
        case 5: return "May";
        case 6: return "June";
        case 7: return "July";
        case 8: return "August";
        case 9: return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";
    }
}

char* getDayFull(int day) {
    switch(day) {
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
    }
}

char* getDayHalf(int day) {
    switch(day) {
        case 0: return "Sun";
        case 1: return "Mon";
        case 2: return "Tue";
        case 3: return "Wed";
        case 4: return "Thu";
        case 5: return "Fri";
        case 6: return "Sat";
    }
}

int validateDate(int dateArr[]) {
    if(dateArr[2]<1900 || dateArr[2]>3000) {
        return 0;
    } else if(dateArr[1]<1 || dateArr[1]>12) {
        return 0;
    } else if(dateArr[0]<1 || dateArr[0]>getNoOfDaysInMonth(dateArr[1], dateArr[2])) {
        return 0;
    }
    return 1;
}

int getNextLeapYear(int year) {
    int i=year;
    while(!checkIfLeapYear(i)) i++;
    return i;
}

void parseDateStr(char dateStr[], int date[]) {
    int temp=0, j=0;
    for(int i=0; i<strlen(dateStr); i++) {
        if(dateStr[i]>=48 && dateStr[i]<=57) {
            temp = temp*10 + (dateStr[i] - 48);
        } else if(dateStr[i] == '/') {
            date[j++] = temp;
            temp=0;
        }
    }
    date[2] = temp;
}

void printCalendar(int date[], int dayNumber) {
    int monthDays = getNoOfDaysInMonth(date[1], date[2]);
    int flag = 0;

    system("clear");
    printf("\nW O R T H L E S S   C A L E N D A R\n\n");
    printf("\n%s  %d\n\n", getMonthName(date[1]), date[2]);

    for(int i=0; i<7; i++)
        printf("%3s  ", getDayHalf(i));

    printf("\n\n");

    for(int i=1; i<=monthDays;) {
        for(int j=0; j<7; j++) {
            if(i==1 && j==dayNumber)
                flag=1;
            
            if(flag && i<=monthDays)
                printf("%3d  ", i++);
            else 
                printf("%3c  ", ' ');
        }
        printf("\n\n");
    }
    printf("\n\n");
}

void getCustomMonth(int date[]) {
    do {
        printf("\nEnter Month (mm) : ");
        scanf("%d", &date[1]);
        getchar();
        printf("\nEnter Year (yyyy) : ");
        scanf("%d", &date[2]);
        getchar();
        if(!validateDate(date))
            printf("Error: Invalid date. Try again.\n");
    } while(!validateDate(date));
}

void displayCalendar(char dateStr[]) {
    int flag=1;
    int fromDate[3], toDate[3];
    char choice;

    parseDateStr( "01/01/1900", fromDate);
    parseDateStr( dateStr, toDate);

    while(flag) {
        int inputFlag=1;
        int remainingDays = findRemainingDays( fromDate, toDate)+1;
        printCalendar( toDate, remainingDays%7);

        printf("Menu:\n\n");
        printf("P: Previous Month   N: Next Month\n\nC: Custom Choice    B: Back\n");

        while(inputFlag) {
            printf("\nEnter your choice: ");
            scanf("%c", &choice);
            getchar();

            switch(choice) {
                case 'p':
                case 'P':
                    toDate[1]--;
                    if(toDate[1]<1) {
                        toDate[1]=12;
                        toDate[2]--;
                    }
                    inputFlag=0;
                    break;
                
                case 'n':
                case 'N':
                    toDate[1]++;
                    if(toDate[1]>12) {
                        toDate[1]=1;
                        toDate[2]++;
                    }
                    inputFlag=0;
                    break;

                case 'c':
                case 'C':
                    getCustomMonth(toDate);
                    inputFlag=0;
                    break;
                
                case 'b':
                case 'B':
                    flag=0;
                    inputFlag=0;
                    break;

                default:
                    printf("Invalid Input. Try Again\n");
            }
        }
    }
}

int findRemainingDays(int from[], int to[]) {

    int remainingDays = 0, swap=0;
    int fromDate = from[0], fromMonth = from[1], fromYear = from[2];
    int toDate = to[0], toMonth = to[1], toYear = to[2];

    //check if to date is greater than from
    if(fromYear > toYear) {
        swap=1;
    } else if(fromYear == toYear) {
        if(fromMonth > toMonth) {
            swap=1;
        } else if(fromMonth == toMonth) {
            if(fromDate > toDate) {
                swap=1;
            }
        }
    }

    if(swap) {
        return -findRemainingDays(to, from);
    }

    //No of days in th years between the dates eg fromYear=1900, toYear=2020, we calculate 1901-2019
    //if fromand to are same year -365 to compensate month addings
    remainingDays += (toYear-fromYear-1)*365;

    //if both years are same and a leap year we need -364 to compensate
    if(fromYear==toYear && checkIfLeapYear(toYear))
        remainingDays--;
    
    //incrementing days by 1 for every leap year.
    for(int i=getNextLeapYear(fromYear+1); i<toYear; i+=4) {
        if(checkIfLeapYear(i))
            remainingDays++;
    }

    //calculating remaining days in from year eg if fromMonth=2, we calculate 3-12
    for(int i=fromMonth+1; i<=12; i++) {
        int noOfDaysInMonth = getNoOfDaysInMonth(i, fromYear);
        remainingDays+=noOfDaysInMonth;
    }

    //calculating past days in to year eg if toMonth=11, we calculate 1-10
    for(int i=1; i<toMonth; i++) {
        int noOfDaysInMonth=getNoOfDaysInMonth(i,toYear);                                                                    
        remainingDays+=noOfDaysInMonth;
    }

    //adding days past in to month if to date is 20 we had 20.
    remainingDays += toDate;
    
    //adding days remaining in from month if from date is 20 we had (total days in that month - 20)
    remainingDays += ( getNoOfDaysInMonth(fromMonth, fromYear) - fromDate );

    return remainingDays;
}

void findDateDifference() {
    char dateStr[100];
    int fromDate[3], toDate[3];
    int remainingDays;

    system("clear");
    printf("\nW O R T H L E S S   C A L E N D A R\n\n");

    do{
        printf("\nEnter From date (dd/mm/yyyy) : ");
        fgets(dateStr, 100, stdin);
        parseDateStr(dateStr, fromDate);
        if(!validateDate(fromDate))
            printf("Error: Invalid date format. Try again.\n");
    } while(!validateDate(fromDate));

    do {
        printf("\nEnter To date (dd/mm/yyyy) : ");
        fgets(dateStr, 100, stdin);
        parseDateStr(dateStr, toDate);
        if(!validateDate(toDate))
            printf("Error: Invalid date. Try again.\n");
    } while(!validateDate(toDate));

    remainingDays = findRemainingDays(fromDate, toDate);

    
    printf("\nDays between %d/%d/%d and %d/%d/%d is %d\n", fromDate[0], fromDate[1], fromDate[2], toDate[0], toDate[1], toDate[2], remainingDays);

    printf("\nPress any key to get back.......");
    getchar();
}

void addDayToDate(int date[], int resultDate[], int days) {
    int tempDate[3], tempDays, remainingDays;
    tempDate[0] = date[0];
    tempDate[1] = date[1];
    tempDate[2] = date[2];
    tempDays = days;

    tempDate[2]+=tempDays/365;
    tempDays%=365;

    if(tempDate[1]+tempDays/30 > 12) {
        tempDate[1]=tempDays/30 - (12 - tempDate[1]); 
        tempDate[2]++;
    } else if(tempDate[1]+tempDays/30 < 1) {
        tempDate[2]--;
        tempDate[1]= 12 + tempDate[1] + tempDays/30;
    } else {
        tempDate[1]+=tempDays/30;
    }
    tempDays%=30;

    if(tempDate[0]+tempDays > getNoOfDaysInMonth(tempDate[1], tempDate[2])) {
        tempDate[0]=tempDays - (getNoOfDaysInMonth(tempDate[1], tempDate[2]) - tempDate[0]);
        if(++tempDate[1] > 12) {
            tempDate[1]=1; 
            tempDate[2]++;
        }      
    } else if(tempDate[0]+tempDays < 1) {
        if(--tempDate[1] < 1) {
            tempDate[2]--;
            tempDate[1]= 12;
        }
        tempDate[0]=getNoOfDaysInMonth(tempDate[1], tempDate[2]) - (-tempDays - tempDate[0]);
    } else {
        tempDate[0]+=tempDays;
    }

    remainingDays = findRemainingDays(date, tempDate);

    if(remainingDays != days) {
        addDayToDate(tempDate, resultDate, days-remainingDays);
    } else{
        resultDate[0] = tempDate[0];
        resultDate[1] = tempDate[1];
        resultDate[2] = tempDate[2];
    }
}

void findDateSum() {
    char dateStr[100];
    int date[3], resultDate[3];
    int days;

    system("clear");
    printf("\nW O R T H L E S S   C A L E N D A R\n\n");

    do{
        printf("\nEnter the date (dd/mm/yyyy) : ");
        fgets(dateStr, 100, stdin);
        parseDateStr(dateStr, date);
        if(!validateDate(date))
            printf("Error: Invalid date format. Try again.\n");
    } while(!validateDate(date));

    do {
        printf("\nEnter The number of Days : ");
        scanf("%d", &days);
        getchar();
        if(days < -10000 || days>10000)
            printf("Error: No of Days must be between -10000 to 10000. Try again.\n");
    } while(days< -10000 || days>10000);

    addDayToDate(date, resultDate, days);

    if(!validateDate(resultDate))
        printf("\nError: Some error.try again\n");
    else 
        printf("\n%d days from %d/%d/%d is %d/%d/%d\n", days, date[0], date[1], date[2], resultDate[0], resultDate[1], resultDate[2]);

    printf("\nPress any key to get back.......");
    getchar();
}

void printDay(int remainingDays) {
    char* day = getDayFull(remainingDays%7);
    printf("\n%s\n", day);
}

void findDay() {
    char dateStr[100];
    int fromDate[3], toDate[3], remainingDays;
    system("clear");
    printf("\nW O R T H L E S S   C A L E N D A R\n");

    do{
        printf("\nEnter The date (dd/mm/yyyy) : ");
        fgets(dateStr, 100, stdin);
        parseDateStr(dateStr,toDate);
        if(!validateDate(toDate))
            printf("Error: Invalid date format. Try again.\n");
    } while(!validateDate(toDate));

    parseDateStr("1/1/1900", fromDate);
    remainingDays = findRemainingDays(fromDate, toDate);
    printf("\nIt is a %s\n", getDayFull((remainingDays+1)%7));
    printf("\nPress any key to get back.....");
    getchar();
}

void dateOperations() {
    int choice, flag=1;
    
    while(flag) {
        int inputFlag=1;
        system("clear");
        printf("\nW O R T H L E S S   C A L E N D A R\n\n");

        printf("Date Operations:\n\n");
        printf("1) Find difference in dates\n\n2) Add days to a date\n\n3) find the day with date\n\n4) Back\n");

        while(inputFlag) {
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
            getchar();

            switch(choice) {
                case 1: 
                    findDateDifference();
                    inputFlag=0;
                    break;
                case 2: 
                    findDateSum();
                    inputFlag=0;
                    break;
                case 3:
                    findDay();
                    inputFlag=0;
                    break;
                case 4:
                    flag=0;
                    inputFlag=0;
                    printf("\n");
                    break;
                default:
                    printf("Invalid Input. Try Again.\n");
            }
        }
    }
}