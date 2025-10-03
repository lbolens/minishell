TO-DO LIST : Implémentation des Heredocs
📋 PHASE 1 : Modifications des fichiers existants
Dans parsing.h
Tâche 1.1 : Ajouter les prototypes des nouvelles fonctions

process_heredoc()
expand_heredoc_line()
setup_heredoc_signals()
handle_heredoc_sigint()

Tâche 1.2 : Modifier le prototype de setup_redirections()

Ajouter le paramètre t_env *env car on aura besoin de l'environnement pour l'expansion


Dans utils_redir.c
Tâche 1.3 : Modifier setup_redirections()

Objectif : Détecter si cmd->heredoc_delim existe
Action : Si oui, appeler process_heredoc() au lieu de open_in()
Priorité : Le heredoc remplace complètement input_file s'il existe
Gestion d'erreur : Si process_heredoc() retourne -1, return 0


Dans tous les fichiers appelant setup_redirections()
Tâche 1.4 : Ajouter le paramètre env aux appels

Fichiers concernés : pipes.c (fonction spawn) et single_exec.c (fonctions run_builtin_parent et run_external_child)
Objectif : Passer l'environnement pour permettre l'expansion dans les heredocs


📋 PHASE 2 : Création du fichier heredoc.c
Fonction principale : process_heredoc()
Tâche 2.1 : Créer la fonction

Paramètres : t_cmd *cmd, t_env *env
Retour : Un file descriptor (int) ou -1 en cas d'erreur
Objectif : Orchestrer toute la logique du heredoc

Tâche 2.2 : Créer un pipe

Objectif : Créer un canal de communication pipe[0] = lecture, pipe[1] = écriture
Gestion d'erreur : Si pipe() échoue, retourner -1

Tâche 2.3 : Configurer les signaux spécifiques au heredoc

Objectif : Appeler setup_heredoc_signals() pour gérer Ctrl+C proprement

Tâche 2.4 : Boucle de lecture

Objectif : Lire ligne par ligne avec readline("> ") jusqu'à trouver le délimiteur
Trois cas à gérer :

Ligne NULL (Ctrl+D) : Afficher warning et break
Ligne == délimiteur exact : free(line) et break
Autre ligne : traiter et continuer



Tâche 2.5 : Traiter chaque ligne lue

Objectif : Appliquer l'expansion si nécessaire
Condition : Si !cmd->heredoc_single_quotes, appeler expand_heredoc_line()
Action : Écrire la ligne (expandée ou non) dans pipe[1] + "\n"
Mémoire : Free les variables temporaires

Tâche 2.6 : Finalisation

Objectif : Fermer pipe[1] (côté écriture)
Objectif : Restaurer les signaux normaux avec setup_signals_command()
Retour : Retourner pipe[0] (côté lecture)


Fonction : expand_heredoc_line()
Tâche 2.7 : Créer la fonction

Paramètres : char *line, t_env *env
Retour : Une nouvelle chaîne allouée avec les variables expandées
Objectif : Remplacer tous les $VAR par leur valeur

Tâche 2.8 : Logique d'expansion

Réutiliser : Ta fonction existante build_full_command() ou adapter sa logique
Spécificités :

$? doit être remplacé par exit_status
$$ peut être remplacé par le PID (optionnel selon le sujet)
$VAR inexistante devient une chaîne vide


Gestion mémoire : Allouer une nouvelle chaîne, ne pas modifier l'originale


Fonction : setup_heredoc_signals()
Tâche 2.9 : Créer la fonction

Objectif : Configurer les gestionnaires de signaux spécifiques au heredoc
Actions :

SIGINT (Ctrl+C) → handle_heredoc_sigint
SIGQUIT (Ctrl+) → SIG_IGN (ignorer)




Fonction : handle_heredoc_sigint()
Tâche 2.10 : Créer le gestionnaire de signal

Paramètre : int sig
Objectif : Gérer Ctrl+C pendant la lecture du heredoc
Actions :

Afficher un retour à la ligne (write(STDOUT_FILENO, "\n", 1))
Sortir avec le code 130 (128 + SIGINT = 2)
Important : Utiliser exit() et non return car on est dans un signal handler




📋 PHASE 3 : Tests et débogage
Tâche 3.1 : Tester heredoc simple
