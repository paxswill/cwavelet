# cWavelets

*cWavelets* is a small library to make computing the [discrete wavelet transforms](http://en.wikipedia.org/wiki/Discrete_wavelet_transform)(DWTs) easy.
I apologize for the semi-OO style code written, but I wanted to leave it open 
for some expansions I have in mind for later down the road (OpenCL, MPI).

## Compiling

This is a fairly simple library, and it just makes use of the C Standard Library
at this time. It does make use of C99 extensions, so be sure your compiler supports them.
The included Makefile uses `clang` as it's default compiler, but you can switch it to 
`gcc` if you wish.


## Usage

First include the `wavelet.h` header.

    #include "wavelet.h"

Then create a wavelet object. `inputData` is an array of doubles representing 
your data. `length` is obviously the length of the data, and `WAVELET` is one 
of the wavelet constants.

    waveletContainer *container = createWavelet(inputData, length, WAVELET);

Currently the Haar and Daubechies 2 through 10 wavelets are implemented. The constants for them are

    HAAR_WAVELET
    DAUBECHIES_N_WAVELET

where N is the number for the Daubechies wavelet. See `tests.c` for further examples of instantiation.

To run the wavelet transform, call the `transform()` function on your wavelet container.

    transform(container);

To access the data, access the `bands` array. This is probably going to change in the future when I clean up the data access functions (read: create them).

When you are done with the wavelet container, destroy it with `destroyWavelet()`. 
This frees all memory associated with the container.

## Extending

To add additional wavelets, there are a few steps you should take. First, 
define wavelet and scaling functions for your wavelet. See `haar.c` for a 
simple example of this. At this time, define an integer constant that 
uniquely identifies your wavelet. I used random numbers for this (see `haar.h`), 
but you can choose whatever number you wish, as log as it does not collide 
with a previously defined value.

Once this is done, add an `else if` clause to the `createWavelet()` function in `wavelet.c`.
This defines parameters unique to your wavelet inside the wavelet container.
