# class_db
# Mini base de données en C – Projet class_db

## Informations

**Nom** : Kone 
**Prénom** : Oumar
**Classe** : 3e année Bachelor Cybersécurité – ESGI

## Objectif

Ce projet a pour but d’implémenter une mini base de données relationnelle en langage C. 


## Arborescence 
── class_db
│   ├── data
│   │   └── test_db.dat
│   ├── db
│   ├── LICENSE
│   ├── Makefile
│   ├── README.md
│   ├── src
│   │   ├── btree.c
│   │   ├── database.c
│   │   ├── database.h
│   │   ├── main.c
│   │   ├── main_table_backup.c
│   │   ├── repl.c
│   │   └── test_database
│   ├── tests
│   │   ├── test_db.c
│   │   ├── test_tree_assert.c
│   │   └── test_tree.c
│   ├── test_tree
│   └── test_tree_assert


## Compilation

```bash
make        # compile le projet
make test   # compile et lance les tests
make clean  # supprime les fichiers compilés
