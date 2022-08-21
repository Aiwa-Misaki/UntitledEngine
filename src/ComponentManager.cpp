//
// Created by 克莉斯丁 on 2022/8/19.
//

#include "ComponentManager.h"
type const ComponentManager::int_type=type::get<int>();
type const ComponentManager::vec3_type=type::get<glm::vec3>();
type const ComponentManager::str_type=type::get<string>();
type const ComponentManager::mesh_type=type::get<shared_ptr<Mesh>>();