#ifndef SPRITE_UTIL_C
#define SPRITE_UTIL_C

#include "sprite_util.h"

void gpu_tile_obj_decompress_alloc_tag_and_upload_small_decompression_buffer(struct SpriteTiles* tile);

u8 display_sprite(u8 sprite_w, u8 sprite_h, u8 sprite_x, u8 sprite_y,
					u16 tiles_tag, void *ptr_to_tile,
					u16 pals_tag,  void *ptr_to_pal,
					u8 filp_h, u8 flip_v){
						
	struct ShapeSize shsi = shapeSizeFromWidthAndHeight(sprite_w, sprite_h);
	const struct OamData map_data = {
		.affine_mode = 0,
		.y = 0,
		.obj_mode = 0,
		.mosaic = 0,
		.bpp = 0,
		.shape = shsi.shape,
		.x = 0,
		.matrix_num = 0,
		.h_flip = filp_h,
		.v_flip = flip_v,
		.size = shsi.size, 
		.tile_num = 0,
		.priority = 2, 
		.palette_num = 0,
		.affine_param = 0,
	};
	
	struct SpriteTiles tiles = {ptr_to_tile, sprite_w * sprite_h, tiles_tag};
	struct SpritePalette pals = {ptr_to_pal, pals_tag};
	struct Template icon_template = {
									.tiles_tag = tiles_tag,
									.pal_tag = pals_tag,
									.oam = &map_data,
									.animation = (const struct Frame (**)[])0x8231CF0,
									.graphics = &tiles,
									.rotscale = (const struct RotscaleFrame (**)[])0x8231CFC,
									.callback = oac_nullsub,
									};
	gpu_tile_obj_alloc_tag_and_upload(&tiles);
	gpu_pal_obj_alloc_tag_and_apply(&pals);
	
	return template_instanciate_forward_search(&icon_template, sprite_x, sprite_y, 0);
}



u8 display_compressed_sprite(u8 sprite_w, u8 sprite_h, u8 sprite_x, u8 sprite_y,
								u16 tiles_tag, void *ptr_to_tile,
								u16 pals_tag,  void *ptr_to_pal,
								u8 filp_h, u8 flip_v){
						
	struct ShapeSize shsi = shapeSizeFromWidthAndHeight(sprite_w, sprite_h);
	const struct OamData map_data = {
		.y = 0,
		.affine_mode = 0,
		.obj_mode = 0,
		.mosaic = 0,
		.bpp = 0,
		.shape = shsi.shape,
		.x = 0,
		.matrix_num = 0,
		.h_flip = filp_h,
		.v_flip = flip_v,
		.size = shsi.size, 
		.tile_num = 0,
		.priority = 2, 
		.palette_num = 0,
		.affine_param = 0,
	};
	
	struct SpriteTiles tiles = {ptr_to_tile, sprite_w * sprite_h, tiles_tag};
	struct SpritePalette pals = {ptr_to_pal, pals_tag};
	struct Template icon_template = {
									.tiles_tag = tiles_tag,
									.pal_tag = pals_tag,
									.oam = &map_data,
									.animation = (const struct Frame (**)[])0x8231CF0,
									.graphics = &tiles,
									.rotscale = (const struct RotscaleFrame (**)[])0x8231CFC,
									.callback = oac_nullsub,
									};
	gpu_tile_obj_decompress_alloc_tag_and_upload_small_decompression_buffer(&tiles);
	gpu_pal_obj_alloc_tag_and_apply(&pals);
	
	return template_instanciate_forward_search(&icon_template, sprite_x, sprite_y, 0);
}

u8 display_sprite_from_offset(void *tile_ptr, void *pal_ptr, u8 sprite_x, u8 sprite_y, u8 tiles_tag, u8 pals_tag){
	struct ShapeSize shsi = shapeSizeFromWidthAndHeight(64, 64);
	const struct OamData map_data = {
		.y = 0,
		.affine_mode = 0,
		.obj_mode = 0,
		.mosaic = 0,
		.bpp = 0,
		.shape = shsi.shape,
		.x = 0,
		.matrix_num = 0,
		.h_flip = 0,
		.v_flip = 0,
		.size = shsi.size,
		.tile_num = 0,
		.priority = 2,
		.palette_num = 0,
		.affine_param = 0,
	};
	struct SpriteTiles tiles = {tile_ptr, 64 * 64, tiles_tag};
	struct SpritePalette pals = {pal_ptr, pals_tag};
	struct Template icon_template = {
									.tiles_tag = tiles_tag,
									.pal_tag = pals_tag,
									.oam = &map_data,
									.animation = (const struct Frame (**)[])0x8231CF0,
									.graphics = &tiles,
									.rotscale = (const struct RotscaleFrame (**)[])0x8231CFC,
									.callback = oac_nullsub,
									};
	gpu_tile_obj_decompress_alloc_tag_and_upload_small_decompression_buffer(&tiles);
	gpu_pal_decompress_alloc_tag_and_upload(&pals);
	return template_instanciate_forward_search(&icon_template, sprite_x, sprite_y, 0);
}

#endif