//----------------------------------------------------------------------------//
//                                                                            //
// ozz-animation is hosted at http://github.com/guillaumeblanc/ozz-animation  //
// and distributed under the MIT License (MIT).                               //
//                                                                            //
// Copyright (c) 2017 Guillaume Blanc                                         //
//                                                                            //
// Permission is hereby granted, free of charge, to any person obtaining a    //
// copy of this software and associated documentation files (the "Software"), //
// to deal in the Software without restriction, including without limitation  //
// the rights to use, copy, modify, merge, publish, distribute, sublicense,   //
// and/or sell copies of the Software, and to permit persons to whom the      //
// Software is furnished to do so, subject to the following conditions:       //
//                                                                            //
// The above copyright notice and this permission notice shall be included in //
// all copies or substantial portions of the Software.                        //
//                                                                            //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    //
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    //
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        //
// DEALINGS IN THE SOFTWARE.                                                  //
//                                                                            //
//----------------------------------------------------------------------------//

#include "ozz/base/maths/simd_math.h"
#include "ozz/base/maths/vec_float.h"

// Code for ozz-animation HowTo: "How to convert between maths types?"

int main(int argc, char const* argv[]) {
  (void)argc;
  (void)argv;

  //////////////////////////////////////////////////////////////////////////////
  // Loading simd types from scalar float values.
  //////////////////////////////////////////////////////////////////////////////
  {
    // Loads an immediate float value to every component of the simd float.
    const ozz::math::SimdFloat4 f4_1i = ozz::math::simd_float4::Load1(46.f);
    (void)f4_1i;

    // Loads 4 immediate float values to each component of the simd float.
    const ozz::math::SimdFloat4 f4_4i =
        ozz::math::simd_float4::Load(0.f, 1.f, 2.f, 3.f);
    (void)f4_4i;

    // There are other variants available to load immediate values. See
    // include/ozz/base/maths/simd_math.h from line 63.

    // Loads a float value from memory to every component of the simd float.
    // Uses Load*PtrU variant as f1 is not aligned (aka Unaligned) to the 16
    // bytes required for simd types.
    const float f1 = 46;
    const ozz::math::SimdFloat4 f4_1pu = ozz::math::simd_float4::Load1PtrU(&f1);
    (void)f4_1pu;

    // Loads 4 float values from memory to each component of the simd float.
    const float af[4] = {0.f, 1.f, 2.f, 3.f};
    const ozz::math::SimdFloat4 f4_afpu = ozz::math::simd_float4::LoadPtrU(af);
    (void)f4_afpu;

    // Loading from a Float4 would be very similar.
    const ozz::math::Float4 f4(0.f, 1.f, 2.f, 3.f);
    const ozz::math::SimdFloat4 f4_4pu =
        ozz::math::simd_float4::LoadPtrU(&f4.x);
    (void)f4_4pu;

    // Smaller types like Float2 and Float3 can also be loaded, setting simd
    // remaining components (z and w) to 0.
    const ozz::math::Float2 f2(0.f, 1.f);
    const ozz::math::SimdFloat4 f4_2pu =
        ozz::math::simd_float4::Load2PtrU(&f2.x);
    (void)f4_2pu;
  }

  //////////////////////////////////////////////////////////////////////////////
  // Storing simd types to scalar float values.
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Loads a 4x4 simd matrix from 16 floats stored as column major.
  //////////////////////////////////////////////////////////////////////////////
  {
    // Column major floats
    const float af[16] = {0.f, 1.f, 2.f,  3.f,  4.f,  5.f,  6.f,  7.f,
                          8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f};

    ozz::math::Float4x4 matrix;
    // Each column must be loaded into matrix simd vectors.
    // Starts loading the first 4 floats of array af, from 0 to 3.
    matrix.cols[0] = ozz::math::simd_float4::LoadPtrU(af + 0);
    // Loads the next 4, float 4 to 7.
    matrix.cols[1] = ozz::math::simd_float4::LoadPtrU(af + 4);
    // Loads the next 4, float 8 to 11.
    matrix.cols[2] = ozz::math::simd_float4::LoadPtrU(af + 8);
    // Loads the next 4, float 12 to 15.
    matrix.cols[3] = ozz::math::simd_float4::LoadPtrU(af + 12);

    // Suppose floats array was in row major format, it matrix needs to be
    // transposed.
    const ozz::math::Float4x4 transposed = Transpose(matrix);
    (void)transposed;
  }

  return EXIT_SUCCESS;
}
