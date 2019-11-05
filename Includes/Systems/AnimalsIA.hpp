#ifndef ANIMALS_IA_UPDATE_HPP
#define ANIMALS_IA_UPDATE_HPP

#include "Systems/AbstractSystem.hpp"

#include "Algorithms/AnimalsMakeChoices.hpp"
#include "Algorithms/ApplyChoices.hpp"

class AnimalsIA: public Gg::Systems::AbstractSystem {

	public:

		AnimalsIA(Gg::GulgEngine &gulgEngine);
		
		virtual ~AnimalsIA();

	protected:
};


#endif