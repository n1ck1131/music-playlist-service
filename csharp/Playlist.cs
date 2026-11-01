namespace MusicPlaylistService;

public enum PlaylistState { Draft, Published, Unpublished, Blocked }

public sealed class Playlist
{
    public const int DefaultTrackLimit = 50;

    public ulong Id { get; }
    public string Title { get; }
    public string Description { get; }
    public PlaylistState State { get; private set; } = PlaylistState.Draft;
    public int TrackLimit { get; }

    // агрегация: треки создаются снаружи, плейлист хранит только ссылки
    private readonly List<Track> _tracks = new();
    public IReadOnlyList<Track> Tracks => _tracks;

    public Playlist(ulong id, string title, string description, int trackLimit = DefaultTrackLimit)
    {
        Id = id;
        Title = title;
        Description = description;
        TrackLimit = trackLimit;
        Console.WriteLine($"[Playlist] created: {Title}");
    }

    public int TrackCount => _tracks.Count;
    public Track? GetTrackAt(int index) => index >= 0 && index < _tracks.Count ? _tracks[index] : null;

    public bool AddTrack(Track track)
    {
        if (State is PlaylistState.Published or PlaylistState.Blocked)
        {
            Console.WriteLine("[Playlist] cannot add track: playlist is not editable");
            return false;
        }
        if (_tracks.Count >= TrackLimit)
        {
            Console.WriteLine($"[Playlist] cannot add track: limit reached ({TrackLimit})");
            return false;
        }
        if (_tracks.Any(t => t.Id == track.Id))
        {
            Console.WriteLine($"[Playlist] cannot add track: duplicate id={track.Id}");
            return false;
        }
        if (!track.IsPlayable())
        {
            Console.WriteLine("[Playlist] cannot add track: track is not available");
            return false;
        }
        _tracks.Add(track);
        Console.WriteLine($"[Playlist] track added: {track.Title}");
        return true;
    }

    public bool RemoveTrack(ulong trackId)
    {
        var found = _tracks.FirstOrDefault(t => t.Id == trackId);
        if (found is null) { Console.WriteLine($"[Playlist] cannot remove track: id={trackId} not found"); return false; }
        _tracks.Remove(found);
        Console.WriteLine($"[Playlist] track removed: id={trackId}");
        return true;
    }

    public bool Publish()
    {
        if (State == PlaylistState.Blocked) { Console.WriteLine("[Playlist] cannot publish: blocked"); return false; }
        if (_tracks.Count == 0) { Console.WriteLine("[Playlist] cannot publish: playlist is empty"); return false; }
        if (_tracks.Any(t => !t.IsPlayable())) { Console.WriteLine("[Playlist] cannot publish: track is not available"); return false; }
        State = PlaylistState.Published;
        Console.WriteLine($"[Playlist] published: {Title}");
        return true;
    }

    public bool Unpublish()
    {
        if (State != PlaylistState.Published) { Console.WriteLine("[Playlist] cannot unpublish: not published"); return false; }
        State = PlaylistState.Unpublished;
        Console.WriteLine($"[Playlist] unpublished: {Title}");
        return true;
    }

    public bool Block()
    {
        State = PlaylistState.Blocked;
        Console.WriteLine($"[Playlist] blocked: {Title}");
        return true;
    }

    public bool IsPlayable() =>
        State == PlaylistState.Published && _tracks.All(t => t.IsPlayable());

    public override string ToString() =>
        $"Playlist({Id}: {Title}, {State}, {TrackCount} tracks)";
}