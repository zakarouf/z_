#ifndef ZAKAROUF__Z__PROC_OMP_BASE_H
#define ZAKAROUF__Z__PROC_OMP_BASE_H

#include "../../prep/prep/nm/pragma.h"


#define z__omp(...) zpp__pragma(omp __VA_ARGS__)

#define z__omp_parallel(...) z__omp(parallel __VA_ARGS__)
#define z__omp_for(...) z__omp(for __VA_ARGS__)


#endif
