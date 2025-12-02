#!/bin/sh
# Lance cub3d sur toutes les cartes map/good, vérifie que le parseur accepte,
# et contrôle les fuites mémoire avec Valgrind.

set -u

BIN="./cub3D"
DIR="map/good"
PARSE_OK=0
PARSE_KO=0
LEAK_OK=0
LEAK_KO=0
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all"

if [ ! -x "$BIN" ]; then
	echo "Binaire introuvable : $BIN (lance 'make' avant)" >&2
	exit 1
fi
if ! command -v valgrind >/dev/null 2>&1; then
	echo "Valgrind introuvable (installe-le pour les tests de fuite)" >&2
	exit 1
fi

for f in "$DIR"/*.cub; do
	if [ ! -f "$f" ]; then
		continue
	fi
	name=$(basename "$f")
	printf "%-25s : " "$name"

	$BIN "$f" >/dev/null 2>&1
	if [ $? -eq 0 ]; then
		printf "OK (parse reussi)"
		PARSE_OK=$((PARSE_OK + 1))
	else
		printf "KO (parse en echec)"
		PARSE_KO=$((PARSE_KO + 1))
	fi

	log_file=$(mktemp)
	$VALGRIND --error-exitcode=42 --log-file="$log_file" $BIN "$f" >/dev/null 2>&1
	if grep -q "ERROR SUMMARY: 0 errors" "$log_file"; then
		printf " | leaks: OK"
		LEAK_OK=$((LEAK_OK + 1))
	else
		printf " | leaks: KO"
		LEAK_KO=$((LEAK_KO + 1))
	fi
	rm -f "$log_file"
	printf "\n"
done

echo "Bilan parse : $PARSE_OK OK / $PARSE_KO KO"
echo "Bilan leaks : $LEAK_OK OK / $LEAK_KO KO"

if [ $PARSE_KO -ne 0 ] || [ $LEAK_KO -ne 0 ]; then
	exit 1
fi

exit 0
