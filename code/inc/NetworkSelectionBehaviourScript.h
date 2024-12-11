#ifndef NETWORKSELECTIONBEHAVIOURSCRIPT_H
#define NETWORKSELECTIONBEHAVIOURSCRIPT_H

#include "Components/IBehaviourScript.h"
#include "UI/Button.h"

#include <list>
#include <vector>

class NetworkSelectionBehaviourScript : public IBehaviourScript
{
public:
	std::unique_ptr<Component> clone() const override
	{
		return std::make_unique<NetworkSelectionBehaviourScript>(*this);
	}

	void onStart() override;
	void onUpdate() override;

	// Callbacks for all buttons in this menu
	void onServerRelease();
	void onClientRelease();
	void onHostRelease();
	void onSearchRelease();
	void onConnectRelease(const std::string& aServerAddress);

private:
	// All the buttons in this menu
	GameObject* mMainMenuObject{nullptr};
	Button* mServerButton{nullptr};
	Button* mClientButton{nullptr};
	Button* mHostButton{nullptr};
	Button* mSearchButton{nullptr};
	std::vector<Button*> mServerAdressButtons;

	// The starting position of the menu items
	const int mMenuStartX{240 + 13};
	const int mMenuStartY{135 + 5};
};
#endif // NETWORKSELECTIONBEHAVIOURSCRIPT_H