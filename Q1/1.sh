echo "Enter a number: "
read n
temp=$n
while [ $temp -gt 0 ]
do
	rem=$((temp%10))
	rev=$((rev*10+rem))
	temp=$((temp/10))
done
if [ $rev -eq $n ]
then
	echo "It is a palindrom"
else
	echo "It is not a palindrom"
fi

