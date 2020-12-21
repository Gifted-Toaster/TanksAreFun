#ifndef ANIMATION_N
#define ANIMATION_H

class Animation {
public:
	unsigned int index;
	unsigned int numFrames;
	unsigned int animationSpeed;
	Animation() {
		index = 0;
		numFrames = 0;
		animationSpeed = 0;
	};
	Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed) {
		this->index = index;
		this->numFrames = numFrames;
		this->animationSpeed = animationSpeed;
	};
};

#endif