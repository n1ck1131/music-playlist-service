#include "author.hpp"

namespace music
{

Author::Author(std::string_view name, std::shared_ptr<Playlist> playlist, std::string_view bio)
    : BaseUser{ name, std::move(playlist) }
    , m_bio{ bio }
{
    std::cout << "[Author] created: " << GetName() << "\n";
}

std::string Author::Describe() const
{
    // Работа со строками: ищем хэштег в биографии
    std::string tag = "none";
    const std::size_t pos = m_bio.find('#');
    if (pos != std::string::npos)
    {
        const std::size_t end = m_bio.find(' ', pos);
        tag = m_bio.substr(pos, end - pos);
    }
    // Полностью заменяем метод базы (не вызываем BaseUser::Describe)
    return "[Author " + std::string(GetName()) + "] | Role: Author | Bio Tag: " + tag;
}

} // namespace music