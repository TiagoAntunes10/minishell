#!/bin/bash/
set -x

test_file="inputs.txt"

while IFS= read -r command; do
    echo "Executing command: $command"
    echo "$command" | valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline_leaks ./minishell
done < "$test_file"
