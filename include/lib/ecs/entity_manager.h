#pragma once

#include <game/components/player_control_component.h>
#include <game/components/price_component.h>
#include <game/components/stamp_remove_component.h>
#include <game/components/texture_component.h>
#include <game/components/transform_component.h>

#include <iostream>
#include <map>
#include <memory>

#include "../../game/components/collider_component.h"
#include "lib/ecs/entity.h"
#include "set"
/**
 * Непосредственно класс, отвечающий за все сущности.
 * В его обязанности входит:
 * - создание и удаление сущностей
 * - хранение этих сущностей
 * - получение сущностей по уникальному ID
 */
class EntityManager {
 private:
  std::map<size_t, std::unique_ptr<Entity>> entities_;
  std::set<size_t> toDelete;

  size_t last_entity_id = 1;  // start from 1 to use 0 as a special entity ID

 public:
  Entity* CreateEntity() {
    auto id = ++last_entity_id;
    entities_.emplace(id, std::make_unique<Entity>(id));
    return entities_.at(id).get();
  }
  void DeleteEntity(size_t id) {
    // std::cout << entities_.size() << std::endl;
    entities_.erase(id);
  }
  EntityManager* DeleteAll() {
    entities_.clear();
    return this;
  }
  Entity* Get(size_t id) const {
    if (entities_.count(id) == 0) {
      std::cout << "[WARNING] there is no entity with id=" << id << std::endl;
      return nullptr;
    }
    return entities_.at(id).get();
  }

  /**
   * Completely removes all marked to delete entities with associated components.
   */
  void SweepDeleted() {
    for (auto& entity : toDelete) {
      //  entity.RemoveAllComponents(); TODO(Nariman):
      entities_.erase(entity);
    }
    toDelete.clear();
  }

  void Check() {
    for (auto& entity : entities_) {
      if (entity.second->Contains<StampRemoveComponent>()) {
        entity.second->Delete<TextureComponent>();
        entity.second->Delete<TransformComponent>();
        entity.second->Delete<ColliderComponent>();
        DeleteEntity(entity.first);
      }
    }
  }

  void Have() {
    for (auto& entity : entities_) {
      if (entity.second->Contains<StampRemoveComponent>()) {
        //
      }
    }
  }

  // Entity* Get(std::string name) const {
  // }

  /**
   * Необходим для того, чтобы не выставлять на показ
   * внутреннюю структуру менеджера при итерировании
   * по сущностям
   */
  class Iterator {
    std::map<size_t, std::unique_ptr<Entity>>::iterator iterator_;

   public:
    explicit Iterator(const std::map<size_t, std::unique_ptr<Entity>>::iterator& iterator) : iterator_(iterator) {}

    Iterator operator++() {
      iterator_.operator++();
      return *this;
    }
    Iterator operator++(int step) {
      iterator_.operator++(step);
      return *this;
    }

    Entity& operator*() {
      return *iterator_.operator*().second;
    }

    Entity* operator->() {
      return iterator_.operator*().second.get();
    }

    bool operator==(const Iterator& rhs) {
      return iterator_ == rhs.iterator_;
    }

    bool operator!=(const Iterator& rhs) {
      return iterator_ != rhs.iterator_;
    }
  };

  Iterator begin() {
    return Iterator{entities_.begin()};
  }

  Iterator end() {
    return Iterator{entities_.end()};
  }
};
