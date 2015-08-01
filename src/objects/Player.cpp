#include "Player.hpp"
#include "../InputHandler.hpp"

Player::Player() : m_position(Vector2D(0, 0)) {
    // empty
}

Player::~Player() {
    std::cout << "Destruction\n";
}

void Player::update(unsigned int deltaTime) {
}

void Player::clean() {

}

void Player::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_dirX = 1;
    m_dirY = 1;
}

void Player::alterPosition(const double x, const double y) {
    Vector2D addVector = Vector2D(x, y);
    m_position += addVector;
}

