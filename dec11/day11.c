#include <stdio.h>


#define GRID_AXIS_SIZE 300
#define GRID_SERIAL_NUMBER 4842 // generated puzzle input


int main(int argc, char** argv)
{
    //
    // build the grid in memory
    //
    int grid[GRID_AXIS_SIZE * GRID_AXIS_SIZE];

    {
        int pos, rack_id, power_level, hundreds_digit;

        for (int y = 1; y <= GRID_AXIS_SIZE; ++y) {
            for (int x = 1; x <= GRID_AXIS_SIZE; ++x)
            {
                // convert coords into flat array member
                pos = ((y - 1) * GRID_AXIS_SIZE) + (x - 1);

                // convoluted calculation from the problem description
                rack_id = x + 10;
                power_level = rack_id * y;
                power_level += GRID_SERIAL_NUMBER;
                power_level *= rack_id;
                hundreds_digit = (power_level / 100) % 10;

                grid[pos] = hundreds_digit - 5;
            }
        }
    }

    //
    // find the square of any size with the highest sum
    //
    int upper_left_x, upper_left_y, max, max_square_size;
    {
        int sum, pos;

        max = max_square_size = 0;

        // loop over all possible square sizes
        for (int size = 1; size <= GRID_AXIS_SIZE; ++size)
        {
            // loop over all possible upper-left-corners-of-AxA-squares, where A is the current size
            for (int y = 1; y <= (GRID_AXIS_SIZE - size + 1); ++y) {
                for (int x = 1; x <= (GRID_AXIS_SIZE - size + 1); ++x)
                {
                    // and for each of those upper-left corners, sum up their AxA grid
                    sum = 0;
                    for (int yl = 0; yl < size; ++yl) {
                        for (int xl = 0; xl < size; ++xl)
                        {
                            pos = ((y - 1 + yl) * GRID_AXIS_SIZE) + (x - 1 + xl);
                            sum += grid[pos];
                        }
                    }
                    if (sum > max) {
                        max = sum;
                        upper_left_x = x;
                        upper_left_y = y;
                        max_square_size = size;
                    }
                }
            }
        }
    }

    printf("At a sum of %d, the %dx%d grid with the best score is at (%d, %d)\n",
            max,
            max_square_size,
            max_square_size,
            upper_left_x,
            upper_left_y);
}
