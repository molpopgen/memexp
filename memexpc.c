#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

typedef struct
{
    double x, y, z;
} Data;

void
vanilla(const gsl_rng *r, size_t nsamples, size_t capacity, Data **data)
{
    size_t current_capacity = capacity;
    size_t i = 0;
    if (*data == NULL)
        {
            current_capacity = 1;
            *data = (Data *)malloc(current_capacity * sizeof(Data));
        }

    for (i = 0; i < nsamples; ++i)
        {
            if (i >= current_capacity)
                {
                    current_capacity *= 2;
                    *data = (Data *)realloc(*data, current_capacity * sizeof(Data));
                }
            (*data)[i].x = gsl_rng_uniform(r);
            (*data)[i].y = gsl_rng_uniform(r);
            (*data)[i].z = gsl_rng_uniform(r);
        }
    fprintf(stdout, "vanilla %ld %ld\n", i, current_capacity);
}

void
set_maxinc_after_maxcap(const gsl_rng *r, size_t nsamples, size_t maxcap,
                        size_t capacity, size_t maxinc, Data **data)
{
    size_t current_capacity = capacity;
    if (*data == NULL)
        {
            current_capacity = 1;
            *data = (Data *)malloc(current_capacity * sizeof(Data));
        }
    size_t i, threshold = maxcap;
    for (i = 0; i < nsamples; ++i)
        {
            if (i >= current_capacity)
                {
                    if (i >= threshold)
                        {
                            current_capacity += maxinc;
                            threshold += maxinc;
                        }
                    else
                        {
                            current_capacity *= 2;
                        }
                    *data = (Data *)realloc(*data, current_capacity * sizeof(Data));
                }
            (*data)[i].x = gsl_rng_uniform(r);
            (*data)[i].y = gsl_rng_uniform(r);
            (*data)[i].z = gsl_rng_uniform(r);
        }
    fprintf(stdout, "vanilla until %ld, then linear by %ld = %ld %ld\n", maxcap, maxinc,
            i, current_capacity);
}

int
main(int argc, char **argv)
{
    size_t arg = 1;
    int seed = atoi(argv[arg++]);
    size_t nsamples = (size_t)atoi(argv[arg++]);
    size_t maxcap = (size_t)atoi(argv[arg++]);
    size_t maxinc = (size_t)atoi(argv[arg++]);
    size_t rv, i;

    Data *data = NULL;
    gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(r, seed);

    if (maxcap == 0)
        {
            vanilla(r, nsamples, 0, &data);
        }
    else
        {
            set_maxinc_after_maxcap(r, nsamples, maxcap, 0, maxinc, &data);
        }

    free(data);
}
