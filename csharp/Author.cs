using System;

namespace MusicPlaylistService;

public sealed class Author : BaseUser // sealed запрещает наследование
{
    public string Bio { get; }

    public Author(string name, Playlist? playlist, string bio) : base(name, playlist)
    {
        Bio = bio;
        Console.WriteLine($"[Author] created: {Name}");
    }

    public override string GetRole() => "Author";

    public override string Describe()
    {
        var tag = "none";
        var pos = Bio.IndexOf('#');
        if (pos != -1)
        {
            var end = Bio.IndexOf(' ', pos);
            tag = end == -1 ? Bio.Substring(pos) : Bio.Substring(pos, end - pos);
        }
        return $"[Author {Name}] | Role: Author | Bio Tag: {tag}";
    }

    public override BaseUser Clone()
    {
        var newPlaylist = PersonalPlaylist != null 
            ? new Playlist(PersonalPlaylist.Id, PersonalPlaylist.Title + " (copy)", "Copied", 50) 
            : null;
        return new Author(Name, newPlaylist, Bio);
    }
}