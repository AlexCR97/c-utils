#ifndef CNS_H
#define CNS_H

#include <stdio.h>
#include <stdlib.h>
#include "maybe.h"

PmMaybe cns_prompt(const char* message, size_t capacity);

#endif // CNS_H
