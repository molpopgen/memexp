#include <vector>
#include <cstdio>
#include <cstdint>
#include <iostream>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

struct Data
{
    double x, y, z;
    Data(double x, double y, double z) : x{x}, y{y}, z{z}
    {
    }
};

void
vanilla(const gsl_rng* r, std::size_t nsamples, std::vector<Data>& data)
{
    for (std::size_t i = 0; i < nsamples; ++i)
        {
            data.emplace_back(gsl_rng_uniform(r), gsl_rng_uniform(r),
                              gsl_rng_uniform(r));
        }
    std::cout << "default behavior: " << data.size() << ' ' << data.capacity() << '\n';
}

void
set_maxinc_after_maxcap(const gsl_rng* r, std::size_t nsamples, std::size_t maxcap,
                        std::size_t maxinc, std::vector<Data>& data)
{
    auto threshold = maxcap;
    for (std::size_t i = 0; i < nsamples; ++i)
        {
            if (data.size() >= threshold)
                {
                    threshold += maxinc;
                    data.reserve(threshold);
                }
            data.emplace_back(gsl_rng_uniform(r), gsl_rng_uniform(r),
                              gsl_rng_uniform(r));
        }
    std::cout << "default behavior until " << maxcap << ' '
              << " then increase capacity by " << maxinc << " : " << data.size() << ' '
              << data.capacity() << '\n';
}

int
main(int argc, char** argv)
{
    std::size_t arg = 1;
    auto seed = std::atoi(argv[arg++]);
    auto nsamples = static_cast<std::size_t>(std::atoi(argv[arg++]));
    auto maxcap = static_cast<std::size_t>(std::atoi(argv[arg++]));
    auto maxinc = static_cast<std::size_t>(std::atoi(argv[arg++]));

    gsl_rng* r = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(r, seed);

    std::vector<Data> data;

    if (maxcap == 0)
        {
            vanilla(r, nsamples, data);
        }
    else
        {
            set_maxinc_after_maxcap(r, nsamples, maxcap, maxinc, data);
        }

    gsl_rng_free(r);
}
