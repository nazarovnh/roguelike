#pragma once
#include "lib/ecs/component.h"

/**
 * Иногда компоненты могут не иметь полей в принципе.
 * В таком случае такие компоненты выступают как тэги, которые
 * используются системами для определения типа сущности
 */
class ObstacleComponent : IComponent {
    // Nothing to do, because it's a tag for systems
};
