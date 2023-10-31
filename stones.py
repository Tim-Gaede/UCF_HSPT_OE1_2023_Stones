# stones.py by Juan Moscoso

from heapq import heapify, heappop, heappush

def transform(minpq):
	final_list = []
	# lets transform the list into a min priority queue
	heapify(minpq)
	while len(minpq) >= 2:
		val1 = heappop(minpq)
		val2 = heappop(minpq)

		# if the values are the same
		# it is equivalent to that value + 1
		if val1 == val2: 	
			heappush(minpq, val1 + 1)
		else:
			# if they are different, we know the smaller of them is in our final list
			heappush(minpq, val2)
			final_list.append(val1)
	# append the final element in the minpq
	final_list.append(minpq[0])
	# since we are using a minpq, values will be in ascending order
	return final_list

days = int(input())
for _ in range(days):
	n = int(input())
	a = list(map(int, input().split()))
	m = int(input())
	b = list(map(int, input().split()))

	# we want to transform our value lists so that the values are unique
	# then we can compare the biggest pile that differs between Alice and Bob
	# and that will be the person with the most stones
	final_a = transform(a)
	final_b = transform(b)

	# compare piles from biggest to smallest
	found_winner = False
	while len(final_a) > 0 and len(final_b) > 0:
		val_a = final_a.pop()
		val_b = final_b.pop()
		# Alice has the bigger stone
		if val_a > val_b:
			print("Alice will have more fun!")
			found_winner = True
			break
		# Bob has the bigger stone
		elif val_b > val_a:
			print("Bob will have more fun!")
			found_winner = True
			break
		# if the values are the same we continue

	# if we broke out of our while loop without finding a winner
	# there are three cases
	# 1. Alice has stones remaining and Bob doesn't and Alice is the winner
	# 2. Bob has stones remaining and Alice doesn't and Bob is the winner
	# 3. Alice and Bob both don't have stones remaining and it is a tie
	if not found_winner:
		if final_a:
			print("Alice will have more fun!")
		elif final_b:
			print("Bob will have more fun!")
		else: 
			print("Tie!")
	


	

	
	
