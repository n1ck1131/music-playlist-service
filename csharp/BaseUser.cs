using System;

namespace MusicPlaylistService;

public abstract class BaseUser
{
    private static int _lastId = 0;
    
    public int Id { get; }
    public string Name { get; }
    public Playlist? PersonalPlaylist { get; set; }

    protected BaseUser(string name, Playlist? playlist)
    {
        Id = ++_lastId;
        Name = name;
        PersonalPlaylist = playlist;
        Console.WriteLine($"[BaseUser] created: {Name} (id {Id})");
    }

    // protected: доступно только наследникам
    protected string GetHeader() => $"[User {Name}]";

    public abstract string GetRole();
    
    public virtual string Describe() => $"{GetHeader()} | Role: {GetRole()}";
    
    public abstract BaseUser Clone();

    // Поверхностное копирование (доступно извне)
    public BaseUser ShallowCopy() => (BaseUser)MemberwiseClone();

    public override bool Equals(object? obj) => obj is BaseUser other && Id == other.Id;
    public override int GetHashCode() => Id.GetHashCode();
}