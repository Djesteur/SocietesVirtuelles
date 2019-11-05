#ifndef NEEDS_UPDATES_HPP
#define NEEDS_UPDATES_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"

class NeedsUpdates: public Gg::Algorithm::AbstractAlgorithm {

	public:

		NeedsUpdates(Gg::GulgEngine &gulgEngine);
		
		virtual ~NeedsUpdates(); 

		void apply(); 

	protected:

};

#endif