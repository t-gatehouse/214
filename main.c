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

    ptime_spec = (struct time_spec_t*) malloc(100 * sizeof( time_spec));

    ptime_spec->year = (num_seconds.seconds)/31557600;

    time_spec.year = ptime_spec->year;
    ptime_spec->month = 0;
    ptime_spec->day = 0;
    ptime_spec->hour = 0;
    ptime_spec->minute = 0;
    ptime_spec->second = 0;



    if (time_spec.year == 1){
        time_spec.month = ptime_spec->month;
        time_spec.day = ptime_spec->day;
        time_spec.hour = ptime_spec->hour;
        time_spec.minute = ptime_spec->minute;
        time_spec.second = ptime_spec->second;
        printf("\n%uy %un %ud %uh %um %us\n", time_spec.year, time_spec.month, time_spec.day, time_spec.hour, time_spec.minute, time_spec.second);

        return ptime_spec;

    }

    else if(num_seconds.seconds/31557600 > 0){

        ptime_spec->year = num_seconds.seconds/31557600;
        ptime_spec->second = (num_seconds.seconds - 31557600);



        time_spec.year = ptime_spec->year;
        time_spec.month = ptime_spec->month;
        time_spec.day = ptime_spec->day;
        time_spec.hour = ptime_spec->hour;
        time_spec.minute = ptime_spec->minute;
        time_spec.second = ptime_spec->second;
        printf("\n%uy %un %ud %uh %um %us\n", time_spec.year, time_spec.month, time_spec.day, time_spec.hour, time_spec.minute, time_spec.second);

        return ptime_spec;


    }

    else{
        return NULL;
    }



}

void print_time_spec( struct time_spec_t *time_spec ){
    /// output a valid time spec on stdout

    printf("\n%uy %un %ud %uh %um %us\n", time_spec->year, time_spec->month, time_spec->day, time_spec->hour, time_spec->minute, time_spec->second);

}

struct bool get_time_arg( char *in_str, struct num_seconds_t *seconds_p ){
    /// the function returns TRUE if it was able to convert the string pointed to by in_str to a number of seconds.
    /// In this case the number of seconds is stored in the location pointed to by seconds_p.
    /// The string pointed to by in_str could be a time spec or it could specify a number of seconds.
    /// The function returns FALSE if it was not able to convert the string pointed to by in_str to a number of seconds;
    /// for example, the string was neither a legal time spec nor a legal number of seconds.
    /// It also returns FALSE if the number of seconds is not less than the limit of 3155760000.
    /// In the latter two cases an appropriate error message is generated on stderr.
    /// If the input pointed to by in_str is neither a legal time spec nor a legal number of seconds,
    /// then no operation should be performed on the location pointed to by seconds_p.

    struct bool true;
    struct bool false;
    true.result = 1;
    false.result = 0;

    is_legal_time_spec(in_str);
    is_legal_seconds(in_str);


    if(sscanf(in_str, "%u", seconds_p->seconds)){
        return true;
    }
    else if(true.result ==1){
        return true;
    }
    else{
        return false;
    }
}

void usage( void ) {
    puts( "\nUsage: \n time_calc help" );
    puts( " time_calc conv " );
    puts( " time_calc {add,subt,comp} " );
}

int main(int argc, char *argv[]) {


    int counter = 0;
    struct bool true;
    struct bool false;

    char * time = "31557600";
    char * time_null = NULL;
    char * time_spec_string = "100y12n12d23h12m12s";
    char * time_spec_string2 = "101y13n13d25h13m13s";
    char * string = "tyler";

    struct num_seconds_t num_seconds1;

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


    num_seconds1.seconds = 3333557601;
    ptime_spec1 = seconds_to_time_spec(num_seconds1);
    if(ptime_spec1->year != 1){
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

//    // ******** testing print_time_spec ********
//    print_time_spec(&time_spec);
//
//    // outputting usage
//    usage();

    printf("\nNumber of errors for Assignment 3: %d\n", counter);


    printf("\n**** Finished Regression Tests for Assignment 3 ****\n");

    // done
    return 0;



}