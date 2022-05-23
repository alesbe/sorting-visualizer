#!/usr/bin/env bash
compile() {
	# Detect is SFML libraries are installed, if not, install them
	ldconfig -p | grep -q libsfml
	if [ $? -ne 0 ]; then
		install_sfml
	fi

	# Compile visualizer
	echo Compiling visualizer...
	g++ ./src/*.cpp -o sorting-visualizer -lsfml-graphics -lsfml-window -lsfml-system
}

install_sfml() {
	# Detect packet manager

	# Arch
	if command -v pacman &>/dev/null; then
		sudo pacman -S sfml
	
	# Debian
	elif command -v apt-get &>/dev/null; then
		sudo apt-get install libsfml-dev

	# Fedora
	elif command -v dnf &>/dev/null; then
		sudo dnf install SFML

	# Void linux (not tested)
	elif command -v xbps &>/dev/null; then
		# add multilib repo
		sudo xbps-install -Su void-repo-multilib
		# install sfml
		sudo xbps-install -Su SFML-32bit

	# Packet manager not found
	else
		# TODO: Implement issue #10 fix here
		echo "Could not install SFML using the system package manager."
		echo "Please install SFML yourself and run this script again."
		exit
	fi
}

main() {
	# Select option
	
	echo "Where do you want to install the visualizer?"
	echo "1.- Compile and leave the executable in this directory"
	echo "2.- Compile and move the executable into /usr/bin (requires root)"
	echo ""
	read -n 1 -p "Option: " option
	echo ""
	echo ""

	# 1: Compile
	if [ "$option" = "1" ]; then
		compile

		echo "Done!"
		exit

	# 2: Compile and move binary to /usr/bin
	elif [ "$option" = "2" ]; then

		compile

		# Move executable to /usr/bin
		echo Moving executable into /usr/bin...
		sudo mv ./sorting-visualizer /usr/bin
		echo Done!
		exit

	# -: Not a valid option
	else
		echo "Select a valid option!"
		exit

	fi
}

main
