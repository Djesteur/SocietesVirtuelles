#include "Algorithms/Graphics/SynchronizePositions.hpp"

SynchronizePositions::SynchronizePositions(Gg::GulgEngine &gulgEngine, const unsigned int pixelPerMeter): 
	AbstractAlgorithm{gulgEngine},
	m_pixelPerMeter{pixelPerMeter} {

	m_signature = gulgEngine.getComponentSignature("Position");
	m_signature += gulgEngine.getComponentSignature("Sprite");
}

SynchronizePositions::~SynchronizePositions() {}

void SynchronizePositions::apply() {

	for(Gg::Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Gg::Component::Sprite> sprite{ 
			std::static_pointer_cast<Gg::Component::Sprite>(m_gulgEngine.getComponent(currentEntity, "Sprite"))
		};

		std::shared_ptr<Gg::Component::Vector2D> position{ 
			std::static_pointer_cast<Gg::Component::Vector2D>(m_gulgEngine.getComponent(currentEntity, "Position"))
		};


		sprite->sprite.setPosition(sf::Vector2f{position->value.x*m_pixelPerMeter, position->value.y*m_pixelPerMeter});
	}
}