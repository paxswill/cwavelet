/*
 *	Copyright (c) 2011, William Ross
 *	All rights reserved
 *	This software is licensed under a modified BSD license. Please see COPYING for the full text.
 *
 *	pthreads_wavelet.c
 *
 */

#include "pthreads_wavelet.h"
#include <pthread.h>

typedef struct{
	double *vals;
	int length;
} splitArg;

int threadCount = 0;
static pthread_mutex_t countMutex = PTHREAD_MUTEX_INITIALIZER;

void * liftSplit_pthread_Task(void *arg){
	splitArg *realArg = arg;
	int half = realArg->length / 2;
	// shuffle
	liftShuffle(realArg->vals, realArg->length);
	// Now recurse on each half
	if(half >= 4){
		liftSplit_pthread(realArg->vals, half);
		liftSplit_pthread(realArg->vals + half, half);
	}
	return NULL;
}

void * liftMerge_pthread_Task(void *arg){
	splitArg *realArg = arg;
	int half = realArg->length / 2;
	// Fix the sub-halves first
	if(half >= 4){
		liftMerge_pthread(realArg->vals, half);
		liftMerge_pthread((realArg->vals) + half, half);
	}
	// shuffle
	liftShuffle(realArg->vals, 	realArg->length);
	return NULL;
}

void liftSplit_pthread(double *vals, int length){
	//Spawn off a new thread for this task
	pthread_t thread;
	splitArg taskArgument = {vals, length};
	int rc = pthread_create(&thread, NULL, liftSplit_pthread_Task, &taskArgument);
	if(rc){
		printf("Error in creating thread\n");
	}else{
		printf("\t\tLaunching spinning thread #%d", rc);
	}
}

void liftMerge_pthread(double *vals, int length){
	//Spawn off a new thread for this task
	pthread_t thread;
	splitArg taskArgument = {vals, length};
	int rc = pthread_create(&thread, NULL, liftMerge_pthread_Task, &taskArgument);
	if(rc){
		printf("Error in creating thread\n");
	}else{
		pthread_mutex_lock(&countMutex);
		++threadCount;
		pthread_mutex_unlock(&countMutex);
	}
}
