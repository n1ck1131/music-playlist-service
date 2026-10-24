#include "track.hpp"

#include <iostream>

namespace music
{

Track::Track(std::uint64_t id,
             std::string_view artist,
             std::string_view title,
             std::string_view genre,
             std::uint32_t durationSec,
             std::string_view filePath,
             std::string_view fileFormat,
             std::uint64_t fileSizeBytes)
    : m_id{ id }
    , m_artist{ artist }
    , m_title{ title }
    , m_genre{ genre }
    , m_durationSec{ durationSec }
    , m_audioFile{ filePath, fileFormat, fileSizeBytes }
{
    std::cout << "[Track] created: " << m_artist << " - " << m_title << '\n';
}

Track::~Track()
{
    std::cout << "[Track] destroyed: " << m_artist << " - " << m_title << '\n';
}

bool Track::Block()
{
    if (m_state == TrackState::eDeleted)
    {
        std::cout << "[Track] cannot block deleted track: " << m_title << '\n';
        return false;
    }
    m_state = TrackState::eBlocked;
    std::cout << "[Track] blocked: " << m_title << '\n';
    return true;
}

bool Track::MarkDeleted()
{
    if (m_state == TrackState::eDeleted)
    {
        std::cout << "[Track] already deleted: " << m_title << '\n';
        return false;
    }
    m_state = TrackState::eDeleted;
    std::cout << "[Track] marked deleted: " << m_title << '\n';
    return true;
}

bool Track::IsPlayable() const
{
    return m_state == TrackState::eAvailable;
}

} // namespace music