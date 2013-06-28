#ifndef RESOURCEMANAGER_HPP_INCLUDED
#define RESOURCEMANAGER_HPP_INCLUDED

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>

class ResourceManager
{
    public:
        /// \brief Load a texture if it isn't loaded yet and/or give a reference to the texture
        sf::Texture& getTexture(const std::string filename);
        /// \brief Load a SoundBuffer if it isn't loaded yet and/or give a reference to the SoundBuffer
        sf::SoundBuffer& getSoundBuffer(const std::string filename);
        /// \brief Load a music if it isn't loaded yet and/or give a reference to the music
        sf::Music& getMusic(const std::string filename);

    private:
        /// \brief Textures
        std::map <const std::string, std::shared_ptr<sf::Texture> > m_textures;

        /// \brief Soundbuffers
        std::map <const std::string, std::shared_ptr<sf::SoundBuffer> > m_soundBuffers;

        /// \brief Musics(these can be played and stopped directly by a state, so there is always only one instance of a certain music)
        std::map <const std::string, std::shared_ptr<sf::Music> > m_musics;
};

#endif // RESOURCEMANAGER_HPP_INCLUDED
