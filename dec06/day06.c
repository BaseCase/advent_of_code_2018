// (40, 45) is the upper left coord
// (353, 358) is the lower right coord
// how the f do I do this?
//
//
// Maybe... we can bound the arena by the min/max of x, y of given coords,
//   because anything on an edge would be infinite? I don't know if that's true, but
//   it *seems* true...
//
// So, if you're on an edge, we still have to compute your area, *but*:
//      - you can't be a winner. if you win, we have to exclude you from the results
//      - we only compute areas up to the edges, so
//             WAIT. Is that true? I think it might not be true...
//             Nope. It's not true.
//             Fuck.
//
//      - AH, but wait! If you can escape past the edge, maybe that means you are infinite and should also
//          be disqualified. I think that sounds plausible.
//      - If that's true, then maybe all we need is a 1-deep wrapper layer around the perimeter, and if you
//          overflow into that, we know you bad.
//
//
//        SO: naive solution could be:
//            1. read in coords.
//            2. establish the perimeter.
//            3. add a 1-deep padding wrapper around the outside, around the outside, around the outside
//            4. For every coord on the grid, find the closest plotted coord via Manhattan Distance.
//               4a. We can do this in a spiral pattern. e.g.
//                          1a 2a 3a 4a 5a
//                          1b 2b 3b 4b 5b
//                          1c 2c 3c 4c 5c
//                          1d 2d 3d 4d 5d
//                          1e 2e 3e 4e 5e
//                    If we want to find the closest coord for 3c, we check concentric rings further and further outside
//                    it, so first pass: 2b, 3b, 4b, 2c, 4c, 2d, 3d, 4d.
//                    If nothing is found there, move out a ring and try again.
//
//                    We always check the *full* ring, because if there's more than one hit, we *might* have a tie.
//                    We don't *necessarily* have a tie, so we still have to computer the distances.
//
//                    Hmm, one wrinkle in this: unless it's square in line with the cell we're looking at, we don't know
//                    that something doesn't have a tied distance cell in a further out ring, because of how Manhattan Distance
//                    works. Like, if you see something on a diagonal, there might be another cell on the next spiral out that's
//                    the same MD away.
//
//                    So, how do we account for that fact?
//
//
//                    .........
//                    .°°......
//                    .........
//                    .........
//                    ....*....
//                    .........
//                    .........
//                    .........
//                    .........
//
//                    theorems:
//                      - if we first see somebody on the same row or col as us, we know they have to be the closest
//                        and *do not* have to check any additional rings.
//                      - if we first see somebody *not* on our row or col, we have to check *at least* the next ring out.
//                          Q: how many additional rings do we have to check?
//
//                    In this way, we can find the closest plotted coord for every point in a reasonably efficient way.
//
//                    If you are looking at a cell and it is already claimed, mark it as a '.' instead. Those are contested
//                    spaces and don't count.
//
//
//                    At first I was thinking we needed some kind of hash table or something, but I *think* we can just include
//                    a "plotted" bool in the struct that lives at each coord, and while we're doing our spiral check, we check
//                    that value in each of the other coords we look at. Checking every single cell in a ring is maybe a little
//                    less efficient than directly checking if the coords are in a hash, well, NO, probably it isn't? I think a hash
//                    lookup would be slower than just checking a value in a struct. We have to check there *anyway*, so why not?
//
//            5. Holy shit, OK. So now we've marked every cell on the map as belonging to one or more of our plotted coords. We need
//               to eliminate ineligible plotted coords. To do this, we look at the outer wrapper ring. Any plotted coords mentioned
//               here could have an infinite area and is ineligible, so we should save those down somewhere to filter out later.
//            6. Now we sum up every plotted coord's areas.
//            7. The largest one wins! After filtering out the inifinites of course.
//
//
//
//
//
//             .........*........
//             x.................
//             ........y.........
//



#include <stdio.h>


int main(int argc, char** argv)
{
    printf("heyo.\n");
}
