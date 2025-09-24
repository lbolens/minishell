📋 TO-DO LIST - Phase Parsing Minishell

DONE 🔧 PHASE 1: CORRECTIONS & AMÉLIORATIONS

 Corriger le bug trim() dans pre_check() (passer char** au lieu de char*)
 Modifier toutes les fonctions de validation pour utiliser le pointeur corrigé
 Ajouter une fonction is_inside_quotes() pour ignorer les opérateurs dans les quotes
 Mettre à jour check_pipes(), check_operators(), check_forbidden_sequences() avec cette fonction
 Créer un fichier de tests test_precheck.c avec tous les cas edge
 Tester et valider que tous les cas passent


DONE 🪙 PHASE 2: TOKENISATION

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


DONE PHASE 3: PARSING SYNTAXIQUE - Plan détaillé
But de cette phase
Objectif principal : Transformer votre liste de tokens en une structure de commandes exécutable.

Transformation : 

INPUT: [TOKEN_WORD:"cat"] → [TOKEN_REDIRECT_IN:"<"] → [TOKEN_WORD:"file.txt"] → [TOKEN_PIPE:"|"] → [TOKEN_WORD:"grep"] → [TOKEN_WORD:"hello"] → [TOKEN_EOF]

OUTPUT: t_cmd {
  args: ["cat", NULL]
  input_file: "file.txt"
  next: t_cmd {
    args: ["grep", "hello", NULL]
    next: NULL
  }
}

Étapes détaillées à implémenter
Étape 1: Ajouter la structure dans minishell.h

Ajouter votre typedef struct s_cmd
Ajouter les prototypes des fonctions du parser
Cette structure est plus simple que mon approche initiale, ce qui est bien

Étape 2: Créer parser.c avec la fonction principale
Fonction parse_tokens():

Prendre en entrée la liste de tokens de votre tokenizer
Parcourir cette liste et identifier les "groupes" de commandes séparés par des pipes
Créer une t_cmd pour chaque groupe
Retourner le premier élément de la liste chaînée de commandes

Logique générale :

Boucler sur les tokens jusqu'à trouver TOKEN_PIPE ou TOKEN_EOF
Pour chaque groupe, créer une t_cmd
Chaîner les t_cmd avec le pointeur next

Étape 3: Implémenter parse_single_command()
But : Parser une seule commande (entre deux pipes ou jusqu'à la fin)
Responsabilités :

Identifier les mots qui sont des arguments
Identifier les redirections et leurs fichiers
Remplir tous les champs de votre t_cmd
Gérer les erreurs (redirection sans fichier, etc.)

Défis spécifiques avec votre structure :

Vous ne pouvez avoir qu'UNE seule redirection d'entrée et UNE seule de sortie par commande
Si vous trouvez < file1 < file2, il faut décider quoi faire (erreur ? dernier gagne ?)
Il faut différencier > (append_mode = false) et >> (append_mode = true)

Étape 4: Créer is_redirection_token()
Simple fonction utilitaire :

Vérifier si un token est TOKEN_REDIRECT_IN, TOKEN_REDIRECT_OUT, TOKEN_REDIRECT_APPEND, ou TOKEN_REDIRECT_HEREDOC
Retourner true/false

Étape 5: Implémenter la gestion des redirections
Fonction handle_redirection():

Selon le type de redirection, remplir le bon champ de votre t_cmd
< → input_file
> → output_file + append_mode = false
>> → output_file + append_mode = true
<< → heredoc_delim

Gérer les cas d'erreur :

Redirection sans fichier : cat > |
Redirection à la fin : cat >

Étape 6: Implémenter add_argument()
But : Ajouter un mot au tableau char **args
Défis :

Vous devez dynamiquement agrandir le tableau args
Garder le track de combien d'arguments vous avez
Le dernier élément doit être NULL (comme pour execve)

Logique :

Compter les arguments actuels
Réallouer args avec +1 espace
Ajouter le nouvel argument
Mettre NULL à la fin

Étape 7: Validation syntaxique
Erreurs à détecter pendant le parsing :

Pipe sans commande après : cat |
Redirection sans fichier : cat <
Double redirection du même type : cat < file1 < file2
Commande vide : | grep hello

Étape 8: Gestion mémoire
Créer les fonctions utilitaires :

init_cmd() : Initialiser une t_cmd avec des valeurs NULL
free_cmd_list() : Libérer toute la liste chaînée
add_cmd_to_list() : Ajouter une t_cmd à la fin de la liste


PHASE 4: EXPANSION - Explication détaillée
But de cette phase
Objectif : Transformer les variables d'environnement en leurs valeurs réelles dans vos commandes déjà parsées.
Transformation :
