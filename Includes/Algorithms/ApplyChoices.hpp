#ifndef APPLY_CHOICES_HPP
#define APPLY_CHOICES_HPP

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"
#include "Components/IAChoice.hpp"

#include "Mathematics/Basics.hpp"

class ApplyChoices: public Gg::Algorithm::AbstractAlgorithm {

	public:

		ApplyChoices(Gg::GulgEngine &gulgEngine);
		
		virtual ~ApplyChoices(); 

		void apply(); 

	protected:

};

#endif