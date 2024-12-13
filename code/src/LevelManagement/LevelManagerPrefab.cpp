#include "LevelManagerPrefab.h"

GameObject* LevelManagerFactory::createLevelManagerPrefab()
{
	GameObject* levelManagerPrefab = new GameObject;
	setTag(levelManagerPrefab);
	addBehaviourScripts(levelManagerPrefab);
	LevelManagerBehaviourScript& levelManagerBehaviourScript =
		levelManagerPrefab->getComponents<LevelManagerBehaviourScript>().at(0);
	levelManagerBehaviourScript.setLevel(1);
	return levelManagerPrefab;
}

void LevelManagerFactory::addBehaviourScripts(GameObject* gameObject)
{
	gameObject->addComponent<LevelManagerBehaviourScript>();
	gameObject->addComponent<LevelCreatorBehaviourScript>();
}

void LevelManagerFactory::setTag(GameObject* gameObject) { gameObject->setTag("LevelManager"); }
