#include "World.h"
#include "Ball.hpp"
#include "Color.h"
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include <algorithm>
#include <fstream>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {
    std::ifstream stream(worldFilePath);

    // Чтение границ мира — можно тоже улучшить
    stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    physics.setWorldBox(topLeft, bottomRight);

    Point center;
    Point velocity_point; // читаем vx, vy как Point
    Color color;
    double radius;
    bool isCollidable;

    while (stream.peek(), stream.good()) {
        stream >> center >> velocity_point;
        stream >> color;
        stream >> radius;
        stream >> std::boolalpha >> isCollidable;

        Velocity velocity{velocity_point.x, velocity_point.y};
        balls.emplace_back(center, velocity, radius, color, isCollidable);
    }
    physics.setWorld(this);
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    for (const Ball& ball : balls) {
        ball.draw(painter);
    }

    // Рисуем частицы
    for (const Dust& dust : dustParticles) {
        dust.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double dt) { // dt — время с прошлого кадра
    restTime += dt;
    const auto ticks = static_cast<size_t>(std::floor(restTime / timePerTick));
    const double timeUsed = static_cast<double>(ticks) * timePerTick;
    restTime -= timeUsed;

    physics.update(balls, ticks);
    updateDust(dt); // ← частицы обновляются за dt
}

void World::addDust(const Dust& dust) {
    dustParticles.push_back(dust);
}

void World::updateDust(double dt) {
    // Обновляем все частицы
    for (auto& dust : dustParticles) {
        dust.update(dt);
    }
    // Удаляем "мёртвые" частицы
    dustParticles.erase(
        std::remove_if(dustParticles.begin(), dustParticles.end(),
                       [](const Dust& d) { return !d.isAlive(); }),
        dustParticles.end());
}
