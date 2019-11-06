my_nof_line=$(wc -l < my_output.txt)
gold_nof_line=$(wc -l < gold_output.txt)
#echo "$my_nof_line"
#echo "$gold_nof_line"

if [ ! -f my_output.txt ]; then
	echo "Wrong!"
elif [ ${my_nof_line} -ne ${gold_nof_line} ]; then
    echo "Wrong!"
elif grep -Fxvq -f my_output.txt gold_output.txt; then
    echo "Wrong!"
else
	echo "Correct!"
fi
