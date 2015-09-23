#include <algorithm>
#include "../memory.h"
#include "pressure_sensor_component.h"

void
pressure_sensor_component_manager::create_component_instance_data(unsigned count) {
    if (count <= buffer.allocated)
        return;

    component_buffer new_buffer;
    instance_data new_pool;

    size_t size = sizeof(c_entity) * count;
    size = sizeof(float) * count + align_size<float>(size);
    size = sizeof(unsigned) * count + align_size<unsigned>(size);
    size += alignof(c_entity);  // for worst-case misalignment of initial ptr

    new_buffer.buffer = malloc(size);
    new_buffer.num = buffer.num;
    new_buffer.allocated = count;
    memset(new_buffer.buffer, 0, size);

    new_pool.entity = align_ptr((c_entity *)new_buffer.buffer);
    new_pool.pressure = align_ptr((float *)(new_pool.entity + count));
    new_pool.type = align_ptr((unsigned *)(new_pool.pressure + count));

    memcpy(new_pool.entity, instance_pool.entity, buffer.num * sizeof(c_entity));
    memcpy(new_pool.pressure, instance_pool.pressure, buffer.num * sizeof(float));
    memcpy(new_pool.type, instance_pool.type, buffer.num * sizeof(unsigned));

    free(buffer.buffer);
    buffer = new_buffer;

    instance_pool = new_pool;
}

void
pressure_sensor_component_manager::destroy_instance(instance i) {
    auto last_index = buffer.num - 1;
    auto last_entity = instance_pool.entity[last_index];
    auto current_entity = instance_pool.entity[i.index];

    instance_pool.entity[i.index] = instance_pool.entity[last_index];
    instance_pool.pressure[i.index] = instance_pool.pressure[last_index];
    instance_pool.type[i.index] = instance_pool.type[last_index];

    entity_instance_map[last_entity] = i.index;
    entity_instance_map.erase(current_entity);

    --buffer.num;
}

void
pressure_sensor_component_manager::entity(const c_entity& e) {
    if (buffer.num >= buffer.allocated) {
        printf("Increasing size of switch buffer. Please adjust\n");
        create_component_instance_data(std::max(1u, buffer.allocated) * 2);
    }

    auto inst = lookup(e);

    instance_pool.entity[inst.index] = e;
}
