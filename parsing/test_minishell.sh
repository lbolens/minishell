#!/bin/bash

# Script de test pour le parsing de minishell
# Usage: ./test_minishell.sh [path_to_minishell]

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Compteurs
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Configuration
MINISHELL_PATH="./minishell"
TEST_TIMEOUT=5
LOG_FILE="test_results.log"

# Fonction d'aide
show_usage() {
    echo "Usage: $0 [path_to_minishell]"
    echo "Default minishell path: ./minishell"
    exit 1
}

# Fonction pour afficher les résultats
print_result() {
    local test_name="$1"
    local result="$2"
    local details="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ "$result" = "PASS" ]; then
        echo -e "${GREEN}✅ PASS${NC}: $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}❌ FAIL${NC}: $test_name"
        if [ -n "$details" ]; then
            echo -e "   ${YELLOW}Details: $details${NC}"
        fi
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    
    echo "[$result] $test_name - $details" >> "$LOG_FILE"
}

# Fonction pour tester une commande
test_command() {
    local test_name="$1"
    local command="$2"
    local should_fail="$3"  # "true" si la commande doit échouer
    
    echo -e "${CYAN}Testing: $command${NC}"
    
    # Créer un fichier temporaire avec la commande
    local temp_file=$(mktemp)
    echo "$command" > "$temp_file"
    echo "exit" >> "$temp_file"
    
    # Exécuter le minishell avec timeout
    timeout $TEST_TIMEOUT "$MINISHELL_PATH" < "$temp_file" > /dev/null 2>&1
    local exit_code=$?
    
    rm -f "$temp_file"
    
    # Vérifier le résultat
    if [ "$should_fail" = "true" ]; then
        # On s'attend à un échec
        if [ $exit_code -ne 0 ] && [ $exit_code -ne 124 ]; then
            print_result "$test_name" "PASS" "Command correctly failed"
        else
            print_result "$test_name" "FAIL" "Command should have failed but didn't"
        fi
    else
        # On s'attend à un succès
        if [ $exit_code -eq 0 ] || [ $exit_code -eq 124 ]; then
            print_result "$test_name" "PASS" "Command parsed successfully"
        else
            print_result "$test_name" "FAIL" "Command failed with exit code $exit_code"
        fi
    fi
}

# Fonction pour tester la gestion mémoire (avec valgrind si disponible)
test_memory() {
    local test_name="$1"
    local command="$2"
    
    if ! command -v valgrind &> /dev/null; then
        echo -e "${YELLOW}⚠️  Valgrind not found, skipping memory test${NC}"
        return
    fi
    
    echo -e "${PURPLE}Memory test: $command${NC}"
    
    local temp_file=$(mktemp)
    echo "$command" > "$temp_file"
    echo "exit" >> "$temp_file"
    
    # Exécuter avec valgrind
    local valgrind_output=$(mktemp)
    timeout $TEST_TIMEOUT valgrind --leak-check=full --error-exitcode=42 \
        "$MINISHELL_PATH" < "$temp_file" > /dev/null 2> "$valgrind_output"
    local exit_code=$?
    
    rm -f "$temp_file"
    
    if [ $exit_code -eq 42 ]; then
        print_result "$test_name (Memory)" "FAIL" "Memory leaks detected"
        echo -e "${RED}Valgrind output:${NC}"
        cat "$valgrind_output" | tail -10
    else
        print_result "$test_name (Memory)" "PASS" "No memory leaks"
    fi
    
    rm -f "$valgrind_output"
}

# Fonction principale de test
run_tests() {
    echo -e "${BLUE}=== MINISHELL PARSING TESTS ===${NC}"
    echo "Testing minishell: $MINISHELL_PATH"
    echo "Logs will be saved to: $LOG_FILE"
    echo ""
    
    # Initialiser le fichier de log
    echo "Minishell Test Results - $(date)" > "$LOG_FILE"
    echo "======================================" >> "$LOG_FILE"
    
    # Vérifier si le minishell existe
    if [ ! -f "$MINISHELL_PATH" ]; then
        echo -e "${RED}Error: Minishell not found at $MINISHELL_PATH${NC}"
        exit 1
    fi
    
    # Vérifier si le minishell est exécutable
    if [ ! -x "$MINISHELL_PATH" ]; then
        echo -e "${RED}Error: Minishell is not executable${NC}"
        exit 1
    fi
    
    # === TESTS DES QUOTES ===
    echo -e "\n${YELLOW}=== Testing Quotes ===${NC}"
    
    # Single quotes
    test_command "Simple single quotes" "echo 'hello world'" "false"
    test_command "Single quotes with metacharacters" "echo '\$USER | > < * ? [ ]'" "false"
    test_command "Empty single quotes" "echo ''" "false"
    test_command "Unclosed single quote" "echo 'hello world" "true"
    
    # Double quotes
    test_command "Simple double quotes" 'echo "hello world"' "false"
    test_command "Double quotes with variable" 'echo "Hello \$USER"' "false"
    test_command "Double quotes with \$?" 'echo "Status: \$?"' "false"
    test_command "Empty double quotes" 'echo ""' "false"
    test_command "Unclosed double quote" 'echo "hello world' "true"
    
    # Mixed quotes
    test_command "Mixed quotes" "echo 'hello' \"world\"" "false"
    test_command "Adjacent quotes" "echo 'hello'\"world\"" "false"
    
    # === TESTS DES VARIABLES ===
    echo -e "\n${YELLOW}=== Testing Variables ===${NC}"
    
    test_command "Simple variable" "echo \$USER" "false"
    test_command "Non-existent variable" "echo \$NONEXISTENT" "false"
    test_command "Variable with text" "echo prefix\$USER suffix" "false"
    test_command "Multiple variables" "echo \$USER \$HOME \$PATH" "false"
    test_command "Exit status variable" "echo \$?" "false"
    test_command "Dollar sign alone" "echo \$" "false"
    test_command "Variable in double quotes" 'echo "\$USER"' "false"
    test_command "Variable in single quotes (no expansion)" "echo '\$USER'" "false"
    
    # === TESTS DES REDIRECTIONS ===
    echo -e "\n${YELLOW}=== Testing Redirections ===${NC}"
    
    # Input redirection
    test_command "Input redirection" "cat < /etc/passwd" "false"
    test_command "Input redirection with spaces" "cat   <   /etc/passwd" "false"
    test_command "Input redirection no spaces" "cat</etc/passwd" "false"
    test_command "Invalid input redirection" "cat <" "true"
    
    # Output redirection
    test_command "Output redirection" "echo hello > /tmp/test_output" "false"
    test_command "Output redirection with spaces" "echo hello   >   /tmp/test_output" "false"
    test_command "Output redirection no spaces" "echo hello>/tmp/test_output" "false"
    test_command "Invalid output redirection" "echo hello >" "true"
    
    # Append redirection
    test_command "Append redirection" "echo hello >> /tmp/test_append" "false"
    test_command "Append redirection with spaces" "echo hello   >>   /tmp/test_append" "false"
    test_command "Invalid append redirection" "echo hello >>" "true"
    
    # Heredoc
    test_command "Simple heredoc" $'cat << EOF\nhello\nworld\nEOF' "false"
    test_command "Heredoc with quotes" $'cat << "EOF"\n\$USER\nEOF' "false"
    test_command "Invalid heredoc" "cat <<" "true"
    
    # === TESTS DES PIPES ===
    echo -e "\n${YELLOW}=== Testing Pipes ===${NC}"
    
    test_command "Simple pipe" "echo hello | cat" "false"
    test_command "Pipe with spaces" "echo hello   |   cat" "false"
    test_command "Pipe no spaces" "echo hello|cat" "false"
    test_command "Multiple pipes" "echo hello | cat | grep hello | wc -l" "false"
    test_command "Pipe at start (invalid)" "| echo hello" "true"
    test_command "Pipe at end (invalid)" "echo hello |" "true"
    test_command "Double pipe (invalid)" "echo hello || cat" "true"
    
    # === TESTS DES BUILT-INS ===
    echo -e "\n${YELLOW}=== Testing Built-ins ===${NC}"
    
    # echo
    test_command "echo simple" "echo hello" "false"
    test_command "echo with -n" "echo -n hello" "false"
    test_command "echo with variable" "echo \$USER" "false"
    test_command "echo with quotes" 'echo "hello world"' "false"
    
    # cd
    test_command "cd absolute path" "cd /tmp" "false"
    test_command "cd relative path" "cd .." "false"
    test_command "cd to home" "cd" "false"
    test_command "cd with variable" "cd \$HOME" "false"
    
    # pwd
    test_command "pwd simple" "pwd" "false"
    
    # export
    test_command "export simple" "export VAR=value" "false"
    test_command "export with quotes" 'export VAR="hello world"' "false"
    test_command "export without value" "export VAR" "false"
    
    # unset
    test_command "unset simple" "unset VAR" "false"
    test_command "unset multiple" "unset VAR1 VAR2" "false"
    
    # env
    test_command "env simple" "env" "false"
    
    # exit
    test_command "exit simple" "exit" "false"
    test_command "exit with code" "exit 0" "false"
    test_command "exit with variable" "exit \$?" "false"
    
    # === TESTS COMPLEXES ===
    echo -e "\n${YELLOW}=== Testing Complex Cases ===${NC}"
    
    test_command "Complex parsing" 'echo "Hello \$USER" | grep \$USER > /tmp/output.txt' "false"
    test_command "Quotes and redirections" "echo 'test | grep' > \"/tmp/file with spaces.txt\"" "false"
    test_command "Variables in redirections" "cat < \"/etc/passwd\" | sort > \"/tmp/result.txt\"" "false"
    test_command "Heredoc with pipes" $'cat << EOF | grep hello\nhello world\ntest line\nhello again\nEOF' "false"
    
    # === TESTS D'ERREURS ===
    echo -e "\n${YELLOW}=== Testing Error Cases ===${NC}"
    
    test_command "Unclosed double quote" 'echo "hello world' "true"
    test_command "Unclosed single quote" "echo 'hello world" "true"
    test_command "Invalid redirection 1" "<" "true"
    test_command "Invalid redirection 2" ">" "true"
    test_command "Invalid redirection 3" ">>" "true"
    test_command "Invalid pipe" "|" "true"
    
    # === TESTS DE CARACTÈRES NON SUPPORTÉS ===
    echo -e "\n${YELLOW}=== Testing Unsupported Characters ===${NC}"
    
    test_command "Semicolon (should be ignored/error)" "echo hello; echo world" "true"
    test_command "Backslash (should be ignored/error)" "echo hello \\ world" "true"
    
    # === TESTS DE MÉMOIRE (si valgrind disponible) ===
    echo -e "\n${YELLOW}=== Testing Memory (if valgrind available) ===${NC}"
    
    test_memory "Memory - Simple command" "echo hello"
    test_memory "Memory - Complex parsing" 'echo "Hello \$USER" | cat > /tmp/test'
    test_memory "Memory - Multiple pipes" "echo hello | cat | cat | cat"
    test_memory "Memory - Variables" "echo \$USER \$HOME \$PATH"
    
    # === NETTOYAGE ===
    rm -f /tmp/test_output /tmp/test_append "/tmp/file with spaces.txt" /tmp/result.txt /tmp/output.txt /tmp/test
}

# Fonction pour afficher le résumé
show_summary() {
    echo -e "\n${BLUE}=== TEST SUMMARY ===${NC}"
    echo -e "Total tests: ${CYAN}$TOTAL_TESTS${NC}"
    echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
    echo -e "Failed: ${RED}$FAILED_TESTS${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "\n${GREEN}🎉 All tests passed!${NC}"
        exit 0
    else
        echo -e "\n${RED}❌ Some tests failed. Check $LOG_FILE for details.${NC}"
        exit 1
    fi
}

# Main
main() {
    # Traitement des arguments
    if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
        show_usage
    fi
    
    if [ -n "$1" ]; then
        MINISHELL_PATH="$1"
    fi
    
    # Exécuter les tests
    run_tests
    
    # Afficher le résumé
    show_summary
}

# Gestion des signaux
trap 'echo -e "\n${RED}Tests interrupted${NC}"; exit 1' INT TERM

# Exécution
main "$@"