# minishell
Replicating the Bash terminal

Readline surpression file and valgrind testing

`valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=readline_supression --track-fds=yes ./$(NAME)`

```
-q -> Coloca em quiet mode, só aparece o valgrind quando detecta leaks
--leak-check=full -> Checa todos os leaks
--show-leak-kinds=all -> Leaks e variaveis não iniciadas
--suppressions=readline_supression -> Lê o arquivo supression e ignora errors da livraria readline
```
