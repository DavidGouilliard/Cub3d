# Call Tree Template

Utilise ce gabarit pour générer un arbre d’appels ASCII (style organigramme) cohérent avec la documentation.

## Règles
- Chaque fonction est une boîte ASCII (`┌─┐ └─┘`) alignée horizontalement avec ses sœurs.
- Aucune branche partagée : si une fonction est appelée par plusieurs parents, duplique sa boîte.
- Les connecteurs utilisent `|`, `┌─┴─┐`, `└──┬──┘`, etc. Privilégie la symétrie.
- Le diagramme est encapsulé dans un bloc de code Markdown pour conserver l’alignement.

## Exemple de structure
```
                 ┌────────────┐
                 │ root_func  │
                 └─────┬──────┘
                       │
        ┌──────────────┴──────────────┐
        │                             │
 ┌────────────┐               ┌────────────┐
 │ child_one  │               │ child_two  │
 └─────┬──────┘               └─────┬──────┘
       │                            │
 ┌─────┴─────┐                ┌─────┴─────┐
 │ leaf_a    │                │ leaf_b    │
 └───────────┘                └───────────┘
```
