#include "ButtonManager.h"
#include "./ButtonComponent.h"

void ButtonManager::AddButton(Entity* ent)
{
	// We populate the array
	buttons.push_back(ent);
	// If this was the first element then save it as the current highlighted
	if (buttons.size() == 1) {
		buttons.at(0)->GetComponent<ButtonComponent>()->highlight = true;
		highlighted_index = 0;
	}
}

/*
Highlight the next element in the list
*/
void ButtonManager::HighLightNext()
{
	if (!buttons.empty()) 
	{
		buttons.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = false;
		// End of list condition
		if (buttons.size() - 1 == highlighted_index) {
			highlighted_index = 0;
		}
		else {
			highlighted_index++;
		}

		buttons.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = true;
	}
}
/*
Highlight the element before in the list
*/
void ButtonManager::HighLightLast()
{
	if (!buttons.empty())
	{
		buttons.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = false;
		// End of list condition
		if (0 == highlighted_index) {
			highlighted_index = buttons.size() - 1;
		}
		else {
			highlighted_index--;
		}

		buttons.at(highlighted_index)->GetComponent<ButtonComponent>()->highlight = true;

	}

}

// Select the highlighted button
ButtonType ButtonManager::SelectButton()
{
	return buttons.at(highlighted_index)->GetComponent<ButtonComponent>()->type;
}
