#include <epoxy/gl.h>

#include "../asset_manager.h"
#include "../common.h"
#include "../ship_space.h"
#include "../mesh.h"
#include "../player.h"
#include "tools.h"


extern GLuint overlay_shader;
extern GLuint simple_shader;

extern ship_space *ship;

extern asset_manager asset_man;

struct add_block_tool : tool
{
    raycast_info_block rc;

    void pre_use(player *pl) override {
        ship->raycast_block(pl->eye, pl->dir, MAX_REACH_DISTANCE, enter_exit_framing, &rc);
    }

    bool can_use() {
        return rc.hit && !rc.inside;
    }

    void use() override
    {
        if (!can_use())
            return; /* n/a */

        /* ensure we can access this x,y,z */
        ship->ensure_block(rc.p);

        block *bl = ship->get_block(rc.p);

        /* can only build on the side of an existing frame */
        if (bl && rc.block->type == block_frame) {
            bl->type = block_frame;
            /* dirty the chunk */
            ship->get_chunk_containing(rc.p)->render_chunk.valid = false;
            ship->get_chunk_containing(rc.p)->phys_chunk.valid = false;
        }
    }

    void preview(frame_data *frame) override
    {
        if (!can_use())
            return; /* n/a */

        block *bl = ship->get_block(rc.p);

        /* can only build on the side of an existing frame */
        if ((!bl || bl->type == block_empty || bl->type == block_untouched) && rc.block->type == block_frame) {
            auto mesh = asset_man.get_mesh("frame");
            auto material = asset_man.get_world_texture_index("white");

            auto mat = frame->alloc_aligned<mesh_instance>(1);
            mat.ptr->world_matrix = mat_position(glm::vec3(rc.p));
            mat.ptr->material = material;
            mat.bind(1, frame);

            glUseProgram(overlay_shader);
            draw_mesh(mesh.hw);
            glUseProgram(simple_shader);
        }
    }

    void get_description(char *str) override
    {
        strcpy(str, "Place Framing");
    }
};


tool *tool::create_add_block_tool() { return new add_block_tool(); }
