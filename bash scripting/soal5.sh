echo “Enter the size of array”
read no
i=0
echo “Enter the numbers”
for i in `seq 0 $[$no-1]`
do
read arr[i]
done
for i in `seq 0 $[$no-1]`
do
j=0
l=$[$no-$i-1]
while [ $l -gt $j ]
do
if [ $[arr[j]] -gt $[arr[$j+1]] ]
then
tmp=$[arr[$j]]
arr[$j]=$[arr[$j+1]]
arr[$j+1]=$tmp
fi
j=`expr $j + 1`
done
done
echo “The ordered array is……”
for i in `seq 0 $[$no-1]`
do
echo “$[arr[$i]]”
done

