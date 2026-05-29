#ifndef QUEST_TABLE_H
#define QUEST_TABLE_H

#include <pokeagb/pokeagb.h>
#include "gui.h"
#include "../config.h"

// Terminator entry: quest_name_ptr == NULL
struct QuestTableEntry{
	void *tile_ptr;       // compressed sprite tile data (NULL = no sprite)
	void *pal_ptr;        // sprite palette data (NULL = no sprite)
	void *quest_name_ptr;
	void *quest_desc_ptr;
	u16 flag_is_available;
	u16 flag_is_completed;
};


#if USE_C_QUESTS
#include "debug_quests.h"
#else
#include "quests.h"
#endif

#define QUEST_IS_UNAVAILABLE 	0
#define QUEST_IS_AVAILABLE 		1
#define QUEST_IS_HIDDEN 		2
#define QUEST_IS_ACCEPTED 		3
#define QUEST_IS_DONE 			4	


u8 check_flag(u16 flag_id);

struct QuestTableEntry empty_quest;

void initGuiQuests(struct QuestGuiInfo * const quest_gui_info);

//returns true if and only if at least one more quest was available, false otherwise
u8 findNextAvailableQuests(struct QuestGuiInfo * const quest_gui_info);

//returns true if and only if at least one more quest was available, false otherwise
u8 findPrevAvailableQuests(struct QuestGuiInfo * const quest_gui_info);

u8 findNextActiveAvailableQuests(struct QuestGuiInfo * const quest_gui_info);
u8 findPrevActiveAvailableQuests(struct QuestGuiInfo * const quest_gui_info);

u8 findNextCompletedAvailableQuests(struct QuestGuiInfo * const quest_gui_info);
u8 findPrevCompletedAvailableQuests(struct QuestGuiInfo * const quest_gui_info);



#endif