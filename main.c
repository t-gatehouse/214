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

    printf("%s",time_spec);


    if(time_spec==NULL){
        printf("please enter a vaild time");
        return false;
    }

    else{
        sscanf(time_spec, "%uy %un %ud %uh %um %us",&time.year, &time.month,&time.day, &time.hour, &time.minute, &time.second);

        printf("\nhit time spec\n");
        printf("\ntime year: %u", time.year);
        printf("\ntime month: %u", time.month);
        printf("\ntime day: %u", time.day);
        printf("\ntime hour: %u", time.hour);
        printf("\ntime minute: %u", time.minute);
        printf("\ntime second: %u", time.second);

        if (time.year <= 100 && time.month <= 12 && time.day <= 31 && time.hour <= 24 && time.minute <= 60 && time.second < 60) {
            printf("\n%uy %un %ud %uh %um %us\n",time.year, time.month, time.day, time.hour, time.minute, time.second);
            return true;
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
    char *ptr;

    struct num_seconds_t *num_seconds_ptr, num_seconds;
    num_seconds_ptr = &num_seconds;

//    sscanf(seconds, "%u", &(*num_seconds_ptr).seconds);
//    printf("\nthe number of seconds for %s is: %u\n", seconds, num_seconds.seconds);

    if(!seconds){
        printf("\nnull worked\n");
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


    struct num_seconds_t num_seconds;

    sscanf(seconds, "%u", &num_seconds.seconds);

    printf("\nthe number in seconds is: %u\n", num_seconds.seconds);

    return num_seconds;
}

struct time_spec_t *seconds_to_time_spec( struct num_seconds_t num_seconds ){
    /// Convert a valid number of seconds to a time spec, and store the fields of the time spec in a dynamically allocated time_spec_t structure.
    /// On success, a pointer to the newly allocated structure is returned. If memory for the struct cannot be allocated, the function returns NULL.

    struct time_spec_t time_spec;
    int time;
    time_spec.year = num_seconds.seconds/31557600;

    if (time_spec.year == 1){
        time_spec.month = 0;
        time_spec.day = 0;
        time_spec.hour = 0;
        time_spec.minute = 0;
        time_spec.second = 0;
        printf("\n%uy %un %ud %uh %um %us\n", time_spec.year, time_spec.month, time_spec.day, time_spec.hour, time_spec.minute, time_spec.second);

        return &time_spec;

    }

    else if(num_seconds.seconds/31557600 > 0){
        time_spec.year = num_seconds.seconds/31557600;
        time_spec.month = (num_seconds.seconds - 31557600)/2629800;
        time_spec.day = (num_seconds.seconds-31557600 - 2629800)/86400;
        time_spec.hour = (num_seconds.seconds - 31557600 - 2629800 - 86400)/3600;
        time_spec.minute = (num_seconds.seconds - 31557600 - 2629800 - 86400 - 3600)/60;
        time_spec.second = (num_seconds.seconds - 31557600 - 2629800 - 86400 - 3600 -60);
        printf("\n%uy %un %ud %uh %um %us\n", time_spec.year, time_spec.month, time_spec.day, time_spec.hour, time_spec.minute, time_spec.second);


        return &time_spec;


    }

    else{
        return NULL;
    }



}

void print_time_spec( struct time_spec_t *time_spec ){
    /// output a valid time spec on stdout

    printf("\n%uy %un %ud %uh %um %us\n", time_spec->year, time_spec->month, time_spec->day, time_spec->hour, time_spec->minute, time_spec->second);

}

struct time_spec_t *string_to_time_spec( char * time_spec){
    /// return a pointer to a dynamically allocated struct containing the fields of a time spec specified by the string passed as the argument to the function.
    /// The string is known to contain a valid time spec. If memory for the struct cannot be allocated, the function returns NULL.
    struct time_spec_t time;

    sscanf(time_spec, "%uy %un %ud %uh %um %us",&time.year, &time.month,&time.day, &time.hour, &time.minute, &time.second);

    printf("\n%uy %un %ud %uh %um %us\n", time.year, time.month, time.day, time.hour, time.minute, time.second);

    return &time;

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
    puts( "Usage: time_calc help" );
    puts( " time_calc conv " );
    puts( " time_calc {add,subt,comp} " );
}

int main(int argc, char *argv[]) {


    int counter = 0;

    char * time = "31557600";
    char * time_null = NULL;
    char * test = "100y12n12d23h12m12s";
    char * string = "tyler";

    struct bool true;
    struct bool false;

    struct num_seconds_t num_seconds1;

    printf("**** Starting Regression Tests for Assignment 3 ****\n");


    // testing for legal seconds in is_legal_seconds, designing for edge cases
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

    false = is_legal_seconds(string);
    if(false.result !=0){
        ++counter;
        printf("\nfalse didn't worked for is_legal_seconds\n");
    }

//    // testing for null in is_legal seconds
//    printf("%s this is null", &time_null);
//    is_legal_seconds(&time_null);
//
//
//    // testing string to seconds
//    num_seconds1 = string_to_seconds(time);
//
//    printf("the num to seconds is: %u",num_seconds1.seconds);
//    if(num_seconds1.seconds != (uint32_t )1234){
//        counter++;
//        printf("\nString to second didn't work when testing for corrected seconds\n");
//    }
//
//    else{
//        printf("%u",num_seconds1);
//    }
//
//    seconds_to_time_spec(num_seconds1);
//
//
//    // testing is_legal_time_spec
//    is_legal_time_spec(test);
//
//
//    //testing print_time_spec
//    print_time_spec(test);

    printf("\nNumber of errors for Assignment3: %d\n", counter);


    printf("\n**** Finished Regression Tests for Assignment 3 ****\n");

    // done
    return 0;



}