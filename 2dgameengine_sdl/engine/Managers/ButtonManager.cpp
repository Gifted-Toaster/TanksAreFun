#include "ButtonManager.h"
#include "./Entity/Component/ButtonComponent.h"

void ButtonManager::AddButton(Entity* ent)
{
	// We populate the array
	container.push_back(ent);
	// If this was the first element then save it as the current highlighted
	if (container.size() == 1) {
		container.at(0)->GetComponent<ButtonComponent>()->highlight = true;
		highlighted_index = 0;
	}
}

Entity* ButtonManager::highlighted_button()
{
	return container.at(highlighted_index);
}

bool ButtonManager::IsEmpty()
{
	return container.size() == 0;
}

void ButtonManager::HighLightOnIndex(int index)
{
	container.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = false;
	highlighted_index = index;
	container.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = true;
}

/*
Highlight the next element in the list
*/
void ButtonManager::HighLightNext()
{
	if (!container.empty())
	{
		container.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = false;
		// End of list condition
		if (container.size() - 1 == highlighted_index) {
			highlighted_index = 0;
		}
		else {
			highlighted_index++;
		}

		container.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = true;
	}
}
/*
Highlight the element before in the list
*/
void ButtonManager::HighLightLast()
{
	if (!container.empty())
	{
		container.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = false;
		// End of list condition
		if (0 == highlighted_index) {
			highlighted_index = container.size() - 1;
		}
		else {
			highlighted_index--;
		}

		container.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = true;
	}

}

// Select the highlighted button
// TODO:  Save its address instead of its index number
ButtonType ButtonManager::SelectButton()
{
	return container.at(highlighted_index)->GetComponent<ButtonComponent>()->type;
}

