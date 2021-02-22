#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

class HealthComponent : public Component {
private:
	int health;
public:
	HealthComponent(int health) {
		this->health = health;
	}
	int getHealth() {
		return health;
	}
	void setHealth(int amount) {
		health += amount;
	}
};

#endif 