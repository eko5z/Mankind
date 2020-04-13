#pragma once

#include <stdio.h>

#define LOG(fmt, args...) (fprintf (stderr, "\x1B[34m%s:%d:%s(): " fmt "\x1B[0m\n", __FILE__, __LINE__, __func__, ##args))
