rm -f out
rm -f data9

cd ../pflayer
make clean
make
cd ../finallayer
make clean
make EQ

i=300
while [[ $i -le 3000 ]]; do
	./a.out $i > out
	printf "$i" >> data9 && cat out | tail -n 2 | head -n 2 | cut -d " " -f 4  | \
	while read LINE; do
		printf "\t$LINE" >> data9
	done && printf "\n" >> data9

	let i=i+300
done
