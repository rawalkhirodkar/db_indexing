#!/bin/bash

rm -f out
rm -f data1 data2 # contain data regarding insertion deletion BTree
rm -f data3 data4 # contain data regarding insertion deletion List
rm -f data5 data6 # contain data regarding range queries Btree
rm -f data7 data8 # contain data regarding range queries List
rm -f data9

cd ../pflayer
make clean
make
cd ../finallayer
make clean
make Btree

i=300
while [[ $i -le 3000 ]]; do
	./a.out $i > out
	printf "$i" >> data1 && cat out | tail -n 4 | head -n 2 | cut -d " " -f 4  | \
	while read LINE; do
		printf "\t$LINE" >> data1
	done && printf "\n" >> data1

	printf "$i" >> data2 && cat out | tail -n 2 | head -n 2 | cut -d " " -f 4  | \
	while read LINE; do
		printf "\t$LINE" >> data2
	done && printf "\n" >> data2

	let i=i+300
done

cd ../pflayer
make clean
make
cd ../finallayer
make clean
make List

i=300
while [[ $i -le 3000 ]]; do
	./a.out $i > out
	printf "$i" >> data3 && cat out | tail -n 4 | head -n 2 | cut -d " " -f 4  | \
	while read LINE; do
		printf "\t$LINE" >> data3
	done && printf "\n" >> data3

	printf "$i" >> data4 && cat out | tail -n 2 | head -n 2 | cut -d " " -f 4  | \
	while read LINE; do
		printf "\t$LINE" >> data4
	done && printf "\n" >> data4

	let i=i+300
done

cd ../pflayer
make clean
make
cd ../finallayer
make clean
make Query

i=150
while [[ $i -lt 1500 ]]; do
	./a.out $i > out
	printf "$i" >> data5 && cat out | tail -n 8 | head -n 4 | cut -d " " -f 4  | \
	while read LINE; do
		printf "\t$LINE" >> data5
	done && printf "\n" >> data5

	printf "$i" >> data6 && cat out | tail -n 4 | head -n 4 | cut -d " " -f 5  | \
	while read LINE; do
		printf "\t$LINE" >> data6
	done && printf "\n" >> data6

	let i=i+150
done

cd ../pflayer
make clean
make
cd ../finallayer
make clean
make QueryList

i=150
while [[ $i -lt 1500 ]]; do
	./a.out $i > out
	printf "$i" >> data7 && cat out | tail -n 8 | head -n 4 | cut -d " " -f 4  | \
	while read LINE; do
		printf "\t$LINE" >> data7
	done && printf "\n" >> data7

	printf "$i" >> data8 && cat out | tail -n 4 | head -n 4 | cut -d " " -f 5  | \
	while read LINE; do
		printf "\t$LINE" >> data8
	done && printf "\n" >> data8

	let i=i+150
done

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
