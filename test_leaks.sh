#!/bin/bash

# Script de test pour détecter les leaks dans minishell
# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "=========================================="
echo "   TESTS DE LEAKS MÉMOIRE - MINISHELL"
echo "=========================================="
echo ""

# Fonction pour tester une commande
test_command() {
    local cmd="$1"
    local description="$2"
    
    echo -e "${YELLOW}TEST:${NC} $description"
    echo -e "${YELLOW}CMD:${NC}  $cmd"
    
    # Créer un fichier temporaire avec la commande
    echo "$cmd" > /tmp/minishell_test_input.txt
    echo "exit" >> /tmp/minishell_test_input.txt
    
    # Exécuter avec valgrind
    valgrind --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --track-fds=yes \
             --suppressions=readline.supp \
             --log-file=/tmp/valgrind_output.txt \
             ./minishell < /tmp/minishell_test_input.txt > /dev/null 2>&1
    
    # Analyser le résultat
    if grep -q "All heap blocks were freed -- no leaks are possible" /tmp/valgrind_output.txt; then
        echo -e "${GREEN}✓ PASSED - Aucun leak détecté${NC}"
    elif grep -q "definitely lost: 0 bytes in 0 blocks" /tmp/valgrind_output.txt && \
         grep -q "indirectly lost: 0 bytes in 0 blocks" /tmp/valgrind_output.txt; then
        echo -e "${GREEN}✓ PASSED - Leaks négligeables (readline)${NC}"
    else
        echo -e "${RED}✗ FAILED - Leaks détectés!${NC}"
        echo "--- Détails des leaks ---"
        grep -A 5 "definitely lost\|indirectly lost" /tmp/valgrind_output.txt | grep -v "0 bytes"
    fi
    echo ""
    
    # Nettoyer
    rm -f /tmp/minishell_test_input.txt
}

# Créer le fichier de suppression readline si nécessaire
cat > readline.supp << 'EOF'
{
   readline_leak
   Memcheck:Leak
   ...
   fun:readline
}
{
   add_history_leak
   Memcheck:Leak
   ...
   fun:add_history
}
EOF

echo "=========================================="
echo "  CATÉGORIE 1 : PATH RESOLUTION"
echo "=========================================="
echo ""

test_command "ls" \
    "Commande simple dans PATH"

test_command "/bin/ls" \
    "Chemin absolu"

test_command "./non_existent_file" \
    "Fichier inexistant (test error handling)"

test_command "/bin/ls /tmp" \
    "Commande avec argument"

echo "=========================================="
echo "  CATÉGORIE 2 : EXPANSION DE VARIABLES"
echo "=========================================="
echo ""

test_command "echo \$PATH" \
    "Expansion variable simple"

test_command "echo \$USER \$HOME" \
    "Expansion multiples variables"

test_command "echo \$?" \
    "Expansion exit code"

test_command "echo \${HOME}" \
    "Expansion avec accolades"

test_command "echo \$NONEXISTENT" \
    "Variable inexistante"

echo "=========================================="
echo "  CATÉGORIE 3 : REDIRECTIONS"
echo "=========================================="
echo ""

test_command "echo test > /tmp/test_minishell.txt" \
    "Redirection sortie simple"

test_command "cat < /etc/passwd" \
    "Redirection entrée"

test_command "echo test >> /tmp/test_minishell.txt" \
    "Redirection append"

test_command "cat < /tmp/test_minishell.txt > /tmp/test2.txt" \
    "Redirections multiples"

test_command "< /etc/passwd cat" \
    "Redirection avant la commande"

echo "=========================================="
echo "  CATÉGORIE 4 : HEREDOC (CRITIQUE!)"
echo "=========================================="
echo ""

# Pour les heredocs, on doit créer un script spécial
cat > /tmp/heredoc_test.sh << 'TESTEOF'
#!/bin/bash
echo "cat << EOF
ligne1
ligne2
EOF
exit" | valgrind --leak-check=full \
                 --show-leak-kinds=all \
                 --track-fds=yes \
                 --log-file=/tmp/valgrind_heredoc.txt \
                 ./minishell 2>&1 > /dev/null

if grep -q "All heap blocks were freed\|definitely lost: 0 bytes" /tmp/valgrind_heredoc.txt; then
    echo -e "${GREEN}✓ HEREDOC SIMPLE - PASSED${NC}"
else
    echo -e "${RED}✗ HEREDOC SIMPLE - FAILED${NC}"
    grep "definitely lost\|indirectly lost" /tmp/valgrind_heredoc.txt
fi
TESTEOF

chmod +x /tmp/heredoc_test.sh
/tmp/heredoc_test.sh
echo ""

echo "=========================================="
echo "  CATÉGORIE 5 : PIPES"
echo "=========================================="
echo ""

test_command "ls | grep minishell" \
    "Pipeline simple"

test_command "echo test | cat | cat" \
    "Pipeline triple"

test_command "ls -la | grep \".c\" | wc -l" \
    "Pipeline avec arguments"

echo "=========================================="
echo "  CATÉGORIE 6 : BUILTINS"
echo "=========================================="
echo ""

test_command "export TEST=value" \
    "Export simple"

test_command "export TEST=value1 TEST2=value2" \
    "Export multiple"

test_command "export INVALID-VAR=test" \
    "Export invalide"

test_command "unset PATH" \
    "Unset variable"

test_command "cd /tmp" \
    "CD simple"

test_command "pwd" \
    "PWD"

test_command "env" \
    "ENV"

test_command "echo -n test" \
    "Echo avec option"

echo "=========================================="
echo "  CATÉGORIE 7 : QUOTES"
echo "=========================================="
echo ""

test_command "echo 'single quotes'" \
    "Single quotes"

test_command "echo \"double quotes\"" \
    "Double quotes"

test_command "echo 'test\$PATH'" \
    "Variable dans single quotes (pas d'expansion)"

test_command "echo \"test\$PATH\"" \
    "Variable dans double quotes (avec expansion)"

echo "=========================================="
echo "  CATÉGORIE 8 : EDGE CASES CRITIQUES"
echo "=========================================="
echo ""

test_command "" \
    "Commande vide"

test_command "   " \
    "Espaces uniquement"

test_command "echo '' '' ''" \
    "Arguments vides multiples"

test_command "echo \$EMPTY_VAR" \
    "Variable vide après expansion"

test_command "| echo test" \
    "Pipe au début (syntax error)"

test_command "echo test |" \
    "Pipe à la fin (syntax error)"

test_command "echo test > > file" \
    "Double redirection (syntax error)"

echo "=========================================="
echo "  RÉSUMÉ ET ANALYSE APPROFONDIE"
echo "=========================================="
echo ""

# Nettoyer les fichiers de test
rm -f /tmp/test_minishell.txt /tmp/test2.txt /tmp/heredoc_test.sh
rm -f readline.supp

echo "Tests terminés!"
echo ""
echo "Pour une analyse détaillée d'un test spécifique, lance:"
echo "  echo 'ta_commande' | valgrind --leak-check=full --show-leak-kinds=all ./minishell"
