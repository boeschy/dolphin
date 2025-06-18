// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <optional>
#include <string>

#include <picojson.h>

#include "Common/MathUtil.h"
#include "Common/Matrix.h"

// Ideally this would use a concept like, 'template <std::ranges::range Range>' to constrain it,
// but unfortunately we'd need to require clang 15 for that, since the ranges library isn't
// fully implemented until then, but this should suffice.

template <typename Range>
picojson::array ToJsonArray(const Range& data)
{
  picojson::array result;
  result.reserve(std::size(data));

  for (const auto& value : data)
  {
    result.emplace_back(static_cast<double>(value));
  }

  return result;
}

template <typename Type>
std::optional<Type> ReadNumericFromJson(const picojson::object& obj, const std::string& key)
{
  const auto it = obj.find(key);
  if (it == obj.end())
    return std::nullopt;
  if (!it->second.is<double>())
    return std::nullopt;
  return MathUtil::SaturatingCast<Type>(it->second.get<double>());
}

picojson::object ToJsonObject(const Common::Vec3& vec);
void FromJson(const picojson::object& obj, Common::Vec3& vec);
