# Developer setup

## Linux

1. Install GCC
```zsh
sudo apt update
sudo apt install build-essential
sudo apt install gdb
sudo apt install valgrind
sudo apt install clang-format
gcc --version
```

2. Create a **private** repository for your group using this template ([clicking "use this template"](https://github.com/miquelvir/dsa-2026)). The name should be `dsa-2026-{labnumber}-{groupnumber}` (e.g. `dsa-2026-101-03`). The `groupnumber` is the one you chose in Aula Global.

3. [Share it](https://docs.github.com/en/enterprise-cloud@latest/repositories/managing-your-repositorys-settings-and-features/repository-access-and-collaboration/inviting-collaborators-to-a-personal-repository) with the rest of team members and [professors](https://github.com/miquelvir/dsa-2026/blob/main/docs/TEACHER_LIST.md).
  
4. Then, [clone it using VSCode](https://code.visualstudio.com/docs/sourcecontrol/intro-to-git#_clone-a-repository-locally)
   
5. Run `make r` and make sure you see this message: `Welcome to DSA!`

## MacOS

1. [Install homebrew](https://brew.sh/)

2. [Install GCC](https://formulae.brew.sh/formula/gcc#default)

3. [Install GDB](https://formulae.brew.sh/formula/gdb#default)

4. [Install make](https://formulae.brew.sh/formula/make#default)

5. [Install clang-format](https://formulae.brew.sh/formula/clang-format#default)

6. Create a **private** repository for your group using this template ([clicking "use this template"](https://github.com/miquelvir/dsa-2026)). The name should be `dsa-2026-{labnumber}-{groupnumber}` (e.g. `dsa-2026-101-03`). The `groupnumber` is the one you chose in Aula Global.

7. [Share it](https://docs.github.com/en/enterprise-cloud@latest/repositories/managing-your-repositorys-settings-and-features/repository-access-and-collaboration/inviting-collaborators-to-a-personal-repository) with the rest of team members and [professors](https://github.com/miquelvir/dsa-2026/blob/main/docs/TEACHER_LIST.md).

8. [Clone the repository using VSCode](https://code.visualstudio.com/docs/sourcecontrol/intro-to-git#_clone-a-repository-locally)
   
9. Run `make r` and make sure you see this message: `Welcome to DSA!`

## Windows

1. [Install WSL with Ubuntu](https://documentation.ubuntu.com/wsl/en/latest/guides/install-ubuntu-wsl2/) (Linux subsystem inside Windows)

2. Follow the instructions for [Linux](#linux) in a WSL terminal
