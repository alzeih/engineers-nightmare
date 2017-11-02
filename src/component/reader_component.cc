#include <algorithm>
#include <string.h>
#include "../memory.h"
#include "reader_component.h"

/* THIS FILE IS AUTOGENERATED BY gen/gen_component_impl.py; DO NOT HAND-MODIFY */

reader_component_stub
reader_component_from_config(const config_setting_t *reader_config) {
    reader_component_stub reader_stub{};

    auto name_member = config_setting_get_member(reader_config, "name");
    reader_stub.name = config_setting_get_string(name_member);

    auto desc_member = config_setting_get_member(reader_config, "desc");
    reader_stub.desc = config_setting_get_string(desc_member);

    return reader_stub;
};

extern std::unordered_map<std::string, std::function<component_stub(config_setting_t *)>> component_stub_generators;

void
reader_component_stub::register_generator() {
    component_stub_generators["reader"] = reader_component_from_config;
}

void
reader_component_manager::create_component_instance_data(unsigned count) {
    if (count <= buffer.allocated)
        return;

    component_buffer new_buffer;
    instance_data new_pool;

    size_t size = sizeof(c_entity) * count;
    size = sizeof(char const *) * count + align_size<char const *>(size);
    size = sizeof(c_entity) * count + align_size<c_entity>(size);
    size = sizeof(char const *) * count + align_size<char const *>(size);
    size = sizeof(float) * count + align_size<float>(size);
    size += 16;   // for worst-case misalignment of initial ptr

    new_buffer.buffer = malloc(size);
    new_buffer.num = buffer.num;
    new_buffer.allocated = count;
    memset(new_buffer.buffer, 0, size);

    new_pool.entity = align_ptr((c_entity *)new_buffer.buffer);
    new_pool.name = align_ptr((char const * *)(new_pool.entity + count));
    new_pool.source = align_ptr((c_entity *)(new_pool.name + count));
    new_pool.desc = align_ptr((char const * *)(new_pool.source + count));
    new_pool.data = align_ptr((float *)(new_pool.desc + count));

    memcpy(new_pool.entity, instance_pool.entity, buffer.num * sizeof(c_entity));
    memcpy(new_pool.name, instance_pool.name, buffer.num * sizeof(char const *));
    memcpy(new_pool.source, instance_pool.source, buffer.num * sizeof(c_entity));
    memcpy(new_pool.desc, instance_pool.desc, buffer.num * sizeof(char const *));
    memcpy(new_pool.data, instance_pool.data, buffer.num * sizeof(float));

    free(buffer.buffer);
    buffer = new_buffer;

    instance_pool = new_pool;
}

void
reader_component_manager::destroy_instance(instance i) {
    auto last_index = buffer.num - 1;
    auto last_entity = instance_pool.entity[last_index];
    auto current_entity = instance_pool.entity[i.index];

    instance_pool.entity[i.index] = instance_pool.entity[last_index];
    instance_pool.name[i.index] = instance_pool.name[last_index];
    instance_pool.source[i.index] = instance_pool.source[last_index];
    instance_pool.desc[i.index] = instance_pool.desc[last_index];
    instance_pool.data[i.index] = instance_pool.data[last_index];

    entity_instance_map[last_entity] = i.index;
    entity_instance_map.erase(current_entity);

    --buffer.num;
}

void
reader_component_manager::entity(c_entity e) {
    if (buffer.num >= buffer.allocated) {
        printf("Increasing size of reader buffer. Please adjust\n");
        create_component_instance_data(std::max(1u, buffer.allocated) * 2);
    }

    auto inst = lookup(e);

    instance_pool.entity[inst.index] = e;
}
