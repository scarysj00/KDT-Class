#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <cassert>
#include <format>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "Enum.h"

using namespace std;
using FAccountName = string;