#ifndef BASIC_COMPONENTS_HPP
#define BASIC_COMPONENTS_HPP

#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Components/Component.hpp"

namespace Gg {

namespace Component {

struct Boolean: public AbstractComponent {

	Boolean(): value{false} {}

	Boolean(const bool val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<Boolean>(*this)); }

	bool value;          
};

struct UnsignedInt: public AbstractComponent {

	UnsignedInt(): value{0} {}

	UnsignedInt(const unsigned int val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<UnsignedInt>(*this)); }

	unsigned int value;          
};

struct Integer: public AbstractComponent {

	Integer(): value{0} {}

	Integer(const int val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<Integer>(*this)); }

	int value;          
};

struct Float: public AbstractComponent {

	Float(): value{0.f} {}

	Float(const float val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<Float>(*this)); }

	float value;          
};


struct EntityComponent: public AbstractComponent {

	EntityComponent(): value{0} {}

	EntityComponent(const Entity val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<EntityComponent>(*this)); }

	Entity value;          
};

struct String: public AbstractComponent {

	String(): value{""} {}

	String(const std::string val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<String>(*this)); }

	std::string value;          
};

struct Vector2D: public AbstractComponent {

	Vector2D(): value{0.f, 0.f} {}
	Vector2D(sf::Vector2f v): value{v} {}
	Vector2D(const float x, const float y): value{x, y} {}
	Vector2D(const Vector2D &vec): value{vec.value} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<Vector2D>(*this)); }

	float norm() { return sqrt(value.x*value.x + value.y*value.y); }
	sf::Vector2f value;          
};

}}

#endif