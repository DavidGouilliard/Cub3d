# Analyse – subject_map.cub rejetée

## Pourquoi le parser refuse cette carte

1. La carte du sujet contient un bloc additionnel sur les lignes 10→13 :
   ```
           11111
           10001
           10001
           11111
   ```
   Ce bloc est collé à droite de la carte principale, séparé par une colonne d’espaces.
2. Notre fonction `scan_row` (cf. `src/parser/parse_map/validate_map.c`) considère qu’un espace interne est valide uniquement si la ligne du dessus et la ligne du dessous possèdent un caractère à la même colonne (`x < len_up` et `x < len_down`). Sinon, elle interprète cette colonne comme une “fuite verticale”.
3. Sur les lignes 10 à 12 du sujet, la ligne du dessus/dessous est plus courte (après trim des espaces de fin) que la position `x` du bloc additionnel. Résultat : la condition `x >= len_up` est vraie, donc on retourne l’erreur “Carte non fermee verticalement”.

En clair : le parser assimile toute zone située après la longueur de la ligne supérieure (ou inférieure) à un trou ouvert. Même si le bloc additionnel est entièrement fermé par des `1`, on ne le voit pas, car on ne cherche pas de murs plus loin sur la même ligne.

## Proposition d’amélioration

1. **Segmenter chaque ligne en “murs” et “vides”** : au lieu de comparer uniquement les longueurs trimées, on inspecte la ligne du dessus et/ou du dessous à la recherche du premier `1` vers la gauche et du premier `1` vers la droite autour de la colonne `x`. Si ces murs existent, on considère que la zone est refermée verticalement.
2. **Mini flood-fill local** : lorsqu’un espace dépasse `len_up`/`len_down`, lancer un flood limité à partir de cette colonne pour vérifier s’il peut rejoindre l’extérieur. Si le flood reste confiné par des `1`, on accepte la zone ; sinon on garde l’erreur.
3. **Option plus simple** : adopter un padding artificiel (ajouter des `1` virtuels) côté droit/gauche pour chaque ligne en prolongeant la plus longue ligne. Cela revient à reconstituer la grille rectangulaire et à vérifier les voisins dans cette grille – équivalent à un flood-fill “extérieur” mais sans gérer la pile manuellement.

Ces pistes permettraient au parser d’accepter des cartes composées de blocs fermés mais non strictement alignés, comme celle du sujet, tout en conservant la détection de véritables fuites (zones ouvertes vers l’extérieur).

## Mise en œuvre actuelle
- La première piste est désormais en place : `wall_span_ok` vérifie qu’une colonne est encadrée par des `1` sur les lignes du dessus/dessous, même si la longueur trimée est plus courte.  
- `space_neighbors_ok` et `zero_position_ok` s’appuient sur cette détection pour accepter des blocs décalés mais fermés (comme celui des lignes 10→13) et continuent de refuser les vraies fuites verticales.
