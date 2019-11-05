#ifndef SYNCHRONIZE_POSITION_HPP
#define SYNCHRONIZE_POSITION_HPP

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"
#include "Components/Graphics/Sprite.hpp"

class SynchronizePositions: public Gg::Algorithm::AbstractAlgorithm {

	public:

		SynchronizePositions(Gg::GulgEngine &gulgEngine, const unsigned int pixelInMeter);
		virtual ~SynchronizePositions();

		void apply();

	private:

		const unsigned int m_pixelPerMeter;
};

#endif