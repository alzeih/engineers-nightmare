#pragma once

/* THIS FILE IS AUTOGENERATED BY gen/gen_component_impl.py; DO NOT HAND-MODIFY */

#include <libconfig.h>
#include <memory>

#include "component_manager.h"

struct pressure_sensor_component_manager : component_manager {
    struct instance_data {
        c_entity *entity;
        float *pressure;
        unsigned *type;
    } instance_pool;

    void create_component_instance_data(unsigned count) override;
    void destroy_instance(instance i) override;
    void entity(c_entity e) override;

    void register_stub_generator();

    instance_data get_instance_data(c_entity e) {
        instance_data d{};
        auto inst = lookup(e);

        d.entity = instance_pool.entity + inst.index;
        d.pressure = instance_pool.pressure + inst.index;
        d.type = instance_pool.type + inst.index;

        return d;
    }

    static pressure_sensor_component_manager* get_manager() {
        return dynamic_cast<pressure_sensor_component_manager*>(::component_managers["pressure_sensor"].get());
    }
};

struct pressure_sensor_component_stub : component_stub {
    pressure_sensor_component_stub() : component_stub("pressure_sensor") {}

    unsigned type{};

    void
    assign_component_to_entity(c_entity entity) override {
        auto man = dynamic_cast<pressure_sensor_component_manager*>(std::move(::component_managers[component_name]).get());

        man->assign_entity(entity);
        auto data = man->get_instance_data(entity);        

        *data.pressure = 0;

        *data.type = 0;

        *data.type = type;
  };
};
