#!/bin/bash
echo 'Iniciando comprobacion...'
clang-format --dry-run -Werror **/*.c **/*.h