#include "slist.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _SLIST_UTIL
#define _SLIST_UTIL

typedef struct SListUtil {
  unsigned int (*lg)(unsigned int);
} SListUtil;

unsigned int lg(unsigned int length) {
  return (unsigned int)log(length) / log(2);
}

SListUtil *new_slist_util() {
  SListUtil *new_util = malloc(sizeof(SListUtil));
  new_util->lg = lg;
  return new_util;
}

#endif