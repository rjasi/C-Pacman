#include "MainMenu.h"
#include "Logger.h"
#include "TextUtilities.hpp"
#include "Ui.hpp"

#include <iostream>

namespace Pacman
{
    
    MainMenu::MainMenu(const sf::Vector2u& windowSize)
    : windowSize_(windowSize), 
      font_(), 
      title_(font_)   
    {
        if (!font_.openFromFile("assets/fonts/PressStart2P-Regular.ttf")) 
        {
            Logger::instance().error("Failed to load font: assets/fonts/PressStart2P.ttf");
            // Menu will still exist, but text will be empty.
            return;
        }

        title_.setFont(font_);
        title_.setString("PACMAN");
        title_.setCharacterSize(48);
        Ui::place(title_, windowSize_, {0.5f, 0.2f});
        rebuildText();
    }

    void MainMenu::rebuildText() 
    {
        items_.clear();
        items_.reserve(labels_.size());

        for (std::size_t i = 0; i < labels_.size(); ++i) 
        {
            sf::Text t(font_);
            t.setCharacterSize(28);
            t.setString(labels_[i]);
            items_.push_back(t);
        }
        updateHighlight();
        
        Ui::layoutLeftAlignedColumn(items_, windowSize_, 40.f);
    }

    void MainMenu::updateHighlight() 
    {
        // Simple highlight rule:
        // - selected item gets a prefix and larger size
        for (std::size_t i = 0; i < items_.size(); ++i) 
        {
            const bool isSelected = (static_cast<int>(i) == selected_);
            if (isSelected) 
            {
                items_[i].setString(">" + labels_[i]);
            } 
            else 
            {
                items_[i].setString(" " + labels_[i]);
            }
        }
    }


    void MainMenu::handleEvent(const sf::Event& event)
    {
        if (auto* key = event.getIf<sf::Event::KeyPressed>()) 
        {
            switch (key->scancode) 
            {
                case sf::Keyboard::Scancode::Up:
                    selected_ = (selected_ - 1 + static_cast<int>(labels_.size()))
                                % static_cast<int>(labels_.size());
                    updateHighlight();
                    break;

                case sf::Keyboard::Scancode::Down:
                    selected_ = (selected_ + 1) % static_cast<int>(labels_.size());
                    updateHighlight();
                    break;

                case sf::Keyboard::Scancode::Enter:
                case sf::Keyboard::Scancode::NumpadEnter:
                    if (selected_ == 0) {
                        pendingAction_ = MenuAction::StartGame;
                    } else {
                        pendingAction_ = MenuAction::Quit;
                    }
                    break;

                case sf::Keyboard::Scancode::Escape:
                    pendingAction_ = MenuAction::Quit;
                    break;

                default:
                    break;
            }
        }
    }

    void MainMenu::render(sf::RenderTarget& target) const 
    {
        // If font didn’t load, avoid drawing invalid text
        if (!font_.getInfo().family.empty()) 
        {
            target.draw(title_);
            for (const auto& item : items_) 
            {
                target.draw(item);
            }
        }
    }

    MenuAction MainMenu::consumeAction() 
    {
        MenuAction a = pendingAction_;
        pendingAction_ = MenuAction::None;
        return a;
    }
}