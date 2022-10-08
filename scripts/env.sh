# Builds without MPI or LSB
alias raw_build='''sh -c "cd build/ && 
    cmake -DUSE_MPI=0 .. &&
    cmake --build ."'''

# Builds with MPI
alias build='''sh -c "cd build/ && 
    cmake -DUSE_MPI=1 .. &&
    cmake --build ."'''

# Builds with LibSciBench (and MPI)
alias bm_build='''sh -c "cd build/ && 
    cmake -DUSE_MPI=1 -DUSE_LSB=1 .. &&
    cmake --build ."'''

# Runs without MPI or LSB
alias raw_run='''raw_build && cd build/ && ./main && cd ..'''

# Runs with MPI
alias run='''build && cd build/ && ./main && cd ..'''

# Runs with LibSciBench (and MPI)
alias bm_run='''bm_build && cd build/ && ./main && cd ..'''

# Init script for the environment in EULER
alias euler_init="module load gcc/8.2.0 cmake openmpi boost"

alias clean="rm -rf build/*"
