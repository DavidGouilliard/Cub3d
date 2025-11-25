# Revue de Conception Narrative – validate_map.c

## 1. But du module
- Vérifier que la carte collectée par `parse_map` est fermée, en autorisant les espaces de fin de ligne (trailing spaces) mais en refusant toute fuite verticale ou latérale.
- Ne modifie pas la carte : uniquement des lectures et des messages d’erreur via `print_error`.
- Double-check “un seul joueur” avant toute validation de géométrie.

## 2. Structures importantes
- `t_parser_state` : lecture seule de `map_lines`, `map_height`, `map_width` (indirect via `trimmed_len`) et `player_count`.
- Helpers utilitaires :
  - `trimmed_len` calcule la longueur sans les espaces de fin, ce qui permet d’accepter des lignes avec padding.
  - `wall_span_ok` repère, pour une colonne donnée, s’il existe un `1` à gauche et à droite sur la même ligne (utilisé pour tolérer des blocs décalés).

## 3. Fonctions principales
### 3.1 validate_map(t_parser_state *state)
- **Objectif** : orchestrer les contrôles de fermeture.
- **Stratégie** :
  - Rejette si carte absente ou joueur ≠ 1.
  - Parcourt toutes les lignes : bords haut/bas via `check_border_line`, lignes internes via `scan_row`.
  - Stoppe au premier échec en renvoyant `false`.
- **Ce que ça modifie** : rien.
- **Exemple** : une première ligne contenant un `0` déclenche “Carte ouverte sur le bord”.

### 3.2 check_border_line(const char *line)
- **Objectif** : garantir que la première et la dernière ligne ne contiennent que des `1` ou des espaces.
- **Stratégie** : boucle sur chaque caractère ; tout autre symbole → erreur.
- **Exemple** : `"11111   "` passe, `"1111 0"` échoue.

### 3.3 scan_row(t_parser_state *st, size_t y)
- **Objectif** : valider une ligne interne en ignorant les espaces de fin.
- **Stratégie** :
  - `line_bounds_ok` trim les espaces de fin, impose `'1'` comme premier et dernier caractère utile, et renvoie `start/end`.
  - Parcourt `x` de `start` à `end-1` et délègue à `handle_cell`.
  - `handle_cell` refuse un espace si la colonne `x` n’est pas encadrée par des murs sur les lignes haut/bas (`wall_span_ok`) ou si un voisin N/E/S/O sort de `{1,' '}`. Refuse un `0` collé aux bords gauche/droit ou sans murs haut/bas autour de `x`.
- **Exemple** : une ligne avec des espaces finaux est acceptée, et un bloc décalé mais fermé par des `1` au-dessus/dessous passe ; une colonne sans mur haut/bas échoue “Carte non fermee verticalement”.

## 4. Guide de lecture du code
1. Lire `validate_map` pour l’orchestration et les gardes initiales.
2. Voir `check_border_line` pour comprendre les exigences des bords haut/bas.
3. Parcourir `scan_row` et `handle_cell` pour suivre l’ordre des contrôles (trim, murs haut/bas via `wall_span_ok`, voisinage).
4. Observer `trimmed_len`/`wall_span_ok` dans `validate_map_utils.c` pour voir comment on tolère des blocs décalés tout en recherchant des murs.

## 5. Check-list de compréhension
- Je sais que les espaces de fin de ligne sont tolérés (trim) mais qu’un espace interne doit être entouré de murs/espaces et encadré par des murs haut/bas à sa colonne.
- Je sais qu’un `0` doit être encadré à gauche/droite et reposer sur des lignes haut/bas qui ont des murs de part et d’autre de cette colonne.
- Je sais que les bords haut/bas acceptent seulement `1` ou espace.
- Je sais que `validate_map` ne modifie rien et s’arrête dès la première anomalie.

## Pièges / invariants importants
- `player_count` doit valoir 1 avant la validation.
- Une ligne vide ou composée uniquement d’espaces échoue car `line_bounds_ok` impose des `'1'` en début/fin de contenu.
- Les checks utilisent des longueurs “trim” : un débordement vertical se calcule sur le contenu réel, pas sur les espaces de padding, mais on accepte un bloc décalé si des murs encadrent la colonne (via `wall_span_ok`).  
