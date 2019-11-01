#include "Systems/Graphics/AgentDraw.hpp"

AgentDraw::AgentDraw(sf::RenderTarget &m_renderTarget, Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<Gg::Algorithm::DrawSprite>(m_renderTarget, std::string{"Sprite"}, gulgEngine));
}

AgentDraw::~AgentDraw() {}
