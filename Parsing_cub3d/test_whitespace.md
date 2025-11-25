# État du parser après `parse_map` – `map/good/test_whitespace.cub`

- map_height : 13 (lignes poussées avant la première ligne vide).
- map_width : 21 (max de la ligne 2).
- Joueur : player_dir='S', player_x=2, player_y=2 (le S est remplacé par 0 dans map_lines).

map_lines tels que stockés après parse_map (espaces de fin conservés, S → 0) :

idx len content (trailing spaces)
0   5   "11111" (0)
1   5   "10001" (0)
2   21  "10001                " (16)
3   5   "10001" (0)
4   5   "10001" (0)
5   5   "10001" (0)
6   20  "11001               " (15)
7   5   "10001" (0)
8   5   "10001" (0)
9   5   "10001" (0)
10  5   "10001" (0)
11  5   "10001" (0)
12  16  "11111           " (11)

Notes :
- parse_map arrête l’ajout de lignes dès la première ligne vide : les nombreuses lignes vides en fin de fichier ne sont pas dans map_lines.
- map_width est la longueur maximale rencontrée pendant le push (len ci-dessus).
