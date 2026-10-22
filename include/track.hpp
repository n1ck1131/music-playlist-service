#pragma once

#include "audio_file.hpp"

#include <cstdint>
#include <string>
#include <string_view>

namespace music
{

enum class TrackState
{
    eAvailable,
    eBlocked,
    eDeleted
};

class Track
{
private:
    std::uint64_t m_id{ 0 };
    std::string m_artist{};
    std::string m_title{};
    std::string m_genre{};
    std::uint32_t m_durationSec{ 0 };
    TrackState m_state{ TrackState::eAvailable };

    // Композиция: AudioFile — часть Track, создаётся и уничтожается вместе с ним.
    AudioFile m_audioFile;

public:
    Track(std::uint64_t id,
          std::string_view artist,
          std::string_view title,
          std::string_view genre,
          std::uint32_t durationSec,
          std::string_view filePath,
          std::string_view fileFormat,
          std::uint64_t fileSizeBytes);

    Track()                          = delete;
    Track(const Track&)              = default;
    Track(Track&&)                   = default;
    Track& operator=(const Track&)   = default;
    Track& operator=(Track&&)        = default;
    ~Track();

    [[nodiscard]] std::uint64_t GetId() const { return m_id; }
    [[nodiscard]] std::string_view GetArtist() const { return m_artist; }
    [[nodiscard]] std::string_view GetTitle() const { return m_title; }
    [[nodiscard]] std::string_view GetGenre() const { return m_genre; }
    [[nodiscard]] std::uint32_t GetDurationSec() const { return m_durationSec; }
    [[nodiscard]] TrackState GetState() const { return m_state; }
    [[nodiscard]] const AudioFile& GetAudioFile() const { return m_audioFile; }

    bool Block();
    bool MarkDeleted();
    [[nodiscard]] bool IsPlayable() const;
};

} // namespace music