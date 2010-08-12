/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
#include <iostream>
#include "qpid/types/Variant.h"

#include "unit_test.h"

using namespace qpid::types;

namespace qpid {
namespace tests {

QPID_AUTO_TEST_SUITE(VariantSuite)

QPID_AUTO_TEST_CASE(testConversions)
{
    Variant value;

    //string to float/double
    value = "1.5";
    BOOST_CHECK_EQUAL((float) 1.5, value.asFloat());
    BOOST_CHECK_EQUAL((double) 1.5, value.asDouble());

    //float to string or double
    value = 1.5f;
    BOOST_CHECK_EQUAL((float) 1.5, value.asFloat());
    BOOST_CHECK_EQUAL((double) 1.5, value.asDouble());
    BOOST_CHECK_EQUAL(std::string("1.5"), value.asString());

    //double to string (conversion to float not valid)
    value = 1.5;
    BOOST_CHECK_THROW(value.asFloat(), InvalidConversion);
    BOOST_CHECK_EQUAL((double) 1.5, value.asDouble());
    BOOST_CHECK_EQUAL(std::string("1.5"), value.asString());

    //uint8 to larger unsigned ints and string
    value = (uint8_t) 7;
    BOOST_CHECK_EQUAL((uint8_t) 7, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 7, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 7, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 7, value.asUint64());
    BOOST_CHECK_EQUAL(std::string("7"), value.asString());

    value = (uint16_t) 8;
    BOOST_CHECK_EQUAL(std::string("8"), value.asString());
    value = (uint32_t) 9;
    BOOST_CHECK_EQUAL(std::string("9"), value.asString());

    //uint32 to larger unsigned ints and string
    value = (uint32_t) 9999999;
    BOOST_CHECK_EQUAL((uint32_t) 9999999, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 9999999, value.asUint64());
    BOOST_CHECK_EQUAL(std::string("9999999"), value.asString());
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);

    value = "true";
    BOOST_CHECK(value.asBool());
    value = "false";
    BOOST_CHECK(!value.asBool());
    value = "1";
    BOOST_CHECK(value.asBool());
    value = "0";
    BOOST_CHECK(!value.asBool());
    value = "other";
    BOOST_CHECK_THROW(value.asBool(), InvalidConversion);
}

QPID_AUTO_TEST_CASE(testSizeConversionsUint)
{
    Variant value;

    //uint8 (in 7 bits) to other uints, ints
    value = (uint8_t) 7;
    BOOST_CHECK_EQUAL((uint8_t) 7, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 7, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 7, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 7, value.asUint64());
    BOOST_CHECK_EQUAL((int8_t) 7, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) 7, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 7, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 7, value.asInt64());

    //uint8 (in 8 bits) to other uints, ints
    value = (uint8_t) 200;
    BOOST_CHECK_EQUAL((uint8_t) 200, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 200, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 200, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 200, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 200, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 200, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 200, value.asInt64());



    //uint16 (in 7 bits) to other uints, ints
    value = (uint16_t) 120;
    BOOST_CHECK_EQUAL((uint8_t) 120, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 120, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 120, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 120, value.asUint64());
    BOOST_CHECK_EQUAL((int8_t) 120, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) 120, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 120, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 120, value.asInt64());

    //uint16 (more than 7 bits) to other uints, ints
    value = (uint16_t) 240;
    BOOST_CHECK_EQUAL((uint8_t) 240, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 240, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 240, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 240, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 240, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 240, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 240, value.asInt64());

    //uint16 (more than 8 bits) to other uints, ints
    value = (uint16_t) 1000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 1000, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 1000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 1000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 1000, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 1000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 1000, value.asInt64());

    //uint16 (more than 15 bits) to other uints, ints
    value = (uint16_t) 32770;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 32770, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 32770, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 32770, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_EQUAL((int32_t) 32770, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 32770, value.asInt64());



    //uint32 (in 7 bits) to other uints, ints
    value = (uint32_t) 120;
    BOOST_CHECK_EQUAL((uint8_t) 120, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 120, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 120, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 120, value.asUint64());
    BOOST_CHECK_EQUAL((int8_t) 120, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) 120, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 120, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 120, value.asInt64());

    //uint32 (more than 7 bits) to other uints, ints
    value = (uint32_t) 240;
    BOOST_CHECK_EQUAL((uint8_t) 240, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 240, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 240, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 240, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 240, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 240, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 240, value.asInt64());

    //uint32 (more than 8 bits) to other uints, ints
    value = (uint32_t) 1000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 1000, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 1000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 1000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 1000, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 1000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 1000, value.asInt64());

    //uint32 (more than 15 bits) to other uints, ints
    value = (uint32_t) 32770;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 32770, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 32770, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 32770, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_EQUAL((int32_t) 32770, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 32770, value.asInt64());

    //uint32 (more than 16 bits) to other uints, ints
    value = (uint32_t) 66000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint32_t) 66000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 66000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_EQUAL((int32_t) 66000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 66000, value.asInt64());



    //uint64 (in 7 bits) to other uints, ints
    value = (uint64_t) 120;
    BOOST_CHECK_EQUAL((uint8_t) 120, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 120, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 120, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 120, value.asUint64());
    BOOST_CHECK_EQUAL((int8_t) 120, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) 120, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 120, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 120, value.asInt64());

    //uint64 (more than 7 bits) to other uints, ints
    value = (uint64_t) 240;
    BOOST_CHECK_EQUAL((uint8_t) 240, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 240, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 240, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 240, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 240, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 240, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 240, value.asInt64());

    //uint64 (more than 8 bits) to other uints, ints
    value = (uint64_t) 1000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 1000, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 1000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 1000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 1000, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 1000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 1000, value.asInt64());

    //uint64 (more than 15 bits) to other uints, ints
    value = (uint64_t) 32770;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 32770, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 32770, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 32770, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_EQUAL((int32_t) 32770, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 32770, value.asInt64());

    //uint64 (more than 16 bits) to other uints, ints
    value = (uint64_t) 66000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint32_t) 66000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 66000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_EQUAL((int32_t) 66000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 66000, value.asInt64());

    //uint64 (more than 31 bits) to other uints, ints
    value = (uint64_t) 3000000000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint32_t) 3000000000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 3000000000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt32(), InvalidConversion);
    BOOST_CHECK_EQUAL((int64_t) 3000000000, value.asInt64());

    //uint64 (more than 32 bits) to other uints, ints
    value = (uint64_t) 7000000000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint64_t) 7000000000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt32(), InvalidConversion);
    BOOST_CHECK_EQUAL((int64_t) 7000000000, value.asInt64());

    //uint64 (more than 63 bits) to other uints, ints
    value = (uint64_t) 0x8000000000000000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint64_t) 0x8000000000000000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt64(), InvalidConversion);
}

QPID_AUTO_TEST_CASE(testSizeConversionsInt)
{
    Variant value;

    //int8 (positive in 7 bits)
    value = (int8_t) 100;
    BOOST_CHECK_EQUAL((uint8_t) 100, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 100, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 100, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 100, value.asUint64());
    BOOST_CHECK_EQUAL((int8_t) 100, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) 100, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 100, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 100, value.asInt64());

    //int8 (negative)
    value = (int8_t) -100;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_EQUAL((int8_t) -100, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) -100, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) -100, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) -100, value.asInt64());



    //int16 (positive in 7 bits)
    value = (int16_t) 100;
    BOOST_CHECK_EQUAL((uint8_t) 100, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 100, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 100, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 100, value.asUint64());
    BOOST_CHECK_EQUAL((int8_t) 100, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) 100, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 100, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 100, value.asInt64());

    //int16 (positive in 8 bits)
    value = (int16_t) 200;
    BOOST_CHECK_EQUAL((uint8_t) 200, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 200, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 200, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 200, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 200, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 200, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 200, value.asInt64());

    //int16 (positive in more than 8 bits)
    value = (int16_t) 1000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 1000, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 1000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 1000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 1000, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 1000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 1000, value.asInt64());

    //int16 (negative in 7 bits)
    value = (int16_t) -100;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_EQUAL((int8_t) -100, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) -100, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) -100, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) -100, value.asInt64());

    //int16 (negative in more than 7 bits)
    value = (int16_t) -1000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) -1000, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) -1000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) -1000, value.asInt64());



    //int32 (positive in 7 bits)
    value = (int32_t) 100;
    BOOST_CHECK_EQUAL((uint8_t) 100, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 100, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 100, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 100, value.asUint64());
    BOOST_CHECK_EQUAL((int8_t) 100, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) 100, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 100, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 100, value.asInt64());

    //int32 (positive in 8 bits)
    value = (int32_t) 200;
    BOOST_CHECK_EQUAL((uint8_t) 200, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 200, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 200, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 200, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 200, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 200, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 200, value.asInt64());

    //int32 (positive in more than 8 bits)
    value = (int32_t) 1000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 1000, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 1000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 1000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 1000, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 1000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 1000, value.asInt64());

    //int32 (positive in more than 15 bits)
    value = (int32_t) 40000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 40000, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 40000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 40000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_EQUAL((int32_t) 40000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 40000, value.asInt64());

    //int32 (negative in 7 bits)
    value = (int32_t) -100;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_EQUAL((int8_t) -100, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) -100, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) -100, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) -100, value.asInt64());

    //int32 (negative in more than 7 bits)
    value = (int32_t) -1000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) -1000, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) -1000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) -1000, value.asInt64());

    //int32 (negative in more than 15 bits)
    value = (int32_t) -40000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_EQUAL((int32_t) -40000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) -40000, value.asInt64());



    //int64 (positive in 7 bits)
    value = (int64_t) 100;
    BOOST_CHECK_EQUAL((uint8_t) 100, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 100, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 100, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 100, value.asUint64());
    BOOST_CHECK_EQUAL((int8_t) 100, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) 100, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 100, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 100, value.asInt64());

    //int64 (positive in 8 bits)
    value = (int64_t) 200;
    BOOST_CHECK_EQUAL((uint8_t) 200, value.asUint8());
    BOOST_CHECK_EQUAL((uint16_t) 200, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 200, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 200, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 200, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 200, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 200, value.asInt64());

    //int64 (positive in more than 8 bits)
    value = (int64_t) 1000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 1000, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 1000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 1000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) 1000, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) 1000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 1000, value.asInt64());

    //int64 (positive in more than 15 bits)
    value = (int64_t) 40000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint16_t) 40000, value.asUint16());
    BOOST_CHECK_EQUAL((uint32_t) 40000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 40000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_EQUAL((int32_t) 40000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) 40000, value.asInt64());

    //int64 (positive in more than 31 bits)
    value = (int64_t) 3000000000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint32_t) 3000000000, value.asUint32());
    BOOST_CHECK_EQUAL((uint64_t) 3000000000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt32(), InvalidConversion);
    BOOST_CHECK_EQUAL((int64_t) 3000000000, value.asInt64());

    //int64 (positive in more than 32 bits)
    value = (int64_t) 5000000000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_EQUAL((uint64_t) 5000000000, value.asUint64());
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt32(), InvalidConversion);
    BOOST_CHECK_EQUAL((int64_t) 5000000000, value.asInt64());

    //int64 (negative in 7 bits)
    value = (int64_t) -100;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_EQUAL((int8_t) -100, value.asInt8());
    BOOST_CHECK_EQUAL((int16_t) -100, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) -100, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) -100, value.asInt64());

    //int64 (negative in more than 7 bits)
    value = (int64_t) -1000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_EQUAL((int16_t) -1000, value.asInt16());
    BOOST_CHECK_EQUAL((int32_t) -1000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) -1000, value.asInt64());

    //int64 (negative in more than 15 bits)
    value = (int64_t) -40000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_EQUAL((int32_t) -40000, value.asInt32());
    BOOST_CHECK_EQUAL((int64_t) -40000, value.asInt64());

    //int64 (negative in more than 31 bits)
    value = (int64_t) -3000000000;
    BOOST_CHECK_THROW(value.asUint8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint32(), InvalidConversion);
    BOOST_CHECK_THROW(value.asUint64(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt8(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt16(), InvalidConversion);
    BOOST_CHECK_THROW(value.asInt32(), InvalidConversion);
    BOOST_CHECK_EQUAL((int64_t) -3000000000, value.asInt64());
}

QPID_AUTO_TEST_CASE(testAssignment)
{
    Variant value("abc");
    Variant other = value;
    BOOST_CHECK_EQUAL(VAR_STRING, value.getType());
    BOOST_CHECK_EQUAL(other.getType(), value.getType());
    BOOST_CHECK_EQUAL(other.asString(), value.asString());

    const uint32_t i(1000);
    value = i;
    BOOST_CHECK_EQUAL(VAR_UINT32, value.getType());
    BOOST_CHECK_EQUAL(VAR_STRING, other.getType());
}

QPID_AUTO_TEST_CASE(testList)
{
    const std::string s("abc");
    const float f(9.876f);
    const int16_t x(1000);

    Variant value = Variant::List();
    value.asList().push_back(Variant(s));
    value.asList().push_back(Variant(f));
    value.asList().push_back(Variant(x));
    BOOST_CHECK_EQUAL(3u, value.asList().size());
    Variant::List::const_iterator i = value.asList().begin();

    BOOST_CHECK(i != value.asList().end());
    BOOST_CHECK_EQUAL(VAR_STRING, i->getType());
    BOOST_CHECK_EQUAL(s, i->asString());
    i++;

    BOOST_CHECK(i != value.asList().end());
    BOOST_CHECK_EQUAL(VAR_FLOAT, i->getType());
    BOOST_CHECK_EQUAL(f, i->asFloat());
    i++;

    BOOST_CHECK(i != value.asList().end());
    BOOST_CHECK_EQUAL(VAR_INT16, i->getType());
    BOOST_CHECK_EQUAL(x, i->asInt16());
    i++;

    BOOST_CHECK(i == value.asList().end());
}

QPID_AUTO_TEST_CASE(testMap)
{
    const std::string red("red");
    const float pi(3.14f);
    const int16_t x(1000);
    const Uuid u(true);

    Variant value = Variant::Map();
    value.asMap()["colour"] = red;
    value.asMap()["pi"] = pi;
    value.asMap()["my-key"] = x;
    value.asMap()["id"] = u;
    BOOST_CHECK_EQUAL(4u, value.asMap().size());

    BOOST_CHECK_EQUAL(VAR_STRING, value.asMap()["colour"].getType());
    BOOST_CHECK_EQUAL(red, value.asMap()["colour"].asString());

    BOOST_CHECK_EQUAL(VAR_FLOAT, value.asMap()["pi"].getType());
    BOOST_CHECK_EQUAL(pi, value.asMap()["pi"].asFloat());

    BOOST_CHECK_EQUAL(VAR_INT16, value.asMap()["my-key"].getType());
    BOOST_CHECK_EQUAL(x, value.asMap()["my-key"].asInt16());

    BOOST_CHECK_EQUAL(VAR_UUID, value.asMap()["id"].getType());
    BOOST_CHECK_EQUAL(u, value.asMap()["id"].asUuid());

    value.asMap()["my-key"] = "now it's a string";
    BOOST_CHECK_EQUAL(VAR_STRING, value.asMap()["my-key"].getType());
    BOOST_CHECK_EQUAL(std::string("now it's a string"), value.asMap()["my-key"].asString());
}

QPID_AUTO_TEST_CASE(testIsEqualTo)
{
    BOOST_CHECK_EQUAL(Variant("abc"), Variant("abc"));
    BOOST_CHECK_EQUAL(Variant(1234), Variant(1234));

    Variant a = Variant::Map();
    a.asMap()["colour"] = "red";
    a.asMap()["pi"] = 3.14f;
    a.asMap()["my-key"] = 1234;
    Variant b = Variant::Map();
    b.asMap()["colour"] = "red";
    b.asMap()["pi"] = 3.14f;
    b.asMap()["my-key"] = 1234;
    BOOST_CHECK_EQUAL(a, b);
}

QPID_AUTO_TEST_CASE(testEncoding)
{
    Variant a("abc");
    a.setEncoding("utf8");
    Variant b = a;
    Variant map = Variant::Map();
    map.asMap()["a"] = a;
    map.asMap()["b"] = b;
    BOOST_CHECK_EQUAL(a.getEncoding(), std::string("utf8"));
    BOOST_CHECK_EQUAL(a.getEncoding(), b.getEncoding());
    BOOST_CHECK_EQUAL(a.getEncoding(), map.asMap()["a"].getEncoding());
    BOOST_CHECK_EQUAL(b.getEncoding(), map.asMap()["b"].getEncoding());
    BOOST_CHECK_EQUAL(map.asMap()["a"].getEncoding(), map.asMap()["b"].getEncoding());
}

QPID_AUTO_TEST_SUITE_END()

}} // namespace qpid::tests
