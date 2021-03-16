def fib(n) -> int:
	if n < 0:
		return -1
	elif n == 0:
		return 0
	elif n == 1:
		return 1
	sum = 0
	prev = 0
	curr = 1
	for i in range(2, n+1):
		sum = prev + curr
		print(sum)
		prev = curr
		curr = sum
	return sum

if __name__ == '__main__':
	num = 2
	print("fib(", num, ") = ", fib(num))