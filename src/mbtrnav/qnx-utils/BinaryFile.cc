/****************************************************************************/
/* Copyright (c) 2000 MBARI                                                 */
/* MBARI Proprietary Information. All rights reserved.                      */
/****************************************************************************/
/* Summary  :                                                               */
/* Filename : BinaryFile.cc                                                 */
/* Author   :                                                               */
/* Project  :                                                               */
/* Version  : 1.0                                                           */
/* Created  : 02/07/2000                                                    */
/* Modified :                                                               */
/* Archived :                                                               */
/****************************************************************************/
/* Modification History:                                                    */
/****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "BinaryFile.h"
#include "Exception.h"
#include "ourTypes.h"
#include "CharData.h"
#include "ShortData.h"
#include "IntegerData.h"
#include "FloatData.h"
#include "DoubleData.h"
#include "StringData.h"

BinaryFile::BinaryFile(FILE *file)
  : FileData(file)
{
    _bufferNBytes = 0;
    _fd = fileno(file);
}


BinaryFile::~BinaryFile()
{
  if (_bufferNBytes != 0) write(_fd, (void *)_buffer, _bufferNBytes);
}


void BinaryFile::set(CharData *charData)
{
  char value = charData->value();

  if ((_bufferNBytes + 1) > _WRITE_BUFFER_SIZE) {
	write(_fd, (void *)_buffer, _bufferNBytes);
	_bufferNBytes = 0;
  }

  memcpy(_buffer+_bufferNBytes, &value, 1); _bufferNBytes++;
/*
  char errorBuf[MAX_EXC_STRING_LEN];

  if (fwrite((void *)&value, sizeof(char), 1, _file) < 1) {
    sprintf(errorBuf, "BinaryFile::set(CharData) - %s", strerror(errno));
    throw Exception(errorBuf);
  }
*/
}


void BinaryFile::set(ShortData *shortData)
{
  short value = shortData->value();

  if ((_bufferNBytes + sizeof(short) ) > _WRITE_BUFFER_SIZE) {
        write(_fd, (void *)_buffer, _bufferNBytes);
        _bufferNBytes = 0;
  }

  memcpy(_buffer+_bufferNBytes, &value, sizeof(short));
  _bufferNBytes += sizeof(short);
/*
  char errorBuf[MAX_EXC_STRING_LEN];

  if (fwrite((void *)&value, sizeof(short), 1, _file) < 1) {
    sprintf(errorBuf, "BinaryFile::set(ShortData) - %s", strerror(errno));
    throw Exception(errorBuf);
  }
*/
}


void BinaryFile::set(IntegerData *integerData)
{
  int value = integerData->value();

  if ((_bufferNBytes + sizeof(int)) > _WRITE_BUFFER_SIZE) {
        write(_fd, (void *)_buffer, _bufferNBytes);
        _bufferNBytes = 0;
  }

  memcpy(_buffer+_bufferNBytes, &value, sizeof(int));
  _bufferNBytes += sizeof(int);
/*
  char errorBuf[MAX_EXC_STRING_LEN];

  if (fwrite((void *)&value, sizeof(int), 1, _file) < 1) {
    sprintf(errorBuf, "BinaryFile::set(IntegerData) - %s", strerror(errno));
    throw Exception(errorBuf);
  }
*/
}


void BinaryFile::set(FloatData *floatData)
{
  float value = floatData->value();

  if ((_bufferNBytes + sizeof(float)) > _WRITE_BUFFER_SIZE) {
        write(_fd, (void *)_buffer, _bufferNBytes);
        _bufferNBytes = 0;
  }

  memcpy(_buffer+_bufferNBytes, &value, sizeof(float));
  _bufferNBytes += sizeof(float);
/*
  char errorBuf[MAX_EXC_STRING_LEN];

  if (fwrite((void *)&value, sizeof(float), 1, _file) < 1) {
    sprintf(errorBuf, "BinaryFile::set(FloatData) - %s", strerror(errno));
    throw Exception(errorBuf);
  }
*/
}


void BinaryFile::set(DoubleData *doubleData)
{
  double value = doubleData->value();

  if ((_bufferNBytes + sizeof(double)) > _WRITE_BUFFER_SIZE) {
        write(_fd, (void *)_buffer, _bufferNBytes);
        _bufferNBytes = 0;
  }

  memcpy(_buffer+_bufferNBytes, &value, sizeof(double));
  _bufferNBytes += sizeof(double);
/*
  char errorBuf[MAX_EXC_STRING_LEN];

  if (fwrite((void *)&value, sizeof(double), 1, _file) < 1) {
    sprintf(errorBuf, "BinaryFile::set(DoubleData) - %s", strerror(errno));
    throw Exception(errorBuf);
  }
*/
}


void BinaryFile::set(StringData *stringData)
{
  char *value = stringData->value();
  char nullChar = '\0';

  // Write string characaters and terminating null
  char errorBuf[MAX_EXC_STRING_LEN];

  if (fwrite((void *)value, strlen(value), 1, _file) < 1 ||
      fwrite((void *)&nullChar, sizeof(nullChar), 1, _file) < 1) {
    sprintf(errorBuf, "BinaryFile::set(StringData) - %s", strerror(errno));
    throw Exception(errorBuf);
  }
}


void BinaryFile::get(CharData *charData)
{
  char errorBuf[MAX_EXC_STRING_LEN];
  char value;

  if (fread((void *)&value, sizeof(char), 1, _file) < 1) {
    if (feof(_file)) {
      throw Exception("eof");
    }
    else {
      sprintf(errorBuf, "BinaryFile::get(CharData) - %s", strerror(errno));
      throw Exception(errorBuf);
    }
  }
  else
    charData->setValue(value);
}



void BinaryFile::get(ShortData *shortData)
{
  char errorBuf[MAX_EXC_STRING_LEN];
  short value;

  if (fread((void *)&value, sizeof(short), 1, _file) < 1) {
    if (feof(_file)) {
      throw Exception("eof");
    }
    else {
      sprintf(errorBuf, "BinaryFile::get(ShortData) - %s", strerror(errno));
      throw Exception(errorBuf);
    }
  }
  else
    shortData->setValue(value);
}


void BinaryFile::get(IntegerData *integerData)
{
  char errorBuf[MAX_EXC_STRING_LEN];
  int value;

  if (fread((void *)&value, sizeof(int), 1, _file) < 1) {
    if (feof(_file)) {
      throw Exception("eof");
    }
    else {
      sprintf(errorBuf, "BinaryFile::get(IntegerData) - %s", strerror(errno));
      throw Exception(errorBuf);
    }
  }
  else
    integerData->setValue(value);
}


void BinaryFile::get(FloatData *floatData)
{
  char errorBuf[MAX_EXC_STRING_LEN];
  float value;

  if (fread((void *)&value, sizeof(float), 1, _file) < 1) {
    if (feof(_file)) {
      throw Exception("eof");
    }
    else {
      sprintf(errorBuf, "BinaryFile::get(FloatData) - %s", strerror(errno));
      throw Exception(errorBuf);
    }
  }
  else
    floatData->setValue(value);
}



void BinaryFile::get(DoubleData *doubleData)
{
  char errorBuf[MAX_EXC_STRING_LEN];
  double value;

  if (fread((void *)&value, sizeof(double), 1, _file) < 1) {
    if (feof(_file)) {
      throw Exception("eof");
    }
    else {
      sprintf(errorBuf, "BinaryFile::get(DoubleData) - %s", strerror(errno));
      throw Exception(errorBuf);
    }
  }
  else
    doubleData->setValue(value);
}


void BinaryFile::get(StringData *stringData)
{
  char errorBuf[MAX_EXC_STRING_LEN];

  // Right now we have a hard-wired upper bound to the length of
  // the string!!!
  char string[100];
  size_t nCopiedBytes = 0;
  Boolean stringFinished = False;

  while (nCopiedBytes < sizeof(string) - 1) {

    int c;
    if ((c = getc(_file)) == -1) {
      // File ended before string retrieved
      sprintf(errorBuf, "BinaryFile::get(StringData) - EOF");
      throw Exception(errorBuf);
    }

    string[nCopiedBytes++] = c;

    if (c == '\0') {
      stringFinished = True;
      break;
    }
  }

  if (!stringFinished) {
    // File data too big to fit in string
    sprintf(errorBuf, "BinaryFile::get(StringData) - too many bytes");
    throw Exception(errorBuf);
  }

  stringData->setValue(string);
}


void BinaryFile::endRecord()
{
  write(_fd, _buffer, _bufferNBytes);
  _bufferNBytes = 0;
  // Does nothing
//  fflush(_file);
  return;
}
