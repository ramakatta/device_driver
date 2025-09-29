#include <stdlib.h>
#include <string.h>

void leaky_definitely(void)
{
    char *p;

    /*
    This is definitely lost because the pointer is a local variable
    and once we exit the function we lose the reference to the
    allocated block, so there's no way to free this block.
    */
    p = malloc(sizeof(char));
}

char *g_p;

void leaky_still_reachable(void)
{
    /*
    This is still reachable because the pointer is a global variable
    that's preserved until the end of our program, so we could have
    called free on it.
    */
    g_p = malloc(sizeof(char));
}

char *leaky_array;

void leaky_possibly(void)
{
    leaky_array = malloc(3*sizeof(char));

    /*
    This is possibly lost because the allocated base pointer was lost
    as we incremented it twice, but because leaky_array still points
    somwewhere in the allocated block, we could have done something
    to recover the base pointer and then free it.

    To transform this possibly lost leak into a definitely lost leak,
    just change '2' to '3' in the loop.
    */
    for(int i = 0; i < 2; i++) {
        *leaky_array = i;
        leaky_array++;
    }
}

char **double_pointer;

void leaky_indirectly(void)
{
    double_pointer = malloc(sizeof(char*));
    *double_pointer = malloc(sizeof(char));
    /*
    This will cause a definitely lost leak because double_pointer is
    lost. It will also cause an indirectly lost leak because
    double_pointer contined a pointer to another memory block.

    Indirectly lost leaks are definitely lost leaks indirectly caused
    by another definitely lost leak.
     */

    /*
    By changing the line bellow to `free(double_pointer)` we would
    create a definitely lost leak on `*double_pointer` instead of a
    indirectly lost.
     */
    // free(double_pointer);
    double_pointer = NULL;
}
void test1()
{
    const int NUM_HEIGHTS = 3;
    int i;
    int *heights = malloc(NUM_HEIGHTS);
    for(i=0;i<NUM_HEIGHTS;i++)
    {
       heights[i]=i*i;
       printf("%d %d\n",i, heights[i]);
    }
}

int main(void)
{
    leaky_definitely();
    leaky_still_reachable();
    leaky_possibly();
    leaky_indirectly();
    test1();

    return 0;
}
