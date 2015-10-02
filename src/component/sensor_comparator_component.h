#pragma once

/* THIS FILE IS AUTOGENERATED BY gen/gen_component_impl.py; DO NOT HAND-MODIFY */

#include "component_manager.h"

struct sensor_comparator_component_manager : component_manager {
    struct instance_data {
        c_entity *entity;
        float *compare_result;
        float *compare_epsilon;
    } instance_pool;

    void create_component_instance_data(unsigned count) override;
    void destroy_instance(instance i) override;
    void entity(c_entity const &e) override;

    float & compare_result(c_entity const &e) {
        auto inst = lookup(e);
        return instance_pool.compare_result[inst.index];
    }
    float & compare_epsilon(c_entity const &e) {
        auto inst = lookup(e);
        return instance_pool.compare_epsilon[inst.index];
    }
};
