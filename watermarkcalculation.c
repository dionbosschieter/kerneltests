#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct node {
    unsigned long managed_pages;
} typedef node;

#define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)
#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)
#define __UNIQ(a) __UNIQUE_ID_##__COUNTER__

/*
  * Multiplies an integer by a fraction, while avoiding unnecessary
  * overflow or loss of precision.
  */
#define mult_frac(x, numer, denom)(                     \
{                                                       \
     typeof(x) quot = (x) / (denom);                 \
     typeof(x) rem  = (x) % (denom);                 \
     (quot * (numer)) + ((rem * (numer)) / (denom)); \
}                                                       \
)

#define do_div(n,base) ({                                      \
      uint32_t __base = (base);                               \
      uint32_t __rem;                                         \
      __rem = ((uint64_t)(n)) % __base;                       \
      (n) = ((uint64_t)(n)) / __base;                         \
      __rem;                                                  \
})

#define __max(t1, t2, max1, max2, x, y) ({              \
        t1 max1 = (x);                                  \
        t2 max2 = (y);                                  \
        (void) (&max1 == &max2);                        \
        max1 > max2 ? max1 : max2; })

#define max_t(type, x, y)                               \
        __max(type, type,                               \
              __UNIQUE_ID(min1_), __UNIQUE_ID(min2_),   \
               x, y)


typedef uint64_t u64;
#define SWAP_CLUSTER_MAX 32UL
#define PAGE_SHIFT 12

int main() 
{
    node *zone = malloc(sizeof(node));
    int min_free_kbytes = 90112;
    int watermark_scale_factor = 10;

    u64 tmp;
    u64 wmark_min;
    u64 wmark_low;
    u64 wmark_high;
    zone->managed_pages = 82574130;
    unsigned long lowmem_pages = 164942104; // all managed pages because #CONFIG_HIGHMEM is not
    unsigned long pages_min = min_free_kbytes >> (PAGE_SHIFT - 10);
    
    printf("pages_min: %lu\n", pages_min);
    printf("lowmem_pages: %lu\n", lowmem_pages);

    tmp = (u64)pages_min * zone->managed_pages;
    do_div(tmp, lowmem_pages);
    /*
     * If it's a lowmem zone, reserve a number of pages
     * proportionate to the zone's size.
     */
    wmark_min = tmp;

    tmp = max_t(u64, tmp >> 2,
            mult_frac(zone->managed_pages,
                  watermark_scale_factor, 10000));

    wmark_low = wmark_min + tmp;
    wmark_high = wmark_min + tmp * 2;

    printf("wmark_low: %lu\nwmark_high: %lu\n", wmark_low, wmark_high);
}