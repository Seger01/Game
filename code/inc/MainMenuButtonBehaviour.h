#include "Components/IButtonBehaviourScript.h"

#include <iostream>

#include "Components/Sprite.h"
#include "GameObject.h"
#include "Text.h"

class MainMenuButtonBehaviour : public IButtonBehaviourScript
{
public:
	MainMenuButtonBehaviour() {}

	~MainMenuButtonBehaviour() {}

	std::unique_ptr<Component> clone() const override { return std::make_unique<MainMenuButtonBehaviour>(*this); }

	void onButtonPressed() override {}

	void onButtonReleased() override {}

	void onButtonHover() override
	{
		for (Sprite& sprite : mGameObject->getComponents<Sprite>())
		{
			sprite.setColorFilter({255, 255, 255, 255});
		}

		for (GameObject* child : mGameObject->getChildren())
		{
			if (dynamic_cast<Text*>(child))
			{
				Text* textobj = dynamic_cast<Text*>(child);

				Color textColor = textobj->getColor();
				textColor.a = 255;

				textobj->setColor(textColor);
			}
		}
	}

	void onButtonUnhover() override
	{
		for (Sprite& sprite : mGameObject->getComponents<Sprite>())
		{
			sprite.setColorFilter({255, 255, 255, 100});
		}

		for (GameObject* child : mGameObject->getChildren())
		{
			if (dynamic_cast<Text*>(child))
			{
				Text* textobj = dynamic_cast<Text*>(child);

				Color textColor = textobj->getColor();
				textColor.a = 150;

				textobj->setColor(textColor);
			}
		}
	}
};
