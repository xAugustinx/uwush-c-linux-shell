#!/bin/sh

gcc main.c -o uwush
cp uwush /bin/
mv uwush /usr/bin/

echo -e Done!
