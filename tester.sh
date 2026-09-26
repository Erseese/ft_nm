#!/bin/sh

if [ $# -lt 1 ]; then
  echo "Erreur : il manque un argument."
  exit 1
fi
for element in "$@"; do
/home/ersees/Documents/ft_nm/ft_nm $element > /home/ersees/Documents/ft_nm/testfile/ftnmresponse && /usr/bin/nm $element > /home/ersees/Documents/ft_nm/testfile/nmresponse && diff /home/ersees/Documents/ft_nm/testfile/ftnmresponse /home/ersees/Documents/ft_nm/testfile/nmresponse

done