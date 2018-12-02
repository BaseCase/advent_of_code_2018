#include <stdio.h>
#include <stdlib.h>


int memo_contains_value(int* list, int size, int target);


#define SEQ_LEN 1000

// Run this like so: `cc -Ofast freq.c && cat input.txt | ./a.out`
int main(int argc, char **argv) {
    char c;
    int parsed, buffer_i, sequence_i, totals_memo_i, current_total, single_total;
    char buffer[20];
    int sequence[SEQ_LEN];
    int totals_memo[SEQ_LEN * 1000];

    sequence_i = totals_memo_i = current_total = single_total = 0;

    // parse complete input into memory before starting the cycle
    for(;;) {
        buffer_i = 0;
        while((c = getc(stdin)) != '\n') {
            if (c == EOF) break;
            buffer[buffer_i++] = c;
        }
        if (c == EOF) break;
        buffer[buffer_i] = 0;
        parsed = atoi(buffer);

        sequence[sequence_i++] = parsed;
    }

    // loop over the sequence of numbers, breaking once we see a repeat sum
    for(;;) {
        if (sequence_i == SEQ_LEN) {
            sequence_i = 0;

            if (single_total == 0)
                single_total = current_total;
        }

        current_total += sequence[sequence_i++];

        if (memo_contains_value(totals_memo, totals_memo_i, current_total))
            break;

        // This is a shockingly lazy way to do this -.-
        totals_memo[totals_memo_i++] = current_total;
    }

    printf("Sum of sequence: %d\n", single_total);
    printf("First duped total: %d\n", current_total);

    return 0;
}

// Truly heinous efficiency characteristics lmaoooo.
int memo_contains_value(int* list, int size, int target) {
    for (int i = 0; i < size; i++)
        if (list[i] == target)
            return 1;

    return 0;
}
