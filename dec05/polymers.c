#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_matched_pair(char a, char b);


int main(int argc, char** argv)
{
    char *original_polymer, *reduced_polymer;
    int polymer_length, original_reduced_polymer_length, smallest_reduced_polymer_length;

    //
    // parse input stream
    //
    {
        char c;
        int buffer_i;
        original_polymer = (char*) malloc(sizeof(char) * 50100); // input is about 50000 long

        buffer_i = 0;
        while ((c = getc(stdin)) != EOF && (c != '\n'))
        {
            original_polymer[buffer_i++] = c;
        }
        original_polymer[buffer_i] = 0;
        polymer_length = buffer_i;
    }


    //
    // Try the reduction 26 times, for each letter of the alphabet,
    // removing one letter from the source input at a time.
    // The answer to part 2 is the length of the shortest of these you can get.
    // We'll do a run first with no removals to get the answer to part 1.
    //
    {
        int src_i, dest_i, eliminations_count, src_len, reduced_polymer_length;
        char *src, *dest;

        src = (char*) malloc(sizeof(char) * polymer_length);
        dest = (char*) malloc(sizeof(char) * polymer_length);

        original_reduced_polymer_length = 0;
        smallest_reduced_polymer_length = 50000;

        for (int removal_i = -1; removal_i < 26; ++removal_i)
        {
            char skipped_uppercase = removal_i + 'A';
            char skipped_lowercase = removal_i + 'a';

            //
            // Trim out the unwanted characters before entering the main reduction process.
            //
            for (src_i = 0, dest_i = 0; src_i < polymer_length; ++src_i)
            {
                if (original_polymer[src_i] == skipped_uppercase || original_polymer[src_i] == skipped_lowercase)
                    continue;

                src[dest_i++] = original_polymer[src_i];
            }
            src_len = dest_i;

            //
            // loop over chars, creating a new array each time and freeing the old one
            // keep track of how many eliminations occurred
            // continue looping until you make it to the end with no eliminations
            //
            {
                do {
                    dest_i = 0;
                    eliminations_count = 0;

                    for (src_i = 0; src_i < src_len; ++src_i)
                    {
                        if ((src_i != src_len - 1)  // don't need to check pairs if we're on the last char
                                && is_matched_pair(src[src_i], src[src_i + 1]))
                        {
                            // jump over pairs while copying the string
                            ++eliminations_count;
                            ++src_i;
                            continue;
                        }


                        dest[dest_i++] = src[src_i];
                    }
                    dest[dest_i] = 0;

                    src = dest;
                    src_len = dest_i;

                } while (eliminations_count > 0);

                reduced_polymer = src;
                reduced_polymer_length = src_len;

                if (original_reduced_polymer_length == 0)
                    original_reduced_polymer_length = reduced_polymer_length;

                if ((reduced_polymer_length < smallest_reduced_polymer_length) && (reduced_polymer_length > 0))
                    smallest_reduced_polymer_length = reduced_polymer_length;
            }

        }
    }


    printf("The full reduced polymer is length %d\n", original_reduced_polymer_length);
    printf("The smallest reduced polymer when stripping one letter at a time is length %d\n", smallest_reduced_polymer_length);
}


int is_matched_pair(char a, char b)
{
    if (a > b)
        return (a == (b + 32));
    else
        return (b == (a + 32));
}
