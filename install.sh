#!/usr/bin/env bash
main() {
	# Build Makefile
	echo "Building Makefile..."
	mkdir -p build
	pushd build
	cmake ..
	
	# Compile using Makefile
	echo ""
	echo "Compiling project..."
	popd
	cmake --build build

	# Select binary location
	echo ""
	echo "Would you like to move the visualizer to /usr/bin? (Requires root)"
	read -n 1 -p "yes (default) / no: " option
	echo ""
	echo ""

	# Option 1: Leave the binary in the same folder (project root)
	if [ "$option" = "n" ]; then
		mv build/sorting-visualizer .
		echo "Done! Run ./sorting-visualizer"
		exit
	fi
	
	# Option 2: Move the binary to /usr/bin
	sudo mv build/sorting-visualizer /usr/bin
	echo "Done! Run sorting-visualizer"
	
	exit
}

main
