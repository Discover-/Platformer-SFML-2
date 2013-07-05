#include <iostream>

#include "resourcemanager.hpp"

sf::Texture& ResourceManager::getTexture(const std::string filename)
{
    if (m_textures.find(filename) == m_textures.end())
    {
        //The texture is not yet loaded, load it now
        sf::Texture texture;
        if (texture.loadFromFile(filename))
        {
            //The texture loaded fine, add it to the list
            //m_textures.emplace(filename, std::make_shared(texture)); NOTE: THIS IS NOT YET IMPLEMENTED BY COMPILERS
            m_textures.insert(std::make_pair(filename, std::shared_ptr<sf::Texture>(new sf::Texture(texture))));
            return *m_textures.at(filename);
        }
        else
        {
            std::cerr<<"The Texture: "<<filename<<" could not be loaded"<<std::endl;
            throw "Problem loading file: "+filename;
        }
    }
    else
    {
        //The texture is already in our memory, we only have to give a reference
        return *m_textures.at(filename);
    }
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string filename)
{
    if (m_soundBuffers.find(filename) == m_soundBuffers.end())
    {
        //The SoundBuffer is not yet loaded, load it now
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(filename))
        {
            //Buffer loaded fine, add it to the list
            //soundBuffers.emplace(filename, std::make_shared(buffer)); NOTE: THIS IS NOT YET IMPLEMENTED BY COMPILES
            m_soundBuffers.insert(std::make_pair(filename, std::shared_ptr<sf::SoundBuffer>(new sf::SoundBuffer(buffer))));
            return *m_soundBuffers.at(filename);
        }
        else
        {
            std::cerr<<"The SoundBuffer: "<<filename<<" could not be loaded"<<std::endl;
            throw "Problem loading file: "+filename;
        }
    }
    else
    {
        //The buffer is already in our memory, we only have to give a reference
        return *m_soundBuffers.at(filename);
    }
}

sf::Music& ResourceManager::getMusic(const std::string filename)
{
    if (m_musics.find(filename) == m_musics.end())
    {
        //The Music is not yet loaded, load it now
        auto music = std::make_shared<sf::Music>();
        if (music->openFromFile(filename))
        {
            //Music loaded fine, add it to the list
            //musics.emplace(filename, std::move(music)); NOTE: THIS IS NOT YET IMPLEMENTED BY COMPILERS
            m_musics.insert(std::make_pair(filename,std::move(music)));
            return *m_musics.at(filename);
        }
        else
        {
            std::cerr<<"The Music: "<<filename<<" could not be loaded"<<std::endl;
            throw "Problem loading file: "+filename;
        }
    }
    else
    {
        //The music is already in our memory, we only have to give a reference
        return *m_musics.at(filename);
    }
}

sf::Font& ResourceManager::getFont(const std::string filename)
{
    if (m_fonts.find(filename) == m_fonts.end())
    {
        //The font is not yet loaded, load it now
        sf::Font font;

        if (font.loadFromFile(filename))
        {
            m_fonts.insert(std::make_pair(filename, std::shared_ptr<sf::Font>(new sf::Font(font))));
            return *m_fonts.at(filename);
        }
        else
        {
            std::cerr<<"The font: "<<filename<<" could not be loaded"<<std::endl;
            throw "Problem loading file: "+filename;
        }
    }
    else
    {
        //The font is already in our memory, we only have to give a reference
        return *m_fonts.at(filename);
    }
}
