//
// Created by bridg on 7/24/2021.
//

#include <file_read_stream.h>

#include <cassert>

namespace json_util
{

FileReadStream::FileReadStream(
  std::FILE * fp,
  char * buffer,
  size_t bufferSize,
  std::size_t lineSizeArrReserve
) :
  fp_ {fp},
  buffer_ {buffer},
  bufferSize_ {bufferSize},
  bufferLast_ {nullptr},
  current_ {buffer},
  readCount_ {0},
  count_ {0},
  error_ {0},
  eof_(false)
{
  assert(fp_ != 0);
  assert(bufferSize >= 4);

  lineSizeArr_.reserve(lineSizeArrReserve);
  lineSizeArr_.push_back(0);

  read();
}

FileReadStream::Ch FileReadStream::Peek() const
{
  return *current_;
}



FileReadStream::Ch FileReadStream::Take()
{
  Ch c = *current_;
  read();
  return c;
}



size_t FileReadStream::Tell() const
{
  return count_ + static_cast<size_t>(current_ - buffer_);
}



FileReadStream::Ch const * FileReadStream::Peek4() const {
  return (current_ + 4 - !eof_ <= bufferLast_) ? current_ : 0;
}


int FileReadStream::error() const
{
  return error_;
}


FileReadStream::Position FileReadStream::getPosition(
  std::size_t character
) const
{
  for (std::size_t i {0}; i != lineSizeArr_.size(); i++)
  {
    std::size_t lineSize {lineSizeArr_[i]};

    if (character >= lineSize)
    {
      character -= lineSize;
    }
    if (character < lineSize)
    {
      return {i + 1, character + 1};
    }
  }

  return {lineSizeArr_.size(), character + 1};
}

void FileReadStream::read()
{
  readRaw();

  if (Peek() == '\r')
  {
    readRaw();

    if (Peek() == '\n')
      readRaw();

    lineSizeArr_.push_back(0);
  }
  else if (Peek() == '\n')
  {
    readRaw();

    if (Peek() == '\r')
      readRaw();

    lineSizeArr_.push_back(0);
  }
  else
  {
    lineSizeArr_.back() += 1;
  }
}


void FileReadStream::readRaw()
{
  if (current_ < bufferLast_)
  {
    ++current_;
  }
  else if (!eof_)
  {
    count_ += readCount_;
    readCount_ = std::fread(buffer_, 1, bufferSize_, fp_);
    bufferLast_ = buffer_ + readCount_ - 1;
    current_ = buffer_;

    if (readCount_ < bufferSize_)
    {
      buffer_[readCount_] = '\0';
      ++bufferLast_;
      eof_ = true;
      error_ = std::ferror(fp_);
    }
  }
}



}