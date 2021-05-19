/*
    Genrating 2D perlin Noise with, OpenMP, Pthread, Nothing
*/

#include <z_/types.h>
#include <z_/proc/pt.h>
#include <z_/proc/omp.h>

#include <math.h>
#include <stdio.h>


/* Enable One 'use' at a time for Bench mark, and uncomment `#define print_map` to print the map */
#define use_pt
//#define use_nothing
//#define use_omp
#define print_map

#define X 10000
#define Y 10000

z__u32 gen(z__u32 x, z__u32 y);



#if defined (print_map)

static void printmap(z__u32Arr *map, z__Vint2 dimen)
{
    for (int i = 0; i < dimen.y; ++i) {
        for (int j = 0; j < dimen.x; ++j) {
            fprintf(stdout , "%d",map->data[j + (i*dimen.x)]);
        }
        putc('\n', stdout);
    }
}

#endif


/* Using Pthread */
#if defined (use_pt)

#define THREAD_MAX 4

#define array_slice_pt(len, t, i) (len/t *i)
#define array_divide_each_on_thread_equal_len(len, t) (len/t)

z__pt_ArgContext_Tag(
    maparg__tag,
        z__u32 *map;
        z__Vint2 dimen;
    );

static void pt_gen_2D_array(z__pt_ArgContext(maparg__tag) *arg)
{
    z__u32 start_index =  array_slice_pt( arg->dimen.y, THREAD_MAX ,arg->_id);

    z__u32 div = array_divide_each_on_thread_equal_len(arg->dimen.y, THREAD_MAX) + start_index;

    // If The Total len is not multiple of Total Threads in Use
    // Then the remainder is mapped out, so we are just extending the div to also include it
    // Only if the we are at the last thread call.
    if(arg->_id == THREAD_MAX-1){
        div += arg->dimen.y % THREAD_MAX;
    }
    z__u32 *map  = arg->map;
    z__u32 x = arg->dimen.x;

    for (int i = start_index; i < div; ++i){
        for (int j = 0; j < x; ++j)
        {
             map[(i * x) + j] = gen(j, i);
        }
       
    }
}

static void gen_2D_array_pt(void)
{
    z__u32Arr map;

    const z__Vint2 dimen = {{X, Y}};
    const int sz = dimen.x * dimen.y;

    z__Arr_new(&map, sz);
    
    /*Pthread*/

    z__pt_ArgContext(maparg__tag) Map_Arg = {.map = map.data, .dimen = dimen};
    z__pt_Job(maparg__tag) mapJob;

    z__pt_Job_new(&mapJob, THREAD_MAX);

    for (int i = 0; i < THREAD_MAX; ++i) {
        z__pt_Job_bind_Arg(&mapJob, Map_Arg, i);
        z__pt_Job_bind_fn(&mapJob, pt_gen_2D_array, i);
    }

    z__pt_Job_run(&mapJob);
    z__pt_Job_end(&mapJob);

    #if defined (print_map)
        printmap(&map, dimen);
    #endif

    z__Arr_delete(&map);
}

#endif


/* Using OpenMP */
#if defined (use_omp)

static void gen_2D_array_omp(void)
{
    const z__Vint2 dimen = {{X, Y}};
    z__size y = 0, x = 0;

    z__u32Arr map;
    z__Arr_new(&map, dimen.x * dimen.y);

    z__omp(parallel for private(x,y))
        for (y = 0; y < dimen.y; ++y) {
            for (x = 0; x < dimen.x; ++x) {
                // Generate 2D map on 1D array.
                map.data[x + (y*dimen.x)] = gen(x, y);
            }
        }

    map.lenUsed = dimen.x * dimen.y;

    #if defined (print_map)
        printmap(&map, dimen);
    #endif

    z__Arr_delete(&map);
}

#endif


/* Traditional Way to Generate 2D map, Single threaded */
#if defined (use_nothing)

static void gen_2D_array_sin(void)
{
    const z__Vint2 dimen = {{X, Y}};
    z__size y = 0, x = 0;

    z__u32Arr map;
    z__u32 s = dimen.x * dimen.y;
    z__Arr_new(&map, (s));

    for (y = 0; y < dimen.y; ++y) {
        for (x = 0; x < dimen.x; ++x) {
            // Generate 2D map on 1D array.
            map.data[x + (y*dimen.x)] = gen(x, y);
        }
    }

    map.lenUsed = dimen.x * dimen.y;
    printf("%d\n", map.data[0]);

    #if defined (print_map)
        printmap(&map, dimen);
    #endif

    z__Arr_delete(&map);
}

#endif


int main(int argc, char const *argv[])
{
    #if defined (use_nothing)
        gen_2D_array_sin();
    #endif

    #if defined (use_pt)
        gen_2D_array_pt();
    #endif

    #if defined (use_omp)
        gen_2D_array_omp();
    #endif

    return 0;
}


// Perlin Noise
/*-----------------------------------------------
    Generate Perlin Noise.
/-----------------------------------------------/
    - Courtesy of nowl (https://gist.github.com/nowl/828013)

    - Code updated by deeemmell
        (https://gist.github.com/deeemmell)
        to support negetive x,y coordinate

-----------------------------------------------*/
//---------------------------------------------//



static int SEED = 1;

static const uint8_t  HASH[] = {
    208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
    185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
    9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
    70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
    203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
    164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
    228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
    232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
    193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
    101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
    135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
    114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219
};

static int noise2(int x, int y)
{
    int  yindex = (y + SEED) & 0xFF;
    if (yindex < 0)
        yindex += 256;
    int  xindex = (HASH[yindex] + x) & 0xFF;
    if (xindex < 0)
        xindex += 256;
    const int  result = HASH[xindex];
    return result;
}

static double lin_inter(double x, double y, double s)
{
    return x + s * (y-x);
}

static double smooth_inter(double x, double y, double s)
{
    return lin_inter( x, y, s * s * (3-2*s) );
}

static double noise2d(double x, double y)
{
    const int  x_int = floor( x );
    const int  y_int = floor( y );
    const double  x_frac = x - x_int;
    const double  y_frac = y - y_int;
    const int  s = noise2( x_int, y_int );
    const int  t = noise2( x_int+1.0f, y_int );
    const int  u = noise2( x_int, y_int+1.0f );
    const int  v = noise2( x_int+1.0f, y_int+1.0f );
    const double  low = smooth_inter( s, t, x_frac );
    const double  high = smooth_inter( u, v, x_frac );
    const double  result = smooth_inter( low, high, y_frac );
    return result;
}



void zse_map_SetNoiseSeed(int seed)
{
    SEED = seed;
}
int zse_map_GetNoiseSeed(void)
{
    return SEED;
}

//----------------------------------------------------------
// Returns single double val according to x,y cord
// Example : foo_array[y][x] = zse_map_gen2d_get_solo(x, y, 0.1, 4)
double zse_map_gen2d_get_solo(double x, double y, double freq, int depth)
{
    double  xa = x*freq;
    double  ya = y*freq;
    double  amp = 1.0f;
    double  fin = 0.0f;
    double  div = 0.0f;
    for (int i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise2d( xa, ya ) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }
    return fin/div;
}

z__u32 gen(z__u32 x, z__u32 y)
{
   return zse_map_gen2d_get_solo(x, y, 0.1, 4) * 10;
}