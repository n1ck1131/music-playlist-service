#include "playlist.hpp"
#include "track.hpp"

#include <iostream>
#include <memory>
#include <vector>

using music::Playlist;
using music::PlaylistState;
using music::Track;

namespace
{

void PrintSeparator(const char* title)
{
    std::cout << "\n===== " << title << " =====\n";
}

void PrintPlaylistState(const Playlist& playlist, const char* prefix)
{
    std::cout << prefix << " playlist '" << playlist.GetTitle()
              << "', state=" << static_cast<int>(playlist.GetState())
              << ", alive tracks=" << playlist.GetTrackCount() << '\n';
}

} // namespace

int main()
{
    PrintSeparator("1. unique_ptr: destroyed at block exit without delete");
    {
        auto owned = std::make_unique<Track>(1, "Queen", "Bohemian Rhapsody", "Rock", 355,
                                             "/music/queen.mp3", "mp3", 8ULL * 1024 * 1024);
        std::cout << "owned title: " << owned->GetTitle() << '\n';
    }
    // здесь ~Track и ~AudioFile без единого delete

    PrintSeparator("2. unique_ptr: ownership transferred via std::move");
    auto original = std::make_unique<Track>(2, "Daft Punk", "Get Lucky", "Electronic", 369,
                                            "/music/lucky.m4a", "m4a", 9ULL * 1024 * 1024);
    std::cout << "original before move: " << (original ? "not null" : "null") << '\n';
    auto moved = std::move(original);
    std::cout << "original after move:  " << (original ? "not null" : "null") << '\n';
    std::cout << "moved title: " << moved->GetTitle() << '\n';

    PrintSeparator("3. shared_ptr: use_count grows and shrinks");
    auto sharedTrack = std::make_shared<Track>(3, "Nirvana", "Smells Like Teen Spirit", "Grunge",
                                               301, "/music/teen.ogg", "ogg", 7ULL * 1024 * 1024);
    std::cout << "use_count (one owner): " << sharedTrack.use_count() << '\n';
    {
        auto copy = sharedTrack;   // второй владелец
        std::cout << "use_count (two owners): " << sharedTrack.use_count() << '\n';
    }
    std::cout << "use_count (copy gone): " << sharedTrack.use_count() << '\n';

    PrintSeparator("4. weak_ptr: lock() while alive, empty after destruction");
    auto playlist = std::make_shared<Playlist>(100, "My Favorite", "Best", 5);
    playlist->AddTrack(sharedTrack);
    std::cout << "use_count after AddTrack (weak_ptr does not count): "
              << sharedTrack.use_count() << '\n';

    if (auto locked = playlist->GetTrackAt(0))
    {
        std::cout << "lock() while alive: " << locked->GetTitle() << '\n';
    }
    else
    {
        std::cout << "unexpected: lock() returned null while alive\n";
    }

    sharedTrack.reset();
    std::cout << "after last shared_ptr reset — object destroyed\n";

    if (auto locked = playlist->GetTrackAt(0))
    {
        std::cout << "unexpected: still alive: " << locked->GetTitle() << '\n';
    }
    else
    {
        std::cout << "lock() returned null, expired handled correctly\n";
    }
    PrintPlaylistState(*playlist, "After reset:");

    PrintSeparator("5. Arrays: vector<unique_ptr> and vector<shared_ptr>");
    std::vector<std::unique_ptr<Track>> uniqArray;
    uniqArray.push_back(std::make_unique<Track>(10, "A", "Song A", "Pop", 200,
                                                "/music/a.mp3", "mp3", 1024));
    uniqArray.push_back(std::make_unique<Track>(11, "B", "Song B", "Rock", 210,
                                                "/music/b.mp3", "mp3", 2048));
    for (const auto& t : uniqArray)
    {
        std::cout << "uniq array: " << t->GetTitle() << '\n';
    }

    std::vector<std::shared_ptr<Track>> sharedArray;
    sharedArray.push_back(std::make_shared<Track>(20, "C", "Song C", "Jazz", 300,
                                                  "/music/c.mp3", "mp3", 1024));
    sharedArray.push_back(std::make_shared<Track>(21, "D", "Song D", "Blues", 310,
                                                  "/music/d.mp3", "mp3", 1024));
    for (const auto& t : sharedArray)
    {
        std::cout << "shared array: " << t->GetTitle() << '\n';
    }

    PrintSeparator("6. Rules: duplicate, limit, empty publish");
    auto trackA = std::make_shared<Track>(30, "E", "Song E", "Pop", 220,
                                          "/music/e.mp3", "mp3", 1024);
    auto trackB = std::make_shared<Track>(31, "F", "Song F", "Rock", 230,
                                          "/music/f.mp3", "mp3", 1024);

    auto strict = std::make_shared<Playlist>(101, "Strict", "Only two", 2);
    strict->AddTrack(trackA);
    strict->AddTrack(trackA);      // дубликат — отказ
    strict->AddTrack(trackB);      // второй трек — ок
    auto extra = std::make_shared<Track>(32, "G", "Song G", "Pop", 240,
                                         "/music/g.mp3", "mp3", 1024);
    strict->AddTrack(extra);       // лимит — отказ

    auto empty = std::make_shared<Playlist>(102, "Empty", "Nothing", 5);
    empty->Publish();              // пустой — отказ

    PrintSeparator("7. blocked track: not added, playlist becomes unplayable");
    auto blockable = std::make_shared<Track>(40, "Some", "Blockable", "Pop", 150,
                                             "/music/blockable.mp3", "mp3", 1024);
    auto pub = std::make_shared<Playlist>(103, "Pub", "Published", 5);
    pub->AddTrack(blockable);
    pub->Publish();
    std::cout << "pub playable before block: " << pub->IsPlayable() << '\n';

    blockable->Block();
    std::cout << "blockable playable: " << blockable->IsPlayable() << '\n';
    std::cout << "pub playable after block:  " << pub->IsPlayable() << '\n';

    auto other = std::make_shared<Playlist>(104, "Other", "New", 5);
    other->AddTrack(blockable);    // отказ: трек недоступен

    PrintSeparator("End of demonstration");
    return 0;
}