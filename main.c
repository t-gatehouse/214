#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct bool{
    int  result;
};

struct time_spec_t{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

struct num_seconds_t{
    uint32_t seconds;
};

struct bool is_legal_time_spec(char * time_spec){
    /// return TRUE if the string given as the input argument is a valid time spec;
    /// otherwise produce diagnostic messages on stderr and return FALSE.
    /// Errors diagnosed include extraneous characters and field values exceeding limits.

    struct bool true;
    struct bool false;
    true.result = 1;
    false.result = 0;
    struct time_spec_t time;

    if(time_spec==NULL){
        return false;
    }

    else{
        if(sscanf(time_spec, "%uy %un %ud %uh %um %us",&time.year, &time.month,&time.day, &time.hour, &time.minute, &time.second) > 5){
//            printf("\nhit time spec\n");
//            printf("\ntime year: %u", time.year);
//            printf("\ntime month: %u", time.month);
//            printf("\ntime day: %u", time.day);
//            printf("\ntime hour: %u", time.hour);
//            printf("\ntime minute: %u", time.minute);
//            printf("\ntime second: %u", time.second);

            if (time.year <= 100 && time.month <= 12 && time.day <= 31 && time.hour <= 24 && time.minute <= 60 && time.second < 60) {
//                printf("\n%uy %un %ud %uh %um %us\n",time.year, time.month, time.day, time.hour, time.minute, time.second);
                return true;
            }
            else {
                return false;
            }

        }
        else{
            return false;
        }
    }

}

struct bool is_legal_seconds(char* seconds){
    /// return TRUE if the string given as the input argument is a valid number of seconds;
    /// otherwise produce diagnostic messages on stderr and return FALSE.
    /// Errors diagnosed include extraneous characters and field values exceeding the limit on the number of seconds

    struct bool true;
    struct bool false;
    true.result = 1;
    false.result = 0;
    struct num_seconds_t *num_seconds_ptr, num_seconds;
    num_seconds_ptr = &num_seconds;

    if(!seconds){
        return false;
    }

    else {
        if (sscanf(seconds, "%u", &(*num_seconds_ptr).seconds) > 0) {
            return true;
        }

        else {
            return false;
        }
    }

}

struct num_seconds_t string_to_seconds(char * seconds) {
    /// return the number of seconds specified by the string passed as the argument to the function.
    /// The string is known to contain a valid "number of seconds" specification
    struct bool flag;
    struct num_seconds_t *num_seconds_ptr, num_seconds;
    num_seconds_ptr = &num_seconds;

    flag = is_legal_seconds(seconds);

    if(flag.result == 1){

        sscanf(seconds, "%u", &(*num_seconds_ptr).seconds);
        return num_seconds;

    }

    else{
        num_seconds.seconds = NULL;
        return num_seconds;
    }

}

struct time_spec_t *string_to_time_spec( char * time_spec){
    /// return a pointer to a dynamically allocated struct containing the fields of a time spec specified by the string passed as the argument to the function.
    /// The string is known to contain a valid time spec. If memory for the struct cannot be allocated, the function returns NULL.
    struct bool flag;
    unsigned int year, month, day, hour, minute, second;
    struct time_spec_t *time_ptr, time;
    time_ptr = &time;

    flag = is_legal_time_spec(time_spec);

    if(flag.result ==1){

        sscanf(time_spec, "%uy %un %ud %uh %um %us",&(*time_ptr).year, &(*time_ptr).month,&(*time_ptr).day, &(*time_ptr).hour, &(*time_ptr).minute, &(*time_ptr).second);
        return &time;

    }

    else{
        return NULL;
    }

}

struct time_spec_t *seconds_to_time_spec( struct num_seconds_t num_seconds ){
    /// Convert a valid number of seconds to a time spec, and store the fields of the time spec in a dynamically allocated time_spec_t structure.
    /// On success, a pointer to the newly allocated structure is returned. If memory for the struct cannot be allocated, the function returns NULL.


    struct time_spec_t *ptime_spec, time_spec;
    unsigned int holder, year, month, day, hour, minute, second;

    ptime_spec = (struct time_spec_t*) malloc(100 * sizeof( time_spec));

    holder = (num_seconds.seconds);

    if(holder > 0){
        year = holder/31557600;
        month = (holder - (year*31557600))/26289800;
        day = (holder - (year*31557600) - (month*2629800))/86400;
        hour= (holder - (year*31557600) - (month*2629800) - (day*86400))/3600;
        minute= (holder - (year*31557600) - (month*2629800) - (day*86400) - (hour*3600))/60;
        second = (holder - (year*31557600) - (month*2629800) - (day*86400) - (hour*3600) - (minute*60))/60;

        ptime_spec->year = (uint8_t) year;
        ptime_spec->month = (uint8_t) month ;
        ptime_spec->day = (uint8_t) day;
        ptime_spec->hour = (uint8_t) hour;
        ptime_spec->minute = (uint8_t) minute;
        ptime_spec->second = (uint8_t) second;

        if (year <= 100 && month <= 12 && day <= 31 && hour <= 24 && minute <= 60 && second <= 60){

            printf("\n%uy %un %ud %uh %um %us\n", ptime_spec->year, ptime_spec->month, ptime_spec->day, ptime_spec->hour, ptime_spec->minute, ptime_spec->second);
            return ptime_spec;
        }

        else{
            return NULL;
        }

    }

    else{
        return NULL;
    }

}

struct num_seconds_t time_spec_to_seconds(char *time_spec){
    struct bool flag;
    struct time_spec_t *time_ptr, time;
    unsigned int seconds;
    struct num_seconds_t num_sec;
    time_ptr = &time;

    flag = is_legal_time_spec(time_spec);

    if(flag.result ==1){
        sscanf(time_spec, "%uy %un %ud %uh %um %us",&(*time_ptr).year, &(*time_ptr).month,&(*time_ptr).day, &(*time_ptr).hour, &(*time_ptr).minute, &(*time_ptr).second);
        seconds = (uint32_t ) (time.year*31557600 + time.month*26289800 + time.day*86400 + time.hour*3600 + time.minute*60 + time.second*60) ;
        num_sec.seconds = seconds;
        return num_sec;
    }

    else{
        num_sec.seconds = NULL;
        return num_sec;
    }

}

struct bool get_time_arg( char *in_str, struct num_seconds_t *seconds_p ){
    /// the function returns TRUE if it was able to convert the string pointed to by in_str to a number of seconds.
    /// In this case the number of seconds is stored in the location pointed to by seconds_p.

    /// The string pointed to by in_str could be a time spec or it could specify a number of seconds.

    /// The function returns FALSE if it was not able to convert the string pointed to by in_str to a number of seconds;
    /// for example, the string was neither a legal time spec nor a legal number of seconds.

    /// It also returns FALSE if the number of seconds more than the limit of 3155760000.

    /// In the latter two cases an appropriate error message is generated on stderr.

    /// If the input pointed to by in_str is neither a legal time spec nor a legal number of seconds,
    /// then no operation should be performed on the location pointed to by seconds_p.

    struct bool flag;
    flag = is_legal_time_spec(in_str);

    if(flag.result == 1){
        *seconds_p = time_spec_to_seconds(in_str);
        return flag;
    }

    else{
        flag = is_legal_seconds(in_str);
        if (flag.result ==1){
            *seconds_p = string_to_seconds(in_str);
            if(seconds_p->seconds < 3155760000){
                return flag;
            }
        }
        printf("The string submitted was not a correct value or was greater than 3155760000.");
        return flag;
    }

}

void print_time_spec( struct time_spec_t *time_spec ){
    /// output a valid time spec on stdout

    printf("\n%uy %un %ud %uh %um %us\n", time_spec->year, time_spec->month, time_spec->day, time_spec->hour, time_spec->minute, time_spec->second);

}

void subtract_seconds(struct num_seconds_t *num1, struct num_seconds_t *num2){

    struct num_seconds_t num_seconds, *pnum_seconds;
    pnum_seconds = &num_seconds;

    struct time_spec_t *ptime_spec;

    pnum_seconds->seconds = num1->seconds - num2->seconds;
    ptime_spec = seconds_to_time_spec(num_seconds);

    print_time_spec(ptime_spec);
}

void add_seconds(struct num_seconds_t *num1, struct num_seconds_t *num2){

    struct num_seconds_t num_seconds, *pnum_seconds;
    pnum_seconds = &num_seconds;

    struct time_spec_t *ptime_spec;

    pnum_seconds->seconds = num1->seconds + num2->seconds;
    ptime_spec = seconds_to_time_spec(num_seconds);

    print_time_spec(ptime_spec);

}

void comp_seconds(struct num_seconds_t *num1, struct num_seconds_t *num2){

    struct num_seconds_t num_seconds, *pnum_seconds;
    pnum_seconds = &num_seconds;

    if (num1->seconds > num2->seconds){
        printf("Greater");
    }

    else if (num1->seconds < num2->seconds){
        printf("Less");
    }

    else{
        printf("Equal");
    }


}

void usage( void ) {
    puts( "\nUsage: \ntime_calc help" );

    puts( "\ntime_calc conv: time_calc will convert between two types of time values."
          "\nEnter format as a time_spec: '(0-100)y (0-12)n (0-31)d (0-24)h (0-60)m (0-60)s'"
          "\nor as a time in seconds between 0 - 3155760000."
          "\ntime_spec input will be converted to seconds and seconds will be converted to time_spec and "
          "\nshown on stdout. eg. 1y 0n 0d 0h 0m 0s will be 31557600\n" );

    puts( "\ntime_calc options {add,subt,comp}\n"
          "\n -add: add two different strings of time together. eg. '1234' '1234' will be 2468\n"
          "\n -sub: subtract two different strings time. eg. '1234' '1234' will be 0\n"
          "\n -comp: compare two different strings of time to see which is greater, less than, or equal to. "
          "\n        eg. '1234' '1234' will be 'equal\n");
}

int main(int argc, char *argv[]) {


    int counter = 0;
    struct bool true;
    struct bool false;

    char * time = "31557600";
    char * time_null = NULL;
    char * time_spec_string = "100y12n12d23h12m12s";
    char * time_spec_string2 = "101y13n13d25h13m13s";
    char * time_spec_string3 = "1y0n0d0h0m0s";
    char * string = "tyler";

    struct num_seconds_t num_seconds1, *pnum_seconds1;
    pnum_seconds1 = &num_seconds1;

    struct time_spec_t time_spec, time_spec1, *ptime_spec1;
    time_spec.year = 100;
    time_spec.month = 12;
    time_spec.day = 12;
    time_spec.hour = 12;
    time_spec.minute = 12;
    time_spec.second = 12;

    ptime_spec1 = &time_spec1;


    printf("**** Starting Regression Tests for Assignment 3 ****\n");

    // ******** testing for legal seconds in is_legal_seconds, designing for edge cases ********
    true = is_legal_seconds(time);
    false = is_legal_seconds(string);

    // testing for true
    if(true.result != 1){
        ++counter;
        printf("\ntrue didn't worked for is_legal_seconds\n");
    }

    // testing for false
    if(false.result !=0){
        ++counter;
        printf("\nfalse didn't worked for is_legal_seconds\n");
    }

    // testing for null
    false = is_legal_seconds(time_null);
    if(false.result !=0){
        ++counter;
        printf("\nfalse didn't worked for NULL in is_legal_seconds\n");
    }

    // ******** testing for legal time spec in is_legal_time_spec, designing for edge cases ********
    true = is_legal_time_spec(time_spec_string);
    false = is_legal_time_spec(string);

    // testing for true
    if(true.result != 1){
        ++counter;
        printf("\ntrue didn't worked for is_legal_time_spec\n");
    }

    // testing for false with string
    if(false.result !=0){
        ++counter;
        printf("\nfalse didn't worked for is_legal_time_spec\n");
    }

    // testing for null
    false = is_legal_time_spec(time_null);
    if(false.result !=0){
        ++counter;
        printf("\nfalse didn't worked for NULL in is_legal_time_spec\n");
    }

    // testing for false with numbers out of range
    false = is_legal_time_spec(time_spec_string2);
    if(false.result !=0){
        ++counter;
        printf("\nfalse didn't worked for is_legal_time_spec with out of range numbers\n");
    }

    // ******** testing for string conversion in string_to_seconds, designing for edge cases ********

    // testing string to seconds with correct input
    num_seconds1 = string_to_seconds(time);
    if(num_seconds1.seconds != (uint32_t )31557600){
        ++counter;
        printf("\nString to second didn't work when testing for correct number of seconds\n");
    }

    // testing for non valid input
    num_seconds1 = string_to_seconds(time_null);
    if(num_seconds1.seconds != NULL){
        ++counter;
        printf("\nString to second didn't work when testing for non-valid input.\n");
    }


    // ******** testing for string conversion in string_to_time_spec, designing for edge cases ********

    // testing with correct input
    ptime_spec1 = string_to_time_spec(time_spec_string);
    if(ptime_spec1->year != 100){
        ++counter;
        printf("\nError with string_to_time_spec with correct input, conversion failed.\n");
    }

    // testing with incorrect input
    ptime_spec1 = string_to_time_spec(time_spec_string2);
    if(ptime_spec1 != NULL){
        ++counter;
        printf("\n Error with string_to_time_spec for incorrect input, conversion failed .");
    }


    // ******** testing for seconds to time conversion for in seconds_to_time_spec, designing for edge cases ********

    // testing seconds for a single year
    num_seconds1.seconds = 31557600;
    ptime_spec1 = seconds_to_time_spec(num_seconds1);
    if(ptime_spec1->year != 1){
        ++counter;
        printf("seconds for 1 year didn't work for seconds_to_time_spec");
    }


    // testing for time greater than 1 year
    num_seconds1.seconds = 31557601;
    ptime_spec1 = seconds_to_time_spec(num_seconds1);
    if(ptime_spec1->year != 1){
        ++counter;
        printf("seconds larger than 1 year didn't work for seconds_to_time_spec");
    }

    // testing for seconds less than 60
    num_seconds1.seconds = 45;
    ptime_spec1 = seconds_to_time_spec(num_seconds1);
    if(ptime_spec1->year != NULL){
        ++counter;
        printf("seconds much larger than 1 year didn't work for seconds_to_time_spec");
    }

    // testing for null value
    num_seconds1.seconds = NULL;
    ptime_spec1 = seconds_to_time_spec(num_seconds1);
    if(ptime_spec1 != NULL){
        ++counter;
        printf("NULL didn't work for seconds_to_time_spec");
    }


    // ******** testing time_spec_to_seconds ********

    // ******** testing get_time_arg ********

//    // ******** testing print_time_spec ********
//    print_time_spec(&time_spec);
//
//    // ******** testing usage ********
    usage();


    time_spec_to_seconds(time_spec_string3);


    get_time_arg(time, pnum_seconds1);
    printf("\nThis should be 31557600: %u\n", pnum_seconds1->seconds);

    get_time_arg(time_spec_string3, pnum_seconds1);
    printf("\nThis should be 31557600: %u\n", pnum_seconds1->seconds);










    printf("\nNumber of errors for Assignment 3: %d\n", counter);


    printf("\n**** Finished Regression Tests for Assignment 3 ****\n");

//    if(argc ==1){
//        usage();
//    }

    // done
    return 0;



}