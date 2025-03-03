
current_dir=$(pwd)
echo $current_dir

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$current_dir
echo $LD_LIBRARY_PATH
./test.run