0) Cadrage & interfaces (30–60 min)

Objectif : définir ce que le parsing produit et ce dont il a besoin.

Choisis les structures (conceptuellement) :

t_token : {type, lexeme, flags}

type ∈ {WORD, PIPE, REDIR_IN, REDIR_OUT, DREDIR_OUT, HEREDOC, END}

flags : quoted_single, quoted_double, no_expand, join_prev, etc.

t_redir : {kind ∈ {IN, OUT, APPEND, HEREDOC}, target, heredoc_no_expand}

t_cmd : {argv[], redirs[], next /*pipe*/}

Contrat de sortie du parser : une liste chaînée de t_cmd représentant un pipeline. Chaque t_cmd contient ses argv (sans quotes) et sa liste de redirections (dans l’ordre de lecture).

Dépendances d’entrée : accès en lecture à l’environnement (t_env clé→valeur) pour $VAR, $?, ~ et pour savoir si * doit s’étendre.

Prototypes (une ligne sur le rôle, pas de code) :

int precheck_syntax(const char *line, t_err *e); → balayage rapide : quotes fermées, fin par opérateur, etc.

t_vec *lex(const char *line, t_err *e); → transforme ligne → tokens bruts.

int expand_tokens(t_vec *toks, t_env *env, int last_status, t_err *e); → $, ~, removal des quotes, word-splitting, globbing.

t_cmd *parse_pipeline(const t_vec *toks, t_err *e); → tokens → structure de commandes (argv + redirs + pipes).

int build_heredocs(t_cmd *ast, t_env *env, t_err *e); → lit le contenu des << (en gérant expansion selon le délimiteur).

void free_tokens/ast(...); → libération sans fuite.

DONE : 1) Pré-vérifications (“precheck”) — 6 tests rapides

But : refuser tôt les entrées manifestement invalides.

Actions :

Trim début/fin ; détecter ligne vide.

Vérifier quotes non fermées (' et " compte pair).

Rejeter opérateurs orphelins : |, >, >>, <, << en fin de ligne ou suivis d’un autre opérateur non autorisé.

Rejeter pipes consécutifs (||) si votre minishell ne gère pas ||.

Rejeter séquences interdites (;;, >>>, <<<, >|).

Heredoc : tolérer << mais exiger un délimiteur non vide derrière.

Critères d’acceptation :

Chaque erreur renvoie un t_err {pos, msg} clair (style bash : syntax error near unexpected token '|').

2) Lexing (tokenisation robuste) — automate à 3 états

But : couper la ligne en unités significatives sans encore interpréter $.

États : NORMAL, IN_SQUOTE, IN_DQUOTE.

Règles :

En NORMAL :

Espace → sépare les mots (mais n’émet pas de token espace).

|, <, >, >>, << → émettre le token opérateur.

~ au début d’un mot → marquer un flag is_tilde_candidate.

\ (backslash) n’échappe que dans NORMAL (et parfois dans DQUOTE selon vos choix projet).

Caractère ordinaire → accumuler dans le buffer courant → token WORD.

En IN_SQUOTE : tout est littéral jusqu’au ' fermant (pas d’escape, pas d’expansion).

En IN_DQUOTE : \" et \\ peuvent être gérés ; $ sera expansible plus tard.

Flags utiles sur WORD :

had_squote, had_dquote (pour savoir si on devra empêcher le split/globbing ensuite).

no_expand pour délimiteurs de heredoc s’ils sont quotés (ex: << "EOF").

join_prev si des segments contigus doivent fusionner (ex : abc"$HOME"def).

Critères d’acceptation :

echo "a b" produit un seul WORD("a b", had_dquote=1).

cat<<'EOF' → tokens [WORD("cat"),HEREDOC,WORD("EOF", had_squote=1, no_expand=1)].

3) Fusion intra-mot (coalescing)

But : recoller les fragments contigus d’un même mot nés du mélange quotes/non-quotes.

Action : parcourir la liste et fusionner WORD adjacents où join_prev est vrai ou séparés uniquement par des transitions de quotes dans un même lexème.

Critère : ab"$HOME"cd → un seul WORD avec des sous-segments marqués (utile pour expansions conservant l’info de quoting partiel).

4) Expansions (dans cet ordre)

But : reproduire la sémantique bash minimale. Ordre recommandé :

Tilde (~) : si WORD débute par ~ non cité → remplacer par $HOME (ou ~user si vous le gérez).

Param expansion :

$? → last_status.

$VAR → valeur depuis t_env (chaîne vide si non définie).

Pas d’expansion dans segments issus de '...' ni dans délimiteur heredoc si no_expand.

Suppression de quotes : enlever les quotes structurelles qui ne doivent pas rester dans argv.

Word splitting (IFS = espace, tab, newline) :

Uniquement si le segment ayant produit ces espaces n’était pas entre quotes.

Produit potentiellement plusieurs WORD à partir d’un.

Globbing (*, ?, [...]) :

Uniquement si non cité.

Remplacer par la liste triée des correspondances du répertoire courant.

Si aucune correspondance : conserver le motif brut (comportement bash par défaut).

Critères d’acceptation :

echo $HOME/Desktop → deux argv si le $HOME introduit un / ? Non : ici un seul argv (/home/…/Desktop).

echo "$HOME Desktop" → un seul argument (pas de split).

echo $UNSET → argument vide supprimé ? (Bash supprime un champ vide né du split : reproduisez ce choix et documentez-le).

cat << 'EOF' puis contenu : aucune expansion dans le corps.

5) Parsing grammatical (tokens → commandes)

But : construire t_cmd (argv + redirs) et chaîner par pipes.

Grammaire simple :
pipeline := command { PIPE command }*
command := {redir}* WORD { (WORD | redir) }*

Règles :

Une commande doit contenir au moins un WORD (la commande) ou un builtin implicite (rare ; rester simple → exiger un WORD).

Redirections acceptées avant ou après les mots ; appliquer dans l’ordre de lecture.

Après REDIR_* / HEREDOC, exiger un WORD (la cible ou le délimiteur).

Critères d’acceptation :

cat < in | grep a >> out →

cmd1.argv = ["cat"], cmd1.redirs = [{IN,"in"}], next=cmd2

cmd2.argv = ["grep","a"], cmd2.redirs = [{APPEND,"out"}]

Erreur si > suivi de | ou de fin de ligne.

6) Heredocs (production du contenu)

But : collecter maintenant le contenu des << pour que l’exécution n’ait plus qu’à ouvrir un fichier/pipe prêt.

Pour chaque t_redir{HEREDOC, delim} :

Déterminer expand_body = !heredoc_no_expand.

Lire lignes tant que ≠ delim (comparaison brute sans trimming).

Si expand_body : appliquer param expansion et $? à chaque ligne ; pas de globbing ni split.

Stocker dans un fichier temporaire (ou un pipe) ; remplacer la redirection par une IN pointant ce fichier.

Ctrl-C pendant le heredoc doit annuler la commande courante (comportement attendu par 42).

Critères d’acceptation :

<< "EOF" → aucune expansion dans le corps.

Plusieurs heredocs dans la même commande → gérés séquentiellement.

7) Validation finale & normalisation

But : garantir que l’AST est exploitable par l’exécuteur.

Vérifier : chaque t_cmd a un argv[0] valide (ou au moins une redirection si vous supportez commandes vides comme > out), cibles de redir non vides, aucun token résiduel.

Normaliser : argv NULL-terminated, flags append bien posés, chemins relatifs conservés tels quels.

8) Gestion mémoire & erreurs

But : zéro fuite, messages clairs.

Décisions :

Soit arena/garbage (liste d’allocs à free d’un coup par ligne), soit freeing granulaire (tokens → ast → heredocs).

Centraliser les erreurs via t_err et ne jamais laisser l’AST partiellement construit sans le libérer.

Critères :

valgrind clean sur une batterie d’inputs (y compris erreurs).

9) Batterie de tests minimaux (à jouer à chaque étape)

Pré-lexing :

echo "a b", echo 'a b', echo a\ b, echo "", | ls, echo >, cat <<
Expansions :

echo $HOME, echo "$HOME", echo $UNSET, echo $?, echo "~" vs echo ~
Word splitting & quotes :

printf "%s\n" $PATH, printf "%s\n" "$PATH"
Globbing :

echo *, echo "*.c", echo a*b (selon fichiers présents)
Redirections :

cat < in > out, echo hi >> out
Pipes :

echo hi | cat | wc -c
Heredocs :

cat <<EOF (avec expansions) / cat <<'EOF' (sans)
Erreurs :

ls || wc, echo >>> a, cat < | wc, quotes non fermées.

Chaque test doit préciser ce que le parser renvoie (argv/redirs/pipes) ou l’erreur attendue.

10) Points d’attention (pièges fréquents)

Ordre des expansions (tilde → $ → remove quotes → split → glob).

Split post-expansion uniquement si non cité à l’origine.

Globbing ne s’applique jamais dans des segments cités.

Heredoc : délimiteur quoté → pas d’expansion du corps.

Espaces autour des opérateurs facultatifs (a<<EOF, cmd>out) → le lexer doit gérer.

Plusieurs redirections de même type → la dernière gagne (bash-like).

11) Handover propre à l’exécuteur (ton binôme)

Expose uniquement :

t_cmd *parse_line(const char *line, t_env *env, int last_status, t_err *e);

Retourne NULL si erreur (avec e rempli).

Si succès : AST prêtes heredocs matérialisés.

void free_cmd(t_cmd *);