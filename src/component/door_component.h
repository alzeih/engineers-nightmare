#pragma once

/* THIS FILE IS AUTOGENERATED BY gen/gen_component_impl.py; DO NOT HAND-MODIFY */

#include <libconfig.h>

#include "component_manager.h"

struct door_component_stub : component_stub {
    static void register_generator();
};

door_component_stub door_stub_from_config(const config_setting_t *door_config);

struct door_component_manager : component_manager {
    struct instance_data {
        c_entity *entity;
        hw_mesh * *mesh;
        float *pos;
        float *desired_pos;
        int *height;
    } instance_pool;

    void create_component_instance_data(unsigned count) override;
    void destroy_instance(instance i) override;
    void entity(c_entity e) override;

    instance_data get_instance_data(c_entity e) {
        instance_data d;
        auto inst = lookup(e);

        d.entity = instance_pool.entity + inst.index;
        d.mesh = instance_pool.mesh + inst.index;
        d.pos = instance_pool.pos + inst.index;
        d.desired_pos = instance_pool.desired_pos + inst.index;
        d.height = instance_pool.height + inst.index;

        return d;
    }
};
