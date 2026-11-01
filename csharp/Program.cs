using System.Runtime.CompilerServices;
using MusicPlaylistService;

// 1. Ссылки и копии: класс vs struct
Console.WriteLine("===== 1a. Class: second = first means same object =====");
var trackA = new Track(1, "Queen", "Bohemian Rhapsody", "Rock", 355,
                       "/music/queen.mp3", "mp3", 8L * 1024 * 1024);
var trackB = trackA;                      // вторая ссылка на ТОТ ЖЕ объект
trackB.Block();
Console.WriteLine($"trackA.State after block via trackB: {trackA.State}");
Console.WriteLine($"Reference equality: {ReferenceEquals(trackA, trackB)}");

Console.WriteLine("\n===== 1b. Struct: b = a means independent copy =====");
var m1 = new Money { Rubles = 150, Kopeks = 50 };
var m2 = m1;
m2.Rubles = 300;
Console.WriteLine($"m1 = {m1}, m2 = {m2}  (m1 unchanged)");

// 2. Композиция: Track создаёт AudioFile сам
Console.WriteLine("\n===== 2. Composition: Track creates AudioFile itself =====");
var track1 = new Track(2, "Daft Punk", "Get Lucky", "Electronic", 369,
                       "/music/lucky.m4a", "m4a", 9L * 1024 * 1024);
Console.WriteLine($"track1 file: {track1.AudioFile.Path}");

// 3. Агрегация: Playlist получает готовые Track снаружи
Console.WriteLine("\n===== 3. Aggregation: Playlist receives tracks from outside =====");
var track2 = new Track(3, "Nirvana", "Smells Like Teen Spirit", "Grunge", 301,
                       "/music/teen.ogg", "ogg", 7L * 1024 * 1024);
var playlist = new Playlist(100, "My Favorite", "Best", 5);
playlist.AddTrack(track1);
playlist.AddTrack(track2);
playlist.Publish();
Console.WriteLine($"playlist: {playlist}");

// 4. Срабатывание проверки правила
Console.WriteLine("\n===== 4. Rule check: duplicate and limit =====");
playlist.AddTrack(track1);                 // duplicate
var strict = new Playlist(101, "Strict", "Only two", 2);
strict.AddTrack(track1);
strict.AddTrack(track2);
strict.AddTrack(trackA);                   // limit
var empty = new Playlist(102, "Empty", "Nothing", 5);
empty.Publish();                            // empty publish

// 5. Освобождение ресурса через IDisposable + using
Console.WriteLine("\n===== 5. IDisposable + using: resource released at block exit =====");
using (var log = new SessionLog("Listened playlist"))
{
    log.Write($"user listened to {playlist.Title}");
    log.Write("now logging more");
}
Console.WriteLine("After using block — Dispose already called");

// 6. Сборщик мусора: объект уничтожается не при выходе из блока, а после GC
Console.WriteLine("\n===== 6. Garbage collector: not destroyed at scope exit =====");
var watcher = CreateTemporaryProbe();
Console.WriteLine("After method return: no finalizer yet (GC not run)");
Console.WriteLine($"Weak reference alive: {watcher.TryGetTarget(out _)}");
GC.Collect();
GC.WaitForPendingFinalizers();
GC.Collect();
Console.WriteLine("After GC.Collect(): finalizer should have run");
Console.WriteLine($"Weak reference alive: {watcher.TryGetTarget(out _)}");

Console.WriteLine("\n===== End =====");

[MethodImpl(MethodImplOptions.NoInlining)]
static WeakReference<GcProbe> CreateTemporaryProbe()
{
    var probe = new GcProbe("Temporary");
    return new WeakReference<GcProbe>(probe);
}

sealed class GcProbe
{
    public string Name { get; }
    public GcProbe(string name)
    {
        Name = name;
        Console.WriteLine($"[GcProbe] created: {Name}");
    }
    ~GcProbe() => Console.WriteLine($"[GcProbe] finalized: {Name}");
}