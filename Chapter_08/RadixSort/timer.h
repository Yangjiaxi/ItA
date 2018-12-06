
/*
    USEFUL TOOLS FOR CLASS
*/
// initialize clock
#define _TIME_INIT clock_t tic = 0;
// time record start
#define _TIME_START tic = clock();
// time record finish and output
#define _TIME_END printf("%lu\n", (clock() - tic));