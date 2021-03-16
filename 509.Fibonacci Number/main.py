def fib(n):
	if n < 0:
		return -1
	elif n == 0:
		return 0
	elif n == 1:
		return 1

	sum = 0
	prev = 0
	curr = 1
	for i in range(3, n):
		sum = prev + curr
		prev = curr
		curr = sum
		pass
	return sum

if __name__ == '__main__':
	num = 10
	print("fib(", num, ") = ", fib(num))