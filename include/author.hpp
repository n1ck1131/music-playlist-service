// наследник 2
#pragma once
#include "base_user.hpp"

namespace music
{

class Author final : public BaseUser // final: от него нельзя наследоваться
{
private:
    std::string m_bio{};

public:
    Author(std::string_view name, std::shared_ptr<Playlist> playlist, std::string_view bio);

    [[nodiscard]] std::string GetRole() const override { return "Author"; }
    [[nodiscard]] std::string Describe() const override; // Заменит базовый
    [[nodiscard]] std::unique_ptr<BaseUser> Clone() const override
    {
        return std::make_unique<Author>(*this);
    }
};

} // namespace music