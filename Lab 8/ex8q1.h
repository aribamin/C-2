#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// This function parses the dreamberg input for you
//
// Returns:
//   is_print:
//      1 if this is a print line 0, if this is an assign line. When is_print
//      is 1, the values returned in index and value must be ignored.
//  index:
//      A floating point index for the dreamberg array
//  value:
//      The integer value being assigned to the dreamberg array at the index
void read_line(int* is_print, float* index, int* value);
