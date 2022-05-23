#!/usr/bin/env bash
main() {
	echo "Building Makefile..."
	cmake CMakeLists.txt
	
	echo ""
	echo "Compiling project..."
	make

	echo ""
	echo "Would you like to move the visualizer to /usr/bin? (Requires root)"
	read -n 1 -p "yes / no: " option
	echo ""
	echo ""

	if [ "$option" = "y" ]; then
		sudo mv ./sorting-visualizer /usr/bin
	fi

	echo "Done!"
	exit
}

main