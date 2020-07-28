#include "random.h"
#include "emmintrin.h"
#include <random>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>

//std::default_random_engine randEngine(time(0)); //Intended narrowing conversion

void srand_sse(unsigned int seed);
void rand_sse(unsigned int*);

uint8_t current{ 0 };
unsigned int randarray[4];
inline unsigned int next();

int random::next_int(int low, int high)
{
    //return std::uniform_int_distribution<>{low, high}(randEngine);
    return low + next() % (high + 1 - low);
}

int random::next_int(int high)
{
    //return std::uniform_int_distribution<>{0, high}(randEngine);
    return next() % (high + 1);
}

int random::next_int23()
{
    return next() % 24;
}

inline unsigned int next()
{
    if (current == 4)
    {
        current = 0;
        rand_sse(randarray);
    }
    return randarray[current++];
}

__declspec(align(16)) static __m128i cur_seed;

void srand_sse(unsigned int seed)

{

    cur_seed = _mm_set_epi32(seed, seed + 1, seed, seed + 1);

}


//I have no idea how this works.
inline void rand_sse(unsigned int* result)

{

    __declspec(align(16)) __m128i cur_seed_split;

    __declspec(align(16)) __m128i multiplier;

    __declspec(align(16)) __m128i adder;

    __declspec(align(16)) __m128i mod_mask;

    __declspec(align(16)) __m128i sra_mask;

    __declspec(align(16)) __m128i sseresult;

    __declspec(align(16)) static const unsigned int mult[4] =

    { 214013, 17405, 214013, 69069 };

    __declspec(align(16)) static const unsigned int gadd[4] =

    { 2531011, 10395331, 13737667, 1 };

    __declspec(align(16)) static const unsigned int mask[4] =

    { 0xFFFFFFFF, 0, 0xFFFFFFFF, 0 };

    __declspec(align(16)) static const unsigned int masklo[4] =

    { 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF };



    adder = _mm_load_si128((__m128i*) gadd);

    multiplier = _mm_load_si128((__m128i*) mult);

    mod_mask = _mm_load_si128((__m128i*) mask);

    sra_mask = _mm_load_si128((__m128i*) masklo);

    cur_seed_split = _mm_shuffle_epi32(cur_seed, _MM_SHUFFLE(2, 3, 0, 1));



    cur_seed = _mm_mul_epu32(cur_seed, multiplier);

    multiplier = _mm_shuffle_epi32(multiplier, _MM_SHUFFLE(2, 3, 0, 1));

    cur_seed_split = _mm_mul_epu32(cur_seed_split, multiplier);


    cur_seed = _mm_and_si128(cur_seed, mod_mask);

    cur_seed_split = _mm_and_si128(cur_seed_split, mod_mask);

    cur_seed_split = _mm_shuffle_epi32(cur_seed_split, _MM_SHUFFLE(2, 3, 0, 1));

    cur_seed = _mm_or_si128(cur_seed, cur_seed_split);

    cur_seed = _mm_add_epi32(cur_seed, adder);


    _mm_storeu_si128((__m128i*) result, cur_seed);

    return;

}

//run on file load
const int load = []() -> int
{
    srand_sse(time(0));
    rand_sse(randarray);
    return 0;
}();