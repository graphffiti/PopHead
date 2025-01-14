#pragma once

#include "interface.hpp"
#include "Events/event.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace ph {

class GameData;

class GUI
{
public:
	GUI();
	~GUI();

	class Gui_drawer : public sf::Drawable
	{
	public:
		Gui_drawer(GameData* gameData, std::string name);

		void init(GUI* gui);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void update(sf::Time delta);

		void move(sf::Vector2f delta, bool recursive = true);

	private:
		GUI* mGui;
	};

	Widget* addInterface(const std::string& name);

	Widget* getInterface(const std::string& name);

	Gui_drawer& getGuiDrawer() { return *mGuiDrawer; }

	void move(const sf::Vector2f&);

	void deleteInterface(const std::string& name);

	void showInterface(const std::string& name);

	void hideInterface(const std::string& name);

	void swap(const std::string& first, const std::string& second);

	void moveUp(const std::string& name);

	void handleEvent(const ph::Event&);

	void update(sf::Time deltaTime);

	void transform();

	void draw();

	void init(GameData* gamedata);

	void clearGUI();

private:
	std::map<std::string, std::unique_ptr<Interface>> mInterfaceList;
	std::unique_ptr<Gui_drawer> mGuiDrawer;
	GameData* mGameData;
};

}
