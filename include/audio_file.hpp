#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace music
{

class AudioFile
{
public:
    static constexpr std::uint64_t MAX_SIZE_BYTES = 20ULL * 1024ULL * 1024ULL;

private:
    std::string m_path{};
    std::string m_format{};
    std::uint64_t m_sizeBytes{ 0 };

public:
    AudioFile(std::string_view path, std::string_view format, std::uint64_t sizeBytes);

    AudioFile()                            = delete;
    AudioFile(const AudioFile&)            = default;
    AudioFile(AudioFile&&)                 = default;
    AudioFile& operator=(const AudioFile&) = default;
    AudioFile& operator=(AudioFile&&)      = default;
    ~AudioFile();

    [[nodiscard]] std::string_view GetPath() const { return m_path; }
    [[nodiscard]] std::string_view GetFormat() const { return m_format; }
    [[nodiscard]] std::uint64_t GetSizeBytes() const { return m_sizeBytes; }

    [[nodiscard]] bool IsSupportedFormat() const;
    [[nodiscard]] bool IsWithinSizeLimit() const;
};

} // namespace music