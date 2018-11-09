#include <iostream>
#include <stdint.h>



struct bool{
    int true = 1;
    int false = 0;
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




};


struct bool is_legal_time_spec(char *){
    /// return TRUE if the string given as the input argument is a valid time spec;
    /// otherwise produce diagnostic messages on stderr and return FALSE.
    /// Errors diagnosed include extraneous characters and field values exceeding limits.


    if (*){
        return 1;
    }
    else{
        return 0;
    }

}


struct bool is_legal_seconds(){

    /// return TRUE if the string given as the input argument is a valid number of seconds;
    /// otherwise produce diagnostic messages on stderr and return FALSE.
    /// Errors diagnosed include extraneous characters and field values exceeding the limit on the number of seconds

}


struct num_seconds_t string_to_seconds(char *) {
    /// return the number of seconds specified by the string passed as the argument to the function.
    /// The string is known to contain a valid "number of seconds" specification


}



struct time_spec_t *string_to_time_spec( char * ){
    /// return a pointer to a dynamically allocated struct containing the fields of a time spec specified by the string passed as the argument to the function.
    /// The string is known to contain a valid time spec. If memory for the struct cannot be allocated, the function returns NULL.

}



struct time_spec_t *seconds_to_time_spec( num_seconds_t ){
    /// convert a valid number of seconds to a time spec, and store the fields of the time spec in a dynamically allocated time_spec_t structure.
    /// On success, a pointer to the newly allocated structure is returned. If memory for the struct cannot be allocated, the function returns NULL.

}

void print_time_spec( struct time_spec_t *time_spec ){
    /// output a valid time spec on stdout

}


struct bool get_time_arg( char *in_str, struct num_seconds_t *seconds_p ){
    /// the function returns TRUE if it was able to convert the string pointed to by in_str to a number of seconds.
    /// In this case the number of seconds is stored in the location pointed to by seconds_p.
    /// The string pointed to by in_str could be a time spec or it could specify a number of seconds.
    /// The function returns FALSE if it was not able to convert the string pointed to by in_str to a number of seconds;
    /// for example, the string was neither a legal time spec nor a legal number of seconds.
    /// It also returns FALSE if the number of seconds is not less than the limit of 3155760000.
    /// In the latter two cases an appropriate error message is generated on stderr.
    /// If the input pointed to by in_str is neither a legal time spec nor a legal number of seconds, then no operation should be performed on the location pointed to by seconds_p.


}

void usage( void ) {
    puts( "Usage: time_calc help" );
    puts( " time_calc conv " );
    puts( " time_calc {add,subt,comp} " );
}



int main(int argc, char *argv[]) {


    std::cout << "testing!" << std::endl;
    return 0;



}