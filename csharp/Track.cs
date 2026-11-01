namespace MusicPlaylistService;

public enum TrackState { Available, Blocked, Deleted }

public sealed class Track
{
    public ulong Id { get; }
    public string Artist { get; }
    public string Title { get; }
    public string Genre { get; }
    public uint DurationSec { get; }
    public TrackState State { get; private set; } = TrackState.Available;

    // композиция: часть создаётся в конструкторе целого, наружу не отдаётся как самостоятельный объект
    private readonly AudioFile _audioFile;
    public AudioFile AudioFile => _audioFile;

    public Track(ulong id, string artist, string title, string genre, uint durationSec,
                 string filePath, string fileFormat, long fileSizeBytes)
    {
        Id = id;
        Artist = artist;
        Title = title;
        Genre = genre;
        DurationSec = durationSec;
        _audioFile = new AudioFile(filePath, fileFormat, fileSizeBytes);
        Console.WriteLine($"[Track] created: {Artist} - {Title}");
    }

    public bool Block()
    {
        if (State == TrackState.Deleted)
        {
            Console.WriteLine($"[Track] cannot block deleted track: {Title}");
            return false;
        }
        State = TrackState.Blocked;
        Console.WriteLine($"[Track] blocked: {Title}");
        return true;
    }

    public bool MarkDeleted()
    {
        if (State == TrackState.Deleted) return false;
        State = TrackState.Deleted;
        Console.WriteLine($"[Track] marked deleted: {Title}");
        return true;
    }

    public bool IsPlayable() => State == TrackState.Available;

    public override string ToString() => $"Track({Id}: {Artist} - {Title}, {State})";
}