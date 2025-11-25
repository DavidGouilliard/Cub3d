# Résumé logique par fonction – validate_map (tolérance aux trailing spaces)

Format “petit 1…” conforme à `doc.md`.

## validate_map
Petit 1 : vérifier que `map_lines` existe, que `map_height > 0` et que `player_count == 1`.  
Petit 2 : boucler sur chaque ligne `y`.  
Petit 3 : si `y` est 0 ou `map_height-1`, refuser tout caractère autre que `'1'` ou espace.  
Petit 4 : sinon appeler `scan_row`; si une règle casse, afficher l’erreur et retourner false.  
Petit 5 : si toutes les lignes passent, retourner true.  
Scénario : une bordure contenant un `0` ou l’absence de joueur unique échoue dès le début.

## scan_row
Petit 1 : `line_bounds_ok` pour trouver `start/end` après trim des espaces de fin et exiger `'1'` au début/à la fin du contenu.  
Petit 2 : boucler `x` de `start` à `end-1` et déléguer à `handle_cell`.  
Petit 3 : `handle_cell` refuse un espace si un voisin N/E/S/O n’est pas dans `{ '1',' ' }` ou si la colonne `x` n’est pas encadrée par des murs au-dessus et au-dessous (via `wall_span_ok`).  
Petit 4 : `handle_cell` refuse un `0` collé au bord gauche/droit ou si aucune paire de murs haut/bas n’encadre la colonne `x`.  
Scénario : une ligne avec des espaces de fin est acceptée (non comptés), et un bloc décalé mais fermé par des `1` au-dessus/dessous passe ; une colonne sans mur haut/bas échoue “Carte non fermee verticalement”.

## line_bounds_ok
Petit 1 : avancer `start` jusqu’au premier caractère non-espace.  
Petit 2 : reculer `end` pour ignorer les espaces de fin.  
Petit 3 : si la ligne est vide ou si `line[start]` ou `line[end-1]` ne valent pas `'1'`, afficher “Carte non fermee sur les bords” et retourner false.  
Petit 4 : sinon, retourner true avec `start/end` prêts pour la boucle.  
Scénario : `"11111   "` passe (`end` ignore les espaces), `"  0  "` échoue.

## space_neighbors_ok
Petit 1 : refuser si `x==0` ou `x+1>=end` (espace en bout de contenu).  
Petit 2 : vérifier `wall_span_ok` sur les lignes haut/bas pour s’assurer qu’un mur existe à gauche et à droite autour de `x`.  
Petit 3 : lire `up/down/left/right` (les indices hors longueur trimée valent `' '`) et refuser si un voisin n’appartient pas à `{ '1',' ' }`.  
Scénario : un espace adjacent à un `0` ou dont la colonne n’est pas encadrée par des `1` sur les lignes du dessus/dessous déclenche “Carte non fermee verticalement” ou “Espace adjacent a vide”.

## zero_position_ok
Petit 1 : refuser si `x==0` ou `x+1>=end` (bord gauche/droit).  
Petit 2 : refuser si `wall_span_ok` échoue sur la ligne du haut ou du bas pour la colonne `x` (pas de mur à gauche/droite sur ces lignes).  
Petit 3 : sinon true.  
Scénario : un `0` placé en colonne finale ou sous une ligne qui n’a pas de `1` encadrant `x` échoue avec “Carte non fermee verticalement”.
