#include "base_user.hpp"

namespace music
{

BaseUser::BaseUser(std::string_view name, std::shared_ptr<Playlist> playlist)
    : m_id{ ++s_lastId }
    , m_name{ name }
    , m_personalPlaylist{ std::move(playlist) }
{
    std::cout << "[BaseUser] created: " << m_name << " (id " << m_id << ")\n";
}

BaseUser::~BaseUser()
{
    std::cout << "[BaseUser] destroyed: " << m_name << " (id " << m_id << ")\n";
}

// Глубокая копия: создаем новый плейлист для копии
BaseUser::BaseUser(const BaseUser& other)
    : m_id{ ++s_lastId }
    , m_name{ other.m_name }
{
    if (other.m_personalPlaylist)
    {
         m_personalPlaylist = std::make_shared<Playlist>(
            m_id, std::string(other.m_personalPlaylist->GetTitle()) + " (copy)", "Copied playlist", 50);
    }
    std::cout << "[BaseUser] deep copied: " << m_name << " (new id " << m_id << ")\n";
}

BaseUser& BaseUser::operator=(const BaseUser& other)
{
    if (this == &other) // Использование this
    {
        return *this;
    }
    m_name = other.m_name;
    if (other.m_personalPlaylist)
    {
                m_personalPlaylist = std::make_shared<Playlist>(
            m_id, std::string(other.m_personalPlaylist->GetTitle()) + " (assigned)", "Copied", 50);
    }
    else
    {
        m_personalPlaylist = nullptr;
    }
    return *this;
}

std::string BaseUser::Describe() const
{
    return GetHeader() + " | Role: " + GetRole();
}

} // namespace music