*Quick note that this readme definitely needs a rewrite and improvements but it is here for now*
# Esp-setup
Template for esp-idf with cmake for esp-32 s3
### Build Instructions

First, install dependencies with
`bash ./install_dependencies.sh`

Load esp32-IDF into your terminal with
`. $HOME/esp/esp-idf/export.sh`

Then build with
`idf.py build`



### Clangd setup
*If you are on feature-heavy IDEs such as Vscode or Eclipse, this may not apply*

Make sure the clangd that is currently active is esp-clang, which should be installed in the `~/.espressif/tools/esp-clang/<version>/esp-clang/bin/` directory. The binary is also downloadable from [the Espressif GitHub](https://github.com/espressif/llvm-project/releases)

In the top level directory of the project, also run:
`idf.py -B build -D IDF_TOOLCHAIN=~/.espressif/tools/esp-clang/<version>/esp-clang/bin/clangd reconfigure`
