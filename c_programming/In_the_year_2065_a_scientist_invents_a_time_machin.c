#include <stdio.h>

struct Time {
    int seconds, minutes, hours;
};

int main() {
    struct Time startTime, stopTime, diff;

    printf("Enter start time (hours minutes seconds): ");
    scanf("%d %d %d", &startTime.hours, &startTime.minutes, &startTime.seconds);

    printf("Enter stop time (hours minutes seconds): ");
    scanf("%d %d %d", &stopTime.hours, &stopTime.minutes, &stopTime.seconds);

    if (stopTime.seconds > startTime.seconds) {
        --startTime.minutes;
        startTime.seconds += 60;
    }
    diff.seconds = startTime.seconds - stopTime.seconds;

    if (stopTime.minutes > startTime.minutes) {
        --startTime.hours;
        startTime.minutes += 60;
    }
    diff.minutes = startTime.minutes - stopTime.minutes;
    diff.hours = startTime.hours - stopTime.hours;

    if (diff.hours < 0) {
        diff.hours += 24;
    }

    printf("%d:%d:%d\n", diff.hours, diff.minutes, diff.seconds);

    return 0;
}
