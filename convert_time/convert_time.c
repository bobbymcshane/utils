#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// TODO: make this posix_strftime which can take in a posix time in millis,
// micros, or nanos and print it with the format specifier %N for nanos, %i for
// millis %o for micros... also accept a precision specifier for any strftime
// param that prints seconds to let it print nanos, millis, etc...
void print_posix_nanoseconds( uint64_t posix_nanoseconds ) {
    time_t posix_seconds = posix_nanoseconds / 1000000000ULL;
    uint64_t nanoseconds = posix_nanoseconds - ((uint64_t)posix_seconds * 1000000000ULL);

    struct tm converted_time;
    localtime_r( &posix_seconds, &converted_time );
    char time_str[BUFSIZ];
    // TODO: scan through the strftime format string and stick the nanoseconds where each %N is.
    // this could be done with snprintf by escaping all format specifiers that
    // aren't mine with an extra %
    // TODO: let the user pass this in
    const char *format = "%%a, %%d %%b %%Y %%H:%%M:%%S.%09" PRIu64 " %%z";
    char format_str[strlen( format ) + 128];
    sprintf( format_str, format, nanoseconds );
    strftime( time_str, sizeof( time_str ), format_str, &converted_time );
    puts( time_str );
}

int main(int argc, const char *argv[]) {
    print_posix_nanoseconds( 1520207703046569440ULL );
    return 0;
}
