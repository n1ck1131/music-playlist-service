#include "listener.hpp"

namespace music
{

Listener::Listener(std::string_view name, std::shared_ptr<Playlist> playlist, std::string_view subscription)
    : BaseUser{ name, std::move(playlist) } // Вызов конструктора базы в списке инициализации
    , m_subscription{ subscription }
{
    std::cout << "[Listener] created: " << GetName() << "\n";
}

std::string Listener::Describe() const
{
    // Дополняем метод базового класса
    return BaseUser::Describe() + " | Subscription: " + m_subscription;
}

} // namespace music