/*
 * Copyright 2023 Max Planck Institute for Software Systems, and
 * National University of Singapore
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <vfio-pci.h>
#include <dma-alloc.h>

#include "../common/reg_defs.h"
#include "driver.h"

/** Use this macro to safely access a register at a specific offset */
#define ACCESS_REG(r) (*(volatile uint64_t *) ((uintptr_t) regs + r))

static void *regs;

/* DMA memory for matrices */
static size_t dma_mem_size = 16 * 1024 * 1024;
static uint8_t *dma_mem;
static uintptr_t dma_mem_phys;

int accelerator_init(bool dma) {
  struct vfio_dev dev;
  size_t reg_len;

  if (vfio_dev_open(&dev, "/dev/vfio/noiommu-0", "0000:00:00.0") != 0) {
    fprintf(stderr, "open device failed\n");
    return -1;
  }

  if(vfio_region_map(&dev, 0, &regs, &reg_len)) {
    fprintf(stderr, "mapping registers failed\n");
    return -1;
  }

  if (dma_alloc_init()) {
    fprintf(stderr, "DMA INIT failed\n");
    return -1;
  }

  if (!(dma_mem = dma_alloc_alloc(dma_mem_size, &dma_mem_phys))) {
    fprintf(stderr, "Allocating DMA memory failed\n");
    return -1;
  }

  // TODO: Probably want to allocate memory for the queues here too

  if (vfio_busmaster_enable(&dev)) {
    fprintf(stderr, "Enabling busmastering failed\n");
    return -1;
  }

  // FILL ME IN

  return 0;
}

int accelerator_matrix_size(void) {
  // FILL ME IN
  return 42;
}

void matmult_accel(const uint8_t * restrict A, const uint8_t * restrict B,
                   uint8_t * restrict out, size_t n) {
  // FILL ME IN
}
