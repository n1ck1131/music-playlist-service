//Это абстрактный класс. Он хранит статический ID, имя и плейлист (для демонстрации копирования)

#pragma once

#include "playlist.hpp"
#include <memory>
#include <string>
#include <string_view>
#include <iostream>

namespace music
{

class BaseUser
{
private:
    inline static int s_lastId{ 0 };
    int m_id{ 0 };
    std::string m_name{};
    std::shared_ptr<Playlist> m_personalPlaylist{};

protected:
    // protected: нужно наследникам для форматирования, но скрыто от внешнего мира
    [[nodiscard]] std::string GetHeader() const { return "[User " + m_name + "]"; }

public:
    BaseUser(std::string_view name, std::shared_ptr<Playlist> playlist);
    virtual ~BaseUser(); // Виртуальный деструктор!

    BaseUser(const BaseUser& other);            // Глубокая копия
    BaseUser& operator=(const BaseUser& other); // Оператор присваивания
    BaseUser(BaseUser&&) noexcept = default;
    BaseUser& operator=(BaseUser&&) noexcept = default;

    [[nodiscard]] int GetId() const { return m_id; }
    [[nodiscard]] std::string_view GetName() const { return m_name; }
    [[nodiscard]] std::shared_ptr<Playlist> GetPlaylist() const { return m_personalPlaylist; }

    // Чисто виртуальные методы (делают класс абстрактным)
    [[nodiscard]] virtual std::string GetRole() const = 0;
    [[nodiscard]] virtual std::unique_ptr<BaseUser> Clone() const = 0;

    // Виртуальный метод с реализацией
    [[nodiscard]] virtual std::string Describe() const;
};

} // namespace music