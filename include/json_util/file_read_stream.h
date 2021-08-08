//
// Created by bridg on 7/24/2021.
//

#include <cstdio>
#include <vector>
#include <cassert>

#ifndef CL_GLITCHER_INCLUDE_JSON_UTIL_FILE_READ_STREAM_H
#define CL_GLITCHER_INCLUDE_JSON_UTIL_FILE_READ_STREAM_H

namespace json_util
{

// Implements rapidjson Stream concept
class FileReadStream {
  public:
    typedef char Ch;    //!< Character type (byte).

    struct Position
    {
      std::size_t line;
      std::size_t column;
    };

    //! Constructor.
    /*!
        \param fp File pointer opened for read.
        \param buffer user-supplied buffer.
        \param bufferSize size of buffer in bytes. Must >=4 bytes.
    */
    FileReadStream(
      std::FILE * fp,
      char * buffer,
      size_t bufferSize,
      std::size_t lineSizeArrReserve=16);

    Ch Peek() const;
    Ch Take();
    size_t Tell() const;

    // Not implemented
    void Put(Ch) { assert(false); }
    void Flush() { assert(false); }
    Ch* PutBegin() { assert(false); return nullptr; }
    size_t PutEnd(Ch*) { assert(false); return 0; }

    // For encoding detection only.
    const Ch* Peek4() const;

    int error() const;
    Position getPosition(std::size_t character) const;

  private:
    void read();
    void readRaw();

    std::FILE* fp_;
    Ch *buffer_;
    size_t bufferSize_;
    Ch *bufferLast_;
    Ch *current_;
    size_t readCount_;
    size_t count_;  //!< Number of characters read
    std::vector<std::size_t> lineSizeArr_;
    int error_;
    bool eof_;
};

}

#endif //CL_GLITCHER_INCLUDE_JSON_UTIL_FILE_READ_STREAM_H
