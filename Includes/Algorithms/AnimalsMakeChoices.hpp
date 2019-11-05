#ifndef ANIMALS_MAKE_CHOICES_HPP
#define ANIMALS_MAKE_CHOICES_HPP

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"
#include "Components/IAChoice.hpp"
#include "Components/FSM.hpp"

class AnimalsMakeChoices: public Gg::Algorithm::AbstractAlgorithm {

	public:

		AnimalsMakeChoices(Gg::GulgEngine &gulgEngine);
		
		virtual ~AnimalsMakeChoices(); 

		void apply(); 

	protected:

};

#endif