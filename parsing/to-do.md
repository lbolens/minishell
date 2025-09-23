📋 TO-DO LIST - Phase Parsing Minishell

🔧 PHASE 1: CORRECTIONS & AMÉLIORATIONS

 Corriger le bug trim() dans pre_check() (passer char** au lieu de char*)
 Modifier toutes les fonctions de validation pour utiliser le pointeur corrigé
 Ajouter une fonction is_inside_quotes() pour ignorer les opérateurs dans les quotes
 Mettre à jour check_pipes(), check_operators(), check_forbidden_sequences() avec cette fonction
 Créer un fichier de tests test_precheck.c avec tous les cas edge
 Tester et valider que tous les cas passent


🪙 PHASE 2: TOKENISATION

 Créer les enums et structures pour les tokens dans minishell.h
 Créer le fichier tokenizer.c
 Implémenter la fonction principale tokenize(char *input)
 Créer skip_whitespace() pour ignorer les espaces
 Créer is_operator() pour détecter |, <, >, <<, >>
 Implémenter add_operator_token() pour créer les tokens d'opérateurs
 Implémenter add_word_token() pour créer les tokens de mots
 Créer extract_word() qui gère les quotes simples et doubles
 Implémenter la gestion des quotes dans l'extraction
 Ajouter les fonctions de manipulation de liste chaînée pour tokens
 Créer des tests pour la tokenisation
 Déboguer et valider tous les cas


🌳 PHASE 3: PARSING SYNTAXIQUE

 Définir les structures t_redirect et t_command dans minishell.h
 Créer le fichier parser.c
 Implémenter parse_tokens() - fonction principale qui parse la liste de tokens
 Créer parse_single_command() qui parse une commande avant un pipe
 Implémenter add_argument() pour ajouter des arguments à une commande
 Créer is_redirection_token() pour identifier les tokens de redirection
 Implémenter add_redirection() pour gérer <, >, <<, >>
 Créer les fonctions utilitaires de manipulation des listes de commandes
 Implémenter la validation syntaxique pendant le parsing
 Gérer les erreurs de syntaxe (redirection sans fichier, etc.)
 Créer des tests pour le parser
 Déboguer et valider


🔄 PHASE 4: EXPANSION

 Créer le fichier expander.c
 Implémenter expand_variables() pour les variables d'environnement ($VAR)
 Gérer la variable spéciale $? (exit status)
 Implémenter l'expansion dans les doubles quotes (mais pas simples)
 Créer get_env_variable() pour récupérer les valeurs d'environnement
 Gérer les cas spéciaux: $, $$, variables inexistantes
 Implémenter l'expansion pour tous les arguments de toutes les commandes
 Créer des tests pour l'expansion
 Déboguer et valider