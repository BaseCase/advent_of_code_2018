#include <stdio.h>
#include <stdint.h>


typedef uint32_t u32;


// this is the number of recipes we have to get to,
// then go another 10 past it to get our answer
#define PUZZLE_INPUT 580741


int main(int argc, char **argv)
{
    int scores[PUZZLE_INPUT + 15] = {0};
    int new_score;
    u32 elf1_pos, elf2_pos, scores_n;

    // given setup
    scores[0] = 3;
    scores[1] = 7;
    scores_n = 2;
    elf1_pos = 0;
    elf2_pos = 1;

    while(1)
    {
        // combine recipes to make new one or two
        new_score = scores[elf1_pos] + scores[elf2_pos];
        if (new_score >= 10) {
            scores[scores_n++] = 1;
            new_score = new_score - 10;
        }
        scores[scores_n++] = new_score;

        // each elf steps forward 1 + current recipe score, looping back around
        elf1_pos = (elf1_pos + scores[elf1_pos] + 1) % (scores_n);
        elf2_pos = (elf2_pos + scores[elf2_pos] + 1) % (scores_n);

        if (scores_n >= PUZZLE_INPUT + 10) {
            printf("Part 1 answer: ");
            for (u32 i = PUZZLE_INPUT; i < scores_n; ++i)
            {
                printf("%d", scores[i]);
            }
            printf("\n");

            break;
        }
    }
}
