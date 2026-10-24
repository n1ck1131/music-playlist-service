#include "playlist.hpp"

#include <algorithm>
#include <iostream>

namespace music
{

Playlist::Playlist(std::uint64_t id,
                   std::string_view title,
                   std::string_view description,
                   std::size_t trackLimit)
    : m_id{ id }
    , m_title{ title }
    , m_description{ description }
    , m_trackLimit{ trackLimit }
{
    std::cout << "[Playlist] created: " << m_title << '\n';
}

Playlist::~Playlist()
{
    std::cout << "[Playlist] destroyed: " << m_title << '\n';
    // Треки не удаляются: они созданы снаружи (агрегация).
}

const Track* Playlist::GetTrackAt(std::size_t index) const
{
    if (index >= m_tracks.size())
    {
        return nullptr;
    }
    return m_tracks[index];
}

bool Playlist::AddTrack(Track& track)
{
    if (m_state == PlaylistState::ePublished || m_state == PlaylistState::eBlocked)
    {
        std::cout << "[Playlist] cannot add track: playlist is not editable\n";
        return false;
    }
    if (m_tracks.size() >= m_trackLimit)
    {
        std::cout << "[Playlist] cannot add track: limit reached (" << m_trackLimit << ")\n";
        return false;
    }
    const auto it = std::find_if(m_tracks.begin(), m_tracks.end(),
                                 [&track](const Track* t) { return t->GetId() == track.GetId(); });
    if (it != m_tracks.end())
    {
        std::cout << "[Playlist] cannot add track: duplicate id=" << track.GetId() << '\n';
        return false;
    }
    if (!track.IsPlayable())
    {
        std::cout << "[Playlist] cannot add track: track is not available\n";
        return false;
    }
    m_tracks.push_back(&track);
    std::cout << "[Playlist] track added: " << track.GetTitle() << '\n';
    return true;
}

bool Playlist::RemoveTrack(std::uint64_t trackId)
{
    const auto it = std::find_if(m_tracks.begin(), m_tracks.end(),
                                 [trackId](const Track* t) { return t->GetId() == trackId; });
    if (it == m_tracks.end())
    {
        std::cout << "[Playlist] cannot remove track: id=" << trackId << " not found\n";
        return false;
    }
    m_tracks.erase(it);
    std::cout << "[Playlist] track removed: id=" << trackId << '\n';
    return true;
}

bool Playlist::Publish()
{
    if (m_state == PlaylistState::eBlocked)
    {
        std::cout << "[Playlist] cannot publish: playlist is blocked\n";
        return false;
    }
    if (m_tracks.empty())
    {
        std::cout << "[Playlist] cannot publish: playlist is empty\n";
        return false;
    }
    for (const auto* track : m_tracks)
    {
        if (track == nullptr || !track->IsPlayable())
        {
            std::cout << "[Playlist] cannot publish: track is not available\n";
            return false;
        }
    }
    m_state = PlaylistState::ePublished;
    std::cout << "[Playlist] published: " << m_title << '\n';
    return true;
}

bool Playlist::Unpublish()
{
    if (m_state != PlaylistState::ePublished)
    {
        std::cout << "[Playlist] cannot unpublish: not published\n";
        return false;
    }
    m_state = PlaylistState::eUnpublished;
    std::cout << "[Playlist] unpublished: " << m_title << '\n';
    return true;
}

bool Playlist::Block()
{
    m_state = PlaylistState::eBlocked;
    std::cout << "[Playlist] blocked: " << m_title << '\n';
    return true;
}

bool Playlist::IsPlayable() const
{
    if (m_state != PlaylistState::ePublished)
    {
        return false;
    }
    return std::all_of(m_tracks.begin(), m_tracks.end(),
                       [](const Track* t) { return t != nullptr && t->IsPlayable(); });
}

} // namespace music