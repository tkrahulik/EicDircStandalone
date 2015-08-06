
--------------------------------------------------------------------------------
Geant4 Compatibility
--------------------------------------------------------------------------------

Developed for Geant4.9.6


--------------------------------------------------------------------------------
Installation
--------------------------------------------------------------------------------

Getting the code from GitHub

git clone https://github.com/tkrahulik/EicDircStandalone.git


--------------------------------------------------------------------------------
Installation
-------------------------------------------------------------------------------- 

(replace /path/to/workdir with directory containing EicDircStandalone source directory)

mkdir /path/to/workdir/EicDircStandalone-build
mkdir /path/to/workdir/EicDircStandalone-install

cd /path/to/workdir/EicDircStandalone-build

cmake -DCMAKE_INSTALL_PREFIX=/path/to/workdir/EicDircStandalone-install /path/to/workdir/EicDircStandalone

make -jN (N = number of processor cores available)

make install -jN (optional- you can run it from the build directory)


--------------------------------------------------------------------------------
Running
-------------------------------------------------------------------------------- 

./dirc

