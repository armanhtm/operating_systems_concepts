var1=$1
var2=$2
fileName=$3
n=1
while read line; do
if [ $var1 -lt $n ]&&[ $n -lt $var2 ]
then
echo "$line"
fi
if [ $var1 -eq $n ] || [ $n -eq $var2 ]
then
echo "$line"
fi
n=$((n+1))
done < $fileName

