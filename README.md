# ObsidianTimer

Это счётчик времени в ваших задачах. В программе используется технология TUI(terminal user interface).

## Инструкция по установке
```zsh
git clone https://github.com/saniqP/ObsidianTimer.git
cd ObsidianTimer
chmod +x main.sh
./main.sh
```

ваши задачи находятся в ```~/.taskrc.jsonc```(p.s их можно там добовлять)

для автоматизации запуска добавте в .zsh(bash)rc:

```zsh
alias obsiTime="~/.config/obsidianTime/main"
```
