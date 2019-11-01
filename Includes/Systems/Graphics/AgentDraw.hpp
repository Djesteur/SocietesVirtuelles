#ifndef AGENT_DRAW_HPP
#define AGENT_DRAW_HPP

#include <SFML/Graphics.hpp>

#include "Systems/AbstractSystem.hpp"
#include "Algorithms/Graphics/DrawSprite.hpp"

class AgentDraw: public Gg::Systems::AbstractSystem {

	public:

		AgentDraw(sf::RenderTarget &renderTarget, Gg::GulgEngine &gulgEngine);
		
		virtual ~AgentDraw(); 

	protected:

};


#endif