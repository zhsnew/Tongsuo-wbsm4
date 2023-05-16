/*
 * Copyright 2023 The Tongsuo Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/Tongsuo-Project/Tongsuo/blob/master/LICENSE.txt
 */

#include "internal/deprecated.h"
#include <stdio.h>
#include <openssl/asn1t.h>
#include <openssl/bulletproofs.h>
#include "range_proof.h"


BP_PUB_PARAM *d2i_BP_PUB_PARAM(BP_PUB_PARAM **pp, const unsigned char **in, long len)
{
    BP_PUB_PARAM *param = NULL;
    const unsigned char *p = *in;

    if (p == NULL)
        return NULL;

    if ((param = BP_PUB_PARAM_decode(p, len)) == NULL)
        return NULL;

    if (pp) {
        BP_PUB_PARAM_free(*pp);
        *pp = param;
    }

    *in = p;
    return param;
}

int i2d_BP_PUB_PARAM(const BP_PUB_PARAM *pp, unsigned char **out)
{
    size_t size;

    if ((size = BP_PUB_PARAM_encode(pp, NULL, 0)) <= 0)
        return 0;

    if (out == NULL)
        return (int)size;

    if (BP_PUB_PARAM_encode(pp, *out, size) <= 0)
        return 0;

    return (int)size;
}

static BP_WITNESS *d2i_BP_WITNESS(BP_WITNESS **witness, const unsigned char **in,
                                  long len, int flag)
{
    BP_WITNESS *ret = NULL;
    const unsigned char *p = *in;

    if (p == NULL)
        return NULL;

    if ((ret = BP_WITNESS_decode(p, len, flag)) == NULL)
        return NULL;

    if (witness) {
        BP_WITNESS_free(*witness);
        *witness = ret;
    }

    *in = p;
    return ret;
}

static int i2d_BP_WITNESS(const BP_WITNESS *witness, unsigned char **out, int flag)
{
    size_t size;

    if ((size = BP_WITNESS_encode(witness, NULL, 0, flag)) <= 0)
        return 0;

    if (out == NULL)
        return (int)size;

    if (BP_WITNESS_encode(witness, *out, size, flag) <= 0)
        return 0;

    return (int)size;
}

BP_WITNESS *d2i_long_BP_WITNESS(BP_WITNESS **witness, const unsigned char **in,
                                long len)
{
    return d2i_BP_WITNESS(witness, in, len, 1);
}

int i2d_long_BP_WITNESS(const BP_WITNESS *witness, unsigned char **out)
{
    return i2d_BP_WITNESS(witness, out, 1);
}

BP_WITNESS *d2i_short_BP_WITNESS(BP_WITNESS **witness, const unsigned char **in,
                                 long len)
{
    return d2i_BP_WITNESS(witness, in, len, 0);
}

int i2d_short_BP_WITNESS(const BP_WITNESS *witness, unsigned char **out)
{
    return i2d_BP_WITNESS(witness, out, 0);
}

BP_RANGE_PROOF *d2i_BP_RANGE_PROOF(BP_RANGE_PROOF **proof, const unsigned char **in,
                                   long len)
{
    BP_RANGE_PROOF *ret = NULL;
    const unsigned char *p = *in;

    if (p == NULL)
        return NULL;

    if ((ret = BP_RANGE_PROOF_decode(p, len)) == NULL)
        return NULL;

    if (proof) {
        BP_RANGE_PROOF_free(*proof);
        *proof = ret;
    }

    *in = p;
    return ret;
}

int i2d_BP_RANGE_PROOF(const BP_RANGE_PROOF *proof, unsigned char **out)
{
    size_t size;

    if ((size = BP_RANGE_PROOF_encode(proof, NULL, 0)) <= 0)
        return 0;

    if (out == NULL)
        return (int)size;

    if (BP_RANGE_PROOF_encode(proof, *out, size) <= 0)
        return 0;

    return (int)size;
}

IMPLEMENT_PEM_rw(BULLETPROOFS_PublicParam, BP_PUB_PARAM, PEM_STRING_BULLETPROOFS_PUB_PARAM, BP_PUB_PARAM)
IMPLEMENT_PEM_rw(BULLETPROOFS_LongWitness, BP_WITNESS, PEM_STRING_BULLETPROOFS_WITNESS, long_BP_WITNESS)
IMPLEMENT_PEM_rw(BULLETPROOFS_ShortWitness, BP_WITNESS, PEM_STRING_BULLETPROOFS_WITNESS, short_BP_WITNESS)
IMPLEMENT_PEM_rw(BULLETPROOFS_RangeProof, BP_RANGE_PROOF, PEM_STRING_BULLETPROOFS_RANGE_PROOF, BP_RANGE_PROOF)
