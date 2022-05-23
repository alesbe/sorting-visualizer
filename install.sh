#!/usr/bin/env bash
compile() {
	# determine if sfml is already installed,
	# if its not then install it
	ldconfig -p | grep -q libsfml
	if [ $? -ne 0 ]; then
		install_sfml
	fi

	# Compile; Makefile is not used for now because
	# it is not working as intended
	echo Compiling visualizer...
	g++ ./src/*.cpp -o sorting-visualizer -lsfml-graphics -lsfml-window -lsfml-system
}

install_sfml() {
	# detect the package manager and install sfml
	# accordingly

	# we need to be root to install packages
	if [ "$EUID" -ne 0 ]; then
		echo "The SFML library needs to be installed to compile the program."
		echo "This script can attempt to install SFML using the system package manager if run as root."
		echo "Please run it again as root (sudo ./install.sh) or install SFML yourself."
		exit
	fi

	if command -v pacman &>/dev/null; then
		pacman -S sfml
	elif command -v apt-get &>/dev/null; then
		apt-get install libsfml-dev
	elif command -v dnf &>/dev/null; then
		dnf install SFML
	else
		# package manager was not found
		# maybe compile sfml ourselves?
		echo "Could not install SFML using the system package manager."
		echo "Please install SFML yourself and run this script again."
		exit
	fi
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

		echo "Done!"
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
