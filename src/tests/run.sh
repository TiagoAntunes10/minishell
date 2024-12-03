set -x
#!/bin/bash/

valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=readline_supression --track-fds=yes ./testshell
