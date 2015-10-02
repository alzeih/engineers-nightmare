#pragma once

/* THIS FILE IS AUTOGENERATED BY gen/gen_component_impl.py; DO NOT HAND-MODIFY */

#include "component_manager.h"

struct relative_position_component_manager : component_manager {
    struct instance_data {
        c_entity *entity;
        glm::vec3 *position;
        glm::mat4 *mat;
    } instance_pool;

    void create_component_instance_data(unsigned count) override;
    void destroy_instance(instance i) override;
    void entity(c_entity const &e) override;

    glm::vec3 & position(c_entity const &e) {
        auto inst = lookup(e);
        return instance_pool.position[inst.index];
    }
    glm::mat4 & mat(c_entity const &e) {
        auto inst = lookup(e);
        return instance_pool.mat[inst.index];
    }
};
