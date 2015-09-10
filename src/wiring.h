#pragma once

#include <glm/glm.hpp>

#include "render_data.h"

struct ship_space;

struct wire_attachment {
    glm::mat4 transform;
    unsigned parent;
    unsigned rank;
};

struct wire_segment {
    unsigned first;
    unsigned second;
};

void
draw_attachments(ship_space *ship, frame_data *frame);

void
draw_segments(ship_space *ship, frame_data *frame);

void
reduce_segments(ship_space *ship);

glm::mat4
calc_segment_matrix(const wire_attachment &start, const wire_attachment &end);

unsigned
attach_topo_find(ship_space *ship, unsigned p);

unsigned
attach_topo_unite(ship_space *ship, unsigned from, unsigned to);

void
attach_topo_rebuild(ship_space *ship);