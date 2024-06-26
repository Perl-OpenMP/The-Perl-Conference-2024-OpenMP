all: first-example basic-task basic2-task atomic-sum affinity simd task-fib

affinity:
	gcc -fopenmp ./affinity.c -o affinity.x

atomic-sum:
	gcc -fopenmp ./atomic-sum.c -o atomic-sum.x

basic-task:
	gcc -fopenmp ./basic-task.c -o basic-task.x

basic2-task:
	gcc -fopenmp ./basic2-task.c -o basic2-task.x

first-example:
	gcc -fopenmp ./first-example.c -o first-example.x

simd:
	gcc -fopenmp ./simd.c -o simd.x

task-fib:
	gcc -fopenmp ./task-fib.c -o task-fib.x

clean:
	rm -rf a.out *.x ./_Inline > /dev/null 2>&1
