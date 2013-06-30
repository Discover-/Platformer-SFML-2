#include "mainmenu.hpp"

MainMenu::MainMenu()
{
    button_play.setPosition(sf::Vector2f(300.0f, 100.0f));
    button_options.setPosition(sf::Vector2f(300.0f, 200.0f));
    button_levelEditor.setPosition(sf::Vector2f(300.0f, 300.0f));
    button_exit.setPosition(sf::Vector2f(300.0f, 400.0f));
    items.push_back(&button_play);
    items.push_back(&button_options);
    items.push_back(&button_levelEditor);
    items.push_back(&button_exit);
}

MainMenu::MainMenu(ResourceManager* resourceManager)
//!Load the default textures
:button_play(sf::Vector2f(300.0f, 100.0f), resourceManager->getTexture("Graphics/Menu/play.png")),
button_options(sf::Vector2f(300.0f, 200.0f), resourceManager->getTexture("Graphics/Menu/options.png")),
button_levelEditor(sf::Vector2f(300.0f, 300.0f), resourceManager->getTexture("Graphics/Menu/level_editor.png")),
button_exit(sf::Vector2f(300.0f, 400.0f), resourceManager->getTexture("Graphics/Menu/quit.png"))
{
    items.push_back(&button_play);
    items.push_back(&button_options);
    items.push_back(&button_levelEditor);
    items.push_back(&button_exit);
}
