#pragma once

/* THIS FILE IS AUTOGENERATED BY gen/gen_component_impl.py; DO NOT HAND-MODIFY */

#include "component_manager.h"

struct type_component_manager : component_manager {
    struct instance_data {
        c_entity *entity;
        unsigned *type;
    } instance_pool;

    void create_component_instance_data(unsigned count) override;
    void destroy_instance(instance i) override;
    void entity(c_entity e) override;

    unsigned & type(c_entity e) {
        auto inst = lookup(e);
        return instance_pool.type[inst.index];
    }
};
