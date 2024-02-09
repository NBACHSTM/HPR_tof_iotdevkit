/*
 * AWS IoT Over-the-air Update v3.3.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file preprocessBase64Index_harness.c
 * @brief Implements the proof harness for preprocessBase64Index function.
 */
/* Include headers for base64 decoding. */
#include "ota_base64_private.h"

/* Inclusive upper bound for the range of valid Base64 index values. */
#define SYMBOL_TO_INDEX_MAP_VALUE_UPPER_BOUND    67U

/* Declaration of the mangled name function generated by CBMC for static functions. */
Base64Status_t __CPROVER_file_local_ota_base64_c_preprocessBase64Index( uint8_t base64Index,
                                                                        int64_t * pNumPadding,
                                                                        int64_t * pNumWhitespace );

void preprocessBase64Index_harness()
{
    uint8_t base64Index;
    int64_t * pNumPadding;
    int64_t * pNumWhitespace;
    int64_t numPadding;
    int64_t numWhitespace;

    pNumPadding = &numPadding;
    pNumWhitespace = &numWhitespace;

    /* base64Index cannot exceed the SYMBOL_TO_INDEX_MAP_VALUE_UPPER_BOUND which is
     * enforced in ota_base64.c. */
    __CPROVER_assume( base64Index <= SYMBOL_TO_INDEX_MAP_VALUE_UPPER_BOUND );

    /* The numPadding is calculated to be less than max value of int64_t. */
    __CPROVER_assume( numPadding < INT64_MAX );

    /* The numWhitespace is calculated to be less than the max value of int64_t. */
    __CPROVER_assume( numWhitespace < INT64_MAX );

    ( void ) __CPROVER_file_local_ota_base64_c_preprocessBase64Index( base64Index, pNumPadding, pNumWhitespace );
}
