#include "audio_file.hpp"
#include "playlist.hpp"
#include "track.hpp"

#include <cstddef>
#include <iostream>

using music::AudioFile;
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
              << ", tracks=" << playlist.GetTrackCount() << '\n';
}

} // namespace

int main()
{
    PrintSeparator("1. Composition: Track owns AudioFile");
    {
        Track track1{ 1, "Queen", "Bohemian Rhapsody", "Rock", 355,
                      "/music/queen_bohemian.mp3", "mp3", 8ULL * 1024 * 1024 };
        std::cout << "track1 playable: " << track1.IsPlayable() << '\n';
        std::cout << "track1 file: " << track1.GetAudioFile().GetPath() << '\n';
        std::cout << "track1 format supported: "
                  << track1.GetAudioFile().IsSupportedFormat() << '\n';
    }
    // При выходе из блока: ~Track, затем ~AudioFile.

    PrintSeparator("2. AudioFile rule: unsupported format and oversize");
    {
        Track badFormat{ 2, "Bad", "BadFormat", "Pop", 100,
                         "/music/bad.wav", "wav", 1024 };
        std::cout << "badFormat IsSupportedFormat: "
                  << badFormat.GetAudioFile().IsSupportedFormat() << '\n';

        Track oversize{ 3, "Big", "Oversize", "Pop", 100,
                        "/music/big.mp3", "mp3",
                        AudioFile::MAX_SIZE_BYTES + 1 };
        std::cout << "oversize IsWithinSizeLimit: "
                  << oversize.GetAudioFile().IsWithinSizeLimit() << '\n';
    }

    PrintSeparator("3. Aggregation: Playlist uses Track created outside");
    Track track2{ 10, "Daft Punk", "Get Lucky", "Electronic", 369,
                  "/music/daft_punk_lucky.m4a", "m4a", 9ULL * 1024 * 1024 };
    Track track3{ 11, "Nirvana", "Smells Like Teen Spirit", "Grunge", 301,
                  "/music/nirvana_teen.ogg", "ogg", 7ULL * 1024 * 1024 };
    {
        Playlist playlist{ 100, "My Favorite", "Best of all time", 5 };
        playlist.AddTrack(track2);
        playlist.AddTrack(track3);
        PrintPlaylistState(playlist, "Before publish:");

        const Track* first = playlist.GetTrackAt(0);
        if (first != nullptr)
        {
            std::cout << "First track: " << first->GetArtist()
                      << " - " << first->GetTitle()
                      << " (file " << first->GetAudioFile().GetFormat() << ")\n";
        }

        playlist.Publish();
        PrintPlaylistState(playlist, "After publish:");
        std::cout << "Playlist playable: " << playlist.IsPlayable() << '\n';
    }
    // Плейлист уничтожен, но track2 и track3 живы — агрегация.
    std::cout << "After playlist destroyed, track2 still alive: "
              << track2.GetTitle() << '\n';
    std::cout << "track2 playable: " << track2.IsPlayable() << '\n';

    PrintSeparator("4. Playlist rules: duplicate, limit, empty publish");
    {
        Playlist strictPlaylist{ 101, "Strict", "Only two tracks", 2 };
        strictPlaylist.AddTrack(track2);
        strictPlaylist.AddTrack(track2);   // дубликат — отказ
        strictPlaylist.AddTrack(track3);   // второй трек — ок
        Track extra{ 12, "Test", "Extra", "Pop", 100,
                     "/music/extra.mp3", "mp3", 1024 };
        strictPlaylist.AddTrack(extra);    // лимит — отказ

        Playlist emptyPlaylist{ 102, "Empty", "Nothing here", 5 };
        emptyPlaylist.Publish();           // пустой — отказ
        std::cout << "Empty playlist state after failed publish: "
                  << static_cast<int>(emptyPlaylist.GetState()) << '\n';
    }

    PrintSeparator("5. Track rule: blocked track cannot be played or added");
    {
        Track blockable{ 13, "Some", "Blockable", "Pop", 150,
                         "/music/blockable.mp3", "mp3", 1024 };
        Playlist pub{ 103, "Pub", "Published", 5 };
        pub.AddTrack(blockable);
        pub.Publish();

        blockable.Block();
        std::cout << "blockable playable: " << blockable.IsPlayable() << '\n';
        std::cout << "pub playlist playable after block: "
                  << pub.IsPlayable() << '\n';

        Playlist other{ 104, "Other", "New", 5 };
        other.AddTrack(blockable);          // отказ: трек недоступен
    }

    PrintSeparator("6. Dynamic memory: new / delete");
    auto* dynamicTrack = new Track{ 20, "Radiohead", "Creep", "Alt Rock", 238,
                                    "/music/radiohead_creep.mp3", "mp3",
                                    6ULL * 1024 * 1024 };
    std::cout << "Dynamic track: " << dynamicTrack->GetTitle() << '\n';
    delete dynamicTrack;

    constexpr std::size_t arraySize = 2;
    auto* trackArray = new Track[arraySize] {
        Track{ 21, "A", "Song A", "Pop", 200, "/music/a.mp3", "mp3", 1024 },
        Track{ 22, "B", "Song B", "Rock", 210, "/music/b.mp3", "mp3", 2048 }
    };
    for (std::size_t i = 0; i < arraySize; ++i)
    {
        std::cout << "Array track " << i << ": " << trackArray[i].GetTitle() << '\n';
    }
    delete[] trackArray;

    constexpr std::size_t ptrArraySize = 2;
    auto** trackPtrArray = new Track*[ptrArraySize];
    trackPtrArray[0] = new Track{ 23, "C", "Song C", "Jazz", 300,
                                  "/music/c.mp3", "mp3", 1024 };
    trackPtrArray[1] = new Track{ 24, "D", "Song D", "Blues", 310,
                                  "/music/d.mp3", "mp3", 1024 };
    for (std::size_t i = 0; i < ptrArraySize; ++i)
    {
        std::cout << "Ptr array track " << i << ": "
                  << trackPtrArray[i]->GetTitle() << '\n';
    }
    for (std::size_t i = 0; i < ptrArraySize; ++i)
    {
        delete trackPtrArray[i];
    }
    delete[] trackPtrArray;

    PrintSeparator("7. Reference and pointer to object");
    Track refTrack{ 30, "E", "Song E", "Pop", 220, "/music/e.mp3", "mp3", 1024 };
    Track& refToTrack = refTrack;
    Track* ptrToTrack = &refTrack;
    std::cout << "By reference: " << refToTrack.GetTitle() << '\n';
    std::cout << "By pointer:   " << ptrToTrack->GetTitle() << '\n';

    PrintSeparator("8. Lifetime difference demonstration");
    std::cout << "--- Aggregation: track outlives playlist ---\n";
    Track longLivingTrack{ 31, "F", "Long Living", "Pop", 200,
                           "/music/f.mp3", "mp3", 1024 };
    {
        Playlist shortLivingPlaylist{ 200, "Short", "Temporary", 5 };
        shortLivingPlaylist.AddTrack(longLivingTrack);
        std::cout << "Inside block, playlist tracks: "
                  << shortLivingPlaylist.GetTrackCount() << '\n';
    }
    std::cout << "Outside block, track still playable: "
              << longLivingTrack.IsPlayable() << '\n';

    std::cout << "\n--- Composition: audio file dies with track ---\n";
    {
        Track tempTrack{ 32, "G", "Temp", "Pop", 200,
                         "/music/g.mp3", "mp3", 1024 };
        std::cout << "Inside block, file: "
                  << tempTrack.GetAudioFile().GetPath() << '\n';
    }

    PrintSeparator("End of demonstration");
    return 0;
}