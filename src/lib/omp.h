#ifndef ZAKAROUF__Z__PROC_OMP_H
#define ZAKAROUF__Z__PROC_OMP_H

#include "prep/nm/pragma.h"
#include <omp.h>

#define z__omp(...) zpp__pragma(omp __VA_ARGS__)

#define z__omp_parallel(...) z__omp(parallel __VA_ARGS__)
#define z__omp_for(...) z__omp(for __VA_ARGS__)



#endif
