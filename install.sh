#!/usr/bin/env bash
main() {
	# Build Makefile
	echo "Building Makefile..."
	cmake CMakeLists.txt
	
	# Compile using Makefile
	echo ""
	echo "Compiling project..."
	make

	# Select binary location
	echo ""
	echo "Would you like to move the visualizer to /usr/bin? (Requires root)"
	read -n 1 -p "yes (default) / no: " option
	echo ""
	echo ""

	# Option 1: Leave the binary in the same folder (project root)
	if [ "$option" = "n" ]; then
		echo "Done! Run ./sorting-visualizer"
		exit
	fi
	
	# Option 2: Move the binary to /usr/bin
	sudo mv ./sorting-visualizer /usr/bin
	echo "Done! Run sorting-visualizer"
	
	exit
}

main
