//
// Created by bridg on 1/19/2021.
//

#include <load_json_file.h>

#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <rapidjson/error/error.h>

#include <iostream>

namespace
{

const RAPIDJSON_ERROR_CHARTYPE* GetParseError_En(rapidjson::ParseErrorCode parseErrorCode) {
  using namespace rapidjson;
  switch (parseErrorCode) {
    case kParseErrorNone:                           return RAPIDJSON_ERROR_STRING("No error.");

    case kParseErrorDocumentEmpty:                  return RAPIDJSON_ERROR_STRING("The document is empty.");
    case kParseErrorDocumentRootNotSingular:        return RAPIDJSON_ERROR_STRING("The document root must not be followed by other values.");

    case kParseErrorValueInvalid:                   return RAPIDJSON_ERROR_STRING("Invalid value.");

    case kParseErrorObjectMissName:                 return RAPIDJSON_ERROR_STRING("Missing a name for object member.");
    case kParseErrorObjectMissColon:                return RAPIDJSON_ERROR_STRING("Missing a colon after a name of object member.");
    case kParseErrorObjectMissCommaOrCurlyBracket:  return RAPIDJSON_ERROR_STRING("Missing a comma or '}' after an object member.");

    case kParseErrorArrayMissCommaOrSquareBracket:  return RAPIDJSON_ERROR_STRING("Missing a comma or ']' after an array element.");

    case kParseErrorStringUnicodeEscapeInvalidHex:  return RAPIDJSON_ERROR_STRING("Incorrect hex digit after \\u escape in string.");
    case kParseErrorStringUnicodeSurrogateInvalid:  return RAPIDJSON_ERROR_STRING("The surrogate pair in string is invalid.");
    case kParseErrorStringEscapeInvalid:            return RAPIDJSON_ERROR_STRING("Invalid escape character in string.");
    case kParseErrorStringMissQuotationMark:        return RAPIDJSON_ERROR_STRING("Missing a closing quotation mark in string.");
    case kParseErrorStringInvalidEncoding:          return RAPIDJSON_ERROR_STRING("Invalid encoding in string.");

    case kParseErrorNumberTooBig:                   return RAPIDJSON_ERROR_STRING("Number too big to be stored in double.");
    case kParseErrorNumberMissFraction:             return RAPIDJSON_ERROR_STRING("Miss fraction part in number.");
    case kParseErrorNumberMissExponent:             return RAPIDJSON_ERROR_STRING("Miss exponent in number.");

    case kParseErrorTermination:                    return RAPIDJSON_ERROR_STRING("Terminate parsing due to Handler error.");
    case kParseErrorUnspecificSyntaxError:          return RAPIDJSON_ERROR_STRING("Unspecific syntax error.");

    default:                                        return RAPIDJSON_ERROR_STRING("Unknown error.");
  }
}

}

namespace json_util
{

rapidjson::Document loadJsonFile(std::string const & filename)
{
  using namespace rapidjson;

  std::FILE * fp = fopen(filename.c_str(), "r"); // non-Windows use "r"

  char readBuffer[65536];
  FileReadStream is(fp, readBuffer, sizeof(readBuffer));

  Document document;
  document.ParseStream(is);

  if (document.HasParseError())
  {
    std::cout << "Failed to parse\n" << filename << '\n';
    std::cout << "Error code " << document.GetParseError();
    std::cout << " at " << document.GetErrorOffset() << '\n';
    std::cout << "Error: " << GetParseError_En(document.GetParseError()) << '\n';
    document.GetParseError();
  }

  fclose(fp);

  return document;
}

}
