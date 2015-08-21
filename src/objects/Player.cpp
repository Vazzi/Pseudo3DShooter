#include "Player.hpp"
#include "../InputHandler.hpp"

Player* Player::s_pInstance = 0;

Player::Player() : m_position(Vector2D(0, 0)) {
    m_health = 100;
    m_dirX = 1;
    m_dirY = 1;
    m_planeX = 0;
    m_planeY = 0.66;
}

Player::~Player() {
    // empty
}

void Player::update(unsigned int deltaTime) {
    m_moveSpeed = 5.0 * (deltaTime / 1000.0);
    m_rotSpeed = 3.0 * (deltaTime / 1000.0);
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        rotateLeft();
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        rotateRight();
    }
}

void Player::clean() {
    // empty
}

void Player::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
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

void Player::rotateLeft() {
    rotate(-1);
}

void Player::rotateRight() {
    rotate(1);
}

void Player::hit(int damage) {
    m_health -= damage;
}

void Player::rotate(int sign) {
    double oldm_dirX = m_dirX;
    m_dirX = m_dirX * cos(sign * m_rotSpeed) - m_dirY * sin(sign * m_rotSpeed);
    m_dirY = oldm_dirX * sin(sign * m_rotSpeed) + m_dirY * cos(sign * m_rotSpeed);
    double oldm_planeX = m_planeX;
    m_planeX = m_planeX * cos(sign * m_rotSpeed) - m_planeY * sin(sign * m_rotSpeed);
    m_planeY = oldm_planeX * sin(sign * m_rotSpeed) + m_planeY * cos(sign * m_rotSpeed);
}



