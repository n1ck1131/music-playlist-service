namespace MusicPlaylistService;

public sealed class AudioFile
{
    public const long MaxSizeBytes = 20L * 1024 * 1024;

    public string Path { get; }
    public string Format { get; }
    public long SizeBytes { get; }

    public AudioFile(string path, string format, long sizeBytes)
    {
        Path = path;
        Format = format;
        SizeBytes = sizeBytes;
        Console.WriteLine($"[AudioFile] created: {Path}");
        if (!IsSupportedFormat())
            Console.WriteLine($"[AudioFile] error: unsupported format '{Format}'");
        if (!IsWithinSizeLimit())
            Console.WriteLine($"[AudioFile] error: file size {SizeBytes} exceeds limit");
    }

    public bool IsSupportedFormat() => Format is "mp3" or "m4a" or "ogg";
    public bool IsWithinSizeLimit() => SizeBytes <= MaxSizeBytes;

    public override string ToString() => $"AudioFile({Path}, {Format}, {SizeBytes} bytes)";
}