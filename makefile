

all: driver.o notification.o item.o aisle.o date.o bill.o map.o
	gcc driver.o notification.o item.o aisle.o date.o bill.o map.o -o out

driver.o: driver.c
	gcc -c driver.c

notification.o: notification.c
	gcc -c notification.c 
item.o: item.c
	gcc -c item.c

aisle.o: aisle.c 
	gcc -c aisle.c

date.o: date.c
	gcc -c date.c 

bill.o: bill.c
	gcc -c bill.c 

map.o: map.c
	gcc -c map.c

clean:
	rm -f  *.o
