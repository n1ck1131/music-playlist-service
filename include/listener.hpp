// Наследник 1
#pragma once
#include "base_user.hpp"

namespace music
{

class Listener : public BaseUser
{
private:
    std::string m_subscription{};

public:
    Listener(std::string_view name, std::shared_ptr<Playlist> playlist, std::string_view subscription);

    [[nodiscard]] std::string GetRole() const override { return "Listener"; }
    [[nodiscard]] std::string Describe() const override; // Будет вызывать базовый
    [[nodiscard]] std::unique_ptr<BaseUser> Clone() const override
    {
        return std::make_unique<Listener>(*this); // Вызывает конструктор копирования
    }
};

} // namespace music