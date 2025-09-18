#!/bin/bash
touch ~/.taskrc.jsonc

mkdir ~/.config/obsidianTime

cp -r * ~/.config/obsidianTime

cat > ~/.taskrc.jsonc <<EOF\n
{
    "0": {
        "endTime": "13:30",
        "startTime": "8:00",
        "text": "пойти в школу"
    },
    "1": {
        "endTime": "06:00",
        "startTime": "18:59",
        "text": "сделать дз"
    }
}


