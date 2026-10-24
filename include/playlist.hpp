#pragma once

#include "track.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace music
{

enum class PlaylistState
{
    eDraft,
    ePublished,
    eUnpublished,
    eBlocked
};

class Playlist
{
public:
    static constexpr std::size_t DEFAULT_TRACK_LIMIT = 50;

private:
    std::uint64_t m_id{ 0 };
    std::string m_title{};
    std::string m_description{};
    PlaylistState m_state{ PlaylistState::eDraft };
    std::size_t m_trackLimit{ DEFAULT_TRACK_LIMIT };

    // Агрегация: указатели на треки, созданные снаружи.
    std::vector<Track*> m_tracks{};

public:
    Playlist(std::uint64_t id,
             std::string_view title,
             std::string_view description,
             std::size_t trackLimit = DEFAULT_TRACK_LIMIT);

    Playlist()                            = delete;
    Playlist(const Playlist&)             = delete;
    Playlist(Playlist&&)                  = delete;
    Playlist& operator=(const Playlist&)  = delete;
    Playlist& operator=(Playlist&&)       = delete;
    ~Playlist();

    [[nodiscard]] std::uint64_t GetId() const { return m_id; }
    [[nodiscard]] std::string_view GetTitle() const { return m_title; }
    [[nodiscard]] std::string_view GetDescription() const { return m_description; }
    [[nodiscard]] PlaylistState GetState() const { return m_state; }
    [[nodiscard]] std::size_t GetTrackCount() const { return m_tracks.size(); }
    [[nodiscard]] const Track* GetTrackAt(std::size_t index) const;

    bool AddTrack(Track& track);
    bool RemoveTrack(std::uint64_t trackId);
    bool Publish();
    bool Unpublish();
    bool Block();
    [[nodiscard]] bool IsPlayable() const;
};

} // namespace music