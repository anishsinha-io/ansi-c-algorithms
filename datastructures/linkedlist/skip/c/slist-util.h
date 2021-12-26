#include "models.h"
#include <math.h>
#include <stdio.h>

#ifndef _SLIST_UTIL
#define _SLIST_UTIL

unsigned int lg(unsigned int length) {
  return (unsigned int)(log(length) / log(2));
}

SListUtil *new_slist_util() {
  SListUtil *new_util = malloc(sizeof(SListUtil));
  new_util->lg = lg;
  return new_util;
}

#endif