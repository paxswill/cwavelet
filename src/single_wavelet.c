/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	pthreads_single.c
 *
 */


void liftSplit_single(double *vals, int length){
	int half = length / 2;
	// shuffle
	liftShuffle(vals, length);
	// Now recurse on each half
	if(half >= 4){
		liftSplit(vals, half);
		liftSplit(vals + half, half);
	}
}

void liftMerge_single(double *vals, int length){
	int half = length / 2;
	// Fix the sub-halves first
	if(half >= 4){
		liftMerge(vals, half);
		liftMerge(vals + half, half);
	}
	// shuffle
	liftShuffle(vals, length);
}