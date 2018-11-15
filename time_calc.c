#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/// structure used for true (1) and false (0)
struct bool{
    int  result;
};

/// time_spec structure used to designate a specific time
struct time_spec_t{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

/// num_seconds  structure used to designate a specific number of seconds
struct num_seconds_t{
    uint32_t seconds;
};

/// is_legal_time_spec returns true if the input argument is a valid time spec,
/// otherwise will return false.
/// Errors diagnosed are extra characters and field values exceeding limits.
/// param: time_spec a string following the time spec format
/// return: true or false depending on
struct bool is_legal_time_spec(char * time_spec){
    struct bool true; // boolean structure used for true
    struct bool false; // boolean structure used for false
    true.result = 1; // initializing boolean structure used for true
    false.result = 0; // initializing boolean structure used for false
    struct time_spec_t time; // time_spec structure used for time spec

    // no input returns NULL
    if(time_spec==NULL){
        printf("There was no input");
        return false;
    }

    else{
        // checking if input string will satisfy the arguments needed for is_legal_time_spec
        if(sscanf(time_spec, "%uy %un %ud %uh %um %us",&time.year, &time.month,&time.day, &time.hour, &time.minute, &time.second) > 5) {

            // checking that time_spec has proper input
            if (time.year <= 100 && time.month <= 12 && time.day <= 31 && time.hour <= 24 && time.minute <= 60 && time.second < 60) {
                return true;
            }
            else {
                printf("The string entered does not conform to time_spec standard, see usage for more detail.");
                return false;
            }
        }
        // poor input
        else{
            printf("There was an improper string entered. See usage for more detail.");
            return false;
        }
    }

}

/// is_legal_seconds returns true if the input argument is a valid second,
/// otherwise will return false.
/// Errors diagnosed are extra characters and field values exceeding limits.
/// param: seconds a string following the num_seconds_t spec format
/// return: true or false depending on input
struct bool is_legal_seconds(char* seconds){
    struct bool true; // boolean structure used for true
    struct bool false; // boolean structure used for false
    true.result = 1; // initializing boolean structure used for true
    false.result = 0; // initializing boolean structure used for false
    struct num_seconds_t *num_seconds_ptr, num_seconds;  // num_seconds_t structure used for num_seconds
    num_seconds_ptr = &num_seconds;

    // checking that input exists
    if(!seconds){
        printf("There was no input");
        return false;
    }

    else {
        // checking that the number of arguments passed was in the correct format
        if (sscanf(seconds, "%u", &(*num_seconds_ptr).seconds) > 0) {
            return true;
        }

        else {
            printf("The number entered is not in the correct format. See usage for more detail.");
            return false;
        }
    }

}

/// string_to_seconds returns the number of seconds passed
/// as the argument to the function.
/// The string is known to be legal using is_legal_seconds function.
/// param: seconds is a string of seconds.
/// return: A num_seconds_t structure resembling seconds, NULL otherwise.
struct num_seconds_t string_to_seconds(char * seconds) {
    struct bool flag; // boolean structure used to check legality of seconds
    struct num_seconds_t *num_seconds_ptr, num_seconds; // structures used for return
    num_seconds_ptr = &num_seconds;

    // checking legality of input
    flag = is_legal_seconds(seconds);

    // checking input
    if(flag.result == 1){

        //converting string to num_seconds_t struct
        sscanf(seconds, "%u", &(*num_seconds_ptr).seconds);
        return num_seconds;

    }
    // return nulle
    else{
        // set num_seconds to null
        num_seconds.seconds = NULL;
        return num_seconds;
    }

}

/// string_to_time_spec returns the time_sec passed
/// as the argument to the function.
/// The string is known to be legal using is_legal_time_spec function.
/// param: time_spec is a string resembling time_spec.
/// return: A time_spec_t structure pointer resembling seconds, NULL otherwise
struct time_spec_t *string_to_time_spec( char * time_spec){
    struct bool flag; // a flag used to check if the passed in argument is legal or not
    unsigned int year, month, day, hour, minute, second;
    struct time_spec_t *ptime, time; // pointer and structure for time
    ptime = &time;

    // check if time_spec is a valid input
    flag = is_legal_time_spec(time_spec);

    if(flag.result ==1){
        // converting input to valid time_spec structure
        sscanf(time_spec, "%uy %un %ud %uh %um %us",&(*ptime).year, &(*ptime).month,&(*ptime).day, &(*ptime).hour, &(*ptime).minute, &(*ptime).second);
        return &time;

    }

    else{
        // returns null
        return NULL;
    }

}

/// seconds_to_time_spec converts a valid number of seconds to a time spec.
/// The fields of the time spec in a dynamically allocated.
/// param: num_seconds: a valid number of seconds
/// return: ptime_spec: a valid pointer of structure type time_spec. converted from seconds. NULL otherwise
struct time_spec_t *seconds_to_time_spec( struct num_seconds_t num_seconds ){
    struct time_spec_t *ptime_spec, time_spec; // time spec that will be used to point toward the corect conversions
    unsigned int holder, year, month, day, hour, minute, second; // using unsigned int to help convert between uint32 to uint8

    ptime_spec = (struct time_spec_t*) malloc(100 * sizeof( time_spec)); // allocating memory for ptime_spec

    holder = (num_seconds.seconds); // holding the number of seconds

    // checking if holder is valid
    if(holder > 0){
        year = holder/31557600; // holding year
        month = (holder - (year*31557600))/26289800; // holding month
        day = (holder - (year*31557600) - (month*2629800))/86400; // holding day
        hour= (holder - (year*31557600) - (month*2629800) - (day*86400))/3600; // holding hour
        minute= (holder - (year*31557600) - (month*2629800) - (day*86400) - (hour*3600))/60; // holding minute
        second = (holder - (year*31557600) - (month*2629800) - (day*86400) - (hour*3600) - (minute*60)); // holding seconds

        ptime_spec->year = (uint8_t) year; // pointing toward correct year
        ptime_spec->month = (uint8_t) month ; // pointing toward correct month
        ptime_spec->day = (uint8_t) day; // pointing toward correct day
        ptime_spec->hour = (uint8_t) hour; // pointing toward correct hour
        ptime_spec->minute = (uint8_t) minute; // pointing toward correct minute
        ptime_spec->second = (uint8_t) second; // pointing toward correct second

        // checking that the input is a valid time_spec
        if (year <= 100 && month <= 12 && day <= 31 && hour <= 24 && minute <= 60 && second <= 60){

            // outputting time_spec
            printf("\n%uy %un %ud %uh %um %us\n", ptime_spec->year, ptime_spec->month, ptime_spec->day, ptime_spec->hour, ptime_spec->minute, ptime_spec->second);
            return ptime_spec;
        }

        else{
            printf("Not enough memory");
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
        seconds = (uint32_t) (time.year*31557600 + time.month*26289800 + time.day*86400 + time.hour*3600 + time.minute*60 + time.second*60) ;
        num_sec.seconds = seconds;
        return num_sec;
    }

    else{
        num_sec.seconds = NULL;
        return num_sec;
    }

}

/// get_time_arg will return true if it was able to convert the string pointed to by in_str to a number of seconds.
/// The number of seconds is stored in the location pointed to by seconds_p.
/// The string pointed to by in_str can be either a time_spec format or num_seconds_t format
/// The function returns FALSE if it was not able to convert the string pointed to by in_str to a number of seconds;
/// or if the number of seconds more than the limit of 3155760000.
/// param: *in_str: a character array in num_seconds_t format or time_spec format
/// param: *seconds_p: a num_seconds_t pointer that will point toward correct numbers_second_t format
/// return: true or false depending on input. Errors will be read to stdout.
struct bool get_time_arg( char *in_str, struct num_seconds_t *seconds_p ){

    struct bool flag;// boolean structure used to check legitimacy of input

    // checking if input is legal time_spec format
    flag = is_legal_time_spec(in_str);
    // checking time_spec
    if(flag.result == 1){
        // setting seconds_p pointer to converted time_spec from seconds
        *seconds_p = time_spec_to_seconds(in_str);
        return flag;
    }

    else{
        // check if the input is legal numbers_seconds_t format
        flag = is_legal_seconds(in_str);
        if (flag.result ==1){
            // converting in_str to proper num_seconds_t structure and setting pointer toward it
            *seconds_p = string_to_seconds(in_str);
            // checking that input is legitimately within bounds
            if(seconds_p->seconds < 3155760000){
                return flag;
            }
        }
        // outputting errors
        printf("\nThe string submitted was not a correct value or was greater than 3155760000.\n");
        return flag;
    }

}

/// print_time_spec outputs a it's input to stdout in time_spec format
/// param: *time_spec: a pointer to a legitimate time_spec.
/// return: none
void print_time_spec( struct time_spec_t *time_spec ){
    //output a valid time spec on stdout
    printf("\n%uy %un %ud %uh %um %us\n", time_spec->year, time_spec->month, time_spec->day, time_spec->hour, time_spec->minute, time_spec->second);

}

/// print_seconds outputs a it's input to stdout in seconds format
/// param: *time_spec: a pointer to a legitimate time_spec.
/// return: none
void print_seconds( struct num_seconds_t *num ){
    //output a valid time spec on stdout
    printf("\n%u\n", num->seconds);

}

/// subtract_seconds subtracts two strings of seconds and outputs the result in time_spec format
/// the input is converted prior to usage.
/// param: *num1: a pointer to a number_of_seconds_t structure
/// param: *num2: a pointer to a number_of_seconds_t structure
/// return: none
void subtract_seconds(struct num_seconds_t *num1, struct num_seconds_t *num2){
    struct num_seconds_t num_seconds, *pnum_seconds; // initilzing structure num_seconds to perform operations
    pnum_seconds = &num_seconds;

    struct time_spec_t *ptime_spec; // time spec structure to be outputted

    pnum_seconds->seconds = num1->seconds - num2->seconds; // performing operations
    num_seconds.seconds = pnum_seconds->seconds; // setting seconds
    ptime_spec = seconds_to_time_spec(num_seconds); // convert input to output
    print_time_spec(ptime_spec);// print output to
}

/// add_seconds adds two strings of seconds and outputs the result in time_spec format
/// the input is converted prior to usage.
/// param: *num1: a pointer to a number_of_seconds_t structure
/// param: *num2: a pointer to a number_of_seconds_t structure
/// return: none
void add_seconds(struct num_seconds_t *num1, struct num_seconds_t *num2){
    struct num_seconds_t num_seconds, *pnum_seconds; // initilzing structure num_seconds to perform operations
    pnum_seconds = &num_seconds;

    struct time_spec_t *ptime_spec; // time spec structure to be outputted

    pnum_seconds->seconds = num1->seconds + num2->seconds; // performing operations
    num_seconds.seconds = pnum_seconds->seconds; // setting seconds
    ptime_spec = seconds_to_time_spec(num_seconds); // convert input to output
    print_time_spec(ptime_spec);// print output to

}

/// comp_seconds compares two strings of seconds and outputs
/// if the time strings are greater than, less than, or equal to one another
/// the input is converted prior to usage.
/// param: *num1: a pointer to a number_of_seconds_t structure
/// param: *num2: a pointer to a number_of_seconds_t structure
/// return: none
void comp_seconds(struct num_seconds_t *num1, struct num_seconds_t *num2){
    // checking the size of seconds
    if (num1->seconds > num2->seconds){
        printf("\nGreater");
    }
    // assuring they are not equal
    else if (num1->seconds < num2->seconds){
        printf("\nLess");
    }
    // otherwise input is equal
    else{
        printf("\nEqual");
    }


}

/// usage outputs the operation documentation for time_calc when flagging -help
/// param: none
/// return: none
void usage( void ) {
    puts( "\nUsage: \ntime_calc help" );

    puts( "\ntime_calc conv: time_calc will convert between two types of time values."
          "\nEnter format as a time_spec: '(0-100)y (0-12)n (0-31)d (0-24)h (0-60)m (0-60)s'"
          "\nor as a time in seconds between 0 - 3155760000."
          "\ntime_spec input will be converted to seconds and seconds will be converted to time_spec and "
          "\nshown on stdout. eg. 1y 0n 0d 0h 0m 0s will be 31557600\n" );

    puts( "\ntime_calc options {add,subt,comp}\n"
          "\n add: add two different strings of time together. eg. '1234' '1234' will be 2468\n"
          "\n sub: subtract two different strings time. eg. '1234' '1234' will be 0\n"
          "\n comp: compare two different strings of time to see which is greater, less than, or equal to. "
          "\n        eg. '1234' '1234' will be 'equal\n");
}

/// main is used for passing arguments through to the time_calc program.
/// Testing was done here for development purposes.
/// param: argc; the number of inputs
/// param: argv; a list of properties for time_spec
/// return: 0
int main(int argc, char *argv[]) {
//    int counter = 0;
//    struct bool true;
//    struct bool false;
//
//    char * time = "31557600";
//    char * time_null = NULL;
//    char * time_spec_string = "100y12n12d23h12m12s";
//    char * time_spec_string2 = "101y13n13d25h13m13s";
//    char * time_spec_string3 = "1y0n0d0h0m0s";
//    char * string = "tyler";
//
//    struct num_seconds_t num_seconds1, *pnum_seconds1, *pnum1, *pnum2, num1, num2;
//    pnum_seconds1 = &num_seconds1;
//    pnum1 = &num1;
//    pnum2 = &num2;
//
//    struct time_spec_t time_spec, time_spec1, *ptime_spec1;
//    time_spec.year = 100;
//    time_spec.month = 12;
//    time_spec.day = 12;
//    time_spec.hour = 12;
//    time_spec.minute = 12;
//    time_spec.second = 12;
//
//    ptime_spec1 = &time_spec1;
//
//    pnum1->seconds = 100;
//    pnum2->seconds = 50;
//
//
//    printf("**** Starting Regression Tests for Assignment 3 ****\n");
//
//    // ******** testing for legal seconds in is_legal_seconds, designing for edge cases ********
//    true = is_legal_seconds(time);
//    false = is_legal_seconds(string);
//
//    // testing for true
//    if(true.result != 1){
//        ++counter;
//        printf("\ntrue didn't worked for is_legal_seconds\n");
//    }
//
//    // testing for false
//    if(false.result !=0){
//        ++counter;
//        printf("\nfalse didn't worked for is_legal_seconds\n");
//    }
//
//    // testing for null
//    false = is_legal_seconds(time_null);
//    if(false.result !=0){
//        ++counter;
//        printf("\nfalse didn't worked for NULL in is_legal_seconds\n");
//    }
//
//    // ******** testing for legal time spec in is_legal_time_spec, designing for edge cases ********
//    true = is_legal_time_spec(time_spec_string);
//    false = is_legal_time_spec(string);
//
//    // testing for true
//    if(true.result != 1){
//        ++counter;
//        printf("\ntrue didn't worked for is_legal_time_spec\n");
//    }
//
//    // testing for false with string
//    if(false.result !=0){
//        ++counter;
//        printf("\nfalse didn't worked for is_legal_time_spec\n");
//    }
//
//    // testing for null
//    false = is_legal_time_spec(time_null);
//    if(false.result !=0){
//        ++counter;
//        printf("\nfalse didn't worked for NULL in is_legal_time_spec\n");
//    }
//
//    // testing for false with numbers out of range
//    false = is_legal_time_spec(time_spec_string2);
//    if(false.result !=0){
//        ++counter;
//        printf("\nfalse didn't worked for is_legal_time_spec with out of range numbers\n");
//    }
//
//    // ******** testing for string conversion in string_to_seconds, designing for edge cases ********
//
//    // testing string to seconds with correct input
//    num_seconds1 = string_to_seconds(time);
//    if(num_seconds1.seconds != (uint32_t )31557600){
//        ++counter;
//        printf("\nString to second didn't work when testing for correct number of seconds\n");
//    }
//
//    // testing for non valid input
//    num_seconds1 = string_to_seconds(time_null);
//    if(num_seconds1.seconds != NULL){
//        ++counter;
//        printf("\nString to second didn't work when testing for non-valid input.\n");
//    }
//
//
//    // ******** testing for string conversion in string_to_time_spec, designing for edge cases ********
//
//    // testing with correct input
//    ptime_spec1 = string_to_time_spec(time_spec_string);
//    if(ptime_spec1->year != 100){
//        ++counter;
//        printf("\nError with string_to_time_spec with correct input, conversion failed.\n");
//    }
//
//    // testing with incorrect input
//    ptime_spec1 = string_to_time_spec(time_spec_string2);
//    if(ptime_spec1 != NULL){
//        ++counter;
//        printf("\n Error with string_to_time_spec for incorrect input, conversion failed .");
//    }
//
//
//    // ******** testing for seconds to time conversion for in seconds_to_time_spec, designing for edge cases ********
//
//    // testing seconds for a single year
//    num_seconds1.seconds = 31557600;
//    ptime_spec1 = seconds_to_time_spec(num_seconds1);
//    if(ptime_spec1->year != 1){
//        ++counter;
//        printf("seconds for 1 year didn't work for seconds_to_time_spec");
//    }
//
//
//    // testing for time greater than 1 year
//    num_seconds1.seconds = 31557601;
//    ptime_spec1 = seconds_to_time_spec(num_seconds1);
//    if(ptime_spec1->year != 1){
//        ++counter;
//        printf("seconds larger than 1 year didn't work for seconds_to_time_spec");
//    }
//
//    // testing for seconds less than 60
//    num_seconds1.seconds = 45;
//    ptime_spec1 = seconds_to_time_spec(num_seconds1);
//    if(ptime_spec1->year != NULL){
//        ++counter;
//        printf("seconds much larger than 1 year didn't work for seconds_to_time_spec");
//    }
//
//    // testing for null value
//    num_seconds1.seconds = NULL;
//    ptime_spec1 = seconds_to_time_spec(num_seconds1);
//    if(ptime_spec1 != NULL){
//        ++counter;
//        printf("NULL didn't work for seconds_to_time_spec");
//    }
//
//    // ******** testing time_spec_to_seconds ********
//    time_spec_to_seconds(time_spec_string3);
//
//    // ******** testing get_time_arg ********
//
//    // testing with regular seconds
//    true = get_time_arg(time, pnum_seconds1);
//    if(true.result!=1){
//        ++counter;
//        printf("\nThis should be 31557600 but showing, error with seconds: %u\n", pnum_seconds1->seconds);
//    }
//
//    // testing with time_spec argument
//    true = get_time_arg(time_spec_string3, pnum_seconds1);
//    if(true.result!=1){
//        ++counter;
//        printf("\nThis should be 31557600 but showing, error with time spec: %u\n", pnum_seconds1->seconds);
//    }
//
//    // testing for large number
//    time = "3155760001";
//    num_seconds1 = string_to_seconds(time);
//    if(false.result!=0){
//        ++counter;
//        printf("\nThis should be 3155760001 but showing, error with time spec: %u\n", pnum_seconds1->seconds);
//    }
//
//    // testing for NULL
//    false = get_time_arg(NULL, pnum_seconds1);
//    if(false.result!=0){
//        ++counter;
//        printf("\nThis should be Nothing but showing, error with NULL: %u\n", pnum_seconds1->seconds);
//    }
//
//
//    // ******** testing print_time_spec ********
//    print_time_spec(&time_spec);
//
//
//    // ******** testing subtract_seconds ********
//
//    // subtracting two whole integers
//    subtract_seconds(pnum1, pnum2);
//
//    // ******** testing add_seconds ********
//
//    // adding two whole integers
//    add_seconds(&num1, &num2);
//
//    // ******** testing comp_seconds ********
//
//    // testing for
//    comp_seconds(&num1, &num2);
//
//    // testing for less than
//    comp_seconds(&num2, &num1);
//
//    // testing for equal
//    num2.seconds = 100;
//    comp_seconds(&num1, &num2);
//
//    // ******** testing usage ********
//    usage();
//
//    printf("\nNumber of errors for Assignment 3: %d\n", counter);
//
//    printf("\n**** Finished Regression Tests for Assignment 3 ****\n");


    struct bool flag;
    struct num_seconds_t num, *pnum;
    pnum = &num;
    struct time_spec_t time, *ptime;
    ptime = &time;

    if(argc == 3) {
        if(argv[1] == "conv"){
            flag = is_legal_seconds(argv[2]);
            if(flag.result == 1){
                num = string_to_seconds(argv[1]);
                ptime = seconds_to_time_spec(num);
                print_time_spec(ptime);
                return 0;
            }
            else{
                flag = is_legal_time_spec(argv[1]);
                if(flag.result == 1){
                    ptime = string_to_time_spec(argv[1]);
                    num = time_spec_to_seconds(ptime);
                    print_seconds(pnum);
                    return 0;

                }
                usage();
                return 0;
            }

        }
        else{
            usage();
        }

    }


    else if( argc > 2 && argc < 4 ) {

        printf("Too many arguments supplied.\n");
    }


    else {
       usage();
       return 0;
    }

    // done
    return 0;



}