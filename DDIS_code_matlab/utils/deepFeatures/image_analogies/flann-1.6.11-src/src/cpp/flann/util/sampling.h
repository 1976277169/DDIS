/***********************************************************************
 * Software License Agreement (BSD License)
 *
 * Copyright 2008-2009  Marius Muja (mariusm@cs.ubc.ca). All rights reserved.
 * Copyright 2008-2009  David G. Lowe (lowe@cs.ubc.ca). All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *************************************************************************/


#ifndef SAMPLING_H_
#define SAMPLING_H_


#include "flann/util/matrix.h"
#include "flann/util/random.h"

namespace flann
{

template<typename T>
Matrix<T> random_sample(Matrix<T>& srcMatrix, long size, bool remove = false)
{
    UniqueRandom rand(srcMatrix.rows);
    Matrix<T> newSet(new T[size * srcMatrix.cols], size,srcMatrix.cols);

    T* src,* dest;
    for (long i=0; i<size; ++i) {
        long r = rand.next();
        dest = newSet[i];
        src = srcMatrix[r];
        for (size_t j=0; j<srcMatrix.cols; ++j) {
            dest[j] = src[j];
        }
        if (remove) {
            dest = srcMatrix[srcMatrix.rows-i-1];
            src = srcMatrix[r];
            for (size_t j=0; j<srcMatrix.cols; ++j) {
                std::swap(*src,*dest);
                src++;
                dest++;
            }
        }
    }

    if (remove) {
        srcMatrix.rows -= size;
    }

    return newSet;
}

template<typename T>
Matrix<T> random_sample(const Matrix<T>& srcMatrix, size_t size)
{
    UniqueRandom rand(srcMatrix.rows);
    Matrix<T> newSet(new T[size * srcMatrix.cols], size,srcMatrix.cols);

    T* src,* dest;
    for (size_t i=0; i<size; ++i) {
        long r = rand.next();
        dest = newSet[i];
        src = srcMatrix[r];
        for (size_t j=0; j<srcMatrix.cols; ++j) {
            dest[j] = src[j];
        }
    }

    return newSet;
}

} // namespace

#endif /* SAMPLING_H_ */
