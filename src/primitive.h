/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_SRC_PRIMITIVE_H_
#define ART_SRC_PRIMITIVE_H_

#include <sys/types.h>

#include "logging.h"
#include "macros.h"

namespace art {

class Object;

class Primitive {
 public:
  enum Type {
    kPrimNot = 0,
    kPrimBoolean,
    kPrimByte,
    kPrimChar,
    kPrimShort,
    kPrimInt,
    kPrimLong,
    kPrimFloat,
    kPrimDouble,
    kPrimVoid,
  };

  static Type GetType(char type) {
    switch (type) {
      case 'B':
        return kPrimByte;
      case 'C':
        return kPrimChar;
      case 'D':
        return kPrimDouble;
      case 'F':
        return kPrimFloat;
      case 'I':
        return kPrimInt;
      case 'J':
        return kPrimLong;
      case 'S':
        return kPrimShort;
      case 'Z':
        return kPrimBoolean;
      case 'V':
        return kPrimVoid;
      default:
        return kPrimNot;
    }
  }

  static size_t ComponentSize(Type type) {
    switch (type) {
      case kPrimVoid:    return 0;
      case kPrimBoolean:
      case kPrimByte:    return 1;
      case kPrimChar:
      case kPrimShort:   return 2;
      case kPrimInt:
      case kPrimFloat:   return 4;
      case kPrimLong:
      case kPrimDouble:  return 8;
      case kPrimNot:     return sizeof(Object*);
      default:
        LOG(FATAL) << "Invalid type " << static_cast<int>(type);
        return 0;
    }
  }

  static size_t FieldSize(Type type) {
    return ComponentSize(type) <= 4 ? 4 : 8;
  }

  static char DescriptorChar(Type type) {
    switch (type) {
      case kPrimBoolean:
        return 'Z';
      case kPrimByte:
        return 'B';
      case kPrimChar:
        return 'C';
      case kPrimShort:
        return 'S';
      case kPrimInt:
        return 'I';
      case kPrimFloat:
        return 'J';
      case kPrimLong:
        return 'J';
      case kPrimDouble:
        return 'D';
      default:
        LOG(FATAL) << "Primitive char conversion on invalid type " << static_cast<int>(type);
        return 0;
    }
  }

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(Primitive);
};

}  // namespace art

#endif  // ART_SRC_PRIMITIVE_H_
