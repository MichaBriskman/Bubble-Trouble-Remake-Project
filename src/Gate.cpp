#include "Gate.h"

Gate::Gate(const sf::Vector2f& loc, b2World* world, const sf::Vector2f& scale)
{
	m_sprite.setTexture(*Resources::instance().getTexture(gameObjects::GATE_GO));
	m_sprite.setPosition(loc);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f));
	m_sprite.scale(scale);
	initGate(loc, world);
}
//=======================================================================================
void Gate::initGate(const sf::Vector2f& loc, b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(loc.x, loc.y);
	m_body = world->CreateBody(&bodyDef);

	auto size = m_sprite.getTexture()->getSize();
	b2PolygonShape groundBox;
	groundBox.SetAsBox(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.5;
	fixtureDef.filter.categoryBits = WALL;
	fixtureDef.filter.maskBits = entity::BALL | entity::PLAYER;
	fixtureDef.filter.groupIndex = id_gate++;
	m_fixture = m_body->CreateFixture(&fixtureDef);
}
