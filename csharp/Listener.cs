using System;

namespace MusicPlaylistService;

public class Listener : BaseUser
{
    public string Subscription { get; }

    public Listener(string name, Playlist? playlist, string subscription) : base(name, playlist)
    {
        Subscription = subscription;
        Console.WriteLine($"[Listener] created: {Name}");
    }

    public override string GetRole() => "Listener";

    public override string Describe()
    {
        return $"{base.Describe()} | Subscription: {Subscription}";
    }

    public override BaseUser Clone()
    {
        // Глубокая копия: создаем новый плейлист для клона
        var newPlaylist = PersonalPlaylist != null 
            ? new Playlist(PersonalPlaylist.Id, PersonalPlaylist.Title + " (copy)", "Copied", 50) 
            : null;
        return new Listener(Name, newPlaylist, Subscription);
    }
}