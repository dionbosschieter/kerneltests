# kernel tests

```bash
$ gcc -Wall watermarkcalculation.c -o watermarkcalculation && ./watermarkcalculation
pages_min: 22528
lowmem_pages: 164942104
wmark_low: 93852
wmark_high: 176426
$ gcc -Wall oldkernelwmarkcalc.c -o oldkernelwmarkcalc && ./oldkernelwmarkcalc
pages_min: 22528
lowmem_pages: 164942104
wmark_low: 14097
wmark_high: 16917
```
