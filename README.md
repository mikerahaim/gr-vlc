# gr-vlc
GNURadio OOT block for visible light communication (i.e., LiFi)

To install, follow the steps below:

1-) cd to the gr-vlc directory
2-) Create a build directory with 'mkdir build'
3-) Run cmake with the path to your local gnuradio installation (assuming installed via PyBOMBS):
	'cmake -DCMAKE_INSTALL_PREFIX=<path-to-target> ../'
4-) Run 'make'
5-) Test the build with 'make test' (shouldn't be any failures)
6-) Install with 'make install'
7-) Configure your linker/debugger with 'sudo ldconfig'
8-) Open gnuradio-companion and you should find a module for VLC. You can test the grc flowgraph(s) in ./examples to check functionality.
