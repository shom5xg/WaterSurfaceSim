/**
 * Copyright (c) 2014 The Motel On Jupiter
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

#include "generator/RainGenerator.h"

#include <cstdlib>

RainGenerator::RainGenerator(
    const OriginOption &option, int ongeneration(int, int, float))
    : Generator(ongeneration),
      option_(option) {
}

RainGenerator::~RainGenerator() {
}

int RainGenerator::Execute() {
  // TODO: improve to get the random value
  float frequency = option_.frequency;
  while (frequency > 0.0f) {
    if (option_.frequency < 1.0f) {
      if (rand() % 100 >= static_cast<int>(frequency * 100)) {
        break;
      }
    }
    // TODO: do not stimulate the same point
    int x = option_.areawidth * rand() / RAND_MAX;
    int y = option_.areaheight * rand() / RAND_MAX;
    float force = option_.minforce
        + (option_.maxforce - option_.minforce) * rand() / RAND_MAX;
    if (0 > Generate(x, y, force)) {
      // TODO: it is OK that to return as soon as onstimulate_() failed
      return -1;
    }
    frequency -= 1.0f;
  }

  return 0;
}
