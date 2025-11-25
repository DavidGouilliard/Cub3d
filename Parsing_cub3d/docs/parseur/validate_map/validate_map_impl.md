# Validator Map – Implémentation (bords + espaces de fin tolérés)

Conforme à `doc.md` : organigrammes ASCII, hiérarchie par niveaux, reflète `src/parser/parse_map/validate_map.c` et `validate_map_utils.c`.

## Vue rapide des appels (Niveau 0)
```
┌──────────────────────────┐
│ validate_map(state)      │
└───────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ garde carte/joueur       │
└───────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ boucle lignes            │
└──────┬─────────┬─────────┘
       │bord     │interne
       ▼         ▼
┌──────────────┐ ┌────────────────┐
│ check_border │ │   scan_row     │
└──────────────┘ └────────────────┘
```

## validate_map (Niveau 1)
```
┌──────────────────────────┐
│ validate_map(state)      │
└───────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ map_lines && height ?    │
│ player_count == 1 ?      │
└──────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ for y in [0..height-1]   │
└──────┬─────────┬─────────┘
       │bord     │interne
       ▼         ▼
┌──────────────┐ ┌────────────────┐
│ check_border │ │   scan_row     │
└──────┬───────┘ └───────┬────────┘
       │ko               │ko
       ▼                 ▼
   ┌────────┐        ┌────────┐
   │erreur  │        │erreur  │
   └────────┘        └────────┘
```

## scan_row (Niveau 1)
```
┌──────────────────────────┐
│ scan_row(st, y)          │
└───────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ line_bounds_ok           │ // trim espaces fin, 1 aux extrémités
└──────┬─────────┬─────────┘
       │ko       │ok
       ▼         ▼
   ┌────────┐ ┌────────────────┐
   │erreur  │ │ len_up/len_down│
   └────────┘ └──────────┬─────┘
                         ▼
┌──────────────────────────┐
│ boucle x ∈ [start,end)   │
└──────┬─────────┬─────────┘
       │espace   │'0'/'1'
       ▼         ▼
┌────────────────┐ ┌────────────────┐
│space_neighbors │ │ zero_position  │
│   _ok          │ │    _ok         │
└──────┬─────────┘ └───────┬────────┘
       │ko                 │ko
       ▼                   ▼
   ┌────────┐          ┌────────┐
   │erreur  │          │erreur  │
   └────────┘          └────────┘
```
Objectif : ne considérer que le contenu utile (après trim des espaces de fin) et refuser tout trou vertical ou voisinage non muré.

## Helpers (Niveau 2)

### line_bounds_ok
```
┌──────────────────────────┐
│ line_bounds_ok(line)     │
└───────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ start = 1er non-espace   │
│ end   = len trim         │
└──────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ line[start] == '1' ?     │
│ line[end-1] == '1' ?     │
└──────┬─────────┬─────────┘
       │non      │oui
       ▼         ▼
   ┌────────┐ ┌────────┐
   │erreur  │ │ success│
   └────────┘ └────────┘
```

### wall_span_ok
```
┌──────────────────────────┐
│ wall_span_ok(line, x)    │
└───────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ chercher '1' à gauche    │
│ et à droite de x         │
└──────┬─────────┬─────────┘
       │manque   │ok
       ▼         ▼
   ┌────────┐ ┌────────┐
   │ false  │ │  true  │
   └────────┘ └────────┘
```
Objectif : valider qu’une colonne est encadrée par des murs sur la ligne même si sa longueur trimée est plus courte que `x`.

### space_neighbors_ok
```
┌──────────────────────────┐
│ space_neighbors_ok(...)  │
└───────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ x>0 et x+1<end ?         │
│ murs haut/bas (wall_span)│
│ up/down/left/right ∈     │
│ {'1',' '} ?              │
└──────┬─────────┬─────────┘
       │non      │oui
       ▼         ▼
   ┌────────┐ ┌────────┐
   │erreur  │ │ success│
   └────────┘ └────────┘
```

### zero_position_ok
```
┌──────────────────────────┐
│ zero_position_ok(...)    │
└──────────┬──────────────┘
            ▼
┌──────────────────────────┐
│ x>0 && x+1<end ?         │
│ murs haut/bas (wall_span)│
└──────┬─────────┬─────────┘
       │non      │oui
       ▼         ▼
   ┌────────┐ ┌────────┐
   │erreur  │ │ success│
   └────────┘ └────────┘
```

## Règles codées
- La carte doit exister et avoir un joueur unique.
- Lignes 0 et dernière : uniquement `'1'` ou espaces.
- Lignes internes : premier/dernier non-espace = `'1'`, calculés après trim des espaces de fin (tolérance aux trailing spaces).
- Un `0` ne peut pas toucher le bord gauche/droit et doit être encadré par des murs au-dessus et au-dessous (recherche de `1` à gauche et à droite sur les lignes voisines).
- Un espace interne doit être entouré de `{ '1',' ' }` (haut, bas, gauche, droite), disposer de murs haut/bas autour de sa colonne, et ne peut pas se trouver sur un bord de contenu.
