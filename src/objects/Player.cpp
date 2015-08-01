#include "Player.hpp"
#include "../InputHandler.hpp"

Player::Player() : m_position(Vector2D(0, 0)) {
    // empty
}

Player::~Player() {
    // empty
}

void Player::update(unsigned int deltaTime) {
    m_moveSpeed = 5.0 * (deltaTime / 1000.0);
    m_rotSpeed = 3.0 * (deltaTime / 1000.0);
}

void Player::clean() {
    // empty
}

void Player::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_dirX = 1;
    m_dirY = 1;
    m_moveSpeed = 0;
    m_rotSpeed = 0;
}

void Player::alterPosition(const double x, const double y) {
    Vector2D addVector = Vector2D(x, y);
    m_position += addVector;
}

void Player::moveSteps(int x, int y) {
    alterPosition(x * m_dirX * m_moveSpeed, y * m_dirY * m_moveSpeed);
}

double Player::nextStepX(bool back) {
    int dir = back ? -4 : 4;
    Vector2D futurePos = m_position + Vector2D(dir * m_dirX * m_moveSpeed, 0);
    return futurePos.getX();
}

double Player::nextStepY(bool back) {
    int dir = back ? -4 : 4;
    Vector2D futurePos = m_position + Vector2D(0, dir * m_dirY * m_moveSpeed);
    return futurePos.getY();
}

