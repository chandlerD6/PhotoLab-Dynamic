#ifndef DIPS_H_INCLUDED_
#define DIPS_H_INCLUDED_

#include "Constants.h"
#include "Image.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

IMAGE *Negative(IMAGE *image);

IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b,
int threshold, int replace_r, int replace_g, int replace_b);

IMAGE *Edge(IMAGE *image);

IMAGE *HFlip(IMAGE *image);

IMAGE *Vmirror(IMAGE *image);

IMAGE *Zoom(IMAGE *image);

#endif /* DIPS_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
