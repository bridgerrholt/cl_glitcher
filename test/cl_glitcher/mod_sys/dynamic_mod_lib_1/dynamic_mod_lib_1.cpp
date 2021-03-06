//
// Created by bridg on 2/3/2021.
//

#define DYNALO_EXPORT_SYMBOLS
#include <dynalo/symbol_helper.hpp>
#include <mod_sys/mod_data_interface.h>
#include <rapidjson/document.h>

DYNALO_EXPORT void execute(rapidjson::Document::ValueType const & json)
{

}

DYNALO_EXPORT clglitch::ModDataInterface getModData()
{
  return {"execute"};
}