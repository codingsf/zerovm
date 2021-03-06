/*
 * Copyright 2011 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */
#include "include/zvmlib.h"
#include <stdio.h>

#define assert(cond) \
  if(!(cond)) \
  { \
    fprintf(STDERR, "assert failed at %d\n", __LINE__); \
    zvm_exit(-1); \
  }

/* This tests for two former nacl-gcc bugs:
   Bug 1:  gcc outputs "jmp *%eax", which fails to validate.
   Bug 2:  gcc outputs "nacljmp *%eax", which fails to assemble.
   This correct assembly output is "nacljmp %eax". */

int test_computed_goto(int index) {
  void *addr[] = { &&label1, &&label2 };
  printf("Jumping to address %p\n", addr[index]);
  goto *addr[index];
 label1:
  return 1234;
 label2:
  return 4567;
}

int main() {
  assert(test_computed_goto(0) == 1234);
  assert(test_computed_goto(1) == 4567);
  return 0;
}
