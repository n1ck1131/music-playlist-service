namespace MusicPlaylistService;

public struct Money
{
    public int Rubles;
    public int Kopeks;
    public override string ToString() => $"{Rubles}.{Kopeks:D2} RUB";
}