#include <stdio.h>
#include <stdlib.h>


int is_matched_pair(char a, char b);


int main(int argc, char** argv)
{
    char *polymer, *reduced_polymer;
    int polymer_length, reduced_polymer_length;

    //
    // parse input stream
    //   (may as well eliminate pairs on the way in, too)
    //
    {
        char c;
        int buffer_i;
        polymer = (char*) malloc(sizeof(char) * 50100); // input is about 50000 long

        buffer_i = 0;
        while ((c = getc(stdin)) != EOF && (c != '\n'))
        {
            polymer[buffer_i++] = c;
        }
        polymer[buffer_i] = 0;
        polymer_length = buffer_i;
    }


    //
    // loop over chars, creating a new array each time and freeing the old one
    // keep track of how many eliminations occurred
    // continue looping until you make it to the end with no eliminations
    //
    {
        int src_i, dest_i, eliminations_count, src_len;
        char *src, *dest, *tmp;

        src_len = polymer_length;
        src = polymer;

        do {
            dest = (char*) malloc(sizeof(char) * src_len);
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

            tmp = src;
            src = dest;
            free(tmp);
            src_len = dest_i;

        } while (eliminations_count > 0);

        reduced_polymer = src;
        reduced_polymer_length = src_len;
    }


    //
    // Answer is the length of the remaining string
    //
    {
        printf("After all that, we wound up with a polymer of length %d\n", reduced_polymer_length);
    }
}


int is_matched_pair(char a, char b)
{
    if (a > b)
        return (a == (b + 32));
    else
        return (b == (a + 32));
}
