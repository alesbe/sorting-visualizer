#!/usr/bin/env bash
compile() {
	# Compile and clean using Makefile
	echo Compiling visualizer...
	make
}

main() {
	# Select option
	echo "Where do you want to install the visualizer?"
	echo "1.- Compile and leave the executable in this folder"
	echo "2.- Compile and move the executable into /usr/bin (requires root)"
	echo ""
	read -n 1 -p "Option: " option
	echo ""
	echo ""

	if [ "$option" = "1" ]; then
		compile
		exit

	elif [ "$option" = "2" ]; then
		# Check if has been runned as sudo
		if [ "$EUID" -ne 0 ]
			then echo "Please, run as root! (sudo ./install.sh)"
			exit
		fi

		compile

		# Move executable to /usr/bin
		echo Moving executable into /usr/bin...
		mv ./sorting-visualizer /usr/bin
		echo Done!
		exit
	fi
}

main
