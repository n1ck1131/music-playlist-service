#include "audio_file.hpp"

#include <iostream>

namespace music
{

AudioFile::AudioFile(std::string_view path, std::string_view format, std::uint64_t sizeBytes)
    : m_path{ path }
    , m_format{ format }
    , m_sizeBytes{ sizeBytes }
{
    std::cout << "[AudioFile] created: " << m_path << '\n';
    if (!IsSupportedFormat())
    {
        std::cout << "[AudioFile] error: unsupported format '" << m_format << "'\n";
    }
    if (!IsWithinSizeLimit())
    {
        std::cout << "[AudioFile] error: file size " << m_sizeBytes << " exceeds limit\n";
    }
}

AudioFile::~AudioFile()
{
    std::cout << "[AudioFile] destroyed: " << m_path << '\n';
}

bool AudioFile::IsSupportedFormat() const
{
    return m_format == "mp3" || m_format == "m4a" || m_format == "ogg";
}

bool AudioFile::IsWithinSizeLimit() const
{
    return m_sizeBytes <= MAX_SIZE_BYTES;
}

} // namespace music