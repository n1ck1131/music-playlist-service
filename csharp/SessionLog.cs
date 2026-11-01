namespace MusicPlaylistService;

public sealed class SessionLog : IDisposable
{
    private readonly string _title;
    private bool _disposed;

    public SessionLog(string title)
    {
        _title = title;
        Console.WriteLine($"[+] session opened: {_title}");
    }

    public void Write(string line) => Console.WriteLine($"    {line}");

    public void Dispose()
    {
        if (_disposed) return;
        _disposed = true;
        Console.WriteLine($"[-] session closed: {_title}");
    }
}