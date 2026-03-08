#/bin/sh

if [ ! -d "/home/$USER/.config/uwush" ]; then
	mkdir /home/$USER/.config/uwush
fi

File=/home/$USER/.config/uwush/config.txt

if [[ -f "$File" && "$#" -eq 0 ]]; then
	echo
else
	touch $File
	echo "bar=uwuSH>" > $File
	echo "color=pink" >> $File
	echo "textColor=yellow" >> $File
	echo "textColorNotUser=blue" >> $File
	echo "printf=echo fortnite" >> $File
	echo "binarySpace=/moje/" >> $File
	echo -e "new config file\n"
fi


