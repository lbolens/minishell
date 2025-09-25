Minishell - Todolist Exécution

🚰 Phase 3: Pipes et Redirections
Pipes

    Création des pipes
        int create_pipes(t_cmd *cmd_list, int ***pipes)
        Calculer le nombre de pipes nécessaires
        Allouer et créer tous les pipes
    Setup des pipes pour chaque commande
        Première commande : stdout → pipe[0][1]
        Commandes intermédiaires : stdin ← pipe[i-1][0], stdout → pipe[i][1]
        Dernière commande : stdin ← pipe[n-1][0]

Redirections

    Redirection d'entrée (<)
        Ouvrir le fichier en lecture
        dup2() vers stdin
        Gérer les erreurs (fichier inexistant, permissions)
    Redirection de sortie (>)
        Ouvrir/créer le fichier en écriture (troncature)
        dup2() vers stdout
        Gérer les erreurs de permissions
    Redirection append (>>)
        Ouvrir/créer le fichier en mode append
        dup2() vers stdout
    Here-document (<<)
        Lire l'entrée jusqu'au délimiteur
        Créer un pipe temporaire
        Écrire le contenu dans le pipe
        Rediriger vers stdin

⚙️ Phase 4: Exécution des Commandes
Exécution simple (sans pipes)

    Commande built-in
        Exécuter directement dans le processus parent
        Gérer les redirections temporaires
    Commande externe
        fork() pour créer un processus enfant
        Dans l'enfant : execve() avec la commande
        Dans le parent : wait() pour récupérer le code de sortie

Exécution avec pipes

    Pipeline complet
        Créer tous les processus enfants
        Setup des pipes pour chaque processus
        Fermer tous les descripteurs inutiles
        Attendre tous les processus enfants
        Récupérer le code de sortie de la dernière commande

Utilitaires d'exécution

    Recherche de commandes
        char *find_command_path(char *cmd, char **envp)
        Chercher dans PATH
        Gérer les chemins absolus/relatifs
    Gestion des signaux
        SIGINT (Ctrl+C) → interruption propre
        SIGQUIT (Ctrl+) → core dump
        Restaurer les signaux par défaut dans les enfants

🧹 Phase 5: Nettoyage et Gestion d'Erreurs
Gestion mémoire

    Libération des structures
        void free_cmd_list(t_cmd *cmd_list)
        void free_pipes(int **pipes, int count)
        Libération de l'environnement

Gestion d'erreurs

    Codes d'erreur appropriés
        0 : succès
        1 : erreur générale
        126 : commande trouvée mais non exécutable
        127 : commande non trouvée
        128+n : terminé par signal n
    Messages d'erreur
        Format bash-compatible
        Redirection vers stderr

Restauration de l'environnement

    Descripteurs de fichiers
        Restaurer stdin/stdout après redirections
        Fermer tous les pipes et fichiers ouverts
    Variables d'environnement
        Sauvegarder/restaurer PWD, OLDPWD
        Mettre à jour le code de sortie

🔄 Phase 6: Intégration et Tests
Tests unitaires

    Chaque built-in individuellement
    Redirections simples
    Pipes simples (2 commandes)
    Combinaisons complexes

Tests d'intégration

    Interface avec le parsing
        Vérifier la conversion tokens → commandes
        Tester avec différents types de tokens
    Tests de stress
        Pipelines longs
        Redirections multiples
        Commandes inexistantes

📋 Fonctions Utilitaires Recommandées
c

// Exécution principale
int execute_command_line(t_token *tokens, t_exec *exec_env);

// Conversion parsing → exécution
t_cmd *tokens_to_commands(t_token *tokens);

// Built-ins
bool is_builtin(char *cmd);
int execute_builtin(char **args, t_exec *exec_env);

// Pipes et redirections
int setup_pipes(t_cmd *cmd_list);
int setup_redirections(t_cmd *cmd);

// Utilitaires
char *find_command_path(char *cmd, char **envp);
void cleanup_execution(t_cmd *cmd_list, int **pipes);

🎯 Priorités

    Commandes simples sans pipes (phase 1-2-4 partielles)
    Built-ins de base (echo, pwd, env)
    Redirections simples (< et >)
    Pipes simples (2 commandes)
    Built-ins avancés (cd, export, unset)
    Fonctionnalités avancées (>>, <<, pipes multiples)

Bon courage pour l'implémentation ! N'hésite pas si tu as des questions sur des points spécifiques.
