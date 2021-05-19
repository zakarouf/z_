# OpenMP vs. Pthread vs. Single Thread

This file documents the Comparism between the different Multi-thread library in The C Programing Language.

## Introduction


### We will go through

* Performance
* Ease of Use
* Safety


## Benchmark

### Tools & Process

We will be creating a 10000x10000 array and filling them with 2D perlin noise geration.
<br>
<br>

There will will be 3 Benchmarks for 3 ways to create

#### Single-Thread

#### Pthread

#### OpenMP

### Result

Average Time. <br>

|          |   Single Thread|        OpenMP|        Pthread|
|:---------|---------------:|-------------:|--------------:|
|Time (Avg)|11.47120 seconds|4.1330 seconds|4.08920 seconds|
|Increase  |             NIL|     64.35290%|      63.97065%|

## Evaluation

## Conclution

## Appendix

The source code can be found on [examples/gen_perlin2D](../../examples/gen_perlin2D) in the parent directory.


