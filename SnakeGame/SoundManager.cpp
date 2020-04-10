#include "SoundManager.h"

#include <iostream>

SoundManager::SoundManager()
{
	std::cout << "SOUND MANAGER CONSTRUCTED" << std::endl;
	LoadSFX("sfx_food_special");
	LoadSFX("sfx_food_standard");
	LoadSFX("sfx_gobble_on");
	LoadSFX("sfx_gobble_off");
	LoadSFX("sfx_menu_move");
	LoadSFX("sfx_menu_pause");
	LoadSFX("sfx_menu_select");
	LoadSFX("sfx_snake_death");
	LoadSFX("sfx_snake_move");

	LoadMusic("music_game");
}

SoundManager::~SoundManager()
{
	for(const auto& sound : m_sfxBuffer)
	{
		delete sound.second;
	}

	for (const auto& music : m_musicBuffer)
	{
		delete music.second;
	}
}

void SoundManager::PlaySFX(const std::string& _sfxName)
{
	m_sfx.setBuffer(*m_sfxBuffer.at(_sfxName));
	m_sfx.play();
}

void SoundManager::PlayMusic(const std::string& _musicName)
{
	m_music.setBuffer(*m_musicBuffer.at(_musicName));
	m_music.play();
}

void SoundManager::StopMusic()
{
	m_music.stop();
}

void SoundManager::LoadSFX(const std::string& _fileName)
{
	auto* newSound{ new sf::SoundBuffer() };
	newSound->loadFromFile("Resources/Sounds/" + _fileName + ".flac");
	m_sfxBuffer.insert(std::pair<std::string, sf::SoundBuffer*>(_fileName, newSound));
}

void SoundManager::LoadMusic(const std::string& _fileName)
{
	auto* newSound{ new sf::SoundBuffer() };
	newSound->loadFromFile("Resources/Sounds/" + _fileName + ".flac");
	m_musicBuffer.insert(std::pair<std::string, sf::SoundBuffer*>(_fileName, newSound));
}
