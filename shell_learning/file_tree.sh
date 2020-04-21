#!/bin/bash
OUTPUT=$2
if [ -e $OUTPUT ];then
	rm $OUTPUT
fi
touch $OUTPUT


cd $1
ABS=$(pwd)
cd -

cd `dirname $ABS`
REL=${ABS#*"$(pwd)/"}
cd -

OLD_IFS=$IFS
IFS=$'\n'
OLD_LANG=$LANG
LANG=en_US.UTF-8

queue=("$REL" "$ABS")
count=1
Dir_count=0
File_count=0
i=0

while [ $count != 0 ]
do
	rel_file="${queue[$i]}"
	let i=i+1;
	abs_file="${queue[$i]}"
	let i=i+1;
	echo "[$rel_file]" >> ${OUTPUT}
	let count=count-1;
	for file in `ls $abs_file`
	do 
		echo "$abs_file/$file" >> ${OUTPUT};
		if [ -d "$abs_file/$file" ];then
			queue=(${queue[@]} "$file")
			queue=(${queue[@]} "$abs_file/$file")
			let count=count+1;
			let Dir_count=Dir_count+1;
		else
			let File_count=File_count+1;
		fi
	done
	echo "" >> ${OUTPUT};
done
echo "[Directories Count]:$Dir_count" >> ${OUTPUT}
echo "[Files Count]:$File_count" >> ${OUTPUT}

IFS=$OLD_IFS
LANG=$LANG
