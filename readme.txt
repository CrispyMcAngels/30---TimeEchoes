E' tutto pilotato da una tabella formattata nella struct QuestTableEntry nel file src/include/quest_table.h che riporto per comodità:
Codice:
//sizeof: 0x10
struct QuestTableEntry{
    /*OFF: 0x0 */ u8  oam_id;
    /*OFF: 0x1 */ void *quest_name_ptr;
    /*OFF: 0x5 */ void *quest_desc_ptr;
    
    /*OFF: 0x9 */ u16 flag_is_available;
    /*OFF: 0xB */ u16 flag_is_completed;
    
    /*OFF: 0xD */ u8  filler1; //for the table to be 2-aligned
    /*OFF: 0xE */ u16 filler2; //for the table to be 0x10-aligned (optional)
};

Quindi:
un byte che indica lo sprite da mostrare (se non ricordo male funziona con le dimensioni standard e anche per gli sprite "piccoli" dei bambini),
4 byte di pointer al testo del nome della quest
4 byte di pointer al testo della descrizione della quest
2 byte che indicano la flag di avvio
2 byte che indicano la flag di completamento
3 byte di filler, così è tutto allineato a 16 byte ed è carino da vedere in un hex editor
Quando la flag di avvio è settata la quest viene resa disponibile, quando la flag di completamento è settata puoi immaginare cosa succeda.

C'è anche il file src/config.h da modificare:
QUEST_TABLE_START indica l'offset dove sta la tabella sopracitata (almeno word-aligned, sarebbe carino fosse 0-aligned)
USE_C_QUESTS va messo a 0 per usare la tabella

Per cambiare dove viene inserita la routine c'è da toccare la riga 13 di src/main.s
Va tutto compilato con armips (se non ricordo male 0.11+)