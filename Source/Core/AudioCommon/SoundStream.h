// Copyright 2009 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <memory>

#include "AudioCommon/Mixer.h"
#include "Common/CommonTypes.h"

class SoundStream
{
protected:
  std::unique_ptr<Mixer> m_mixer;

public:
  SoundStream(unsigned int backendSampleRate = 48000) : m_mixer(new Mixer(backendSampleRate)) {}
  virtual ~SoundStream() {}
  static bool IsValid() { return false; }
  Mixer* GetMixer() const { return m_mixer.get(); }
  virtual bool Init() { return false; }
  virtual void SetVolume(int) {}
  // Returns true if successful.
  virtual bool SetRunning(bool running) { return false; }
  // Needed for libretro
  virtual void Update() {}
};
