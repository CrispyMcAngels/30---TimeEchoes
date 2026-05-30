E' tutto pilotato da una tabella formattata nella struct QuestTableEntry nel file src/include/quest_table.h che riporto per comodità:
Codice:
struct QuestTableEntry{
    void *tile_ptr;         // pointer ai tile compressi LZ77 dello sprite 64x64 (NULL = nessuno sprite)
    void *pal_ptr;          // pointer alla palette compressa LZ77 dello sprite (NULL = nessuno sprite)
    void *quest_name_ptr;   // pointer al nome della quest (NULL = fine tabella)
    void *quest_desc_ptr;   // pointer alla descrizione della quest
    u16 flag_is_available;  // flag che rende la quest disponibile
    u16 flag_is_completed;  // flag che segna la quest come completata
};

Quindi:
- tile_ptr e pal_ptr puntano ai dati dello sprite da mostrare per la quest, compressi in LZ77.
  Gli sprite devono essere 64x64 pixel. Se entrambi sono NULL non viene mostrato nessuno sprite.
- quest_name_ptr punta al testo del nome della quest in encoding Gen 3.
  Un entry con quest_name_ptr == NULL funge da terminatore della tabella.
- quest_desc_ptr punta al testo della descrizione della quest.
- flag_is_available: quando settata la quest diventa visibile nella modalità "attive".
- flag_is_completed: quando settata la quest appare nella modalità "completate".

--- Comportamento tasto A ---
Premendo A su una quest in modalità "attive":
- Se la flag 0x11 è settata, viene impostata la variabile 0x4067 al valore dell'indice 1-based della quest nella tabella.
- Se la flag 0x11 NON è settata, nella casella descrizione appare il messaggio di errore in rosso:
  "Errore, devi avvicinarti alla statua"
  Il messaggio rimane visibile finché non si preme A o B.

--- Navigazione ---
- LEFT/RIGHT: sposta il cursore tra le quest della pagina corrente.
- L/R: cambia pagina.
- SELECT: alterna tra modalità "attive" e "completate".
- B: chiude la GUI.

--- File di configurazione: src/config.h ---
QUEST_TABLE_START: offset ROM dove si trova la tabella delle quest (usato solo se USE_C_QUESTS=0).
USE_C_QUESTS: impostare a 1 per usare la tabella definita in C (src/include/debug_quests.c),
              impostare a 0 per usare la tabella all'offset QUEST_TABLE_START nella ROM.

--- Punto di iniezione ---
L'offset di iniezione della routine è definito in src/main.s (attualmente 0x0883F6C0).
La GUI va invocata da script con: callasm 0x0883F6C1
Il dirottamento del menu start è stato rimosso.

--- Compilazione ---
Compilare con: python scripts/build2
Richiede devkitARM e armips (0.11+). Il percorso di armips è hardcoded in scripts/build2.